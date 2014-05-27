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

#include "environment_variable.h"

#include <cstdlib>
#include <string>
#include <vector>

#include "catch.hpp"


namespace amm {
namespace service {

SCENARIO("EnvironmentVariable", "[environmentvariable]") {
  GIVEN("XDG_DATA_HOME and XDG_DATA_DIRS are set") {
    EnvironmentVariable environment_variable;

    setenv("XDG_DATA_HOME", "/data/home", 1);
    setenv("XDG_DATA_DIRS", "/data/dir1:/data/dir2/", 1);

    WHEN("XDG data home is asked") {
      THEN("it is the directory pointed to by XDG_DATA_HOME") {
        REQUIRE(environment_variable.XdgDataHome() == "/data/home");
      }
    }

    WHEN("XDG data directories is asked") {
      THEN("it is a list of directories pointed to by XDG_DATA_DIRS") {
        std::vector<std::string> directories = environment_variable.XdgDataDirectories();
        REQUIRE(directories.size() == 2);
        REQUIRE(directories[0] == "/data/dir1");
        REQUIRE(directories[1] == "/data/dir2/");
      }
    }

    WHEN("base directories for 'applications' subdirectory is asked") {
      THEN("it is a list of directories pointed to by XDG_DATA_HOME, XDG_DATA_DIRS") {
        std::vector<std::string> directories = environment_variable.ApplicationBaseDirectories();
        REQUIRE(directories.size() == 3);
        REQUIRE(directories[0] == "/data/home");
        REQUIRE(directories[1] == "/data/dir1");
        REQUIRE(directories[2] == "/data/dir2/");
      }
    }
  }

  GIVEN("XDG_DATA_HOME is unset and XDG_DATA_DIRS is unset") {
    EnvironmentVariable environment_variable;

    setenv("HOME", "/home", 1);
    unsetenv("XDG_DATA_HOME");
    unsetenv("XDG_DATA_DIRS");

    WHEN("base directories for 'applications' subdirectory is asked") {
      THEN("it is a list of directories pointed to by $HOME/.local/share, /usr/local/share:/usr/share") {
        std::vector<std::string> directories = environment_variable.ApplicationBaseDirectories();
        REQUIRE(directories.size() == 3);
        REQUIRE(directories[0] == "/home/.local/share");
        REQUIRE(directories[1] == "/usr/local/share");
        REQUIRE(directories[2] == "/usr/share");
      }
    }
  }
}

} // namespace service
} // namespace amm
