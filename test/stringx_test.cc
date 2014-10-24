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

#include "stringx.h"

#include <string>
#include <vector>

#include "catch.hpp"

namespace amm {

SCENARIO("StringX", "[stringx]") {
    GIVEN("A stringx with content") {
        StringX stringx("vlc.desktop");

        WHEN("it has a sub-string at the end") {
            THEN("it ends with the substring") {
                REQUIRE(stringx.endsWith(".desktop"));
            }

            THEN("it doesn't end with a substring that is not at the end") {
                REQUIRE(!stringx.endsWith(".desk"));
            }

            THEN("it doesn't ends with a superstring") {
                REQUIRE(!stringx.endsWith("vlc.desktop file"));
            }
        }
    }

    GIVEN("A stringx without terminating delimeters") {
        StringX stringx("AudioVideo;GTK");

        WHEN("terminated with a delimeter") {
            std::string result = stringx.terminateWith(";");
            THEN("it appends the delimeter to itself") {
                REQUIRE(result == "AudioVideo;GTK;");
            }
        }

        WHEN("split by the delimeter") {
            std::vector<std::string> result = stringx.split(";");
            THEN("the last token is included") {
                REQUIRE(result.size() == 2);
                REQUIRE(result[0] == "AudioVideo");
                REQUIRE(result[1] == "GTK");
            }
        }
    }

    GIVEN("A stringx with a terminating delimeters") {
        StringX stringx("AudioVideo;GTK;");

        WHEN("terminated with the delimeter") {
            std::string result = stringx.terminateWith(";");
            THEN("it doesn't duplicate the delimeter") {
                REQUIRE(result == "AudioVideo;GTK;");
            }
        }

        WHEN("split by the delimeter") {
            std::vector<std::string> result = stringx.split(";");
            THEN("the original string becomes a list of tokens") {
                REQUIRE(result.size() == 2);
                REQUIRE(result[0] == "AudioVideo");
                REQUIRE(result[1] == "GTK");
            }
        }
    }

    GIVEN("An empty stringx") {
        StringX stringx("");

        WHEN("terminated with a delimeter") {
            std::string result = stringx.terminateWith(";");
            THEN("it appends the delimeter to itself") {
                REQUIRE(result == ";");
            }
        }

        WHEN("split") {
            std::vector<std::string> result = stringx.split(";");
            THEN("it is empty") {
                REQUIRE(result.empty());
            }
        }
    }

    GIVEN("A stringx with XML tags") {
        StringX stringx("Icon=<\'foo\' & \"bar\">");

        WHEN("XML encoded") {
            std::string result = stringx.encode();
            THEN("the XML tags are replaced by corresponding XML escpace sequences") {
                REQUIRE(result == "Icon=&lt;&apos;foo&apos; &amp; &quot;bar&quot;&gt;");
            }
        }
    }

    GIVEN("A stringx with whitespaces at extremes") {
        StringX stringx(" \taccessories-text-editor \t\n");

        WHEN("trimmed") {
            std::string result = stringx.trim();
            THEN("all whitespaces at the beginning and in the end are removed") {
                REQUIRE(result == "accessories-text-editor");
            }
        }
    }
}

} // namespace amm
