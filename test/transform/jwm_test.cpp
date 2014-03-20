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

#include "../QUnit.hpp"

#include "../../src/desktop_file.h"
#include "../../src/menu_entry/jwm.h"
#include "../../src/transform/jwm.h"

namespace amm
{
	namespace transform
	{
		class jwm_test
		{
			QUnit::UnitTest qunit;

			void test_transform_for_jwm_converts_desktop_file_to_menu_entry_for_jwm()
			{
				QUNIT_IS_TRUE(true);
			}

		public:
			jwm_test(std::ostream &out, int verbose_level) : qunit(out, verbose_level) {}

			int run()
			{
				test_transform_for_jwm_converts_desktop_file_to_menu_entry_for_jwm();
				return qunit.errors();
			}

		};
	}
}

int main()
{
	return amm::transform::jwm_test(std::cerr, QUnit::normal).run();
}
