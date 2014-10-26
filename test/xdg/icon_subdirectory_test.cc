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

#include "xdg/icon_subdirectory.h"

#include <climits>
#include <string>

#include "../catch.hpp"

namespace amm {
namespace xdg {

SCENARIO("xdg::IconSubdirectory", "[iconsubdir]") {
    GIVEN("A subdirectory") {

        WHEN("without optional values") {
            IconSubdirectory subdir = IconSubdirectory("subdirectory", "24");

            THEN("its type is Threshold") {
                REQUIRE(subdir.type() == THRESHOLD);
            }

            THEN("its maximum size equals its size") {
                REQUIRE(subdir.maxSize() == 24);
            }

            THEN("its minimum size equals its size") {
                REQUIRE(subdir.minSize() == 24);
            }

            THEN("its threshold is 2") {
                REQUIRE(subdir.threshold() == 2);
            }
        }

        WHEN("when optional values are empty") {
            IconSubdirectory subdir = IconSubdirectory("subdirectory", "24").type("").maxSize("").minSize("").threshold("");

            THEN("its type is retained") {
                REQUIRE(subdir.type() == THRESHOLD);
            }

            THEN("its maximum size is retained") {
                REQUIRE(subdir.maxSize() == 24);
            }

            THEN("its minimum size is retained") {
                REQUIRE(subdir.minSize() == 24);
            }

            THEN("its threshold is retained") {
                REQUIRE(subdir.threshold() == 2);
            }
        }

        WHEN("when assigned a location") {
            IconSubdirectory subdir = IconSubdirectory("subdirectory", "24");
            std::string firefox = "/usr/share/icons/hicolor/256x256/apps/firefox.png";
            subdir.location(firefox);

            THEN("its location can be retrieved") {
                REQUIRE(subdir.location() == firefox);
            }

            THEN("it can't be reset to an empty value") {
                subdir.location("");
                REQUIRE(subdir.location() == firefox);
            }
        }
    }

    GIVEN("A fixed subdirectory") {
        IconSubdirectory fixed = IconSubdirectory("fixed", "24").type("Fixed");

        WHEN("required size equals the size") {
            int size = 24;
            THEN("its type is fixed") {
                REQUIRE(fixed.type() == FIXED);
            }

            THEN("it matches the required size") {
                REQUIRE(fixed.matches(size));
            }

            THEN("its distance from the size is zero") {
                REQUIRE(fixed.distance(size) == 0);
            }
        }

        WHEN("required size is lesser than the size") {
            int size = 22;
            THEN("it doesn't match the required size") {
                REQUIRE(!fixed.matches(size));
            }

            THEN("its distance is the difference between the actual size and the required size") {
                REQUIRE(fixed.distance(size) == 2);
            }
        }

        WHEN("required size is greater than the size") {
            int size = 26;
            THEN("it doesn't match the required size") {
                REQUIRE(!fixed.matches(size));
            }

            THEN("its distance is the difference between the actual size and the required size") {
                REQUIRE(fixed.distance(size) == 2);
            }
        }
    }

    GIVEN("A scalable subdirectory") {
        IconSubdirectory scalable = IconSubdirectory("scaled", "24").type("Scalable").maxSize("256").minSize("2");

        WHEN("required size is between the minimum size and size") {
            THEN("its type is scalable") {
                REQUIRE(scalable.type() == SCALABLE);
            }

            THEN("it matches the required size") {
                REQUIRE(scalable.matches(2));
                REQUIRE(scalable.matches(24));
                REQUIRE(scalable.matches(256));
            }

            THEN("its distance from the required size is zero") {
                REQUIRE(scalable.distance(2) == 0);
                REQUIRE(scalable.distance(24) == 0);
                REQUIRE(scalable.distance(256) == 0);
            }
        }

        WHEN("required size is lesser than the minimum size") {
            int size = 1;
            THEN("it doesn't match the required size") {
                REQUIRE(!scalable.matches(size));
            }

            THEN("its distance is the difference of the required size and the minimum size") {
                REQUIRE(scalable.distance(size) == 1);
            }
        }

        WHEN("required size is greater than the maximum size") {
            int size = 257;
            THEN("it doesn't match the required size") {
                REQUIRE(!scalable.matches(size));
            }

            THEN("its distance is the difference of the required size and the maximum size") {
                REQUIRE(scalable.distance(size) == 1);
            }
        }
    }

    GIVEN("A threshold subdirectory") {
        IconSubdirectory threshold = IconSubdirectory("threshold", "24").type("Threshold").threshold("10").maxSize("34").minSize("14");

        WHEN("it is between threshold around the size") {
            THEN("its type is threshold") {
                REQUIRE(threshold.type() == THRESHOLD);
            }

            THEN("it matches the required size") {
                REQUIRE(threshold.matches(14));
                REQUIRE(threshold.matches(24));
                REQUIRE(threshold.matches(34));
            }

            THEN("its distance from the required size is zero") {
                REQUIRE(threshold.distance(14) == 0);
                REQUIRE(threshold.distance(24) == 0);
                REQUIRE(threshold.distance(34) == 0);
            }
        }

        WHEN("required size is lesser than the inner threshold size") {
            int size = 13;
            THEN("it doesn't match the required size") {
                REQUIRE(!threshold.matches(13));
            }

            THEN("its distance is the difference of the required size and the minimum size") {
                REQUIRE(threshold.distance(size) == 1);
            }
        }

        WHEN("required size is greater than the outer threshold size") {
            int size = 35;
            THEN("it doesn't match the required size") {
                REQUIRE(!threshold.matches(size));
            }

            THEN("its distance is the difference of the required size and the maximum size") {
                REQUIRE(threshold.distance(size) == 1);
            }
        }
    }

    GIVEN("An subdirectory with type in mixed case") {
        IconSubdirectory mixed_type = IconSubdirectory("fixed", "24").type("fIXeD");

        WHEN("asked its type") {
            THEN("it is converted to camel-case") {
                REQUIRE(mixed_type.type() == FIXED);
            }
        }
    }

    GIVEN("An invalid subdirectory") {
        IconSubdirectory invalid = IconSubdirectory();

        WHEN("matched for a size") {
            THEN("its type is invalid") {
                REQUIRE(invalid.type() == INVALID);
            }

            THEN("it never satisfies a size requirement") {
                REQUIRE(!invalid.matches(24));
                REQUIRE(!invalid.matches(0));
                REQUIRE(!invalid.matches(100));
            }

            THEN("it is at a huge distance") {
                REQUIRE(invalid.distance(24) == INT_MAX);
                REQUIRE(invalid.distance(0) == INT_MAX);
                REQUIRE(invalid.distance(100) == INT_MAX);
            }
        }
    }
}

} // namespace xdg
} // namespace amm
