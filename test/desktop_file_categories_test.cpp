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

#include "QUnit.hpp"

#include "../src/stringx.h"
#include "../src/desktop_file_categories.h"

namespace amm
{
	// Verifies what sub-section should a single desktop file entry belong to as per FreeDesktop guidelines
	class categories_test
	{
		QUnit::UnitTest qunit;

		void test_categories_as_audiovideo_if_tag_includes_AudioVideo()
		{
			desktop_file_categories categories("AudioVideo;Audio;Player;GTK;");
			QUNIT_IS_TRUE(categories.is_a("AudioVideo"));
		}

		void test_categories_not_as_audiovideo_if_tag_excludes_AudioVideo()
		{
			desktop_file_categories categories("Audio;Video;Player;GTK;");
			QUNIT_IS_FALSE(categories.is_a("AudioVideo"));
		}

		void test_categories_as_audiovideo_if_tag_includes_AudioVideo_without_trailing_semicolon()
		{
			desktop_file_categories categories("Video;AudioVideo");
			QUNIT_IS_TRUE(categories.is_a("AudioVideo"));
		}

		void test_categories_not_as_audiovideo_if_empty()
		{
			desktop_file_categories categories("");
			QUNIT_IS_FALSE(categories.is_a("AudioVideo"));
		}

		void test_categories_serializes_to_an_output_stream()
		{
			desktop_file_categories categories("AudioVideo;Player;GTK;");
			std::stringstream stream;
			stream << categories;
			QUNIT_IS_EQUAL("AudioVideo; GTK; Player; ", stream.str());
		}

	public:
		categories_test(std::ostream &out, int verbose_level) : qunit(out, verbose_level) {}

		int run()
		{
			test_categories_as_audiovideo_if_tag_includes_AudioVideo();
			test_categories_not_as_audiovideo_if_tag_excludes_AudioVideo();
			test_categories_as_audiovideo_if_tag_includes_AudioVideo_without_trailing_semicolon();
			test_categories_not_as_audiovideo_if_empty();
			test_categories_serializes_to_an_output_stream();
			return qunit.errors();
		}

	};
}

int main()
{
	return amm::categories_test(std::cerr, QUnit::normal).run();
}
