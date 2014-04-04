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

#include "subcategory.h"

#include <iostream>
#include <vector>

#include "catch.hpp"
#include "desktop_file.h"

namespace amm {

static DesktopFile mousepad_desktop_file() {
  DesktopFile entry;
  entry.Populate("Name=Mousepad");
  entry.Populate("Icon=accessories-text-editor");
  entry.Populate("Exec=mousepad %F");
  entry.Populate("Categories=Application;Utility;TextEditor;GTK;");
  return entry;
}

static DesktopFile sakura_desktop_file() {
  DesktopFile entry;
  entry.Populate("Name=Sakura");
  entry.Populate("Icon=terminal-tango");
  entry.Populate("Exec=sakura");
  entry.Populate("Categories=GTK;Utility;TerminalEmulator;System;");
  return entry;
}

SCENARIO("subcategory", "[subcategory]") {
  GIVEN("A subcategory") {
    Subcategory subcategory("Accessories", "accessories", "Utilities");

    WHEN("without desktop-files") {
      THEN("it has no entries") {
        REQUIRE(!subcategory.HasEntries());
      }
    }

    WHEN("with one desktop-file") {
      subcategory.AddDesktopFile(mousepad_desktop_file());
      THEN("it has entries") {
        REQUIRE(subcategory.HasEntries());
      }
    }

    WHEN("with two desktop-file") {
      subcategory.AddDesktopFile(sakura_desktop_file());
      subcategory.AddDesktopFile(mousepad_desktop_file());
      WHEN("sorted") {
        subcategory.SortDesktopFiles();
        THEN("its entries in alphabetical order by name") {
          std::vector<DesktopFile> desktop_files = subcategory.desktop_files();
          REQUIRE(desktop_files.size() == 2);
          REQUIRE(desktop_files[0].Name() == "Mousepad");
          REQUIRE(desktop_files[1].Name() == "Sakura");
        }
      }
    }
  }
}

} // namespace amm
