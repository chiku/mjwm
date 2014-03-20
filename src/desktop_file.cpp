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
#include <fstream>
#include <string>

#include "desktop_file.h"

static const std::string NAME       = "Name";
static const std::string EXECUTABLE = "Exec";
static const std::string ICON       = "Icon";
static const std::string CATEGORIES = "Categories";

amm::desktop_file::desktop_file() {}

std::string
amm::desktop_file::name() const
{
	return _name;
}

std::string
amm::desktop_file::icon() const
{
	return _icon;
}

std::string
amm::desktop_file::executable() const
{
	return _executable;
}

amm::categories
amm::desktop_file::categories() const
{
	return _categories;
}

bool
amm::desktop_file::operator < (const amm::desktop_file &other) const
{
	return name() < other.name();
}

bool
amm::desktop_file::operator > (const amm::desktop_file &other) const
{
	return name() > other.name();
}

bool
amm::desktop_file::operator == (const amm::desktop_file &other) const
{
	return name() == other.name();
}

bool
amm::desktop_file::operator != (const amm::desktop_file &other) const
{
	return name() != other.name();
}

bool
amm::desktop_file::is_valid() const
{
	return (executable().length() > 0) && (name().length() > 0) && (icon().length() > 0);
}

void
amm::desktop_file::populate(std::string line)
{
	if (line[0] == '\0') {
		return;
	}

	std::string delim = "=";
	unsigned long int location = line.find(delim);
	std::string first_part = line.substr(0, location);
	std::string second_part = line.substr(location + delim.length(), line.length());

	std::string trimmed_first_part = trim(first_part);

	if (trimmed_first_part == NAME) {
		_name = encode(trim(second_part));
	} else if (trimmed_first_part == ICON) {
		_icon = trim(second_part);
	} else if (trimmed_first_part == EXECUTABLE) {
		_executable = trim(second_part);
	} else if (trimmed_first_part == CATEGORIES) {
		_categories = amm::categories(trim(second_part));
	}
}

std::string
amm::desktop_file::trim(std::string input) const
{
	const std::string whitespace = " \t\n";
	const unsigned long int begin = input.find_first_not_of(whitespace);

	if (begin == std::string::npos) {
		return "";
	}

	const unsigned long int end = input.find_last_not_of(whitespace);
	const unsigned long int range = end - begin + 1;

	return input.substr(begin, range);
}

// based on http://stackoverflow.com/questions/5665231/most-efficient-way-to-escape-xml-html-in-c-string#answer-5665377
std::string
amm::desktop_file::encode(std::string data) const
{
	std::string buffer;
	buffer.reserve(data.size());
	for(size_t pos = 0; pos != data.size(); ++pos) {
		switch(data[pos]) {
			case '&' : buffer.append("&amp;");       break;
			case '\"': buffer.append("&quot;");      break;
			case '\'': buffer.append("&apos;");      break;
			case '<' : buffer.append("&lt;");        break;
			case '>' : buffer.append("&gt;");        break;
			default  : buffer.append(&data[pos], 1); break;
		}
	}
	return buffer;
}
