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
#include <vector>

#include "../desktop_file.h"
#include "subcategory.h"
#include "menu.h"

amm::jwm::menu::menu(std::vector<std::string> desktop_file_names, std::string icon_extension)
{
	_desktop_file_names = desktop_file_names;
	_icon_extension = icon_extension;
	_parsed = false;
	create_categories();
}

void
amm::jwm::menu::create_categories()
{
	_unclassified_subcategory = amm::jwm::subcategory("Others", "Others", "others", _icon_extension);

	_subcategories.push_back(amm::jwm::subcategory("Settings",    "Settings",    "settings",    _icon_extension));
	_subcategories.push_back(amm::jwm::subcategory("Utility",     "Accessories", "accessories", _icon_extension));
	_subcategories.push_back(amm::jwm::subcategory("Development", "Development", "development", _icon_extension));
	_subcategories.push_back(amm::jwm::subcategory("Education",   "Education",   "education",   _icon_extension));
	_subcategories.push_back(amm::jwm::subcategory("Game",        "Games",       "games",       _icon_extension));
	_subcategories.push_back(amm::jwm::subcategory("Graphics",    "Graphics",    "graphics",    _icon_extension));
	_subcategories.push_back(amm::jwm::subcategory("Network",     "Internet",    "internet",    _icon_extension));
	_subcategories.push_back(amm::jwm::subcategory("AudioVideo",  "Multimedia",  "multimedia",  _icon_extension));
	_subcategories.push_back(amm::jwm::subcategory("Office",      "Office",      "office",      _icon_extension));
	_subcategories.push_back(amm::jwm::subcategory("Science",     "Science",     "science",     _icon_extension));
	_subcategories.push_back(amm::jwm::subcategory("System",      "System",      "system",      _icon_extension));
}

void
amm::jwm::menu::populate()
{
	std::vector<std::string>::iterator name;
	for (name = _desktop_file_names.begin(); name != _desktop_file_names.end(); ++name) {
		std::string line;
		amm::desktop_file entry;
		std::ifstream file(name->c_str());

		if (!file.good()) {
			continue;
		}

		while (std::getline(file, line)) {
			entry.populate(line);
		}

		if (entry.is_valid()) {
			_parsed = true;
			if (!classify(entry)) {
				_unclassified_subcategory.add_desktop_file(entry);
			}
		}

		file.close();
	}

	_subcategories.push_back(_unclassified_subcategory);

	if (!_parsed) {
		_error = "No valid .desktop file found";
	}
}

bool
amm::jwm::menu::classify(amm::desktop_file entry)
{
	amm::desktop_file_categories categories = entry.categories();
	bool classified = false;

	std::vector<amm::jwm::subcategory>::iterator group;
	for (group = _subcategories.begin(); group != _subcategories.end(); ++group) {
		if (categories.is_a(group->classification_name())) {
			classified = true;
			group->add_desktop_file(entry);
		}
	}

	return classified;
}

bool
amm::jwm::menu::is_valid() const
{
	return _error == "";
}

std::string
amm::jwm::menu::error() const
{
	return _error;
}

void
amm::jwm::menu::sort()
{
	std::vector<amm::jwm::subcategory>::iterator group;
	for (group = _subcategories.begin(); group != _subcategories.end(); ++group) {
		group->sort_desktop_files();
	}
}

std::ostream&
amm::jwm::operator << (std::ostream& stream, const amm::jwm::menu& menu)
{
	stream << "<JWM>" << std::endl;

	std::vector<amm::jwm::subcategory> menu_subcategories = menu._subcategories;
	std::vector<amm::jwm::subcategory>::iterator group;
	for (group = menu_subcategories.begin(); group != menu_subcategories.end(); ++group) {
		stream << *group;
	}

	stream << "</JWM>" << std::endl;

	return stream;
}
