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

mjwm::categories::categories()
{
	_raw = "";

	_audiovideo  = false;
	_development = false;
	_education   = false;
	_game        = false;
	_graphics    = false;
	_network     = false;
	_office      = false;
	_science     = false;
	_settings    = false;
	_system      = false;
	_utility     = false;
}


mjwm::categories::categories(std::string raw)
{
	_raw = raw;

	parse();
	sort();
	interpret();
}

void
mjwm::categories::parse()
{
	std::string raw = _raw;
	unsigned int size = raw.length();

	if (size >= 1 && raw.at(size - 1) != DELIM.at(0)) {
		raw += DELIM;
	}

	unsigned long int start = 0U;
	unsigned long int end = raw.find(DELIM);

	while (end != std::string::npos) {
		_categories.push_back(raw.substr(start, end - start));
		start = end + DELIM.length();
		end = raw.find(DELIM, start);
	}
}

void
mjwm::categories::sort()
{
	std::sort(_categories.begin(), _categories.end());
}

void mjwm::categories::interpret()
{
	_audiovideo  = std::binary_search(_categories.begin(), _categories.end(), AUDIO_VIDEO);
	_development = std::binary_search(_categories.begin(), _categories.end(), DEVELOPMENT);
	_education   = std::binary_search(_categories.begin(), _categories.end(), EDUCATION);
	_game        = std::binary_search(_categories.begin(), _categories.end(), GAME);
	_graphics    = std::binary_search(_categories.begin(), _categories.end(), GRAPHICS);
	_network     = std::binary_search(_categories.begin(), _categories.end(), NETWORK);
	_office      = std::binary_search(_categories.begin(), _categories.end(), OFFICE);
	_science     = std::binary_search(_categories.begin(), _categories.end(), SCIENCE);
	_settings    = std::binary_search(_categories.begin(), _categories.end(), SETTINGS);
	_system      = std::binary_search(_categories.begin(), _categories.end(), SYSTEM);
	_utility     = std::binary_search(_categories.begin(), _categories.end(), UTILITY);
}

bool
mjwm::categories::is_audiovideo() const
{
	return _audiovideo;
}

bool
mjwm::categories::is_development() const
{
	return _development;
}

bool
mjwm::categories::is_education() const
{
	return _education;
}

bool
mjwm::categories::is_game() const
{
	return _game;
}

bool
mjwm::categories::is_graphics() const
{
	return _graphics;
}

bool
mjwm::categories::is_network() const
{
	return _network;
}

bool
mjwm::categories::is_office() const
{
	return _office;
}

bool
mjwm::categories::is_science() const
{
	return _science;
}

bool
mjwm::categories::is_settings() const
{
	return _settings;
}

bool
mjwm::categories::is_system() const
{
	return _system;
}

bool
mjwm::categories::is_utility() const
{
	return _utility;
}

std::ostream&
mjwm::operator << (std::ostream& stream, const mjwm::categories& categories)
{
	std::vector<std::string> container = categories._categories;

	for(std::vector<std::string>::iterator category = container.begin(); category != container.end(); ++category) {
		stream << *category << "; ";
	}

	return stream;
}
