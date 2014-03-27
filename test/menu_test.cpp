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
#include <vector>
#include <algorithm>

#include "QUnit.hpp"

#include "../src/menu.h"


namespace amm
{
	// Verifies a collection of desktop file entries
	class menu_test
	{
		QUnit::UnitTest qunit;

		void test_menu_gives_back_files_with_extension_desktop()
		{
			std::vector<std::string> directory_names;
			directory_names.push_back("test/fixtures/");
			amm::menu menu;
			menu.register_directories(directory_names);
			menu.resolve();

			std::vector<std::string> file_names = menu.desktop_file_names();

			assert_files_are_present_in_list(file_names);
		}

		void test_menu_ignores_repeated_input_directories()
		{
			std::vector<std::string> directory_names;
			directory_names.push_back("test/fixtures");
			directory_names.push_back("test/fixtures/");
			amm::menu menu;
			menu.register_directories(directory_names);
			menu.resolve();

			std::vector<std::string> file_names = menu.desktop_file_names();

			QUNIT_IS_EQUAL(4, file_names.size());
		}

		void test_menu_need_not_end_with_a_slash()
		{
			std::vector<std::string> directory_names;
			directory_names.push_back("test/fixtures");
			amm::menu menu;
			menu.register_directories(directory_names);
			menu.resolve();

			std::vector<std::string> file_names = menu.desktop_file_names();

			assert_files_are_present_in_list(file_names);
		}

		void test_menu_gives_back_files_when_one_directory_is_missing()
		{
			std::vector<std::string> directory_names;
			directory_names.push_back("test/fixtures");
			directory_names.push_back("test/does-not-exist");
			amm::menu menu;
			menu.register_directories(directory_names);
			menu.resolve();

			std::vector<std::string> file_names = menu.desktop_file_names();

			assert_files_are_present_in_list(file_names);
		}

		void test_menu_tracks_bad_paths_it_couldnt_open()
		{
			std::vector<std::string> directory_names;
			directory_names.push_back("test/fixtures");
			directory_names.push_back("test/does-not-exist");
			amm::menu menu;
			menu.register_directories(directory_names);
			menu.resolve();

			std::vector<std::string> bad_paths = menu.bad_paths();

			QUNIT_IS_EQUAL(1, bad_paths.size());
			QUNIT_IS_EQUAL("test/does-not-exist/",bad_paths[0]);
		}

		bool present_in(std::string item, std::vector<std::string> list)
		{
			return std::find(list.begin(), list.end(), item) != list.end();
		}

		void assert_files_are_present_in_list(std::vector<std::string> file_names)
		{
			QUNIT_IS_EQUAL(4, file_names.size());

			QUNIT_IS_TRUE(present_in("test/fixtures/missing.desktop", file_names));
			QUNIT_IS_TRUE(present_in("test/fixtures/mousepad.desktop", file_names));
			QUNIT_IS_TRUE(present_in("test/fixtures/unclassified.desktop", file_names));
			QUNIT_IS_TRUE(present_in("test/fixtures/vlc.desktop", file_names));
		}

	public:
		menu_test(std::ostream &out, int verbose_level) : qunit(out, verbose_level) {}

		int run()
		{
			test_menu_gives_back_files_with_extension_desktop();
			test_menu_ignores_repeated_input_directories();
			test_menu_need_not_end_with_a_slash();
			test_menu_gives_back_files_when_one_directory_is_missing();
			test_menu_tracks_bad_paths_it_couldnt_open();
			return qunit.errors();
		}

	};
}

int main()
{
	return amm::menu_test(std::cerr, QUnit::normal).run();
}
