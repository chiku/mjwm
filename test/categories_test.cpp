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

		void test_categories_as_multimedia_if_tag_includes_AudioVideo()
		{
			categories categories("AudioVideo;Audio;Player;GTK;");
			QUNIT_IS_TRUE(categories.is_multimedia());
		}

		void test_categories_not_as_multimedia_if_tag_excludes_AudioVideo()
		{
			categories categories("Audio;Video;Player;GTK;");
			QUNIT_IS_FALSE(categories.is_multimedia());
		}

	public:
		categories_test(std::ostream &out, int verbose_level) : qunit(out, verbose_level) {}

		int run()
		{
			test_categories_as_multimedia_if_tag_includes_AudioVideo();
			test_categories_not_as_multimedia_if_tag_excludes_AudioVideo();
			return qunit.errors();
		}

	};
}

int main()
{
	return mjwm::categories_test(std::cerr, QUnit::normal).run();
}
