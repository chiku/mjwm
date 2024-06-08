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

#include <string>

#include "doctest.h"
#include "amm_options.h"

namespace amm {

SCENARIO("Amm options") {
    GIVEN("Amm options") {
        WHEN("$HOME ends with /") {
            THEN("it sets output file without extra /") {
                AmmOptions options = AmmOptions::Default("/home/user/", "en");
                CHECK(options.output_file_name == "/home/user/.jwmrc-mjwm");
            }
        }

        WHEN("$HOME does not ends with /") {
            THEN("it sets output file with extra /") {
                AmmOptions options = AmmOptions::Default("/home/user", "en");
                CHECK(options.output_file_name == "/home/user/.jwmrc-mjwm");
            }
        }
    }
}

} // namespace amm
