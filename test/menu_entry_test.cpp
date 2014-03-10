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

#include "tpunit++.hpp"

#include "../src/menu_entry.h"

namespace mjwm
{
	struct menu_entry_test : tpunit::TestFixture
	{
		menu_entry_test() : tpunit::TestFixture(
			TEST(menu_entry_test::test_menu_entry_parses_name),
			TEST(menu_entry_test::test_menu_entry_parses_icon),
			TEST(menu_entry_test::test_menu_entry_parses_executable),
			TEST(menu_entry_test::test_menu_entry_parses_categories),
			TEST(menu_entry_test::test_menu_entry_escapes_tokens),
			TEST(menu_entry_test::test_menu_entry_parse_doesnt_fail_when_entry_is_missing),
			TEST(menu_entry_test::test_menu_entry_parse_doesnt_fail_when_line_is_missing),
			TEST(menu_entry_test::test_menu_entry_has_same_name_when_names_are_same),
			TEST(menu_entry_test::test_menu_entry_doesnt_have_same_name_when_names_are_different),
			TEST(menu_entry_test::test_menu_entry_is_valid_only_when_it_has_name_and_icon_and_executable),
			TEST(menu_entry_test::test_menu_entry_is_not_valid_without_name),
			TEST(menu_entry_test::test_menu_entry_is_not_valid_without_icon),
			TEST(menu_entry_test::test_menu_entry_is_not_valid_without_executable)
		) {}

		void test_menu_entry_parses_name()
		{
			menu_entry entry;
			entry.populate("Name=Mousepad\n");
			EXPECT_EQUAL("Mousepad", entry.name());
		}

		void test_menu_entry_parses_icon()
		{
			menu_entry entry;
			entry.populate("Icon=accessories-text-editor\n");
			EXPECT_EQUAL("accessories-text-editor", entry.icon());
		}

		void test_menu_entry_parses_executable()
		{
			menu_entry entry;
			entry.populate("Exec=mousepad %F\n");
			EXPECT_EQUAL("mousepad %F", entry.executable());
		}

		void test_menu_entry_parses_categories()
		{
			menu_entry entry;
			entry.populate("Categories=Application;Utility;TextEditor;GTK;\n");
			EXPECT_EQUAL("Application;Utility;TextEditor;GTK;", entry.categories());
		}

		void test_menu_entry_escapes_tokens()
		{
			menu_entry entry;
			entry.populate("Name=<'Complicated' & \"Fun\">\n");
			EXPECT_EQUAL("&lt;&apos;Complicated&apos; &amp; &quot;Fun&quot;&gt;", entry.name());
		}

		void test_menu_entry_parse_doesnt_fail_when_entry_is_missing()
		{
			menu_entry entry;
			entry.populate("Categories=");
			EXPECT_EQUAL("", entry.executable());
		}

		void test_menu_entry_parse_doesnt_fail_when_line_is_missing()
		{
			menu_entry entry;
			entry.populate("");
			EXPECT_EQUAL("", entry.name());
		}

		void test_menu_entry_has_same_name_when_names_are_same()
		{
			menu_entry first_entry, second_entry;
			first_entry.populate("Name=Mousepad\n");
			first_entry.populate("Icon=accessories-text-editor\n");
			second_entry.populate("Name=Mousepad\n");
			second_entry.populate("Icon=mousepad\n");
			EXPECT_TRUE(first_entry.has_same_name(second_entry));
		}

		void test_menu_entry_doesnt_have_same_name_when_names_are_different()
		{
			menu_entry first_entry, second_entry;
			first_entry.populate("Name=Mousepad\n");
			first_entry.populate("Icon=accessories-text-editor\n");
			second_entry.populate("Name=mousepad");
			second_entry.populate("Icon=accessories-text-editor\n");
			EXPECT_FALSE(first_entry.has_same_name(second_entry));
		}

		void test_menu_entry_is_valid_only_when_it_has_name_and_icon_and_executable()
		{
			menu_entry valid_entry;
			valid_entry.populate("Name=Mousepad\n");
			valid_entry.populate("Icon=accessories-text-editor\n");
			valid_entry.populate("Exec=mousepad %F\n");
			EXPECT_TRUE(valid_entry.is_valid());
		}

		void test_menu_entry_is_not_valid_without_name()
		{
			menu_entry missing_name_entry;
			missing_name_entry.populate("Icon=accessories-text-editor\n");
			missing_name_entry.populate("Exec=mousepad %F\n");
			EXPECT_FALSE(missing_name_entry.is_valid());
		}

		void test_menu_entry_is_not_valid_without_icon()
		{
			menu_entry missing_icon_entry;
			missing_icon_entry.populate("Name=Mousepad\n");
			missing_icon_entry.populate("Exec=mousepad %F\n");
			EXPECT_FALSE(missing_icon_entry.is_valid());
		}

		void test_menu_entry_is_not_valid_without_executable()
		{
			menu_entry missing_executable_entry;
			missing_executable_entry.populate("Name=Mousepad\n");
			missing_executable_entry.populate("Icon=accessories-text-editor\n");
			EXPECT_FALSE(missing_executable_entry.is_valid());
		}

	} __menu_entry_test;
}
