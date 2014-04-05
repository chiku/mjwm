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

#include "service/icon_service.h"

#include <string>

#include "../catch.hpp"

namespace amm {
namespace service {

SCENARIO("IconService default", "[iconservice]") {
  GIVEN("An icon service without extension") {
    IconService service;

    WHEN("resolving a name") {
      std::string result = service.ResolvedName("mousepad");

      THEN("it gives back the name") {
        REQUIRE(result == "mousepad");
      }
    }
  }

  GIVEN("An icon service with extension") {
    IconService service;
    service.RegisterExtension(".png");

    WHEN("resolving a name without extension") {
      std::string result = service.ResolvedName("mousepad");

      THEN("it is gives back the name appended with extension") {
        REQUIRE(result == "mousepad.png");
      }
    }

    WHEN("resolving a name with .png extension") {
      std::string result = service.ResolvedName("mousepad.png");

      THEN("it doesn't duplicate the extension") {
        REQUIRE(result == "mousepad.png");
      }
    }

    WHEN("resolving a name with .svg extension") {
      std::string result = service.ResolvedName("mousepad.svg");

      THEN("it doesn't append the extension") {
        REQUIRE(result == "mousepad.svg");
      }
    }

    WHEN("resolving a name with .xpm extension") {
      std::string result = service.ResolvedName("mousepad.xpm");

      THEN("it doesn't append the extension") {
        REQUIRE(result == "mousepad.xpm");
      }
    }
  }
}

} // namespace service
} // namespace amm
