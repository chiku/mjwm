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

#include "../src/vectorx.h"

namespace amm
{
	namespace utils
	{
		class vectorx_test
		{
			QUnit::UnitTest qunit;

			void test_vectorx_joins_into_a_string_with_a_delimiter()
			{
				std::vector<std::string> vector;
				vector.push_back("foo");
				vector.push_back("bar");
				vector.push_back("baz");
				QUNIT_IS_EQUAL("foo; bar; baz; ", amm::vectorx(vector).join("; "));
			}

		public:
			vectorx_test(std::ostream &out, int verbose_level) : qunit(out, verbose_level) {}

			int run()
			{
				test_vectorx_joins_into_a_string_with_a_delimiter();
				return qunit.errors();
			}
		};
	}
}


int main()
{
	return amm::utils::vectorx_test(std::cerr, QUnit::normal).run();
}
