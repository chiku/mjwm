/*
  This file is part of mjwm.
  Copyright (C) 2014-2016  Chirantan Mitra <chirantan.mitra@gmail.com>

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

#include "xdg/desktop_entry.h"

#include <vector>
#include <string>

#include "../doctest.h"

namespace amm {
namespace xdg {

SCENARIO("Populate DesktopEntry") {
    GIVEN("A desktop-file") {
        DesktopEntry entry;

        WHEN("created") {
            std::vector<std::string> lines;
            lines.push_back("[Desktop Entry]\n");
            lines.push_back("Name=Mousepad\n");
            lines.push_back("Icon=accessories-text-editor\n");
            lines.push_back("Exec=mousepad %F\n");
            lines.push_back("Categories=Application;Utility;TextEditor;GTK;\n");
            lines.push_back("Comment=Simple Text Editor\n");
            entry.parse(lines);

            THEN("it has a name") {
                CHECK(entry.name() == "Mousepad");
            }

            THEN("it has an icon") {
                CHECK(entry.icon() == "accessories-text-editor");
            }

            THEN("it has an executable") {
                CHECK(entry.executable() == "mousepad %F");
            }

            THEN("it has categories") {
                std::vector<std::string> categories = entry.categories();
                REQUIRE(categories.size() == 4);
                CHECK(categories[0] == "Application");
                CHECK(categories[1] == "GTK");
                CHECK(categories[2] == "TextEditor");
                CHECK(categories[3] == "Utility");
            }

            THEN("it has a comment") {
                CHECK(entry.comment() == "Simple Text Editor");
            }

            THEN("it knows if it would be displayed by default") {
                CHECK(entry.display());
            }

            WHEN("NoDisplay is set to true") {
                std::vector<std::string> lines;
                lines.push_back("[Desktop Entry]\n");
                lines.push_back("NoDisplay=true\n");
                entry.parse(lines);
                THEN("it is not marked as displayed") {
                    CHECK_FALSE(entry.display());
                }
            }

            WHEN("NoDisplay is set to 1") {
                std::vector<std::string> lines;
                lines.push_back("[Desktop Entry]\n");
                lines.push_back("NoDisplay=1\n");
                entry.parse(lines);
                THEN("it is not marked as displayed") {
                    CHECK_FALSE(entry.display());
                }
            }
        }
    }
}

SCENARIO("Language-aware DesktopEntry") {
    GIVEN("A desktop-file") {
        DesktopEntry entry;
        entry.hasLanguage("sr");

        WHEN("created") {
            std::vector<std::string> lines;
            lines.push_back("[Desktop Entry]\n");
            lines.push_back("Name=Mousepad\n");
            lines.push_back("Name[sr]=Мишоловка\n");
            lines.push_back("Icon=accessories-text-editor\n");
            lines.push_back("Exec=mousepad %F\n");
            lines.push_back("Categories=Application;Utility;TextEditor;GTK;\n");
            lines.push_back("Comment=Simple Text Editor\n");
            lines.push_back("Comment[sr]=Једноставан уређивач текста\n");
            entry.parse(lines);

            THEN("it picks the name with matching language") {
                CHECK(entry.name() == "Мишоловка");
            }

            THEN("it picks comment with the matching language") {
                CHECK(entry.comment() == "Једноставан уређивач текста");
            }
        }
    }
}


SCENARIO("DesktopEntry comparisons") {
    DesktopEntry entry;
    DesktopEntry other_entry;

    GIVEN("A desktop-file") {
        std::vector<std::string> lines;
        lines.push_back("[Desktop Entry]\n");
        lines.push_back("Name=Mousepad");
        lines.push_back("Exec=mousepad");
        entry.parse(lines);

        WHEN("compared to another desktop-file") {
            WHEN("the other desktop-file has an alphabetically greater name") {
                std::vector<std::string> other_lines;
                other_lines.push_back("[Desktop Entry]\n");
                other_lines.push_back("Name=VLC");
                other_entry.parse(other_lines);

                THEN("the desktop file is lesser than the other desktop file") {
                    CHECK(entry < other_entry);
                    CHECK_FALSE(other_entry < entry);
                }
            }

            WHEN("the other desktop-file has an alphabetically lesser name") {
                std::vector<std::string> other_lines;
                other_lines.push_back("[Desktop Entry]\n");
                other_lines.push_back("Name=GParted");
                other_entry.parse(other_lines);

                THEN("the desktop file is greater than the other desktop file") {
                    CHECK(entry > other_entry);
                    CHECK_FALSE(other_entry > entry);
                }
            }

            WHEN("the other desktop-file has same name and executable") {
                std::vector<std::string> other_lines;
                other_lines.push_back("[Desktop Entry]\n");
                other_lines.push_back("Name=Mousepad");
                other_lines.push_back("Exec=mousepad");
                other_entry.parse(other_lines);

                THEN("the desktop file is equal to the other desktop file") {
                    CHECK(entry == other_entry);
                    CHECK_FALSE(other_entry != entry);
                }
            }

            WHEN("the other desktop-file has a different name") {
                std::vector<std::string> other_lines;
                other_lines.push_back("[Desktop Entry]\n");
                other_lines.push_back("Name=VLC Server");
                other_lines.push_back("Exec=vlc");
                other_entry.parse(other_lines);

                THEN("the desktop file is not equal to the other desktop file") {
                    CHECK(entry != other_entry);
                    CHECK_FALSE(other_entry == entry);
                }
            }

            WHEN("the other desktop-file has a different executable") {
                std::vector<std::string> other_lines;
                other_lines.push_back("[Desktop Entry]\n");
                other_lines.push_back("Name=VLC");
                other_lines.push_back("Exec=svlc");
                other_entry.parse(other_lines);

                THEN("the desktop file is not equal to the other desktop file") {
                    CHECK(entry != other_entry);
                    CHECK_FALSE(other_entry == entry);
                }
            }
        }
    }
}


SCENARIO("DesktopEntry validity") {
    DesktopEntry entry;

    GIVEN("A desktop-file") {
        WHEN("it has a name, an icon and an executable") {
            std::vector<std::string> lines;
            lines.push_back("[Desktop Entry]\n");
            lines.push_back("Name=Mousepad\n");
            lines.push_back("Icon=accessories-text-editor\n");
            lines.push_back("Exec=mousepad %F\n");
            entry.parse(lines);
            THEN("it is valid") {
                CHECK(entry.isValid());
            }
        }

        WHEN("it has a no name") {
            std::vector<std::string> lines;
            lines.push_back("[Desktop Entry]\n");
            lines.push_back("Icon=accessories-text-editor\n");
            lines.push_back("Exec=mousepad %F\n");
            entry.parse(lines);
            THEN("it is not valid") {
                CHECK_FALSE(entry.isValid());
            }
        }

        WHEN("it has no icon") {
            std::vector<std::string> lines;
            lines.push_back("[Desktop Entry]\n");
            lines.push_back("Name=Mousepad\n");
            lines.push_back("Exec=mousepad %F\n");
            entry.parse(lines);
            THEN("it is not valid") {
                CHECK_FALSE(entry.isValid());
            }
        }

        WHEN("it has no executable") {
            std::vector<std::string> lines;
            lines.push_back("[Desktop Entry]\n");
            lines.push_back("Name=Mousepad\n");
            lines.push_back("Icon=accessories-text-editor\n");
            entry.parse(lines);
            THEN("it is not valid") {
                CHECK_FALSE(entry.isValid());
            }
        }
    }
}

SCENARIO("DesktopEntry classifications") {
    DesktopEntry entry;

    GIVEN("A desktop-file") {
        WHEN("it has one of the categories as AudioVideo") {
            std::vector<std::string> lines;
            lines.push_back("[Desktop Entry]\n");
            lines.push_back("Categories=AudioVideo;Audio;Player;GTK;\n");
            entry.parse(lines);
            THEN("it is an AudioVideo") {
                CHECK(entry.isA("AudioVideo"));
            }

            THEN("it is either of AudioVideo and Multimedia") {
                std::vector<std::string> classifications;
                classifications.push_back("AudioVideo");
                classifications.push_back("Multimedia");
                CHECK(entry.isAnyOf(classifications));
            }
        }

        WHEN("it has none of the categories as AudioVideo") {
            std::vector<std::string> lines;
            lines.push_back("[Desktop Entry]\n");
            lines.push_back("Categories=Audio;Video;Player;GTK;\n");
            entry.parse(lines);
            THEN("it is not an AudioVideo") {
                CHECK_FALSE(entry.isA("AudioVideo"));
            }

            THEN("it is not either of AudioVideo or Multimedia") {
                std::vector<std::string> classifications;
                classifications.push_back("AudioVideo");
                classifications.push_back("Multimedia");
                CHECK_FALSE(entry.isAnyOf(classifications));
            }
        }
    }
}

} // namespace xdg
} // namespace amm
