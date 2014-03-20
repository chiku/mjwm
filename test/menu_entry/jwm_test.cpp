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

#include "../QUnit.hpp"

#include "../../src/menu_entry/jwm.h"

namespace amm
{
	namespace menu_entry
	{
		class jwm_test
		{
			QUnit::UnitTest qunit;

			void test_menu_entry_serializes_to_an_output_stream()
			{
				amm::menu_entry::jwm jwm_menu_entry("VLC", "vlc.svg", "vlc");

				std::stringstream stream;
				stream << jwm_menu_entry;

				std::string expected = "<Program label=\"VLC\" icon=\"vlc.svg\">vlc</Program>";
				QUNIT_IS_EQUAL(expected, stream.str());
			}

		public:
			jwm_test(std::ostream &out, int verbose_level) : qunit(out, verbose_level) {}

			int run()
			{
				test_menu_entry_serializes_to_an_output_stream();
				return qunit.errors();
			}

		};
	}
}

int main()
{
	return amm::menu_entry::jwm_test(std::cerr, QUnit::normal).run();
}
