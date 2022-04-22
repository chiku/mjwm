/*
  This file is part of mjwm.
  Copyright (C) 2022  Chirantan Mitra <chirantan.mitra@gmail.com>

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

#include "summary_type.h"

#include "doctest.h"

namespace amm {

SCENARIO("Summary type comparison") {
    GIVEN("Source is verbose") {
        THEN("it is compatible with silent") {
            CHECK(summaryTypeCompatible(SummaryType::Verbose, SummaryType::Silent));
        }
        THEN("it is compatible with normal") {
            CHECK(summaryTypeCompatible(SummaryType::Verbose, SummaryType::Normal));
        }
        THEN("it is compatible with verbose") {
            CHECK(summaryTypeCompatible(SummaryType::Verbose, SummaryType::Verbose));
        }
    }

    GIVEN("Source is normal") {
        THEN("it is compatible with silent") {
            CHECK(summaryTypeCompatible(SummaryType::Normal, SummaryType::Silent));
        }
        THEN("it is compatible with normal") {
            CHECK(summaryTypeCompatible(SummaryType::Normal, SummaryType::Normal));
        }
        THEN("it is not compatible with verbose") {
            CHECK_FALSE(summaryTypeCompatible(SummaryType::Normal, SummaryType::Verbose));
        }
    }

    GIVEN("Source is silent") {
        THEN("it is compatible with silent") {
            CHECK(summaryTypeCompatible(SummaryType::Silent, SummaryType::Silent));
        }
        THEN("it is not compatible with normal") {
            CHECK_FALSE(summaryTypeCompatible(SummaryType::Silent, SummaryType::Normal));
        }
        THEN("it is not compatible with verbose") {
            CHECK_FALSE(summaryTypeCompatible(SummaryType::Silent, SummaryType::Verbose));
        }
    }
}

} // namespace amm
