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
#include <fstream>
#include <string>
#include <streambuf>
#include <algorithm>
#include <cstdlib>

#include "QUnit.hpp"

#include "../src/menu_group.h"

namespace mjwm
{
	class menu_group_test
	{
		QUnit::UnitTest qunit;
		std::string _fixtures_directory;

		void setup()
		{
			char resolved_path[1024];
			realpath("fixtures", resolved_path);
			_fixtures_directory = resolved_path;
			_fixtures_directory += "/";
		}

		void test_menu_group_is_valid_when_created()
		{
			menu_group group(_fixtures_directory + "not-present/", "");
			QUNIT_IS_TRUE(group.is_valid());
		}

		void test_menu_group_has_error_when_scanning_absent_directory()
		{
			menu_group group(_fixtures_directory + "not-present/", "");
			group.populate();
			QUNIT_IS_FALSE(group.is_valid());
			assert_start_with(group.error(), "Couldn't open directory");
		}

		void test_menu_group_populates_entries_for_desktop_files()
		{
			menu_group group(_fixtures_directory + "desktop-files/", "");
			group.populate();
			QUNIT_IS_TRUE(group.is_valid());
			QUNIT_IS_EQUAL("", group.error());
		}

		void test_menu_group_has_error_when_no_desktop_files_exist_directory()
		{
			menu_group group(_fixtures_directory + "no-desktop-files/", "");
			group.populate();
			QUNIT_IS_FALSE(group.is_valid());
			assert_start_with(group.error(), "Doesn't have any valid .desktop files");
		}

		bool start_with(std::string sentence, std::string fragment)
		{
			return std::mismatch(fragment.begin(), fragment.end(), sentence.begin()).first == fragment.end();
		}

		bool assert_start_with(std::string sentence, std::string fragment)
		{
			if (start_with(sentence, fragment)) {
				return true;
			} else {
				std::cout << "Sentence: >>" << sentence << "<<" << std::endl
				          << "Doesn't start with: >>" << fragment << "<<" << std::endl;
				return false;
			}
			return std::mismatch(fragment.begin(), fragment.end(), sentence.begin()).first == fragment.end();
		}


	public:
		menu_group_test(std::ostream &out, int verbose_level) : qunit(out, verbose_level) {}

		int run()
		{
			setup();
			test_menu_group_is_valid_when_created();
			test_menu_group_has_error_when_scanning_absent_directory();
			test_menu_group_populates_entries_for_desktop_files();
			test_menu_group_has_error_when_no_desktop_files_exist_directory();
			return qunit.errors();
		};
	};
}


int main()
{
	return mjwm::menu_group_test(std::cerr, QUnit::normal).run();
}
