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
#include <vector>
#include <algorithm>

#include "stringx.h"
#include "vectorx.h"
#include "desktop_file_categories.h"

amm::desktop_file_categories::desktop_file_categories()
{
	_raw = "";
}


amm::desktop_file_categories::desktop_file_categories(std::string raw)
{
	_raw = raw;

	parse();
	sort();
}

void
amm::desktop_file_categories::parse()
{
	_categories = amm::stringx(_raw).split(";");
}

void
amm::desktop_file_categories::sort()
{
	std::sort(_categories.begin(), _categories.end());
}

bool
amm::desktop_file_categories::is_a(std::string type) const
{
	return std::binary_search(_categories.begin(), _categories.end(), type);
}

std::vector<std::string>
amm::desktop_file_categories::categories() const
{
	return _categories;
}

std::ostream&
amm::operator << (std::ostream& stream, const amm::desktop_file_categories& categories)
{
	stream << amm::vectorx(categories.categories()).join("; ");
	return stream;
}
