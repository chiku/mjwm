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

#include "../QUnit.hpp"

#include "../../src/icon_service.h"
#include "../../src/desktop_file.h"
#include "../../src/jwm/menu_entry.h"
#include "../../src/jwm/transformer.h"

namespace amm
{
	namespace jwm
	{
		// Verifies convertion of a FreeDesktop .desktop file into a Program entry in JWM configuration file
		class transformer_test
		{
			QUnit::UnitTest qunit;

			void test_jwm_transformer_converts_desktop_file_to_menu_entry_for_jwm()
			{
				amm::desktop_file desktop_file = desktop_file_fixture();

				amm::jwm::transformer transformer;
				amm::jwm::menu_entry jwm_menu_entry = transformer.transform(desktop_file);

				QUNIT_IS_EQUAL("VLC", jwm_menu_entry.name());
				QUNIT_IS_EQUAL("vlc", jwm_menu_entry.icon());
				QUNIT_IS_EQUAL("vlc", jwm_menu_entry.executable());
			}

			void test_jwm_transformer_appends_the_icon_extension_to_icon_name()
			{
				amm::desktop_file desktop_file = desktop_file_fixture();
				amm::icon_service icon_service;
				icon_service.register_extension(".svg");

				amm::jwm::transformer transformer;
				transformer.register_icon_service(icon_service);
				amm::jwm::menu_entry jwm_menu_entry = transformer.transform(desktop_file);

				QUNIT_IS_EQUAL("vlc.svg", jwm_menu_entry.icon());
			}

			void test_jwm_transformer_XML_escapes_name()
			{
				amm::desktop_file desktop_file = desktop_file_fixture();
				desktop_file.populate("Name=<\'foo\' & \"bar\">");

				amm::jwm::transformer transformer;
				amm::jwm::menu_entry jwm_menu_entry = transformer.transform(desktop_file);

				QUNIT_IS_EQUAL("&lt;&apos;foo&apos; &amp; &quot;bar&quot;&gt;", jwm_menu_entry.name());
			}

			void test_jwm_transformer_XML_escapes_icon()
			{
				amm::desktop_file desktop_file = desktop_file_fixture();
				desktop_file.populate("Icon=<\'foo\' & \"bar\">");

				amm::jwm::transformer transformer;
				amm::jwm::menu_entry jwm_menu_entry = transformer.transform(desktop_file);

				QUNIT_IS_EQUAL("&lt;&apos;foo&apos; &amp; &quot;bar&quot;&gt;", jwm_menu_entry.icon());
			}

			void test_jwm_transformer_doesnt_XML_escape_executable()
			{
				amm::desktop_file desktop_file = desktop_file_fixture();
				desktop_file.populate("Exec=vlc &");

				amm::jwm::transformer transformer;
				amm::jwm::menu_entry jwm_menu_entry = transformer.transform(desktop_file);

				QUNIT_IS_EQUAL("vlc &", jwm_menu_entry.executable());
			}

			void test_jwm_transformer_strips_field_codes_from_executable()
			{
				amm::desktop_file desktop_file = desktop_file_fixture();
				desktop_file.populate("Exec=foo %f %U bar");

				amm::jwm::transformer transformer;
				amm::jwm::menu_entry jwm_menu_entry = transformer.transform(desktop_file);

				QUNIT_IS_EQUAL("foo bar", jwm_menu_entry.executable());
			}

			amm::desktop_file desktop_file_fixture()
			{
				amm::desktop_file desktop_file;
				desktop_file.populate("Name=VLC");
				desktop_file.populate("Icon=vlc");
				desktop_file.populate("Exec=vlc");
				desktop_file.populate("Categories=AudioVideo;Audio;Video;");
				return desktop_file;
			}

		public:
			transformer_test(std::ostream &out, int verbose_level) : qunit(out, verbose_level) {}

			int run()
			{
				test_jwm_transformer_converts_desktop_file_to_menu_entry_for_jwm();
				test_jwm_transformer_appends_the_icon_extension_to_icon_name();
				test_jwm_transformer_XML_escapes_name();
				test_jwm_transformer_XML_escapes_icon();
				test_jwm_transformer_doesnt_XML_escape_executable();
				test_jwm_transformer_strips_field_codes_from_executable();
				return qunit.errors();
			}

		};
	}
}

int main()
{
	return amm::jwm::transformer_test(std::cerr, QUnit::normal).run();
}
