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
#include <vector>
#include <string>

#include "QUnit.hpp"

#include "desktop_file.h"
#include "subcategory.h"

namespace amm
{
	// Verifies a collection of desktop files belonging to the same category
	class subcategory_test
	{
		QUnit::UnitTest qunit;

		void test_subcategory_has_no_entries_before_desktop_files_are_added()
		{
			subcategory subcategory("Accessories", "accessories", "Utilities");
			QUNIT_IS_FALSE(subcategory.has_entries());
		}

		void test_subcategory_has_entries_after_a_desktop_file_is_added()
		{
			subcategory subcategory("Accessories", "accessories", "Utilities");
			subcategory.add_desktop_file(mousepad_desktop_file());
			QUNIT_IS_TRUE(subcategory.has_entries());
		}

		void test_subcategory_alphabetically_sorts_desktop_files_by_their_names()
		{
			subcategory subcategory("Accessories", "accessories", "Utilities");
			subcategory.add_desktop_file(sakura_desktop_file());
			subcategory.add_desktop_file(mousepad_desktop_file());
			subcategory.sort_desktop_files();

			std::vector<amm::desktop_file> desktop_files = subcategory.desktop_files();
			QUNIT_IS_EQUAL(2, desktop_files.size());
			QUNIT_IS_EQUAL("Mousepad", desktop_files[0].name());
			QUNIT_IS_EQUAL("Sakura", desktop_files[1].name());
		}

		desktop_file mousepad_desktop_file()
		{
			desktop_file entry;
			entry.populate("Name=Mousepad");
			entry.populate("Icon=accessories-text-editor");
			entry.populate("Exec=mousepad %F");
			entry.populate("Categories=Application;Utility;TextEditor;GTK;");
			return entry;
		}

		desktop_file sakura_desktop_file()
		{
			desktop_file entry;
			entry.populate("Name=Sakura");
			entry.populate("Icon=terminal-tango");
			entry.populate("Exec=sakura");
			entry.populate("Categories=GTK;Utility;TerminalEmulator;System;");
			return entry;
		}

	public:
		subcategory_test(std::ostream &out, int verbose_level) : qunit(out, verbose_level) {}

		int run()
		{
			test_subcategory_has_no_entries_before_desktop_files_are_added();
			test_subcategory_has_entries_after_a_desktop_file_is_added();
			test_subcategory_alphabetically_sorts_desktop_files_by_their_names();
			return qunit.errors();
		}
	};
}


int main()
{
	return amm::subcategory_test(std::cerr, QUnit::normal).run();
}
