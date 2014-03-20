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
#include <algorithm>

#include "categories.h"

amm::categories::categories()
{
	_raw = "";
}


amm::categories::categories(std::string raw)
{
	_raw = raw;

	parse();
	sort();
}

void
amm::categories::parse()
{
	std::string raw = _raw;

	if ((raw.length() >= DELIM.length()) && (raw.compare(raw.length() - DELIM.length(), DELIM.length(), DELIM) != 0)) {
		raw += DELIM;
	}

	size_t start = 0U;
	size_t end = raw.find(DELIM);

	while (end != std::string::npos) {
		_categories.push_back(raw.substr(start, end - start));
		start = end + DELIM.length();
		end = raw.find(DELIM, start);
	}
}

void
amm::categories::sort()
{
	std::sort(_categories.begin(), _categories.end());
}

bool
amm::categories::is_a(std::string type) const
{
	return std::binary_search(_categories.begin(), _categories.end(), type);
}

std::ostream&
amm::operator << (std::ostream& stream, const amm::categories& categories)
{
	std::vector<std::string> container = categories._categories;

	for(std::vector<std::string>::iterator category = container.begin(); category != container.end(); ++category) {
		stream << *category << "; ";
	}

	return stream;
}
