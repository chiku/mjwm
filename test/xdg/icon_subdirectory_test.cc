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

#include "xdg/icon_subdirectory.h"

#include <climits>
#include <string>

#include "../doctest.h"

namespace amm {
namespace xdg {

SCENARIO("xdg::IconSubdirectory") {
    GIVEN("A subdirectory") {

        WHEN("without optional values") {
            IconSubdirectory subdir = IconSubdirectory("subdirectory", "24");

            THEN("its type is Threshold") {
                CHECK(subdir.type() == THRESHOLD);
            }

            THEN("its maximum size equals its size") {
                CHECK(subdir.maxSize() == 24);
            }

            THEN("its minimum size equals its size") {
                CHECK(subdir.minSize() == 24);
            }

            THEN("its threshold is 2") {
                CHECK(subdir.threshold() == 2);
            }
        }

        WHEN("when optional values are empty") {
            IconSubdirectory subdir = IconSubdirectory("subdirectory", "24").type("").maxSize("").minSize("").threshold("");

            THEN("its type is retained") {
                CHECK(subdir.type() == THRESHOLD);
            }

            THEN("its maximum size is retained") {
                CHECK(subdir.maxSize() == 24);
            }

            THEN("its minimum size is retained") {
                CHECK(subdir.minSize() == 24);
            }

            THEN("its threshold is retained") {
                CHECK(subdir.threshold() == 2);
            }
        }

        WHEN("when assigned a location") {
            IconSubdirectory subdir = IconSubdirectory("subdirectory", "24");
            std::string firefox = "/usr/share/icons/hicolor/256x256/apps/firefox.png";
            subdir.location(firefox);

            THEN("its location can be retrieved") {
                CHECK(subdir.location() == firefox);
            }

            THEN("it can't be reset to an empty value") {
                subdir.location("");
                CHECK(subdir.location() == firefox);
            }
        }
    }

    GIVEN("A fixed subdirectory") {
        IconSubdirectory fixed = IconSubdirectory("fixed", "24").type("Fixed");

        WHEN("required size equals the size") {
            int size = 24;
            THEN("its type is fixed") {
                CHECK(fixed.type() == FIXED);
            }

            THEN("it matches the required size") {
                CHECK(fixed.matches(size));
            }

            THEN("its distance from the size is zero") {
                CHECK(fixed.distance(size) == 0);
            }
        }

        WHEN("required size is lesser than the size") {
            int size = 22;
            THEN("it doesn't match the required size") {
                CHECK_FALSE(fixed.matches(size));
            }

            THEN("its distance is the difference between the actual size and the required size") {
                CHECK(fixed.distance(size) == 2);
            }
        }

        WHEN("required size is greater than the size") {
            int size = 26;
            THEN("it doesn't match the required size") {
                CHECK_FALSE(fixed.matches(size));
            }

            THEN("its distance is the difference between the actual size and the required size") {
                CHECK(fixed.distance(size) == 2);
            }
        }
    }

    GIVEN("A scalable subdirectory") {
        IconSubdirectory scalable = IconSubdirectory("scaled", "24").type("Scalable").maxSize("256").minSize("2");

        WHEN("required size is between the minimum size and size") {
            THEN("its type is scalable") {
                CHECK(scalable.type() == SCALABLE);
            }

            THEN("it matches the required size") {
                CHECK(scalable.matches(2));
                CHECK(scalable.matches(24));
                CHECK(scalable.matches(256));
            }

            THEN("its distance from the required size is zero") {
                CHECK(scalable.distance(2) == 0);
                CHECK(scalable.distance(24) == 0);
                CHECK(scalable.distance(256) == 0);
            }
        }

        WHEN("required size is lesser than the minimum size") {
            int size = 1;
            THEN("it doesn't match the required size") {
                CHECK_FALSE(scalable.matches(size));
            }

            THEN("its distance is the difference of the required size and the minimum size") {
                CHECK(scalable.distance(size) == 1);
            }
        }

        WHEN("required size is greater than the maximum size") {
            int size = 257;
            THEN("it doesn't match the required size") {
                CHECK_FALSE(scalable.matches(size));
            }

            THEN("its distance is the difference of the required size and the maximum size") {
                CHECK(scalable.distance(size) == 1);
            }
        }
    }

    GIVEN("A threshold subdirectory") {
        IconSubdirectory threshold = IconSubdirectory("threshold", "24").type("Threshold").threshold("10").maxSize("34").minSize("14");

        WHEN("it is between threshold around the size") {
            THEN("its type is threshold") {
                CHECK(threshold.type() == THRESHOLD);
            }

            THEN("it matches the required size") {
                CHECK(threshold.matches(14));
                CHECK(threshold.matches(24));
                CHECK(threshold.matches(34));
            }

            THEN("its distance from the required size is zero") {
                CHECK(threshold.distance(14) == 0);
                CHECK(threshold.distance(24) == 0);
                CHECK(threshold.distance(34) == 0);
            }
        }

        WHEN("required size is lesser than the inner threshold size") {
            int size = 13;
            THEN("it doesn't match the required size") {
                CHECK_FALSE(threshold.matches(13));
            }

            THEN("its distance is the difference of the required size and the minimum size") {
                CHECK(threshold.distance(size) == 1);
            }
        }

        WHEN("required size is greater than the outer threshold size") {
            int size = 35;
            THEN("it doesn't match the required size") {
                CHECK_FALSE(threshold.matches(size));
            }

            THEN("its distance is the difference of the required size and the maximum size") {
                CHECK(threshold.distance(size) == 1);
            }
        }
    }

    GIVEN("An subdirectory with type in mixed case") {
        IconSubdirectory mixed_type = IconSubdirectory("fixed", "24").type("fIXeD");

        WHEN("asked its type") {
            THEN("it is converted to camel-case") {
                CHECK(mixed_type.type() == FIXED);
            }
        }
    }

    GIVEN("An invalid subdirectory") {
        IconSubdirectory invalid = IconSubdirectory();

        WHEN("matched for a size") {
            THEN("its type is invalid") {
                CHECK(invalid.type() == INVALID);
            }

            THEN("it never satisfies a size requirement") {
                CHECK_FALSE(invalid.matches(24));
                CHECK_FALSE(invalid.matches(0));
                CHECK_FALSE(invalid.matches(100));
            }

            THEN("it is at a huge distance") {
                CHECK(invalid.distance(24) == INT_MAX);
                CHECK(invalid.distance(0) == INT_MAX);
                CHECK(invalid.distance(100) == INT_MAX);
            }
        }
    }
}

} // namespace xdg
} // namespace amm
