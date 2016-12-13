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

#include "amm_options.h"

#include "doctest.h"

namespace amm {

SCENARIO("Amm options") {
    GIVEN("Amm options") {
        AmmOptions options;

        WHEN("summary type is normal") {
            THEN("it is valid") {
                options.summary_type = "normal";
                CHECK(options.hasValidSummaryType());
            }
        }

        WHEN("summary type is long") {
            THEN("it is valid") {
                options.summary_type = "long";
                CHECK(options.hasValidSummaryType());
            }
        }

        WHEN("summary type is something else") {
            THEN("it is invalid") {
                options.summary_type = "unknown";
                CHECK_FALSE(options.hasValidSummaryType());
            }
        }
    }
}

} // namespace amm