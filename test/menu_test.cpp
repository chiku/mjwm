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
#include <algorithm>
#include <cstdio>

#include "QUnit.hpp"

#include "../src/menu.h"

namespace amm
{
	const std::string fixtures_directory = "test/fixtures/";

	// Verifies a collection of desktop files divided in subcategories
	class menu_test
	{
		QUnit::UnitTest qunit;

		void test_menu_loads_categories_from_colon_separated_lines()
		{
			std::vector<std::string> lines;
			lines.push_back("Accessories:Utility:accessories");
			lines.push_back("Games:Game:games");
			menu menu;

			menu.load_custom_categories(lines);
			std::vector<amm::subcategory> subcategories = menu.subcategories();

			QUNIT_IS_EQUAL(2, subcategories.size());
			QUNIT_IS_EQUAL("Accessories", subcategories[0].display_name());
			QUNIT_IS_EQUAL("Games", subcategories[1].display_name());
		}

		void test_menu_loads_categories_ignores_comments()
		{
			std::vector<std::string> lines;
			lines.push_back("# Comments");
			lines.push_back("Games:Game:games");
			lines.push_back("#More:comment:here");
			menu menu;

			menu.load_custom_categories(lines);
			std::vector<amm::subcategory> subcategories = menu.subcategories();

			QUNIT_IS_EQUAL(1, subcategories.size());
			QUNIT_IS_EQUAL("Games", subcategories[0].display_name());
		}

		void test_menu_loads_categories_ignores_entries_without_three_tokens()
		{
			std::vector<std::string> lines;
			lines.push_back("Accessories::accessories");
			lines.push_back("Game:Games");
			menu menu;

			menu.load_custom_categories(lines);
			std::vector<amm::subcategory> subcategories = menu.subcategories();

			QUNIT_IS_EQUAL(0, subcategories.size());
		}

		void test_menu_counts_total_desktop_files_parsed_successfully()
		{
			std::vector<std::string> files;
			files.push_back(fixtures_directory + "vlc.desktop");
			files.push_back(fixtures_directory + "mousepad.desktop");
			menu menu;

			menu.populate(files);

			QUNIT_IS_EQUAL(2, menu.total_parsed_files());
		}

		void test_menu_counts_total_unclassified_desktop_files_parsed_successfully()
		{
			std::vector<std::string> files;
			files.push_back(fixtures_directory + "unclassified.desktop");
			files.push_back(fixtures_directory + "mousepad.desktop");
			menu menu;

			menu.populate(files);

			QUNIT_IS_EQUAL(1, menu.total_unclassified_parsed_files());
		}

		void test_menu_has_a_list_of_unparsed_files()
		{
			std::vector<std::string> files;
			files.push_back(fixtures_directory + "vlc.desktop");
			files.push_back(fixtures_directory + "missing.desktop");
			menu menu;

			menu.populate(files);

			std::vector<std::string> unparsed_files = menu.unparsed_file_names();
			QUNIT_IS_EQUAL(1, unparsed_files.size());
			QUNIT_IS_EQUAL(fixtures_directory + "missing.desktop", unparsed_files[0]);
		}

		bool assert_start_with(std::string sentence, std::string fragment)
		{
			if (std::mismatch(fragment.begin(), fragment.end(), sentence.begin()).first == fragment.end()) {
				return true;
			} else {
				std::cout << "Sentence: >>" << sentence << "<<" << std::endl
				          << "Doesn't start with: >>" << fragment << "<<" << std::endl;
				return false;
			}
			return std::mismatch(fragment.begin(), fragment.end(), sentence.begin()).first == fragment.end();
		}

	public:
		menu_test(std::ostream &out, int verbose_level) : qunit(out, verbose_level) {}

		int run()
		{
			test_menu_loads_categories_from_colon_separated_lines();
			test_menu_loads_categories_ignores_comments();
			test_menu_loads_categories_ignores_entries_without_three_tokens();
			test_menu_counts_total_desktop_files_parsed_successfully();
			test_menu_counts_total_unclassified_desktop_files_parsed_successfully();
			test_menu_has_a_list_of_unparsed_files();
			return qunit.errors();
		}
	};
}


int main()
{
	return amm::menu_test(std::cerr, QUnit::normal).run();
}
