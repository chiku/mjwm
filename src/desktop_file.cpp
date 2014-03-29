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

#include "stringx.h"
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

std::vector<std::string>
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

bool
amm::desktop_file::is_a(std::string type) const
{
	return std::binary_search(_categories.begin(), _categories.end(), type);
}

void
amm::desktop_file::populate(std::string line)
{
	if (line[0] == '\0') {
		return;
	}

	std::string delim = "=";
	size_t location = line.find(delim);
	std::string first_part = line.substr(0, location);
	std::string second_part = line.substr(location + delim.length(), line.length());

	std::string trimmed_first_part = amm::stringx(first_part).trim();

	if (trimmed_first_part == NAME) {
		_name = amm::stringx(second_part).trim();
	} else if (trimmed_first_part == ICON) {
		_icon = amm::stringx(second_part).trim();
	} else if (trimmed_first_part == EXECUTABLE) {
		_executable = amm::stringx(second_part).trim();
	} else if (trimmed_first_part == CATEGORIES) {
		_categories = amm::stringx(amm::stringx(second_part).trim()).split(";");
		std::sort(_categories.begin(), _categories.end());
	}
}
