/*
	This file is part of mjwm.
	Copyright (C) 2014  Chirantan Mitra <chirantan.mitra@gmail.com>

	This program is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software 0oundation, either version 3 of the License, or
	(at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <iostream>

#include "../QUnit.hpp"
#include "jwm/transformer.h"

namespace amm
{
	namespace jwm
	{
		// Verifies the conversion of representation into a JWM menu
		class transformer_test
		{
			QUnit::UnitTest qunit;

			void test_jwm_transformer_converts_menu_start_to_JWM_start_tag()
			{
				amm::representation::menu_start menu_start;
				amm::transformer::jwm jwm_transformer;
				QUNIT_IS_EQUAL("<JWM>\n<!--Menu start-->", jwm_transformer.transform(&menu_start));
			}

			void test_jwm_transformer_converts_menu_end_to_JWM_end_tag()
			{
				amm::representation::menu_end menu_end;
				amm::transformer::jwm jwm_transformer;
				QUNIT_IS_EQUAL("<!--Menu end-->\n</JWM>", jwm_transformer.transform(&menu_end));
			}

			void test_jwm_transformer_converts_subcategory_start_to_JWM_menu_start_tag()
			{
				amm::representation::subcategory_start subcategory_start("Application", "application.png");
				amm::transformer::jwm jwm_transformer;
				QUNIT_IS_EQUAL("  <Menu label=\"Application\" icon=\"application.png\">", jwm_transformer.transform(&subcategory_start));
			}

			void test_jwm_transformer_XML_escapes_subcategory_start_name()
			{
				amm::representation::subcategory_start subcategory_start("Fun & Games", "application.png");
				amm::transformer::jwm jwm_transformer;
				QUNIT_IS_EQUAL("  <Menu label=\"Fun &amp; Games\" icon=\"application.png\">", jwm_transformer.transform(&subcategory_start));
			}

			void test_jwm_transformer_converts_subcategory_end_to_JWM_menu_end_tag()
			{
				amm::representation::subcategory_end subcategory_end("Application");
				amm::transformer::jwm jwm_transformer;
				QUNIT_IS_EQUAL("  <!--Application end-->\n  </Menu>", jwm_transformer.transform(&subcategory_end));
			}

			void test_jwm_transformer_converts_menu_entry_to_JWM_propram_tag()
			{
				amm::representation::menu_entry menu_entry("Application", "application.png", "/usr/bin/application");
				amm::transformer::jwm jwm_transformer;
				QUNIT_IS_EQUAL("    <Program label=\"Application\" icon=\"application.png\">/usr/bin/application</Program>", jwm_transformer.transform(&menu_entry));
			}

			void test_jwm_transformer_XML_escapes_menu_entry_name()
			{
				amm::representation::menu_entry menu_entry("Fun & Games", "application.png", "/usr/bin/application");
				amm::transformer::jwm jwm_transformer;
				QUNIT_IS_EQUAL("    <Program label=\"Fun &amp; Games\" icon=\"application.png\">/usr/bin/application</Program>", jwm_transformer.transform(&menu_entry));
			}

		public:
			transformer_test(std::ostream &out, int verbose_level) : qunit(out, verbose_level) {}

			int run()
			{
				test_jwm_transformer_converts_menu_start_to_JWM_start_tag();
				test_jwm_transformer_converts_menu_end_to_JWM_end_tag();
				test_jwm_transformer_converts_subcategory_start_to_JWM_menu_start_tag();
				test_jwm_transformer_converts_subcategory_end_to_JWM_menu_end_tag();
				test_jwm_transformer_XML_escapes_subcategory_start_name();
				test_jwm_transformer_converts_menu_entry_to_JWM_propram_tag();
				test_jwm_transformer_XML_escapes_menu_entry_name();
				return qunit.errors();
			}

		};
	}
}

int main()
{
	return amm::jwm::transformer_test(std::cerr, QUnit::normal).run();
}
