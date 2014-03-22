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

#include <iostream>
#include <string>
#include <sstream>

#include "QUnit.hpp"

#include "../src/menu_group.h"

namespace amm
{
	// Verifies how different sub-sections of menu would be constructed
	class menu_subcategory_test
	{
		QUnit::UnitTest qunit;

		void test_menu_subcategory_has_no_entries_before_desktop_files_are_added()
		{
			menu_subcategory menu_subcategory("Utilitiies", "Accessories", "accessories", ".png");
			QUNIT_IS_FALSE(menu_subcategory.has_entries());
		}

		void test_menu_subcategory_has_entries_after_a_desktop_file_is_added()
		{
			menu_subcategory menu_subcategory("Utilitiies", "Accessories", "accessories", ".png");
			menu_subcategory.add_desktop_file(mousepad_desktop_file());
			QUNIT_IS_TRUE(menu_subcategory.has_entries());
		}

		void test_menu_subcategory_is_serializable_to_output_stream()
		{
			menu_subcategory menu_subcategory("Utilitiies", "Accessories", "accessories", ".png");
			menu_subcategory.add_desktop_file(sakura_desktop_file());
			menu_subcategory.add_desktop_file(mousepad_desktop_file());
			std::stringstream stream;
			stream << menu_subcategory;

			std::string expected = "\
  <Menu label=\"Accessories\" icon=\"accessories.png\">\n\
    <Program label=\"Sakura\" icon=\"terminal-tango.png\">sakura</Program>\n\
    <Program label=\"Mousepad\" icon=\"accessories-text-editor.png\">mousepad %F</Program>\n\
  </Menu>\n\
";
			QUNIT_IS_EQUAL(expected, stream.str());
		}

		void test_menu_subcategory_sort_arranges_desktop_files_by_their_names_alphabetically()
		{
			menu_subcategory menu_subcategory("Utilitiies", "Accessories", "accessories", ".png");
			menu_subcategory.add_desktop_file(sakura_desktop_file());
			menu_subcategory.add_desktop_file(mousepad_desktop_file());
			menu_subcategory.sort_desktop_files();
			std::stringstream stream;
			stream << menu_subcategory;

			std::string expected = "\
  <Menu label=\"Accessories\" icon=\"accessories.png\">\n\
    <Program label=\"Mousepad\" icon=\"accessories-text-editor.png\">mousepad %F</Program>\n\
    <Program label=\"Sakura\" icon=\"terminal-tango.png\">sakura</Program>\n\
  </Menu>\n\
";
			QUNIT_IS_EQUAL(expected, stream.str());
		}

		desktop_file mousepad_desktop_file()
		{
			desktop_file mousepad;
			mousepad.populate("Name=Mousepad");
			mousepad.populate("Icon=accessories-text-editor");
			mousepad.populate("Exec=mousepad %F");
			mousepad.populate("Categories=Application;Utility;TextEditor;GTK;");
			return mousepad;
		}

		desktop_file sakura_desktop_file()
		{
			desktop_file sakura;
			sakura.populate("Name=Sakura");
			sakura.populate("Icon=terminal-tango");
			sakura.populate("Exec=sakura");
			sakura.populate("Categories=GTK;Utility;TerminalEmulator;System;");
			return sakura;
		}

	public:
		menu_subcategory_test(std::ostream &out, int verbose_level) : qunit(out, verbose_level) {}

		int run()
		{
			test_menu_subcategory_has_no_entries_before_desktop_files_are_added();
			test_menu_subcategory_has_entries_after_a_desktop_file_is_added();
			test_menu_subcategory_is_serializable_to_output_stream();
			test_menu_subcategory_sort_arranges_desktop_files_by_their_names_alphabetically();
			return qunit.errors();
		};
	};
}


int main()
{
	return amm::menu_subcategory_test(std::cerr, QUnit::normal).run();
}
