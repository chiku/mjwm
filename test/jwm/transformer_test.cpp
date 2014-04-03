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

#include <iostream>

#include "../catch.hpp"

#include "representation.h"
#include "jwm/transformer.h"


SCENARIO("amm::transformer::Jwm", "[transformerjwm]") {
  GIVEN("A JWM transformer") {
    amm::transformer::jwm jwm_transformer;

    WHEN("transforming a menu-start representation") {
      amm::representation::menu_start menu_start;
      std::string result = jwm_transformer.transform(&menu_start);

      THEN("it gives static message") {
        REQUIRE(result == "<JWM>\n<!--Menu start-->");
      }
    }

    WHEN("transforming a menu-end representation") {
      amm::representation::menu_end menu_end;
      std::string result = jwm_transformer.transform(&menu_end);

      THEN("it gives static message") {
        REQUIRE(result == "<!--Menu end-->\n</JWM>");
      }
    }

    WHEN("transforming a subcategory-start representation") {
      amm::representation::subcategory_start subcategory_start("Application", "application.png");
      std::string result = jwm_transformer.transform(&subcategory_start);

      THEN("it includes the subcategory name and icon") {
        REQUIRE(result == "    <Menu label=\"Application\" icon=\"application.png\">");
      }

      THEN("it XML excapes the name") {
        amm::representation::subcategory_start subcategory_start("Fun & Games", "games.png");
        std::string result = jwm_transformer.transform(&subcategory_start);
        REQUIRE(result == "    <Menu label=\"Fun &amp; Games\" icon=\"games.png\">");
      }
    }

    WHEN("transforming a subcategory-end representation") {
      amm::representation::subcategory_end subcategory_end("Application");
      std::string result = jwm_transformer.transform(&subcategory_end);

      THEN("it includes the subcategory names in XML comments") {
        REQUIRE(result == "    <!--Application end-->\n    </Menu>");
      }
    }

    WHEN("transforming a menu-entry representation") {
      amm::representation::menu_entry menu_entry("Application", "application.png", "/usr/bin/application");
      std::string result = jwm_transformer.transform(&menu_entry);

      THEN("it gives static message") {
        REQUIRE(result == "        <Program label=\"Application\" icon=\"application.png\">/usr/bin/application</Program>");
      }

      THEN("it XML excapes the name") {
        amm::representation::menu_entry menu_entry("Shoot & Run", "shooter.png", "/usr/bin/shooter");
        std::string result = jwm_transformer.transform(&menu_entry);
        REQUIRE(result == "        <Program label=\"Shoot &amp; Run\" icon=\"shooter.png\">/usr/bin/shooter</Program>");
      }

      THEN("it removes field codes from the executable") {
        amm::representation::menu_entry menu_entry("Mousepad", "application-text-editor", "mousepad %F");
        std::string result = jwm_transformer.transform(&menu_entry);
        REQUIRE(result == "        <Program label=\"Mousepad\" icon=\"application-text-editor\">mousepad</Program>");
      }
    }
  }
}
