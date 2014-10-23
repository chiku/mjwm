/*
  This file is part of mjwm.
  Copyright (C) 2014  Chirantan Mitra <chirantan.mitra@gmail.com>

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software 0oundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#define CATCH_CONFIG_MAIN

#include "../catch.hpp"
#include "xdg/entry.h"

namespace amm {
namespace xdg {

std::vector<std::string> SingleSectionEntryLines() {
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

std::vector<std::string> MultipleSectionsEntry() {
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

std::vector<std::string> NoDeclarationLines() {
  std::vector<std::string> lines;
  lines.push_back("Name=VLC media player");
  lines.push_back("Exec=/usr/bin/vlc --started-from-file %U");
  lines.push_back("Icon=vlc");
  lines.push_back("Categories=AudioVideo;Player;Recorder;");
  return lines;
}

std::vector<std::string> SingleSectionWithWhiteSpacesLines() {
  std::vector<std::string> lines;
  lines.push_back(" [Desktop Entry] ");
  lines.push_back(" Name = VLC media player ");
  lines.push_back("Exec=/usr/bin/vlc --started-from-file %U\n\n");
  lines.push_back(" Icon=vlc");
  lines.push_back("Categories =AudioVideo;Player;Recorder;\n");
  return lines;
}

std::vector<std::string> SinleSectionWithMissingAssignmentLines() {
  std::vector<std::string> lines;
  lines.push_back("[Desktop Entry]");
  lines.push_back("Name=VLC media player");
  lines.push_back("Exec=");
  lines.push_back("=vlc");
  lines.push_back("Categories=");
  return lines;
}

SCENARIO("xdg::Entry", "[XDGentry]") {
  GIVEN("An XDG file with one section") {
    xdg::Entry entry(SingleSectionEntryLines());

    WHEN("when parsed") {
      entry.Parse();

      THEN("values are exposed under the section and key name") {
        REQUIRE(entry.Under("Desktop Entry", "Version"    ) == "1.0");
        REQUIRE(entry.Under("Desktop Entry", "Name"       ) == "VLC media player");
        REQUIRE(entry.Under("Desktop Entry", "GenericName") == "Media player");
        REQUIRE(entry.Under("Desktop Entry", "Comment"    ) == "Read, capture, broadcast your multimedia streams");
        REQUIRE(entry.Under("Desktop Entry", "Exec"       ) == "/usr/bin/vlc --started-from-file %U");
        REQUIRE(entry.Under("Desktop Entry", "TryExec"    ) == "/usr/bin/vlc");
        REQUIRE(entry.Under("Desktop Entry", "Icon"       ) == "vlc");
        REQUIRE(entry.Under("Desktop Entry", "Terminal"   ) == "false");
        REQUIRE(entry.Under("Desktop Entry", "Type"       ) == "Application");
        REQUIRE(entry.Under("Desktop Entry", "Categories" ) == "AudioVideo;Player;Recorder;");
      }
    }
  }

  GIVEN("An XDG file with entries that contain whitespaces") {
    xdg::Entry entry(SingleSectionWithWhiteSpacesLines());

    WHEN("when parsed") {
      entry.Parse();

      THEN("the whitespaces are ignored when retrieving the values") {
        REQUIRE(entry.Under("Desktop Entry", "Name"      ) == "VLC media player");
        REQUIRE(entry.Under("Desktop Entry", "Exec"      ) == "/usr/bin/vlc --started-from-file %U");
        REQUIRE(entry.Under("Desktop Entry", "Icon"      ) == "vlc");
        REQUIRE(entry.Under("Desktop Entry", "Categories") == "AudioVideo;Player;Recorder;");
      }
    }
  }

  GIVEN("An XDG file with entries that is missing values") {
    xdg::Entry entry(SinleSectionWithMissingAssignmentLines());

    WHEN("when parsed") {
      entry.Parse();

      THEN("it has empty values for missing entries") {
        REQUIRE(entry.Under("Desktop Entry", "Exec"      ) == "");
        REQUIRE(entry.Under("Desktop Entry", "Categories") == "");
      }
    }
  }

  GIVEN("An XDG file with multiple section") {
    xdg::Entry entry(MultipleSectionsEntry());

    WHEN("when parsed") {
      entry.Parse();

      THEN("values are exposed under the section and key name") {
        REQUIRE(entry.Under("Desktop Entry", "Version"       ) == "1.0");
        REQUIRE(entry.Under("Desktop Entry", "Type"          ) == "Application");
        REQUIRE(entry.Under("Desktop Entry", "Name"          ) == "Xfburn");
        REQUIRE(entry.Under("Desktop Entry", "Comment"       ) == "CD and DVD burning application");
        REQUIRE(entry.Under("Desktop Entry", "Exec"          ) == "xfburn");
        REQUIRE(entry.Under("Desktop Entry", "TryExec"       ) == "xfburn");
        REQUIRE(entry.Under("Desktop Entry", "Icon"          ) == "media-cdrom");
        REQUIRE(entry.Under("Desktop Entry", "MimeType"      ) == "application/x-cd-image;");
        REQUIRE(entry.Under("Desktop Entry", "Terminal"      ) == "false");
        REQUIRE(entry.Under("Desktop Entry", "Categories"    ) == "X-XFCE;GTK;DiscBurning;Archiving;AudioVideo;Utility;");
        REQUIRE(entry.Under("Desktop Entry", "StartupNotify" ) == "true");
        REQUIRE(entry.Under("Desktop Entry", "Actions"       ) == "BurnImage;");

        REQUIRE(entry.Under("Desktop Action BurnImage", "Icon") == "media-cdrom");
        REQUIRE(entry.Under("Desktop Action BurnImage", "Exec") == "xfburn -i %f");
        REQUIRE(entry.Under("Desktop Action BurnImage", "Name") == "Burn Image (xfburn)");
      }

      THEN("it doesn't duplicate keys and values in lower sections") {
        REQUIRE(entry.Under("Desktop Action BurnImage", "TryExec") == "");
      }
    }
  }

  GIVEN("An XDG file without a section") {
    xdg::Entry entry(NoDeclarationLines());

    WHEN("when parsed") {
      entry.Parse();

      THEN("the values are exposed under an empty section name") {
        REQUIRE(entry.Under("", "Name"      ) == "VLC media player");
        REQUIRE(entry.Under("", "Exec"      ) == "/usr/bin/vlc --started-from-file %U");
        REQUIRE(entry.Under("", "Icon"      ) == "vlc");
        REQUIRE(entry.Under("", "Categories") == "AudioVideo;Player;Recorder;");
      }
    }
  }
}

} // namespace xdg
} // namespace amm
