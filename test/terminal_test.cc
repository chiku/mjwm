/*
  This file is part of mjwm.
  Copyright (C) 2014-2024  Chirantan Mitra <chirantan.mitra@gmail.com>

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

#include "terminal.h"

#include <string>

#include "doctest.h"

namespace amm {

SCENARIO("Terminal") {
    GIVEN("TERM is alacritty") {
        WHEN("generating executable") {
            THEN("it is for alacritty") {
                CHECK(terminalCommand("alacritty", "htop", "Process Viewer") == "alacritty --title \"Process Viewer\" --class \"Process Viewer\" -e htop");
            }
        }
    }

    GIVEN("TERM is sakura") {
        WHEN("generating executable") {
            THEN("it is for sakura") {
                CHECK(terminalCommand("sakura", "htop", "Process Viewer") == "sakura --name \"Process Viewer\" --class \"Process Viewer\" -e htop");
            }
        }
    }

    GIVEN("TERM is xterm") {
        WHEN("generating executable") {
            THEN("it is for xterm") {
                CHECK(terminalCommand("xterm", "htop", "Process Viewer") == "xterm -class \"Process Viewer\" htop");
            }
        }
    }

    GIVEN("TERM is unknown") {
        WHEN("generating executable") {
            THEN("it is for xterm") {
                CHECK(terminalCommand("unknown", "htop", "Process Viewer") == "xterm -class \"Process Viewer\" htop");
            }
        }
    }
}

} // namespace amm
