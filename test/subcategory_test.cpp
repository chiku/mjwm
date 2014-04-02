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
#include <vector>

#include "catch.hpp"

#include "desktop_file.h"
#include "subcategory.h"

static amm::DesktopFile mousepad_desktop_file()
{
  amm::DesktopFile entry;
  entry.Populate("Name=Mousepad");
  entry.Populate("Icon=accessories-text-editor");
  entry.Populate("Exec=mousepad %F");
  entry.Populate("Categories=Application;Utility;TextEditor;GTK;");
  return entry;
}

static amm::DesktopFile sakura_desktop_file()
{
  amm::DesktopFile entry;
  entry.Populate("Name=Sakura");
  entry.Populate("Icon=terminal-tango");
  entry.Populate("Exec=sakura");
  entry.Populate("Categories=GTK;Utility;TerminalEmulator;System;");
  return entry;
}

SCENARIO("amm::subcategory", "[subcategory]") {
  GIVEN("A subcategory") {
    amm::subcategory subcategory("Accessories", "accessories", "Utilities");

    WHEN("without desktop-files") {
      THEN("it has no entries") {
        REQUIRE(!subcategory.has_entries());
      }
    }

    WHEN("with one desktop-file") {
      subcategory.add_desktop_file(mousepad_desktop_file());
      THEN("it has entries") {
        REQUIRE(subcategory.has_entries());
      }
    }

    WHEN("with two desktop-file") {
      subcategory.add_desktop_file(sakura_desktop_file());
      subcategory.add_desktop_file(mousepad_desktop_file());
      WHEN("sorted") {
        subcategory.sort_desktop_files();
        THEN("its entries in alphabetical order by name") {
          std::vector<amm::DesktopFile> desktop_files = subcategory.desktop_files();
          REQUIRE(desktop_files.size() == 2);
          REQUIRE(desktop_files[0].name() == "Mousepad");
          REQUIRE(desktop_files[1].name() == "Sakura");
        }
      }
    }
  }
}
