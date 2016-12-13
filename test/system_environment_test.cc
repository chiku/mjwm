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

#include "system_environment.h"

#include <cstdlib>
#include <string>
#include <vector>

#include "doctest.h"

namespace amm {

SCENARIO("SystemEnvironment") {
    GIVEN("HOME is not set") {
        unsetenv("HOME");

        SystemEnvironment environment;

        WHEN("validated") {
            THEN("it is invalid") {
                CHECK_FALSE(environment.isValid());
            }
        }
    }

    GIVEN("HOME is set") {
        setenv("HOME", "/home/mjwm", 1);

        SystemEnvironment environment;

        WHEN("validated") {
            THEN("it is valid") {
                CHECK(environment.isValid());
            }
        }

        GIVEN("XDG_DATA_HOME and XDG_DATA_DIRS are set") {
            setenv("XDG_DATA_HOME", "/data/home", 1);
            setenv("XDG_DATA_DIRS", "/data/dir1:/data/dir2/", 1);

            SystemEnvironment environment;

            WHEN("XDG data home is asked") {
                THEN("it is the directory pointed to by XDG_DATA_HOME") {
                    CHECK(environment.xdgDataHome() == "/data/home");
                }
            }

            WHEN("XDG data directories is asked") {
                THEN("it is a list of directories pointed to by XDG_DATA_DIRS") {
                    std::vector<std::string> directories = environment.xdgDataDirectories();
                    REQUIRE(directories.size() == 2);
                    CHECK(directories[0] == "/data/dir1");
                    CHECK(directories[1] == "/data/dir2/");
                }
            }

            WHEN("directories for 'applications' subdirectories is asked") {
                THEN("it is a list of directories pointed to by XDG_DATA_HOME/applications, XDG_DATA_DIRS/applications") {
                    std::vector<std::string> directories = environment.applicationDirectories();
                    REQUIRE(directories.size() == 3);
                    CHECK(directories[0] == "/data/home/applications");
                    CHECK(directories[1] == "/data/dir1/applications");
                    CHECK(directories[2] == "/data/dir2/applications");
                }
            }
        }

        GIVEN("XDG_DATA_HOME is unset and XDG_DATA_DIRS is unset") {
            unsetenv("XDG_DATA_HOME");
            unsetenv("XDG_DATA_DIRS");

            SystemEnvironment environment;

            WHEN("directories for 'applications' subdirectories is asked") {

                THEN("it is a list of directories pointed to by $HOME/.local/share/applications, /usr/local/share/applications and /usr/share/applications") {
                    std::vector<std::string> directories = environment.applicationDirectories();
                    REQUIRE(directories.size() == 3);
                    CHECK(directories[0] == "/home/mjwm/.local/share/applications");
                    CHECK(directories[1] == "/usr/local/share/applications");
                    CHECK(directories[2] == "/usr/share/applications");
                }
            }

            WHEN("directories for icon themes is asked") {
                THEN("it is a list of directories pointed to by $HOME/.icons, /usr/local/share/icons, /usr/share/icons and /usr/share/pixmaps") {
                    std::vector<std::string> directories = environment.iconThemeDirectories();
                    REQUIRE(directories.size() == 4);
                    CHECK(directories[0] == "/home/mjwm/.icons");
                    CHECK(directories[1] == "/usr/local/share/icons");
                    CHECK(directories[2] == "/usr/share/icons");
                    CHECK(directories[3] == "/usr/share/pixmaps");
                }
            }
        }
    }

    GIVEN("LANGUAGE is set with encoding and sub-type") {
        WHEN("langauage is asked") {
            THEN("it is the first part of the LANGUAGE") {
                setenv("LANGUAGE", "en_IN.UTF-8", 1);
                CHECK(SystemEnvironment().language() == "en");
            }
        }
    }

    GIVEN("LANGUAGE is set but LC_ALL and LANG is not set") {
        WHEN("langauage is asked") {
            THEN("it is the first part of the LANGUAGE") {
                setenv("LANGUAGE", "en_IN.UTF-8", 1);
                unsetenv("LC_ALL");
                unsetenv("LANG");
                CHECK(SystemEnvironment().language() == "en");
            }
        }
    }

    GIVEN("LANGUAGE is set without encoding and without sub-type") {
        WHEN("langauage is asked") {
            THEN("it is the first part of the LANGUAGE") {
                setenv("LANGUAGE", "en", 1);
                CHECK(SystemEnvironment().language() == "en");
            }
        }
    }

    GIVEN("LANGUAGE is not set but LC_ALL is set") {
        WHEN("langauage is asked") {
            THEN("it is the first part of the LC_ALL") {
                unsetenv("LANGUAGE");
                setenv("LC_ALL", "en_IN.UTF-8", 1);
                CHECK(SystemEnvironment().language() == "en");
            }
        }
    }

    GIVEN("LANGUAGE and LC_ALL are not set but LANG is set") {
        WHEN("langauage is asked") {
            THEN("it is the first part of the LANG") {
                unsetenv("LANGUAGE");
                unsetenv("LC_ALL");
                setenv("LANG", "en_IN.UTF-8", 1);
                CHECK(SystemEnvironment().language() == "en");
            }
        }
    }

    GIVEN("LANGUAGE, LC_ALL and LANG are not set") {
        WHEN("langauage is asked") {
            THEN("it empty") {
                unsetenv("LANGUAGE");
                unsetenv("LC_ALL");
                unsetenv("LANG");
                CHECK(SystemEnvironment().language() == "");
            }
        }
    }
}

} // namespace amm
