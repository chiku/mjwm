/*
  This file is part of mjwm.
  Copyright (C) 2014  Chirantan Mitra <chirantan.mitra@gmail.com>

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#define CATCH_CONFIG_MAIN

#include "desktop_file.h"

#include <vector>
#include <string>

#include "catch.hpp"

namespace amm {

SCENARIO("DesktopFile.Populate()", "[desktopfile]") {
  GIVEN("A desktop-file") {
    DesktopFile entry;

    WHEN("populated") {
      entry.Populate("Name=Mousepad\n");
      entry.Populate("Icon=accessories-text-editor\n");
      entry.Populate("Exec=mousepad %F\n");
      entry.Populate("Categories=Application;Utility;TextEditor;GTK;\n");

      THEN("it has a name") {
        REQUIRE(entry.Name() == "Mousepad");
      }

      THEN("it has an icon") {
        REQUIRE(entry.Icon() == "accessories-text-editor");
      }

      THEN("it has an executable") {
        REQUIRE(entry.Executable() == "mousepad %F");
      }

      THEN("it has categories") {
        std::vector<std::string> categories = entry.Categories();
        REQUIRE(categories.size() == 4);
        REQUIRE(categories[0] == "Application");
        REQUIRE(categories[1] == "GTK");
        REQUIRE(categories[2] == "TextEditor");
        REQUIRE(categories[3] == "Utility");
      }

      THEN("it knows that it will displayed by default") {
        REQUIRE(entry.Display());
      }

      WHEN("NoDisplay is set to true") {
        entry.Populate("NoDisplay=true");
        THEN("it is not marked as displayed") {
          REQUIRE(!entry.Display());
        }
      }

      WHEN("NoDisplay is set to 1") {
        entry.Populate("NoDisplay=1");
        THEN("it is not marked as displayed") {
          REQUIRE(!entry.Display());
        }
      }
    }

    WHEN("populated with missing entry") {
      DesktopFile missing_entry;
      entry.Populate("Categories=");
      entry.Populate("Executable=");
      THEN("entries are empty") {
        std::vector<std::string> categories = entry.Categories();
        REQUIRE(categories.size() == 0);
        REQUIRE(entry.Executable() == "");
      }
    }

    WHEN("populated with entry line") {
      DesktopFile entry;
      entry.Populate("");
      THEN("entries are empty") {
        REQUIRE(entry.Categories().size() == 0);
        REQUIRE(entry.Executable() == "");
      }
    }
  }
}


SCENARIO("DesktopFile comparisons", "[desktopfile]") {
  GIVEN("A desktop-file") {
    DesktopFile entry;
    entry.Populate("Name=Mousepad");

    WHEN("compared to another desktop-file") {
      DesktopFile other_entry;

      WHEN("the other desktop-file has an alphabetically greater name") {
        other_entry.Populate("Name=VLC");

        DesktopFile greater_entry;
        THEN("the desktop file is lesser than the other desktop file") {
          REQUIRE(entry < other_entry);
          REQUIRE(!(other_entry < entry));
        }
      }

      WHEN("the other desktop-file has an alphabetically lesser name") {
        other_entry.Populate("Name=GParted");

        THEN("the desktop file is greater than the other desktop file") {
          REQUIRE(entry > other_entry);
          REQUIRE(!(other_entry > entry));
        }
      }

      WHEN("the other desktop-file has same name") {
        other_entry.Populate("Name=Mousepad");

        THEN("the desktop file is equal to the other desktop file") {
          REQUIRE(entry == other_entry);
          REQUIRE(!(other_entry != entry));
        }
      }

      WHEN("the other desktop-file has a different name") {
        other_entry.Populate("Name=VLC");

        THEN("the desktop file is not equal to the other desktop file") {
          REQUIRE(entry != other_entry);
          REQUIRE(!(other_entry == entry));
        }
      }
    }
  }
}


SCENARIO("DesktopFile validity", "[desktopfile]") {
  GIVEN("A desktop-file") {
    WHEN("it has a name, an icon and an executable") {
      DesktopFile entry;
      entry.Populate("Name=Mousepad");
      entry.Populate("Icon=accessories-text-editor\n");
      entry.Populate("Exec=mousepad %F\n");
      THEN("it is valid") {
        REQUIRE(entry.IsValid());
      }
    }

    WHEN("it has a no name") {
      DesktopFile entry;
      entry.Populate("Icon=accessories-text-editor\n");
      entry.Populate("Exec=mousepad %F\n");
      THEN("it is not valid") {
        REQUIRE(!entry.IsValid());
      }
    }

    WHEN("it has no icon") {
      DesktopFile entry;
      entry.Populate("Name=Mousepad");
      entry.Populate("Exec=mousepad %F\n");
      THEN("it is not valid") {
        REQUIRE(!entry.IsValid());
      }
    }

    WHEN("it has no executable") {
      DesktopFile entry;
      entry.Populate("Name=Mousepad");
      entry.Populate("Icon=accessories-text-editor\n");
      THEN("it is not valid") {
        REQUIRE(!entry.IsValid());
      }
    }
  }
}

SCENARIO("DesktopFile classifications", "[desktopfile]") {
  GIVEN("A desktop-file") {
    DesktopFile entry;

    WHEN("it has one of the categories as AudioVideo") {
      entry.Populate("Categories=AudioVideo;Audio;Player;GTK;\n");
      THEN("it is an AudioVideo") {
        REQUIRE(entry.IsA("AudioVideo"));
      }
    }

    WHEN("it has none of the categories as AudioVideo") {
      entry.Populate("Categories=Audio;Video;Player;GTK;\n");
      THEN("it is not as AudioVideo") {
        REQUIRE(!entry.IsA("AudioVideo"));
      }
    }

    WHEN("it has one of the categories as AudioVideo") {
      entry.Populate("Categories=AudioVideo;Audio;Player;GTK;\n");
      THEN("it is any of AudioVideo and Multimedia") {
        std::vector<std::string> classifications;
        classifications.push_back("AudioVideo");
        classifications.push_back("Multimedia");
        REQUIRE(entry.IsAnyOf(classifications));
      }
    }

    WHEN("it has none of the categories as AudioVideo") {
      entry.Populate("Categories=Audio;Video;Player;GTK;\n");
      THEN("it is not any of AudioVideo and Multimedia") {
        std::vector<std::string> classifications;
        classifications.push_back("AudioVideo");
        classifications.push_back("Multimedia");
        REQUIRE(!entry.IsAnyOf(classifications));
      }
    }
  }
}

} // namespace amm
