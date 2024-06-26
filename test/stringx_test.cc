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
#include <vector>

#include "doctest.h"
#include "stringx.h"

namespace amm {
namespace stringx {

SCENARIO("stringx") {
    GIVEN("A stringx with content") {
        WHEN("it has a sub-string at the end") {
            THEN("it ends with the substring") {
                CHECK(stringx::endsWith("vlc.desktop", ".desktop"));
            }

            THEN("it doesn't end with a substring that is not at the end") {
                CHECK_FALSE(stringx::endsWith("vlc.desktop", ".desk"));
            }

            THEN("it doesn't ends with a superstring") {
                CHECK_FALSE(stringx::endsWith("vlc.desktop", "vlc.desktop file"));
            }
        }
    }

    GIVEN("A stringx without terminating delimeters") {
        WHEN("terminated with a delimeter") {
            std::string result = stringx::terminateWith("AudioVideo;GTK", ";");
            THEN("it appends the delimeter to itself") {
                CHECK(result == "AudioVideo;GTK;");
            }
        }

        WHEN("split by the delimeter") {
            std::vector<std::string> result = stringx::split("AudioVideo;GTK", ";");
            THEN("the last token is included") {
                REQUIRE(result.size() == 2);
                CHECK(result[0] == "AudioVideo");
                CHECK(result[1] == "GTK");
            }
        }
    }

    GIVEN("A stringx with a terminating delimeters") {
        WHEN("terminated with the delimeter") {
            std::string result = stringx::terminateWith("AudioVideo;GTK;", ";");
            THEN("it doesn't duplicate the delimeter") {
                CHECK(result == "AudioVideo;GTK;");
            }
        }

        WHEN("split by the delimeter") {
            std::vector<std::string> result = stringx::split("AudioVideo;GTK;", ";");
            THEN("the original string becomes a list of tokens") {
                REQUIRE(result.size() == 2);
                CHECK(result[0] == "AudioVideo");
                CHECK(result[1] == "GTK");
            }
        }
    }

    GIVEN("An empty stringx") {
        WHEN("terminated with a delimeter") {
            std::string result = stringx::terminateWith("", ";");
            THEN("it appends the delimeter to itself") {
                CHECK(result == ";");
            }
        }

        WHEN("split") {
            std::vector<std::string> result = stringx::split("", ";");
            THEN("it is empty") {
                CHECK(result.empty());
            }
        }
    }

    GIVEN("A stringx with XML tags") {
        WHEN("XML encoded") {
            std::string result = stringx::encode("Icon=<\'foo\' & \"bar\">");
            THEN("the XML tags are replaced by corresponding XML escpace sequences") {
                CHECK(result == "Icon=&lt;&apos;foo&apos; &amp; &quot;bar&quot;&gt;");
            }
        }
    }

    GIVEN("A stringx with whitespaces at extremes") {
        WHEN("trimmed") {
            std::string result = stringx::trim(" \taccessories-text-editor \t\n");
            THEN("all whitespaces at the beginning and in the end are removed") {
                CHECK(result == "accessories-text-editor");
            }
        }
    }
}

} // namespace stringx
} // namespace amm
