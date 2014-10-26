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

#include "command_line_options_parser.h"

#include <cstring>
#include <string>
#include <vector>

#include "catch.hpp"

namespace amm {

SCENARIO("CommandLineOptionsParser.parse() default", "[commandlineoptions]") {
	GIVEN("command line options") {
		std::string home = "/home/mjwm";
		CommandLineOptionsParser parser;

		WHEN("parsing default") {
			char* argv[] = {strdup("amm"), 0};
			AmmOptions options = parser.parse(1, argv, home);

			THEN("the parsing succeeds") {
				REQUIRE(options.is_parsed);
			}

			THEN("it doesn't have deprecations") {
				REQUIRE(options.deprecations.size() == 0);
			}

			THEN("its help flag is off") {
				REQUIRE(!options.is_help);
			}

			THEN("its version flag is off") {
				REQUIRE(!options.is_version);
			}

			THEN("its iconize flag is off") {
				REQUIRE(!options.is_iconize);
			}

			THEN("its icon theme is hicolor") {
				REQUIRE(options.icon_theme_name == "hicolor");
			}

			THEN("it retains its input directories") {
				REQUIRE(!options.override_default_directories);
			}

			THEN("its output file is '.jwmrc-mjwm' under $HOME") {
				REQUIRE(options.output_file_name == "/home/mjwm/.jwmrc-mjwm");
			}

			THEN("its input directories is empty") {
				REQUIRE(options.input_directory_names.size() == 0);
			}

			THEN("its category file is empty") {
				REQUIRE(options.category_file_name == "");
			}

			THEN("its summary style is normal") {
				REQUIRE(options.summary_type == "normal");
			}
		}
	}
}

SCENARIO("CommandLineOptionsParser.parse() flags", "[commandlineoptions]") {
	GIVEN("command line options") {
		std::string home = "/home/mjwm";
		CommandLineOptionsParser parser;

		WHEN("parsing --help") {
			char* argv[] = {strdup("amm"), strdup("--help"), 0};
			AmmOptions options = parser.parse(2, argv, home);

			THEN("its help flag is on") {
				REQUIRE(options.is_help);
			}
		}

		WHEN("parsing --version") {
			char* argv[] = {strdup("amm"), strdup("--version"), 0};
			AmmOptions options = parser.parse(2, argv, home);

			THEN("its version flag is on") {
				REQUIRE(options.is_version);
			}
		}

		WHEN("parsing --iconize") {
			char* argv[] = {strdup("amm"), strdup("--iconize"), 0};
			AmmOptions options = parser.parse(2, argv, home);

			THEN("its iconize flag is on") {
				REQUIRE(options.is_iconize);
			}
		}

		WHEN("parsing --iconize=Faenza") {
			char* argv[] = {strdup("amm"), strdup("--iconize=Faenza"), 0};
			AmmOptions options = parser.parse(2, argv, home);

			THEN("its iconize flag is on") {
				REQUIRE(options.is_iconize);
			}

			THEN("its icon theme is Faenza") {
				REQUIRE(options.icon_theme_name == "Faenza");
			}
		}
	}
}

SCENARIO("CommandLineOptionsParser.parse() options", "[commandlineoptions]") {
	GIVEN("command line options") {
		std::string home = "/home/mjwm";
		CommandLineOptionsParser parser;

		WHEN("parsing --output-file") {
			char* argv[] = {strdup("amm"), strdup("--output-file"), strdup("menu.out"), 0};
			AmmOptions options = parser.parse(3, argv, home);

			THEN("its output-file is set to the given value") {
				REQUIRE(options.output_file_name == "menu.out");
			}
		}

		WHEN("parsing -o") {
			char* argv[] = {strdup("amm"), strdup("-o"), strdup("menu.out"), 0};
			AmmOptions options = parser.parse(3, argv, home);

			THEN("its output-file is set to the given value") {
				REQUIRE(options.output_file_name == "menu.out");
			}
		}

		WHEN("parsing --input-directory") {
			char* argv[] = {strdup("amm"), strdup("--input-directory"), strdup("/usr/share/applications:/usr/local/share/applications"), 0};
			AmmOptions options = parser.parse(3, argv, home);

			THEN("its input-directories is set to the given values") {
				std::vector<std::string> input_directory_names = options.input_directory_names;

				REQUIRE(input_directory_names.size() == 2);
				REQUIRE(input_directory_names[0] == "/usr/share/applications");
				REQUIRE(input_directory_names[1] == "/usr/local/share/applications");
			}

			THEN("its marks that default directory are overridden") {
				REQUIRE(options.override_default_directories);
			}
		}

		WHEN("parsing -i") {
			char* argv[] = {strdup("amm"), strdup("-i"), strdup("/usr/share/applications:/usr/local/share/applications"), 0};
			AmmOptions options = parser.parse(3, argv, home);

			THEN("its input-directories is set to the given values") {
				std::vector<std::string> input_directory_names = options.input_directory_names;

				REQUIRE(input_directory_names.size() == 2);
				REQUIRE(input_directory_names[0] == "/usr/share/applications");
				REQUIRE(input_directory_names[1] == "/usr/local/share/applications");
			}
		}

		WHEN("parsing --category-file") {
			char* argv[] = {strdup("amm"), strdup("--category-file"), strdup("default.mjwm"), 0};
			AmmOptions options = parser.parse(3, argv, home);

			THEN("its category-file is set to the given value") {
				REQUIRE(options.category_file_name == "default.mjwm");
			}
		}

		WHEN("parsing -c") {
			char* argv[] = {strdup("amm"), strdup("-c"), strdup("default.mjwm"), 0};
			AmmOptions options = parser.parse(3, argv, home);

			THEN("its category-file is set to the given value") {
				REQUIRE(options.category_file_name == "default.mjwm");
			}
		}

		WHEN("parsing --summary long") {
			char* argv[] = {strdup("amm"), strdup("--summary"), strdup("long"), 0};
			AmmOptions options = parser.parse(3, argv, home);

			THEN("its summary is set to long") {
				REQUIRE(options.summary_type == "long");
			}
		}
	}
}


SCENARIO("CommandLineOptionsParser.parse() failure", "[commandlineoptions]") {
	GIVEN("command line options") {
		std::string home = "/home/mjwm";
		CommandLineOptionsParser parser;

		WHEN("parsing a bad option") {
			char* argv[] = {strdup("amm"), strdup("--bad-option"), strdup("default.mjwm"), 0};
			AmmOptions options = parser.parse(3, argv, home);

			THEN("the parsing fails") {
				REQUIRE(!options.is_parsed);
			}
		}

		WHEN("parsing a missing mandatory option") {
			char* argv[] = {strdup("amm"), strdup("-c"), 0};
			AmmOptions options = parser.parse(2, argv, home);

			THEN("the parsing fails") {
				REQUIRE(!options.is_parsed);
			}
		}
	}
}

} // namespace amm
