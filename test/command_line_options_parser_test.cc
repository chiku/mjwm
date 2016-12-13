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

#include "command_line_options_parser.h"

#include <cstring>
#include <string>
#include <vector>

#include "doctest.h"

namespace amm {

SCENARIO("Command-line arguments default parse") {
    GIVEN("command line options") {
        std::string home = "/home/mjwm";
        std::string language = "hn";
        CommandLineOptionsParser parser(home, language);

        WHEN("parsing default") {
            char* argv[] = {strdup("amm"), 0};
            AmmOptions options = parser.parse(1, argv);

            THEN("the parsing succeeds") {
                CHECK(options.is_parsed);
            }

            THEN("it doesn't have deprecations") {
                CHECK(options.deprecations.empty());
            }

            THEN("its help flag is off") {
                CHECK_FALSE(options.is_help);
            }

            THEN("its version flag is off") {
                CHECK_FALSE(options.is_version);
            }

            THEN("its iconize flag is off") {
                CHECK_FALSE(options.is_iconize);
            }

            THEN("its backup flag is on") {
                CHECK(options.is_backup);
            }

            THEN("its icon theme is hicolor") {
                CHECK(options.icon_theme_name == "hicolor");
            }

            THEN("it retains its input directories") {
                CHECK_FALSE(options.override_default_directories);
            }

            THEN("its output file is '.jwmrc-mjwm' under $HOME") {
                CHECK(options.output_file_name == "/home/mjwm/.jwmrc-mjwm");
            }

            THEN("its input directories is empty") {
                CHECK(options.input_directory_names.empty());
            }

            THEN("its category file is empty") {
                CHECK(options.category_file_name == "");
            }

            THEN("its summary style is normal") {
                CHECK(options.summary_type == "normal");
            }

            THEN("its language is the supplied one") {
                CHECK(options.language == language);
            }
        }
    }
}

SCENARIO("Command-line arguments parse with options") {
    GIVEN("command line options") {
        std::string home = "/home/mjwm";
        std::string language = "hn";
        CommandLineOptionsParser parser(home, language);

        WHEN("parsing --help") {
            char* argv[] = {strdup("amm"), strdup("--help"), 0};
            AmmOptions options = parser.parse(2, argv);

            THEN("its help flag is on") {
                CHECK(options.is_help);
            }
        }

        WHEN("parsing --version") {
            char* argv[] = {strdup("amm"), strdup("--version"), 0};
            AmmOptions options = parser.parse(2, argv);

            THEN("its version flag is on") {
                CHECK(options.is_version);
            }
        }

        WHEN("parsing --iconize") {
            char* argv[] = {strdup("amm"), strdup("--iconize"), 0};
            AmmOptions options = parser.parse(2, argv);

            THEN("its iconize flag is on") {
                CHECK(options.is_iconize);
            }
        }

        WHEN("parsing --iconize=[ICON]") {
            char* argv[] = {strdup("amm"), strdup("--iconize=Faenza"), 0};
            AmmOptions options = parser.parse(2, argv);

            THEN("its iconize flag is on") {
                CHECK(options.is_iconize);
            }

            THEN("its icon theme is Faenza") {
                CHECK(options.icon_theme_name == "Faenza");
            }
        }

        WHEN("parsing --verbose") {
            char* argv[] = {strdup("amm"), strdup("--verbose"), 0};
            AmmOptions options = parser.parse(2, argv);

            THEN("its summary is set to long") {
                CHECK(options.summary_type == "long");
            }
        }

        WHEN("parsing -v") {
            char* argv[] = {strdup("amm"), strdup("-v"), 0};
            AmmOptions options = parser.parse(2, argv);

            THEN("its summary is set to long") {
                CHECK(options.summary_type == "long");
            }
        }

        WHEN("parsing --no-backup") {
            char* argv[] = {strdup("amm"), strdup("--no-backup"), 0};
            AmmOptions options = parser.parse(2, argv);

            THEN("its backup is off") {
                CHECK_FALSE(options.is_backup);
            }
        }

        WHEN("parsing --output-file [FILE]") {
            char* argv[] = {strdup("amm"), strdup("--output-file"), strdup("menu.out"), 0};
            AmmOptions options = parser.parse(3, argv);

            THEN("its output-file is set to the given value") {
                CHECK(options.output_file_name == "menu.out");
            }
        }

        WHEN("parsing -o [FILE]") {
            char* argv[] = {strdup("amm"), strdup("-o"), strdup("menu.out"), 0};
            AmmOptions options = parser.parse(3, argv);

            THEN("its output-file is set to the given value") {
                CHECK(options.output_file_name == "menu.out");
            }
        }

        WHEN("parsing --input-directory [DIRECTORY]") {
            char* argv[] = {strdup("amm"), strdup("--input-directory"), strdup("/usr/share/applications:/usr/local/share/applications"), 0};
            AmmOptions options = parser.parse(3, argv);

            THEN("its input-directories is set to the given values") {
                std::vector<std::string> input_directory_names = options.input_directory_names;

                REQUIRE(input_directory_names.size() == 2);
                CHECK(input_directory_names[0] == "/usr/share/applications");
                CHECK(input_directory_names[1] == "/usr/local/share/applications");
            }

            THEN("its marks that default directory are overridden") {
                CHECK(options.override_default_directories);
            }
        }

        WHEN("parsing -i [DIRECTORY]") {
            char* argv[] = {strdup("amm"), strdup("-i"), strdup("/usr/share/applications:/usr/local/share/applications"), 0};
            AmmOptions options = parser.parse(3, argv);

            THEN("its input-directories is set to the given values") {
                std::vector<std::string> input_directory_names = options.input_directory_names;

                REQUIRE(input_directory_names.size() == 2);
                CHECK(input_directory_names[0] == "/usr/share/applications");
                CHECK(input_directory_names[1] == "/usr/local/share/applications");
            }
        }

        WHEN("parsing --category-file [FILE]") {
            char* argv[] = {strdup("amm"), strdup("--category-file"), strdup("default.mjwm"), 0};
            AmmOptions options = parser.parse(3, argv);

            THEN("its category-file is set to the given value") {
                CHECK(options.category_file_name == "default.mjwm");
            }
        }

        WHEN("parsing -c [FILE]") {
            char* argv[] = {strdup("amm"), strdup("-c"), strdup("default.mjwm"), 0};
            AmmOptions options = parser.parse(3, argv);

            THEN("its category-file is set to the given value") {
                CHECK(options.category_file_name == "default.mjwm");
            }
        }

        WHEN("parsing --summary [SUMMARY-TYPE]") {
            char* argv[] = {strdup("amm"), strdup("--summary"), strdup("long"), 0};
            AmmOptions options = parser.parse(3, argv);

            THEN("its summary is set to long") {
                CHECK(options.summary_type == "long");
            }

            THEN("it has deprecations") {
                REQUIRE_FALSE(options.deprecations.empty());
                CHECK(options.deprecations[0] == "--summary [SUMMARY TYPE] is deprecated. Use -v for verbose output instead.");
            }
        }

        WHEN("parsing --language [LANGUAGE]") {
            char* argv[] = {strdup("amm"), strdup("--language"), strdup("bn"), 0};
            AmmOptions options = parser.parse(3, argv);

            THEN("its language is set to bn") {
                CHECK(options.language == "bn");
            }
        }
    }
}


SCENARIO("Command-line arguments parse failure") {
    GIVEN("command line options") {
        std::string home = "/home/mjwm";
        std::string language = "hn";
        CommandLineOptionsParser parser(home, language);

        WHEN("parsing a bad option") {
            char* argv[] = {strdup("amm"), strdup("--bad-option"), strdup("default.mjwm"), 0};
            AmmOptions options = parser.parse(3, argv);

            THEN("the parsing fails") {
                CHECK_FALSE(options.is_parsed);
            }
        }

        WHEN("parsing a missing mandatory option") {
            char* argv[] = {strdup("amm"), strdup("-c"), 0};
            AmmOptions options = parser.parse(2, argv);

            THEN("the parsing fails") {
                CHECK_FALSE(options.is_parsed);
            }
        }
    }
}

} // namespace amm
