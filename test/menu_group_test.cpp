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
#include <cstdio>

#include "QUnit.hpp"

#include "../src/menu_group.h"

namespace amm
{
	const std::string fixtures_directory = "test/fixtures/";
	const std::string results_directory = "test/results/";
	const std::string all_proper_output = results_directory + "all-proper.output";
	const std::string all_proper_with_extension_output = results_directory + "all-proper-with-extension.output";
	const std::string unclassified_content_output = results_directory + "unclassified-content.output";

	// Verifies how a directory with FreeDesktop .desktop files is converted to a JWM menu section
	class menu_group_test
	{
		QUnit::UnitTest qunit;

		void setup()
		{
			std::remove(all_proper_output.c_str());
			std::remove(all_proper_with_extension_output.c_str());
			std::remove(unclassified_content_output.c_str());
		}

		void test_menu_group_is_valid_when_created()
		{
			std::vector<std::string> files;

			menu_group group(files, "");

			QUNIT_IS_TRUE(group.is_valid());
		}

		void test_menu_group_has_error_when_no_files_present()
		{
			std::vector<std::string> files;
			menu_group group(files, "");

			group.populate();

			QUNIT_IS_FALSE(group.is_valid());
			assert_start_with(group.error(), "No valid .desktop file found");
		}

		void test_menu_group_has_error_when_all_files_are_invalid()
		{
			std::vector<std::string> files;
			files.push_back(fixtures_directory + "missing.desktop");
			menu_group group(files, "");

			group.populate();

			QUNIT_IS_FALSE(group.is_valid());
			assert_start_with(group.error(), "No valid .desktop file found");
		}

		void test_menu_group_is_valid_for_proper_desktop_files()
		{
			std::vector<std::string> files;
			files.push_back(fixtures_directory + "vlc.desktop");
			files.push_back(fixtures_directory + "mousepad.desktop");
			menu_group group(files, "");

			group.populate();

			QUNIT_IS_TRUE(group.is_valid());
			QUNIT_IS_EQUAL("", group.error());
		}

		void test_menu_group_writes_populated_entries_to_file()
		{
			std::string output_file_name = all_proper_with_extension_output;
			std::vector<std::string> files;
			files.push_back(fixtures_directory + "vlc.desktop");
			files.push_back(fixtures_directory + "mousepad.desktop");
			menu_group group(files, "");

			group.populate();
			group.sort();
			group.write(output_file_name);

			std::string file_content = read_file(output_file_name);
			std::string expected_content = "\
<JWM>\n\
  <Menu label=\"Accessories\" icon=\"accessories\">\n\
    <Program label=\"Mousepad\" icon=\"accessories-text-editor\">mousepad %F</Program>\n\
  </Menu>\n\
  <Menu label=\"Multimedia\" icon=\"multimedia\">\n\
    <Program label=\"VLC media player\" icon=\"vlc\">/usr/bin/vlc --started-from-file %U</Program>\n\
  </Menu>\n\
</JWM>\n\
";
			QUNIT_IS_EQUAL(expected_content, file_content);
		}

		void test_menu_group_writes_populated_entries_with_extension_to_file()
		{
			std::string output_file_name = all_proper_with_extension_output;
			std::vector<std::string> files;
			files.push_back(fixtures_directory + "vlc.desktop");
			files.push_back(fixtures_directory + "mousepad.desktop");
			menu_group group(files, ".png");

			group.populate();
			group.sort();
			group.write(output_file_name);

			std::string file_content = read_file(output_file_name);
			std::string expected_content = "\
<JWM>\n\
  <Menu label=\"Accessories\" icon=\"accessories.png\">\n\
    <Program label=\"Mousepad\" icon=\"accessories-text-editor.png\">mousepad %F</Program>\n\
  </Menu>\n\
  <Menu label=\"Multimedia\" icon=\"multimedia.png\">\n\
    <Program label=\"VLC media player\" icon=\"vlc.png\">/usr/bin/vlc --started-from-file %U</Program>\n\
  </Menu>\n\
</JWM>\n\
";
			QUNIT_IS_EQUAL(expected_content, file_content);
		}

		void test_menu_group_writes_entries_not_belonging_to_a_known_category_to_end_of_the_file()
		{
			std::string output_file_name = all_proper_with_extension_output;
			std::vector<std::string> files;
			files.push_back(fixtures_directory + "unclassified.desktop");
			files.push_back(fixtures_directory + "mousepad.desktop");
			menu_group group(files, "");

			group.populate();
			group.sort();
			group.write(output_file_name);

			std::string file_content = read_file(output_file_name);
			std::string expected_content = "\
<JWM>\n\
  <Menu label=\"Accessories\" icon=\"accessories\">\n\
    <Program label=\"Mousepad\" icon=\"accessories-text-editor\">mousepad %F</Program>\n\
  </Menu>\n\
  <Menu label=\"Others\" icon=\"others\">\n\
    <Program label=\"Unclassified\" icon=\"unclassified\">unclassify</Program>\n\
  </Menu>\n\
</JWM>\n\
";
			QUNIT_IS_EQUAL(expected_content, file_content);
		}

		void test_menu_group_skips_files_that_are_missing_content()
		{
			std::string output_file_name = all_proper_with_extension_output;
			std::vector<std::string> files;
			files.push_back(fixtures_directory + "missing.desktop");
			menu_group group(files, "");

			group.populate();
			group.sort();
			group.write(output_file_name);

			QUNIT_IS_FALSE(group.is_valid());
			assert_start_with(group.error(), "No valid .desktop file found");
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

		std::string read_file(std::string output_file_name)
		{
			std::ifstream file(output_file_name.c_str());
			std::stringstream stream;
		    stream << file.rdbuf();
		    file.close();
		    return stream.str();
		}

	public:
		menu_group_test(std::ostream &out, int verbose_level) : qunit(out, verbose_level) {}

		int run()
		{
			test_menu_group_is_valid_when_created();
			test_menu_group_has_error_when_no_files_present();
			test_menu_group_has_error_when_all_files_are_invalid();
			test_menu_group_is_valid_for_proper_desktop_files();
			test_menu_group_writes_populated_entries_to_file();
			test_menu_group_writes_populated_entries_with_extension_to_file();
			test_menu_group_writes_entries_not_belonging_to_a_known_category_to_end_of_the_file();
			test_menu_group_skips_files_that_are_missing_content();
			return qunit.errors();
		};
	};
}


int main()
{
	return amm::menu_group_test(std::cerr, QUnit::normal).run();
}
