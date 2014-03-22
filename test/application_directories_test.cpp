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

#include "../src/application_directories.h"


namespace amm
{
	// Verifies what sub-section should a single desktop file entry belong to as per FreeDesktop guidelines
	class application_directories_test
	{
		QUnit::UnitTest qunit;

		void test_application_directories_gives_back_files_with_extension_desktop()
		{
			std::vector<std::string> directory_names;
			directory_names.push_back("test/fixtures/");

			std::vector<std::string> file_names = application_directories(directory_names).desktop_file_names();

			QUNIT_IS_EQUAL(4, file_names.size());

			QUNIT_IS_TRUE(present_in("test/fixtures/missing.desktop", file_names));
			QUNIT_IS_TRUE(present_in("test/fixtures/mousepad.desktop", file_names));
			QUNIT_IS_TRUE(present_in("test/fixtures/unclassified.desktop", file_names));
			QUNIT_IS_TRUE(present_in("test/fixtures/vlc.desktop", file_names));
		}

		void test_application_directories_need_not_end_with_a_slash()
		{
			std::vector<std::string> directory_names;
			directory_names.push_back("test/fixtures");

			std::vector<std::string> file_names = application_directories(directory_names).desktop_file_names();

			for (auto i = file_names.begin(); i != file_names.end(); ++i) {
				std::cout << *i << std::endl;
			}

			QUNIT_IS_EQUAL(4, file_names.size());

			QUNIT_IS_TRUE(present_in("test/fixtures/missing.desktop", file_names));
			QUNIT_IS_TRUE(present_in("test/fixtures/mousepad.desktop", file_names));
			QUNIT_IS_TRUE(present_in("test/fixtures/unclassified.desktop", file_names));
			QUNIT_IS_TRUE(present_in("test/fixtures/vlc.desktop", file_names));
		}

		bool present_in(std::string item, std::vector<std::string> list)
		{
			return std::find(list.begin(), list.end(), item) != list.end();
		}

	public:
		application_directories_test(std::ostream &out, int verbose_level) : qunit(out, verbose_level) {}

		int run()
		{
			test_application_directories_gives_back_files_with_extension_desktop();
			test_application_directories_need_not_end_with_a_slash();
			return qunit.errors();
		}

	};
}

int main()
{
	return amm::application_directories_test(std::cerr, QUnit::normal).run();
}
