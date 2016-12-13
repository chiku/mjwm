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

#include "vectorx.h"

#include <string>
#include <vector>

#include "doctest.h"

namespace amm {

SCENARIO("VectorX") {
    GIVEN("A VectorX with more than one item") {
        std::vector<std::string> vector;
        vector.push_back("foo");
        vector.push_back("bar");
        vector.push_back("baz");
        VectorX vectorx(vector);

        WHEN("joined with a delimeter") {
            std::string result = vectorx.join("; ");
            THEN("it is a string with the delimeter in between the items") {
                CHECK(result == "foo; bar; baz");
            }
        }
    }

    GIVEN("A vectorx with one item") {
        std::vector<std::string> vector;
        vector.push_back("foo");
        VectorX vectorx(vector);

        WHEN("joined with a delimeter") {
            std::string result = vectorx.join("; ");
            THEN("it the item in the original vector") {
                CHECK(result == "foo");
            }
        }
    }

    GIVEN("A vectorx with no items") {
        std::vector<std::string> vector;
        VectorX vectorx(vector);

        WHEN("joined with a delimeter") {
            std::string result = vectorx.join("; ");
            THEN("it is an empty string") {
                CHECK(result == "");
            }
        }
    }

    GIVEN("A vectorx with some items ending in a delimeter") {
        std::vector<std::string> vector;
        vector.push_back("foo/");
        vector.push_back("bar");
        vector.push_back("baz/");
        VectorX vectorx(vector);

        WHEN("terminated with a delimeter") {
            std::vector<std::string> result = vectorx.terminateEachWith("/");
            THEN("it adds the delimeter without duplicating it") {
                REQUIRE(result.size() == 3);
                CHECK(result[0] == "foo/");
                CHECK(result[1] == "bar/");
                CHECK(result[2] == "baz/");
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
            std::vector<std::string> result = vectorx.unique();
            THEN("it de-duplicates") {
                REQUIRE(result.size() == 2);
                CHECK(result[0] == "bar");
                CHECK(result[1] == "foo");
            }
        }
    }
}

} // namespace amm
