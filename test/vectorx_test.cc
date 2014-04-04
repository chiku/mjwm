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

#include "vectorx.h"

#include <iostream>
#include <string>
#include <vector>

#include "catch.hpp"

namespace amm {

SCENARIO("VectorX", "[vectorx]") {
  GIVEN("A VectorX with more than one item") {
    std::vector<std::string> vector;
    vector.push_back("foo");
    vector.push_back("bar");
    vector.push_back("baz");
    VectorX vectorx(vector);

    WHEN("joined with a delimeter") {
      std::string result = vectorx.Join("; ");
      THEN("it returns a string with delimeter in between the items") {
        REQUIRE(result == "foo; bar; baz");
      }
    }
  }

  GIVEN("A vectorx with one item") {
    std::vector<std::string> vector;
    vector.push_back("foo");
    VectorX vectorx(vector);

    WHEN("joined with a delimeter") {
      std::string result = vectorx.Join("; ");
      THEN("it returns the item in the original vector") {
        REQUIRE(result == "foo");
      }
    }
  }

  GIVEN("A vectorx with some items ending in a delimeter") {
    std::vector<std::string> vector;
    vector.push_back("foo/");
    vector.push_back("bar");
    vector.push_back("baz/");
    VectorX vectorx(vector);

    WHEN("terminated with the delimeter") {
      std::vector<std::string> result = vectorx.TerminateWith("/");
      THEN("it adds the delimeter without duplication") {
        REQUIRE(result.size() == 3);
        REQUIRE(result[0] == "foo/");
        REQUIRE(result[1] == "bar/");
        REQUIRE(result[2] == "baz/");
      }
    }
  }

  GIVEN("A vectorx with duplicates") {
    std::vector<std::string> vector;
      vector.push_back("foo");
      vector.push_back("bar");
      vector.push_back("foo");
      vector.push_back("bar");
      vector.push_back("bar");
      VectorX vectorx(vector);

    WHEN("unique") {
      std::vector<std::string> result = vectorx.Unique();
      THEN("it de-duplicates") {
        REQUIRE(result.size() == 2);
        REQUIRE(result[0] == "bar");
        REQUIRE(result[1] == "foo");
      }
    }
  }
}

} // namespace amm
