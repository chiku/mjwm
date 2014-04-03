/*
  This file is part of mjwm.
  Copyright (C) 2014  Chirantan Mitra <chirantan.mitra@gmail.com>

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software 0oundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#define CATCH_CONFIG_MAIN

#include "command_line_options.h"

#include <cstring>
#include <iostream>
#include <string>
#include <vector>

#include "catch.hpp"

namespace amm {

SCENARIO("CommandLineOptions.Parse() default", "[commandlineoptions]") {
  GIVEN("command line options") {
    CommandLineOptions options;

    WHEN("parsing default") {
      char* argv[] = {strdup("amm"), 0};
      bool parse_result = options.Parse(1, argv);

      THEN("it has no deprecations") {
        REQUIRE(options.deprecations().size() == 0);
      }

      THEN("it is true") {
        REQUIRE(parse_result == true);
      }

      THEN("it help flag is off") {
        REQUIRE(!options.is_help());
      }

      THEN("its version flag is off") {
        REQUIRE(!options.is_version());
      }

      THEN("its output-file is 'automenu'") {
        REQUIRE(options.output_file_name() == "./automenu");
      }

      THEN("its input-directories is empty") {
        REQUIRE(options.input_directory_names().size() == 0);
      }

      THEN("its category file is empty") {
        REQUIRE(options.category_file_name() == "");
      }

      THEN("its icon-extenstion is empty") {
        REQUIRE(options.icon_extension() == "");
      }
    }
  }
}

SCENARIO("CommandLineOptions.Parse() flags", "[commandlineoptions]") {
  GIVEN("command line options") {
    CommandLineOptions options;

    WHEN("parsing --help") {
      char* argv[] = {strdup("amm"), strdup("--help"), 0};
      options.Parse(2, argv);

      THEN("its help flag is on") {
        REQUIRE(options.is_help());
      }
    }

    WHEN("parsing -h") {
      char* argv[] = {strdup("amm"), strdup("-h"), 0};
      options.Parse(2, argv);

      THEN("it help flag is on") {
        REQUIRE(options.is_help());
      }

      THEN("it has deprecations") {
        std::vector<std::string> deprecations = options.deprecations();
        REQUIRE(deprecations.size() == 1);
        REQUIRE(deprecations[0] == "-h is deprecated. Please use --help instead.");
      }
    }

    WHEN("parsing --version") {
      char* argv[] = {strdup("amm"), strdup("--version"), 0};
      options.Parse(2, argv);

      THEN("its version flag is on") {
        REQUIRE(options.is_version());
      }
    }

    WHEN("parsing -v") {
      char* argv[] = {strdup("amm"), strdup("-v"), 0};
      options.Parse(2, argv);

      THEN("it version flag is on") {
        REQUIRE(options.is_version());
      }

      THEN("it has deprecations") {
        std::vector<std::string> deprecations = options.deprecations();
        REQUIRE(deprecations.size() == 1);
        REQUIRE(deprecations[0] == "-v is deprecated. Please use --version instead.");
      }
    }

    WHEN("parsing --append-png") {
      char* argv[] = {strdup("amm"), strdup("--append-png"), 0};
      options.Parse(2, argv);

      THEN("it icon-extenstion is '.png'") {
        REQUIRE(options.icon_extension() == ".png");
      }
    }

    WHEN("parsing -a") {
      char* argv[] = {strdup("amm"), strdup("-a"), 0};
      options.Parse(2, argv);

      THEN("it icon-extenstion is '.png'") {
        REQUIRE(options.icon_extension() == ".png");
      }
    }
  }
}

SCENARIO("CommandLineOptions.Parse() options", "[commandlineoptions]") {
  GIVEN("command line options") {
    CommandLineOptions options;

    WHEN("parsing --output-file") {
      char* argv[] = {strdup("amm"), strdup("--output-file"), strdup("menu.out"), 0};
      options.Parse(3, argv);

      THEN("its output-file is set to the given value") {
        REQUIRE(options.output_file_name() == "menu.out");
      }
    }

    WHEN("parsing -o") {
      char* argv[] = {strdup("amm"), strdup("-o"), strdup("menu.out"), 0};
      options.Parse(3, argv);

      THEN("its output-file is set to the given value") {
        REQUIRE(options.output_file_name() == "menu.out");
      }
    }

    WHEN("parsing --input-directory") {
      char* argv[] = {strdup("amm"), strdup("--input-directory"), strdup("/usr/share/applications:/usr/local/share/applications"), 0};
      options.Parse(3, argv);

      THEN("its input-directories is set to the given values") {
        std::vector<std::string> input_directory_names = options.input_directory_names();

        REQUIRE(input_directory_names.size() == 2);
        REQUIRE(input_directory_names[0] == "/usr/share/applications");
        REQUIRE(input_directory_names[1] == "/usr/local/share/applications");
      }
    }

    WHEN("parsing -i") {
      char* argv[] = {strdup("amm"), strdup("-i"), strdup("/usr/share/applications:/usr/local/share/applications"), 0};
      options.Parse(3, argv);

      THEN("its input-directories is set to the given values") {
        std::vector<std::string> input_directory_names = options.input_directory_names();

        REQUIRE(input_directory_names.size() == 2);
        REQUIRE(input_directory_names[0] == "/usr/share/applications");
        REQUIRE(input_directory_names[1] == "/usr/local/share/applications");
      }
    }

    WHEN("parsing -s") {
      char* argv[] = {strdup("amm"), strdup("-s"), strdup("/usr/share/applications:/usr/local/share/applications"), 0};
      options.Parse(3, argv);

      THEN("its input-directories is set to the given values") {
        std::vector<std::string> input_directory_names = options.input_directory_names();

        REQUIRE(input_directory_names.size() == 2);
        REQUIRE(input_directory_names[0] == "/usr/share/applications");
        REQUIRE(input_directory_names[1] == "/usr/local/share/applications");
      }

      THEN("it has deprecations") {
        std::vector<std::string> deprecations = options.deprecations();
        REQUIRE(deprecations.size() == 1);
        REQUIRE(deprecations[0] == "-s is deprecated. Please use -i instead.");
      }
    }

    WHEN("parsing --category-file") {
      char* argv[] = {strdup("amm"), strdup("--category-file"), strdup("default.mjwm"), 0};
      options.Parse(3, argv);

      THEN("its category-file is set to the given value") {
        REQUIRE(options.category_file_name() == "default.mjwm");
      }
    }

    WHEN("parsing -c") {
      char* argv[] = {strdup("amm"), strdup("-c"), strdup("default.mjwm"), 0};
      options.Parse(3, argv);

      THEN("its category-file is set to the given value") {
        REQUIRE(options.category_file_name() == "default.mjwm");
      }
    }
  }
}


SCENARIO("CommandLineOptions.Parse() failure", "[commandlineoptions]") {
  GIVEN("command line options") {
    CommandLineOptions options;

    WHEN("parsing a bad option") {
      char* argv[] = {strdup("amm"), strdup("--bad-option"), strdup("default.mjwm"), 0};
      bool parse_result = options.Parse(3, argv);

      THEN("it is false") {
        REQUIRE(parse_result == false);
      }
    }

    WHEN("parsing a missing mandatory option") {
      char* argv[] = {strdup("amm"), strdup("-c"), 0};
      bool parse_result = options.Parse(2, argv);

      THEN("it is false") {
        REQUIRE(parse_result == false);
      }
    }
  }
}

} // namespace amm
