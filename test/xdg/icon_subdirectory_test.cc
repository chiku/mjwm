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
        REQUIRE(subdir.Type() == THRESHOLD);
      }

      THEN("its maximum size equals its size") {
        REQUIRE(subdir.MaxSize() == 24);
      }

      THEN("its minimum size equals its size") {
        REQUIRE(subdir.MinSize() == 24);
      }

      THEN("its threshold equals 2") {
        REQUIRE(subdir.Threshold() == 2);
      }
    }

    WHEN("when optional values are set to empty") {
      IconSubdirectory subdir = IconSubdirectory("subdirectory", "24").Type("").MaxSize("").MinSize("").Threshold("");

      THEN("its type is retained") {
        REQUIRE(subdir.Type() == THRESHOLD);
      }

      THEN("its maximum size is retained") {
        REQUIRE(subdir.MaxSize() == 24);
      }

      THEN("its minimum size is retained") {
        REQUIRE(subdir.MinSize() == 24);
      }

      THEN("its threshold is retained") {
        REQUIRE(subdir.Threshold() == 2);
      }
    }

    WHEN("when assigned a location") {
      IconSubdirectory subdir = IconSubdirectory("subdirectory", "24");
      std::string firefox = "/usr/share/icons/hicolor/256x256/apps/firefox.png";
      subdir.Location(firefox);

      THEN("its location can be retrieved") {
        REQUIRE(subdir.Location() == firefox);
      }

      THEN("it can't be reset to empty value") {
        subdir.Location("");
        REQUIRE(subdir.Location() == firefox);
      }
    }
  }

  GIVEN("A fixed subdirectory") {
    IconSubdirectory fixed = IconSubdirectory("fixed", "24").Type("Fixed");

    WHEN("required size equals the size") {
      int size = 24;
      THEN("its type is fixed") {
        REQUIRE(fixed.Type() == FIXED);
      }

      THEN("it matches the required size") {
        REQUIRE(fixed.Matches(size));
      }

      THEN("its distance from the size is zero") {
        REQUIRE(fixed.Distance(size) == 0);
      }
    }

    WHEN("required size is lesser than the size") {
      int size = 22;
      THEN("is doesn't match the required size") {
        REQUIRE(!fixed.Matches(size));
      }

      THEN("its distance is the difference between the actual size and the required size") {
        REQUIRE(fixed.Distance(size) == 2);
      }
    }

    WHEN("required size is greater than the size") {
      int size = 26;
      THEN("it doesn't match the required size") {
        REQUIRE(!fixed.Matches(size));
      }

      THEN("its distance is the difference between the actual size and the required size") {
        REQUIRE(fixed.Distance(size) == 2);
      }
    }
  }

  GIVEN("A scalable subdirectory") {
    IconSubdirectory scalable = IconSubdirectory("scaled", "24").Type("Scalable").MaxSize("256").MinSize("2");

    WHEN("required size is between the minimum size and size") {
      THEN("its type is scalable") {
        REQUIRE(scalable.Type() == SCALABLE);
      }

      THEN("it matches the required size") {
        REQUIRE(scalable.Matches(2));
        REQUIRE(scalable.Matches(24));
        REQUIRE(scalable.Matches(256));
      }

      THEN("its distance from the required size is zero") {
        REQUIRE(scalable.Distance(2) == 0);
        REQUIRE(scalable.Distance(24) == 0);
        REQUIRE(scalable.Distance(256) == 0);
      }
    }

    WHEN("required size is lesser than the minimum size") {
      int size = 1;
      THEN("is doesn't match the required size") {
        REQUIRE(!scalable.Matches(size));
      }

      THEN("its distance is the difference of the required size the minimum size") {
        REQUIRE(scalable.Distance(size) == 1);
      }
    }

    WHEN("required size is greater than the maximum size") {
      int size = 257;
      THEN("is doesn't match the required size") {
        REQUIRE(!scalable.Matches(size));
      }

      THEN("its distance is the difference of the required size the maximum size") {
        REQUIRE(scalable.Distance(size) == 1);
      }
    }
  }

  GIVEN("A threshold subdirectory") {
    IconSubdirectory threshold = IconSubdirectory("threshold", "24").Type("Threshold").Threshold("10").MaxSize("34").MinSize("14");

    WHEN("it is between threshold around the size") {
      THEN("its type is threshold") {
        REQUIRE(threshold.Type() == THRESHOLD);
      }

      THEN("it matches the required size") {
        REQUIRE(threshold.Matches(14));
        REQUIRE(threshold.Matches(24));
        REQUIRE(threshold.Matches(34));
      }

      THEN("it distance from the required size is zero") {
        REQUIRE(threshold.Distance(14) == 0);
        REQUIRE(threshold.Distance(24) == 0);
        REQUIRE(threshold.Distance(34) == 0);
      }
    }

    WHEN("required size is lesser than the inner threshold size") {
      int size = 13;
      THEN("is doesn't match the required size") {
        REQUIRE(!threshold.Matches(13));
      }

      THEN("its distance is the difference of the required size the minimum size") {
        REQUIRE(threshold.Distance(size) == 1);
      }
    }

    WHEN("required size is greater than the outer threshold size") {
      int size = 35;
      THEN("is doesn't match the required size") {
        REQUIRE(!threshold.Matches(size));
      }

      THEN("its distance is the difference of the required size the maximum size") {
        REQUIRE(threshold.Distance(size) == 1);
      }
    }
  }

  GIVEN("An subdirectory with type in mixed case") {
    IconSubdirectory mixed_type = IconSubdirectory("fixed", "24").Type("fIXeD");

    WHEN("asked storing its type") {
      THEN("it is converted to camel-case") {
        REQUIRE(mixed_type.Type() == FIXED);
      }
    }
  }

  GIVEN("An invalid subdirectory") {
    IconSubdirectory invalid = IconSubdirectory();

    WHEN("matched for a size") {
      THEN("its type is invalid") {
        REQUIRE(invalid.Type() == INVALID);
      }

      THEN("it never satisfied") {
        REQUIRE(!invalid.Matches(24));
        REQUIRE(!invalid.Matches(0));
        REQUIRE(!invalid.Matches(100));
      }

      THEN("it is at a huge distance") {
        REQUIRE(invalid.Distance(24) == INT_MAX);
        REQUIRE(invalid.Distance(0) == INT_MAX);
        REQUIRE(invalid.Distance(100) == INT_MAX);
      }
    }
  }
}

} // namespace xdg
} // namespace amm
