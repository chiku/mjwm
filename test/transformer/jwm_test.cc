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

#include "transformer/jwm.h"

#include "../doctest.h"
#include "representation/menu_start.h"
#include "representation/menu_end.h"
#include "representation/subcategory_start.h"
#include "representation/subcategory_end.h"
#include "representation/program.h"

namespace amm {

SCENARIO("transformer::Jwm") {
    GIVEN("A JWM transformer") {
        transformer::Jwm jwm_transformer;

        WHEN("transforming a menu-start representation") {
            representation::MenuStart menu_start;
            std::string result = jwm_transformer.transform(menu_start);

            THEN("it is a static message") {
                CHECK(result == "<JWM>\n    <!--Menu start-->");
            }
        }

        WHEN("transforming a menu-end representation") {
            representation::MenuEnd menu_end;
            std::string result = jwm_transformer.transform(menu_end);

            THEN("it is a static message") {
                CHECK(result == "    <!--Menu end-->\n</JWM>");
            }
        }

        WHEN("transforming a subcategory-start representation") {
            representation::SubcategoryStart subcategory_start("Application", "application.png");
            std::string result = jwm_transformer.transform(subcategory_start);

            THEN("it includes the subcategory name and icon") {
                CHECK(result == "    <Menu label=\"Application\" icon=\"application.png\">");
            }

            THEN("it XML escapes the name") {
                representation::SubcategoryStart subcategory_start("Fun & Games", "games.png");
                std::string result = jwm_transformer.transform(subcategory_start);
                CHECK(result == "    <Menu label=\"Fun &amp; Games\" icon=\"games.png\">");
            }
        }

        WHEN("transforming a subcategory-end representation") {
            representation::SubcategoryEnd subcategory_end("Application");
            std::string result = jwm_transformer.transform(subcategory_end);

            THEN("it includes the subcategory names in XML comments") {
                CHECK(result == "        <!--Application end-->\n    </Menu>");
            }
        }

        WHEN("transforming a menu-entry representation") {
            representation::Program program("Application", "application.png", "/usr/bin/application", "Application uses");
            std::string result = jwm_transformer.transform(program);

            THEN("it is a static message") {
                CHECK(result == "        <Program label=\"Application\" icon=\"application.png\">/usr/bin/application</Program>");
            }

            THEN("it XML escapes the name") {
                representation::Program program("Shoot & Run", "shooter.png", "/usr/bin/shooter", "First person shooter game");
                std::string result = jwm_transformer.transform(program);
                CHECK(result == "        <Program label=\"Shoot &amp; Run\" icon=\"shooter.png\">/usr/bin/shooter</Program>");
            }

            THEN("it removes field codes from the executable") {
                representation::Program program("Mousepad", "application-text-editor", "mousepad %F", "Simple Text Editor");
                std::string result = jwm_transformer.transform(program);
                CHECK(result == "        <Program label=\"Mousepad\" icon=\"application-text-editor\">mousepad</Program>");
            }
        }
    }
}

} // namespace amm
