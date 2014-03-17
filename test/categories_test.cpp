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

#include "../src/categories.h"


namespace mjwm
{
	class categories_test
	{
		QUnit::UnitTest qunit;

		void test_categories_as_audiovideo_if_tag_includes_AudioVideo()
		{
			categories categories("AudioVideo;Audio;Player;GTK;");
			QUNIT_IS_TRUE(categories.is_audiovideo());
		}

		void test_categories_not_as_audiovideo_if_tag_excludes_AudioVideo()
		{
			categories categories("Audio;Video;Player;GTK;");
			QUNIT_IS_FALSE(categories.is_audiovideo());
		}

		void test_categories_as_audiovideo_if_tag_includes_AudioVideo_without_trailing_semicolon()
		{
			categories categories("Video;AudioVideo");
			QUNIT_IS_TRUE(categories.is_audiovideo());
		}


		void test_categories_as_development_if_tag_includes_Development()
		{
			categories categories("Development;GTK;");
			QUNIT_IS_TRUE(categories.is_development());
		}

		void test_categories_not_as_development_if_tag_excludes_Development()
		{
			categories categories("GTK;");
			QUNIT_IS_FALSE(categories.is_development());
		}


		void test_categories_as_education_if_tag_includes_Education()
		{
			categories categories("Education;GTK;");
			QUNIT_IS_TRUE(categories.is_education());
		}

		void test_categories_not_as_education_if_tag_excludes_Education()
		{
			categories categories("GTK;");
			QUNIT_IS_FALSE(categories.is_education());
		}


		void test_categories_as_game_if_tag_includes_Game()
		{
			categories categories("Game;GTK;");
			QUNIT_IS_TRUE(categories.is_game());
		}

		void test_categories_not_as_game_if_tag_excludes_Game()
		{
			categories categories("GTK;");
			QUNIT_IS_FALSE(categories.is_game());
		}


		void test_categories_as_graphics_if_tag_includes_Graphics()
		{
			categories categories("Graphics;GTK:");
			QUNIT_IS_TRUE(categories.is_graphics());
		}

		void test_categories_not_as_graphics_if_tag_excludes_Graphics()
		{
			categories categories("GTK;");
			QUNIT_IS_FALSE(categories.is_graphics());
		}


		void test_categories_as_network_if_tag_includes_Network()
		{
			categories categories("Network;GTK:");
			QUNIT_IS_TRUE(categories.is_network());
		}

		void test_categories_not_as_network_if_tag_excludes_Network()
		{
			categories categories("GTK;");
			QUNIT_IS_FALSE(categories.is_network());
		}


		void test_categories_as_office_if_tag_includes_Office()
		{
			categories categories("Office;GTK:");
			QUNIT_IS_TRUE(categories.is_office());
		}

		void test_categories_not_as_office_if_tag_excludes_Office()
		{
			categories categories("GTK;");
			QUNIT_IS_FALSE(categories.is_office());
		}


		void test_categories_as_science_if_tag_includes_Science()
		{
			categories categories("Science;GTK:");
			QUNIT_IS_TRUE(categories.is_science());
		}

		void test_categories_not_as_science_if_tag_excludes_Science()
		{
			categories categories("GTK;");
			QUNIT_IS_FALSE(categories.is_science());
		}


		void test_categories_as_settings_if_tag_includes_Settings()
		{
			categories categories("Settings;GTK:");
			QUNIT_IS_TRUE(categories.is_settings());
		}

		void test_categories_not_as_settings_if_tag_excludes_Settings()
		{
			categories categories("GTK;");
			QUNIT_IS_FALSE(categories.is_settings());
		}


		void test_categories_as_system_if_tag_includes_System()
		{
			categories categories("System;GTK:");
			QUNIT_IS_TRUE(categories.is_system());
		}

		void test_categories_not_as_system_if_tag_excludes_System()
		{
			categories categories("GTK;");
			QUNIT_IS_FALSE(categories.is_system());
		}


		void test_categories_as_utility_if_tag_includes_Utility()
		{
			categories categories("Utility;GTK:");
			QUNIT_IS_TRUE(categories.is_utility());
		}

		void test_categories_not_as_utility_if_tag_excludes_Utility()
		{
			categories categories("GTK;");
			QUNIT_IS_FALSE(categories.is_utility());
		}

	public:
		categories_test(std::ostream &out, int verbose_level) : qunit(out, verbose_level) {}

		int run()
		{
			test_categories_as_audiovideo_if_tag_includes_AudioVideo();
			test_categories_not_as_audiovideo_if_tag_excludes_AudioVideo();
			test_categories_as_audiovideo_if_tag_includes_AudioVideo_without_trailing_semicolon();
			test_categories_as_development_if_tag_includes_Development();
			test_categories_not_as_development_if_tag_excludes_Development();
			test_categories_as_education_if_tag_includes_Education();
			test_categories_not_as_education_if_tag_excludes_Education();
			test_categories_as_game_if_tag_includes_Game();
			test_categories_not_as_game_if_tag_excludes_Game();
			test_categories_as_graphics_if_tag_includes_Graphics();
			test_categories_not_as_graphics_if_tag_excludes_Graphics();
			test_categories_as_network_if_tag_includes_Network();
			test_categories_not_as_network_if_tag_excludes_Network();
			test_categories_as_office_if_tag_includes_Office();
			test_categories_not_as_office_if_tag_excludes_Office();
			test_categories_as_science_if_tag_includes_Science();
			test_categories_not_as_science_if_tag_excludes_Science();
			test_categories_as_settings_if_tag_includes_Settings();
			test_categories_not_as_settings_if_tag_excludes_Settings();
			test_categories_as_system_if_tag_includes_System();
			test_categories_not_as_system_if_tag_excludes_System();
			test_categories_as_utility_if_tag_includes_Utility();
			test_categories_not_as_utility_if_tag_excludes_Utility();
			return qunit.errors();
		}

	};
}

int main()
{
	return mjwm::categories_test(std::cerr, QUnit::normal).run();
}
