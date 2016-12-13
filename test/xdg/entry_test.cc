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

#include "../doctest.h"
#include "xdg/entry.h"

namespace amm {
namespace xdg {

std::vector<std::string> singleSectionEntryLines()
{
    std::vector<std::string> lines;
    lines.push_back("[Desktop Entry]");
    lines.push_back("Version=1.0");
    lines.push_back("Name=VLC media player");
    lines.push_back("GenericName=Media player");
    lines.push_back("Comment=Read, capture, broadcast your multimedia streams");
    lines.push_back("Exec=/usr/bin/vlc --started-from-file %U");
    lines.push_back("TryExec=/usr/bin/vlc");
    lines.push_back("Icon=vlc");
    lines.push_back("Terminal=false");
    lines.push_back("Type=Application");
    lines.push_back("Categories=AudioVideo;Player;Recorder;");
    return lines;
}

std::vector<std::string> singleSectionEntryLinesWithLanguages()
{
    std::vector<std::string> lines;
    lines.push_back("[Desktop Entry]");
    lines.push_back("Version=1.0");
    lines.push_back("Name=VLC media player");
    lines.push_back("GenericName=Media player");
    lines.push_back("Comment=Read, capture, broadcast your multimedia streams");
    lines.push_back("Name[bn]=VLC মিডিয়া প্লেয়ার");
    lines.push_back("Comment[bn]=আপনার মাল্টিমিডিয়া স্ট্রীম পড়ুন, ধরে রাখুন এবং ছড়িয়ে দিন");
    lines.push_back("Name[br]=VLC lenner mediaoù");
    lines.push_back("GenericName[br]=Lenner mediaoù");
    lines.push_back("Comment[br]=Lenn, enrollañ, skignañ ho lanvioù liesvedia");
    lines.push_back("Exec=/usr/bin/vlc --started-from-file %U");
    lines.push_back("TryExec=/usr/bin/vlc");
    lines.push_back("Icon=vlc");
    lines.push_back("Terminal=false");
    lines.push_back("Type=Application");
    lines.push_back("Categories=AudioVideo;Player;Recorder;");
    return lines;
}

std::vector<std::string> multipleSectionsEntry()
{
    std::vector<std::string> lines;
    lines.push_back("[Desktop Entry]");
    lines.push_back("Version=1.0");
    lines.push_back("Type=Application");
    lines.push_back("Name=Xfburn");
    lines.push_back("Comment=CD and DVD burning application");
    lines.push_back("");
    lines.push_back("Exec=xfburn");
    lines.push_back("TryExec=xfburn");
    lines.push_back("Icon=media-cdrom");
    lines.push_back("MimeType=application/x-cd-image;");
    lines.push_back("Terminal=false");
    lines.push_back("Categories=X-XFCE;GTK;DiscBurning;Archiving;AudioVideo;Utility;");
    lines.push_back("StartupNotify=true");
    lines.push_back("");
    lines.push_back("Actions=BurnImage;");
    lines.push_back("");
    lines.push_back("[Desktop Action BurnImage]");
    lines.push_back("Icon=media-cdrom");
    lines.push_back("Exec=xfburn -i %f");
    lines.push_back("Name=Burn Image (xfburn)");
    return lines;
}

std::vector<std::string> noDeclarationLines()
{
    std::vector<std::string> lines;
    lines.push_back("Name=VLC media player");
    lines.push_back("Exec=/usr/bin/vlc --started-from-file %U");
    lines.push_back("Icon=vlc");
    lines.push_back("Categories=AudioVideo;Player;Recorder;");
    return lines;
}

std::vector<std::string> singleSectionWithWhiteSpacesLines()
{
    std::vector<std::string> lines;
    lines.push_back(" [Desktop Entry] ");
    lines.push_back(" Name = VLC media player ");
    lines.push_back("Exec=/usr/bin/vlc --started-from-file %U\n\n");
    lines.push_back(" Icon=vlc");
    lines.push_back("Categories =AudioVideo;Player;Recorder;\n");
    return lines;
}

std::vector<std::string> singleSectionWithMissingAssignmentLines()
{
    std::vector<std::string> lines;
    lines.push_back("[Desktop Entry]");
    lines.push_back("Name=VLC media player");
    lines.push_back("Exec=");
    lines.push_back("=vlc");
    lines.push_back("Categories=");
    return lines;
}

SCENARIO("xdg::Entry") {
    GIVEN("An XDG file with one section") {
        xdg::Entry entry(singleSectionEntryLines());

        WHEN("when parsed") {
            entry.parse();

            THEN("values are exposed under the section and key name") {
                CHECK(entry.under("Desktop Entry", "Version"    ) == "1.0");
                CHECK(entry.under("Desktop Entry", "Name"       ) == "VLC media player");
                CHECK(entry.under("Desktop Entry", "GenericName") == "Media player");
                CHECK(entry.under("Desktop Entry", "Comment"    ) == "Read, capture, broadcast your multimedia streams");
                CHECK(entry.under("Desktop Entry", "Exec"       ) == "/usr/bin/vlc --started-from-file %U");
                CHECK(entry.under("Desktop Entry", "TryExec"    ) == "/usr/bin/vlc");
                CHECK(entry.under("Desktop Entry", "Icon"       ) == "vlc");
                CHECK(entry.under("Desktop Entry", "Terminal"   ) == "false");
                CHECK(entry.under("Desktop Entry", "Type"       ) == "Application");
                CHECK(entry.under("Desktop Entry", "Categories" ) == "AudioVideo;Player;Recorder;");
            }
        }
    }

    GIVEN("An XDG file for an existing language") {
        xdg::Entry entry(singleSectionEntryLinesWithLanguages(), "bn");

        WHEN("when parsed") {
            entry.parse();

            THEN("values are exposed for the language") {
                CHECK(entry.under("Desktop Entry", "Version"    ) == "1.0");
                CHECK(entry.under("Desktop Entry", "Name"       ) == "VLC মিডিয়া প্লেয়ার");
                CHECK(entry.under("Desktop Entry", "GenericName") == "Media player");
                CHECK(entry.under("Desktop Entry", "Comment"    ) == "আপনার মাল্টিমিডিয়া স্ট্রীম পড়ুন, ধরে রাখুন এবং ছড়িয়ে দিন");
                CHECK(entry.under("Desktop Entry", "Exec"       ) == "/usr/bin/vlc --started-from-file %U");
                CHECK(entry.under("Desktop Entry", "TryExec"    ) == "/usr/bin/vlc");
                CHECK(entry.under("Desktop Entry", "Icon"       ) == "vlc");
                CHECK(entry.under("Desktop Entry", "Terminal"   ) == "false");
                CHECK(entry.under("Desktop Entry", "Type"       ) == "Application");
                CHECK(entry.under("Desktop Entry", "Categories" ) == "AudioVideo;Player;Recorder;");
            }
        }
    }

    GIVEN("An XDG file for a non-existing language") {
        xdg::Entry entry(singleSectionEntryLinesWithLanguages(), "bad");

        WHEN("when parsed") {
            entry.parse();

            THEN("default values are exposed") {
                CHECK(entry.under("Desktop Entry", "Version"    ) == "1.0");
                CHECK(entry.under("Desktop Entry", "Name"       ) == "VLC media player");
                CHECK(entry.under("Desktop Entry", "GenericName") == "Media player");
                CHECK(entry.under("Desktop Entry", "Comment"    ) == "Read, capture, broadcast your multimedia streams");
                CHECK(entry.under("Desktop Entry", "Exec"       ) == "/usr/bin/vlc --started-from-file %U");
                CHECK(entry.under("Desktop Entry", "TryExec"    ) == "/usr/bin/vlc");
                CHECK(entry.under("Desktop Entry", "Icon"       ) == "vlc");
                CHECK(entry.under("Desktop Entry", "Terminal"   ) == "false");
                CHECK(entry.under("Desktop Entry", "Type"       ) == "Application");
                CHECK(entry.under("Desktop Entry", "Categories" ) == "AudioVideo;Player;Recorder;");
            }
        }
    }

    GIVEN("An XDG file with entries that contain whitespaces") {
        xdg::Entry entry(singleSectionWithWhiteSpacesLines());

        WHEN("when parsed") {
            entry.parse();

            THEN("the whitespaces are ignored when retrieving the values") {
                CHECK(entry.under("Desktop Entry", "Name"      ) == "VLC media player");
                CHECK(entry.under("Desktop Entry", "Exec"      ) == "/usr/bin/vlc --started-from-file %U");
                CHECK(entry.under("Desktop Entry", "Icon"      ) == "vlc");
                CHECK(entry.under("Desktop Entry", "Categories") == "AudioVideo;Player;Recorder;");
            }
        }
    }

    GIVEN("An XDG file with entries that is missing values") {
        xdg::Entry entry(singleSectionWithMissingAssignmentLines());

        WHEN("when parsed") {
            entry.parse();

            THEN("it has empty values for missing entries") {
                CHECK(entry.under("Desktop Entry", "Exec"      ) == "");
                CHECK(entry.under("Desktop Entry", "Categories") == "");
            }
        }
    }

    GIVEN("An XDG file with multiple section") {
        xdg::Entry entry(multipleSectionsEntry());

        WHEN("when parsed") {
            entry.parse();

            THEN("values are exposed under the section and key name") {
                CHECK(entry.under("Desktop Entry", "Version"       ) == "1.0");
                CHECK(entry.under("Desktop Entry", "Type"          ) == "Application");
                CHECK(entry.under("Desktop Entry", "Name"          ) == "Xfburn");
                CHECK(entry.under("Desktop Entry", "Comment"       ) == "CD and DVD burning application");
                CHECK(entry.under("Desktop Entry", "Exec"          ) == "xfburn");
                CHECK(entry.under("Desktop Entry", "TryExec"       ) == "xfburn");
                CHECK(entry.under("Desktop Entry", "Icon"          ) == "media-cdrom");
                CHECK(entry.under("Desktop Entry", "MimeType"      ) == "application/x-cd-image;");
                CHECK(entry.under("Desktop Entry", "Terminal"      ) == "false");
                CHECK(entry.under("Desktop Entry", "Categories"    ) == "X-XFCE;GTK;DiscBurning;Archiving;AudioVideo;Utility;");
                CHECK(entry.under("Desktop Entry", "StartupNotify" ) == "true");
                CHECK(entry.under("Desktop Entry", "Actions"       ) == "BurnImage;");

                CHECK(entry.under("Desktop Action BurnImage", "Icon") == "media-cdrom");
                CHECK(entry.under("Desktop Action BurnImage", "Exec") == "xfburn -i %f");
                CHECK(entry.under("Desktop Action BurnImage", "Name") == "Burn Image (xfburn)");
            }

            THEN("it doesn't duplicate keys and values in lower sections") {
                CHECK(entry.under("Desktop Action BurnImage", "TryExec") == "");
            }
        }
    }

    GIVEN("An XDG file without a section") {
        xdg::Entry entry(noDeclarationLines());

        WHEN("when parsed") {
            entry.parse();

            THEN("the values are exposed under an empty section name") {
                CHECK(entry.under("", "Name"      ) == "VLC media player");
                CHECK(entry.under("", "Exec"      ) == "/usr/bin/vlc --started-from-file %U");
                CHECK(entry.under("", "Icon"      ) == "vlc");
                CHECK(entry.under("", "Categories") == "AudioVideo;Player;Recorder;");
            }
        }
    }
}

} // namespace xdg
} // namespace amm
