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
				amm::desktop_file desktop_file = desktop_file_fixture();

				amm::transform::jwm transformer;
				amm::menu_entry::jwm jwm_menu_entry = transformer.transform(desktop_file, "");

				QUNIT_IS_EQUAL("VLC", jwm_menu_entry.name());
				QUNIT_IS_EQUAL("vlc", jwm_menu_entry.icon());
				QUNIT_IS_EQUAL("vlc", jwm_menu_entry.executable());
			}

			void test_transform_for_jwm_appends_the_icon_extension_to_icon_name()
			{
				amm::desktop_file desktop_file = desktop_file_fixture();

				amm::transform::jwm transformer;
				amm::menu_entry::jwm jwm_menu_entry = transformer.transform(desktop_file, ".svg");

				QUNIT_IS_EQUAL("vlc.svg", jwm_menu_entry.icon());
			}

			void test_transform_for_jwm_XML_escapes_name()
			{
				amm::desktop_file desktop_file = desktop_file_fixture();
				desktop_file.populate("Name=<\'foo\' & \"bar\">");

				amm::transform::jwm transformer;
				amm::menu_entry::jwm jwm_menu_entry = transformer.transform(desktop_file, "");

				QUNIT_IS_EQUAL("&lt;&apos;foo&apos; &amp; &quot;bar&quot;&gt;", jwm_menu_entry.name());
			}

			void test_transform_for_jwm_XML_escapes_icon()
			{
				amm::desktop_file desktop_file = desktop_file_fixture();
				desktop_file.populate("Icon=<\'foo\' & \"bar\">");

				amm::transform::jwm transformer;
				amm::menu_entry::jwm jwm_menu_entry = transformer.transform(desktop_file, "");

				QUNIT_IS_EQUAL("&lt;&apos;foo&apos; &amp; &quot;bar&quot;&gt;", jwm_menu_entry.icon());
			}

			void test_transform_for_jwm_XML_doesnt_escape_executable()
			{
				amm::desktop_file desktop_file = desktop_file_fixture();
				desktop_file.populate("Exec=vlc &");

				amm::transform::jwm transformer;
				amm::menu_entry::jwm jwm_menu_entry = transformer.transform(desktop_file, "");

				QUNIT_IS_EQUAL("vlc &", jwm_menu_entry.executable());
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
			jwm_test(std::ostream &out, int verbose_level) : qunit(out, verbose_level) {}

			int run()
			{
				test_transform_for_jwm_converts_desktop_file_to_menu_entry_for_jwm();
				test_transform_for_jwm_appends_the_icon_extension_to_icon_name();
				test_transform_for_jwm_XML_escapes_name();
				test_transform_for_jwm_XML_escapes_icon();
				test_transform_for_jwm_XML_doesnt_escape_executable();
				return qunit.errors();
			}

		};
	}
}

int main()
{
	return amm::transform::jwm_test(std::cerr, QUnit::normal).run();
}
