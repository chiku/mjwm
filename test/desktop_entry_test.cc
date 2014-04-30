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

#include "desktop_entry.h"

#include <vector>
#include <string>

#include "catch.hpp"

namespace amm {

SCENARIO("DesktopEntry.Populate()", "[desktopfile]") {
  GIVEN("A desktop-file") {
    DesktopEntry entry;

    WHEN("populated") {
      std::vector<std::string> lines;
      lines.push_back("[Desktop Entry]\n");
      lines.push_back("Name=Mousepad\n");
      lines.push_back("Icon=accessories-text-editor\n");
      lines.push_back("Exec=mousepad %F\n");
      lines.push_back("Categories=Application;Utility;TextEditor;GTK;\n");
      DesktopEntry entry(lines);

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
        std::vector<std::string> lines;
        lines.push_back("[Desktop Entry]\n");
        lines.push_back("NoDisplay=true\n");
        DesktopEntry entry(lines);
        THEN("it is not marked as displayed") {
          REQUIRE(!entry.Display());
        }
      }

      WHEN("NoDisplay is set to 1") {
        std::vector<std::string> lines;
        lines.push_back("[Desktop Entry]\n");
        lines.push_back("NoDisplay=1\n");
        DesktopEntry entry(lines);
        THEN("it is not marked as displayed") {
          REQUIRE(!entry.Display());
        }
      }
    }
  }
}


SCENARIO("DesktopEntry comparisons", "[desktopfile]") {
  GIVEN("A desktop-file") {
    std::vector<std::string> lines;
    lines.push_back("[Desktop Entry]\n");
    lines.push_back("Name=Mousepad");
    lines.push_back("Exec=mousepad");
    DesktopEntry entry(lines);

    WHEN("compared to another desktop-file") {
      WHEN("the other desktop-file has an alphabetically greater name") {
        std::vector<std::string> other_lines;
        other_lines.push_back("[Desktop Entry]\n");
        other_lines.push_back("Name=VLC");
        DesktopEntry other_entry(other_lines);

        THEN("the desktop file is lesser than the other desktop file") {
          REQUIRE(entry < other_entry);
          REQUIRE(!(other_entry < entry));
        }
      }

      WHEN("the other desktop-file has an alphabetically lesser name") {
        std::vector<std::string> other_lines;
        other_lines.push_back("[Desktop Entry]\n");
        other_lines.push_back("Name=GParted");
        DesktopEntry other_entry(other_lines);

        THEN("the desktop file is greater than the other desktop file") {
          REQUIRE(entry > other_entry);
          REQUIRE(!(other_entry > entry));
        }
      }

      WHEN("the other desktop-file has same name and executable") {
        std::vector<std::string> other_lines;
        other_lines.push_back("[Desktop Entry]\n");
        other_lines.push_back("Name=Mousepad");
        other_lines.push_back("Exec=mousepad");
        DesktopEntry other_entry(other_lines);

        THEN("the desktop file is equal to the other desktop file") {
          REQUIRE(entry == other_entry);
          REQUIRE(!(other_entry != entry));
        }
      }

      WHEN("the other desktop-file has a different name") {
        std::vector<std::string> other_lines;
        other_lines.push_back("[Desktop Entry]\n");
        other_lines.push_back("Name=VLC Server");
        other_lines.push_back("Exec=vlc");
        DesktopEntry other_entry(other_lines);

        THEN("the desktop file is not equal to the other desktop file") {
          REQUIRE(entry != other_entry);
          REQUIRE(!(other_entry == entry));
        }
      }

      WHEN("the other desktop-file has a different executable") {
        std::vector<std::string> other_lines;
        other_lines.push_back("[Desktop Entry]\n");
        other_lines.push_back("Name=VLC");
        other_lines.push_back("Exec=svlc");
        DesktopEntry other_entry(other_lines);

        THEN("the desktop file is not equal to the other desktop file") {
          REQUIRE(entry != other_entry);
          REQUIRE(!(other_entry == entry));
        }
      }
    }
  }
}


SCENARIO("DesktopEntry validity", "[desktopfile]") {
  GIVEN("A desktop-file") {
    WHEN("it has a name, an icon and an executable") {
      std::vector<std::string> lines;
      lines.push_back("[Desktop Entry]\n");
      lines.push_back("Name=Mousepad\n");
      lines.push_back("Icon=accessories-text-editor\n");
      lines.push_back("Exec=mousepad %F\n");
      DesktopEntry entry(lines);

      THEN("it is valid") {
        REQUIRE(entry.IsValid());
      }
    }

    WHEN("it has a no name") {
      std::vector<std::string> lines;
      lines.push_back("[Desktop Entry]\n");
      lines.push_back("Icon=accessories-text-editor\n");
      lines.push_back("Exec=mousepad %F\n");
      DesktopEntry entry(lines);
      THEN("it is not valid") {
        REQUIRE(!entry.IsValid());
      }
    }

    WHEN("it has no icon") {
      std::vector<std::string> lines;
      lines.push_back("[Desktop Entry]\n");
      lines.push_back("Name=Mousepad\n");
      lines.push_back("Exec=mousepad %F\n");
      DesktopEntry entry(lines);
      THEN("it is not valid") {
        REQUIRE(!entry.IsValid());
      }
    }

    WHEN("it has no executable") {
      std::vector<std::string> lines;
      lines.push_back("[Desktop Entry]\n");
      lines.push_back("Name=Mousepad\n");
      lines.push_back("Icon=accessories-text-editor\n");
      DesktopEntry entry(lines);
      THEN("it is not valid") {
        REQUIRE(!entry.IsValid());
      }
    }
  }
}

SCENARIO("DesktopEntry classifications", "[desktopfile]") {
  GIVEN("A desktop-file") {
    WHEN("it has one of the categories as AudioVideo") {
      std::vector<std::string> lines;
      lines.push_back("[Desktop Entry]\n");
      lines.push_back("Categories=AudioVideo;Audio;Player;GTK;\n");
      DesktopEntry entry(lines);
      THEN("it is an AudioVideo") {
        REQUIRE(entry.IsA("AudioVideo"));
      }
    }

    WHEN("it has none of the categories as AudioVideo") {
      std::vector<std::string> lines;
      lines.push_back("[Desktop Entry]\n");
      lines.push_back("Categories=Audio;Video;Player;GTK;\n");
      DesktopEntry entry(lines);
      THEN("it is not as AudioVideo") {
        REQUIRE(!entry.IsA("AudioVideo"));
      }
    }

    WHEN("it has one of the categories as AudioVideo") {
      std::vector<std::string> lines;
      lines.push_back("[Desktop Entry]\n");
      lines.push_back("Categories=AudioVideo;Audio;Player;GTK;\n");
      DesktopEntry entry(lines);
      THEN("it is any of AudioVideo and Multimedia") {
        std::vector<std::string> classifications;
        classifications.push_back("AudioVideo");
        classifications.push_back("Multimedia");
        REQUIRE(entry.IsAnyOf(classifications));
      }
    }

    WHEN("it has none of the categories as AudioVideo") {
      std::vector<std::string> lines;
      lines.push_back("[Desktop Entry]\n");
      lines.push_back("Categories=Audio;Video;Player;GTK;\n");
      DesktopEntry entry(lines);
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
