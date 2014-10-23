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

#include "filex.h"

#include <string>
#include <vector>

#include "catch.hpp"

namespace amm {

SCENARIO("FileX", "[filex]") {
  GIVEN("A filex") {
    WHEN("pointing to a file that exists") {
      FileX filex("test/fixtures/applications/vlc.desktop");

      THEN("it exists") {
        REQUIRE(filex.Exists());
      }

      THEN("it isn't a directory") {
        REQUIRE(!filex.ExistsAsDirectory());
      }

      THEN("it succeeds in reading its contents") {
        std::vector<std::string> lines;
        REQUIRE(filex.Load(&lines));
      }

      THEN("it reads the content of the file") {
        std::vector<std::string> lines;
        filex.Load(&lines);
        REQUIRE(lines.size() == 11);
        REQUIRE(lines[0] == "[Desktop Entry]");
        REQUIRE(lines[1] == "Version=1.0");
        REQUIRE(lines[2] == "Name=VLC media player");
        REQUIRE(lines[3] == "GenericName=Media player");
        REQUIRE(lines[4] == "Comment=Read, capture, broadcast your multimedia streams");
        REQUIRE(lines[5] == "Exec=/usr/bin/vlc --started-from-file %U");
        REQUIRE(lines[6] == "TryExec=/usr/bin/vlc");
        REQUIRE(lines[7] == "Icon=vlc");
        REQUIRE(lines[8] == "Terminal=false");
        REQUIRE(lines[9] == "Type=Application");
        REQUIRE(lines[10] == "Categories=AudioVideo;Player;Recorder;");
      }

      THEN("it over-writes the older content") {
        std::vector<std::string> lines;
        filex.Load(&lines);
        filex.Load(&lines);
        REQUIRE(lines.size() == 11);
      }
    }

    WHEN("it points to a directory that exists") {
      FileX dirx("test/fixtures/applications");

      THEN("it exists") {
        REQUIRE(dirx.Exists());
      }

      THEN("it is a directory") {
        REQUIRE(dirx.ExistsAsDirectory());
      }
    }

    WHEN("it points to a file that doesn't exist") {
      FileX filex("test/fixtures/applications/does-not-exist.desktop");

      THEN("it doesn't exist") {
        REQUIRE(!filex.Exists());
      }

      THEN("it isn't a directory") {
        REQUIRE(!filex.ExistsAsDirectory());
      }

      THEN("it fails to read its contents") {
        std::vector<std::string> lines;
        REQUIRE(!filex.Load(&lines));
      }

      THEN("its lines are empty") {
        std::vector<std::string> lines;
        filex.Load(&lines);
        REQUIRE(lines.empty());
      }

      THEN("it doesn't over-write the older contents") {
        std::vector<std::string> lines;
        lines.push_back("existing line");
        filex.Load(&lines);
        REQUIRE(lines.size() == 1);
        REQUIRE(lines[0] == "existing line");
      }
    }
  }
}

} // namespace amm
