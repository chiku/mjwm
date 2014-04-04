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

#include "transformer/jwm.h"

#include <iostream>

#include "../catch.hpp"
#include "representation.h"

namespace amm {

SCENARIO("transformer::Jwm", "[transformerjwm]") {
  GIVEN("A JWM transformer") {
    transformer::Jwm jwm_transformer;

    WHEN("transforming a menu-start representation") {
      representation::MenuStart menu_start;
      std::string result = jwm_transformer.Transform(menu_start);

      THEN("it gives static message") {
        REQUIRE(result == "<JWM>\n<!--Menu start-->");
      }
    }

    WHEN("transforming a menu-end representation") {
      representation::MenuEnd menu_end;
      std::string result = jwm_transformer.Transform(menu_end);

      THEN("it gives static message") {
        REQUIRE(result == "<!--Menu end-->\n</JWM>");
      }
    }

    WHEN("transforming a subcategory-start representation") {
      representation::SubcategoryStart subcategory_start("Application", "application.png");
      std::string result = jwm_transformer.Transform(subcategory_start);

      THEN("it includes the subcategory name and icon") {
        REQUIRE(result == "    <Menu label=\"Application\" icon=\"application.png\">");
      }

      THEN("it XML excapes the name") {
        representation::SubcategoryStart subcategory_start("Fun & Games", "games.png");
        std::string result = jwm_transformer.Transform(subcategory_start);
        REQUIRE(result == "    <Menu label=\"Fun &amp; Games\" icon=\"games.png\">");
      }
    }

    WHEN("transforming a subcategory-end representation") {
      representation::SubcategoryEnd subcategory_end("Application");
      std::string result = jwm_transformer.Transform(subcategory_end);

      THEN("it includes the subcategory names in XML comments") {
        REQUIRE(result == "    <!--Application end-->\n    </Menu>");
      }
    }

    WHEN("transforming a menu-entry representation") {
      representation::Program program("Application", "application.png", "/usr/bin/application");
      std::string result = jwm_transformer.Transform(program);

      THEN("it gives static message") {
        REQUIRE(result == "        <Program label=\"Application\" icon=\"application.png\">/usr/bin/application</Program>");
      }

      THEN("it XML excapes the name") {
        representation::Program program("Shoot & Run", "shooter.png", "/usr/bin/shooter");
        std::string result = jwm_transformer.Transform(program);
        REQUIRE(result == "        <Program label=\"Shoot &amp; Run\" icon=\"shooter.png\">/usr/bin/shooter</Program>");
      }

      THEN("it removes field codes from the executable") {
        representation::Program program("Mousepad", "application-text-editor", "mousepad %F");
        std::string result = jwm_transformer.Transform(program);
        REQUIRE(result == "        <Program label=\"Mousepad\" icon=\"application-text-editor\">mousepad</Program>");
      }
    }
  }
}

} // namespace amm