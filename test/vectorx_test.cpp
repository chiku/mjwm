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

#include "vectorx.h"

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
				QUNIT_IS_EQUAL("foo; bar; baz", amm::vectorx(vector).join("; "));
			}

			void test_vectorx_joins_into_vector_with_one_entry()
			{
				std::vector<std::string> vector;
				vector.push_back("foo");
				QUNIT_IS_EQUAL("foo", amm::vectorx(vector).join("; "));
			}

			void test_vectorx_joins_into_vector_with_no_entries()
			{
				std::vector<std::string> vector;
				QUNIT_IS_EQUAL("", amm::vectorx(vector).join("; "));
			}

			void test_vectorx_terminated_with_an_end_is_applied_to_all_elements()
			{
				std::vector<std::string> vector;
				vector.push_back("foo/");
				vector.push_back("bar");
				vector.push_back("baz/");

				std::vector<std::string> terminated_vector = amm::vectorx(vector).terminate_with("/");
				QUNIT_IS_EQUAL(3, terminated_vector.size());
				QUNIT_IS_EQUAL("foo/", terminated_vector[0]);
				QUNIT_IS_EQUAL("bar/", terminated_vector[1]);
				QUNIT_IS_EQUAL("baz/", terminated_vector[2]);
			}

			void test_vectorx_unique_removes_duplicates()
			{
				std::vector<std::string> vector;
				vector.push_back("foo");
				vector.push_back("bar");
				vector.push_back("foo");
				vector.push_back("bar");
				vector.push_back("bar");

				std::vector<std::string> unique_vector = amm::vectorx(vector).unique();
				QUNIT_IS_EQUAL(2, unique_vector.size());
				QUNIT_IS_EQUAL("bar", unique_vector[0]);
				QUNIT_IS_EQUAL("foo", unique_vector[1]);
			}

		public:
			vectorx_test(std::ostream &out, int verbose_level) : qunit(out, verbose_level) {}

			int run()
			{
				test_vectorx_joins_into_a_string_with_a_delimiter();
				test_vectorx_joins_into_vector_with_one_entry();
				test_vectorx_joins_into_vector_with_no_entries();
				test_vectorx_terminated_with_an_end_is_applied_to_all_elements();
				test_vectorx_unique_removes_duplicates();
				return qunit.errors();
			}
		};
	}
}


int main()
{
	return amm::utils::vectorx_test(std::cerr, QUnit::normal).run();
}
