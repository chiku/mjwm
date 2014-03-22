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

#include "../src/messages.h"

namespace amm
{
	namespace messages
	{
		class test
		{
			QUnit::UnitTest qunit;

			void test_summary_includes_unparsed_files_when_present()
			{
				std::vector<std::string> unparsed_file_names;
				unparsed_file_names.push_back("missing-icon.desktop");
				unparsed_file_names.push_back("missing-exec.desktop");

				std::string summary = amm::messages::summary(100, 98, 2, unparsed_file_names);

				std::string expected;
				expected += "Total desktop files: 100\n";
				expected += "Valid desktop files: 98\n";
				expected += "Unclassified valid desktop files: 2\n";
				expected += "List of unparsed files: missing-icon.desktop missing-exec.desktop \n";
				QUNIT_IS_EQUAL(expected, summary);
			}

			void test_summary_doesnt_include_unparsed_files_when_absent()
			{
				std::vector<std::string> unparsed_file_names;

				std::string summary = amm::messages::summary(100, 100, 2, unparsed_file_names);

				std::string expected;
				expected += "Total desktop files: 100\n";
				expected += "Valid desktop files: 100\n";
				expected += "Unclassified valid desktop files: 2\n";
				QUNIT_IS_EQUAL(expected, summary);
			}

		public:
			test(std::ostream &out, int verbose_level) : qunit(out, verbose_level) {}

			int run()
			{
				test_summary_includes_unparsed_files_when_present();
				test_summary_doesnt_include_unparsed_files_when_absent();
				return qunit.errors();
			}
		};
	}
}


int main()
{
	return amm::messages::test(std::cerr, QUnit::normal).run();
}
