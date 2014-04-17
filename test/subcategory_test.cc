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

#include <vector>

#include "catch.hpp"
#include "desktop_entry.h"

namespace amm {

static DesktopEntry mousepad_desktop_entry() {
  DesktopEntry entry;
  entry.Populate("Name=Mousepad");
  entry.Populate("Icon=accessories-text-editor");
  entry.Populate("Exec=mousepad %F");
  entry.Populate("Categories=Application;Utility;TextEditor;GTK;");
  return entry;
}

static DesktopEntry sakura_desktop_entry() {
  DesktopEntry entry;
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
      subcategory.AddDesktopEntry(mousepad_desktop_entry());
      THEN("it has entries") {
        REQUIRE(subcategory.HasEntries());
      }
    }

    WHEN("with two desktop-file") {
      subcategory.AddDesktopEntry(sakura_desktop_entry());
      subcategory.AddDesktopEntry(mousepad_desktop_entry());
      WHEN("sorted") {
        subcategory.SortDesktopEntries();
        THEN("its entries in alphabetical order by name") {
          std::vector<DesktopEntry> desktop_entries = subcategory.DesktopEntries();
          REQUIRE(desktop_entries.size() == 2);
          REQUIRE(desktop_entries[0].Name() == "Mousepad");
          REQUIRE(desktop_entries[1].Name() == "Sakura");
        }
      }
    }

    WHEN("with a repeated desktop file") {
      subcategory.AddDesktopEntry(sakura_desktop_entry());
      subcategory.AddDesktopEntry(mousepad_desktop_entry());
      subcategory.AddDesktopEntry(sakura_desktop_entry());
      WHEN("sorted") {
        subcategory.SortDesktopEntries();
        THEN("it doesn't repeat entries") {
          std::vector<DesktopEntry> desktop_entries = subcategory.DesktopEntries();
          REQUIRE(desktop_entries.size() == 2);
          REQUIRE(desktop_entries[0].Name() == "Mousepad");
          REQUIRE(desktop_entries[1].Name() == "Sakura");
        }
      }
    }
  }
}

} // namespace amm
