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

#include <iostream>
#include <string>
#include <vector>

#include "catch.hpp"
#include "QUnit.hpp"

#include "util.h"

SCENARIO("amm::StringX", "[stringx]") {
  GIVEN("A stringx with content") {
    amm::StringX stringx("vlc.desktop");

    WHEN("it has a sub-string at the end") {
      THEN("it ends with the substring") {
        REQUIRE(stringx.EndsWith(".desktop"));
      }

      THEN("it doesn't end with a substring present inside") {
        REQUIRE(!stringx.EndsWith(".desk"));
      }

      THEN("it doesn't ends with a superstring") {
        REQUIRE(!stringx.EndsWith("vlc.desktop file"));
      }
    }
  }

  GIVEN("A stringx without a terminating delimeters") {
    amm::StringX stringx("AudioVideo;GTK");

    WHEN("it is terminated with the delimeter") {
      std::string result = stringx.TerminateWith(";");
      THEN("it appends the delimeter to the stringx") {
        REQUIRE(result == "AudioVideo;GTK;");
      }
    }

    WHEN("it is split by the delimeter") {
      std::vector<std::string> result = stringx.Split(";");
      THEN("the the last token is included") {
        REQUIRE(result.size() == 2);
        REQUIRE(result[0] == "AudioVideo");
        REQUIRE(result[1] == "GTK");
      }
    }
  }

  GIVEN("A stringx with a terminating delimeters") {
    amm::StringX stringx("AudioVideo;GTK;");

    WHEN("it is terminated with the delimeter") {
      std::string result = stringx.TerminateWith(";");
      THEN("it doesn't duplicate the delimeter") {
        REQUIRE(result == "AudioVideo;GTK;");
      }
    }

    WHEN("it is split by the delimeter") {
      std::vector<std::string> result = stringx.Split(";");
      THEN("the original string becomes a list of tokens") {
        REQUIRE(result.size() == 2);
        REQUIRE(result[0] == "AudioVideo");
        REQUIRE(result[1] == "GTK");
      }
    }
  }

  GIVEN("A empty stringx") {
    amm::StringX stringx("");

    WHEN("it is terminated with the delimeter") {
      std::string result = stringx.TerminateWith(";");
      THEN("it adds a delimeter") {
        REQUIRE(result == ";");
      }
    }
  }

  GIVEN("A stringx with XML tags") {
    amm::StringX stringx("Icon=<\'foo\' & \"bar\">");

    WHEN("it is XML encoded") {
      std::string result = stringx.Encode();
      THEN("the XML tags are replaced by corresponding XML escpace sequences") {
        REQUIRE(result == "Icon=&lt;&apos;foo&apos; &amp; &quot;bar&quot;&gt;");
      }
    }
  }

  GIVEN("A stringx with whitespaces at extremes") {
    amm::StringX stringx(" \taccessories-text-editor \t\n");

    WHEN("it is trimmed") {
      std::string result = stringx.Trim();
      THEN("all whitespaces at the beginning and end are removed") {
        REQUIRE(result == "accessories-text-editor");
      }
    }
  }
}


SCENARIO("amm::VectorX", "[vectorx]") {
  GIVEN("A VectorX with more than one item") {
    std::vector<std::string> vector;
    vector.push_back("foo");
    vector.push_back("bar");
    vector.push_back("baz");
    amm::VectorX vectorx(vector);

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
    amm::VectorX vectorx(vector);

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
    amm::VectorX vectorx(vector);

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
      amm::VectorX vectorx(vector);

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
