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

#include "../stringx.h"
#include "../icon_service.h"
#include "../desktop_file.h"
#include "subcategory.h"
#include "menu.h"

amm::jwm::menu::menu()
{
	_total_parsed_files = 0;
	_total_unclassified_parsed_files = 0;
	_unclassified_subcategory = amm::jwm::subcategory("Others", "Others", "others", _icon_service);

	create_default_categories();
}

void
amm::jwm::menu::create_default_categories()
{
	_subcategories.clear();

	_subcategories.push_back(amm::jwm::subcategory("Settings",    "Settings",    "settings",    _icon_service));
	_subcategories.push_back(amm::jwm::subcategory("Utility",     "Accessories", "accessories", _icon_service));
	_subcategories.push_back(amm::jwm::subcategory("Development", "Development", "development", _icon_service));
	_subcategories.push_back(amm::jwm::subcategory("Education",   "Education",   "education",   _icon_service));
	_subcategories.push_back(amm::jwm::subcategory("Game",        "Games",       "games",       _icon_service));
	_subcategories.push_back(amm::jwm::subcategory("Graphics",    "Graphics",    "graphics",    _icon_service));
	_subcategories.push_back(amm::jwm::subcategory("Network",     "Internet",    "internet",    _icon_service));
	_subcategories.push_back(amm::jwm::subcategory("AudioVideo",  "Multimedia",  "multimedia",  _icon_service));
	_subcategories.push_back(amm::jwm::subcategory("Office",      "Office",      "office",      _icon_service));
	_subcategories.push_back(amm::jwm::subcategory("Science",     "Science",     "science",     _icon_service));
	_subcategories.push_back(amm::jwm::subcategory("System",      "System",      "system",      _icon_service));
}

void
amm::jwm::menu::register_icon_service(amm::icon_service icon_service)
{
	_icon_service = icon_service;
	for (std::vector<amm::jwm::subcategory>::iterator iter = _subcategories.begin(); iter != _subcategories.end(); ++iter) {
		iter->register_icon_service(_icon_service);
	}
	_unclassified_subcategory.register_icon_service(_icon_service);
}

void
amm::jwm::menu::load_categories(std::vector<std::string> lines)
{
	_subcategories.clear();

	for (std::vector<std::string>::const_iterator line = lines.begin(); line != lines.end(); ++line) {
		if ((*line)[0] != '#') {
			std::vector<std::string> tokens = amm::stringx(*line).split(":");
			if (tokens.size() >= 3 && tokens[0] != "" && tokens[1] != "" && tokens[2] != "") {
				amm::jwm::subcategory subcategory(tokens[0], tokens[1], tokens[2], _icon_service);
				_subcategories.push_back(subcategory);
			}
		}
	}
}

void
amm::jwm::menu::populate(std::vector<std::string> desktop_file_names)
{
	_unparsed_file_names.clear();

	std::vector<std::string>::iterator name;
	for (name = desktop_file_names.begin(); name != desktop_file_names.end(); ++name) {
		std::string line;
		amm::desktop_file desktop_file;
		std::ifstream file(name->c_str());

		if (file.good()) {
			while (std::getline(file, line)) {
				desktop_file.populate(line);
			}

			if (desktop_file.is_valid()) {
				classify(desktop_file);
			} else {
				_unparsed_file_names.push_back(*name);
			}

			file.close();
		}
	}

	_subcategories.push_back(_unclassified_subcategory);
}

void
amm::jwm::menu::classify(amm::desktop_file desktop_file)
{
	bool classified = false;
	amm::desktop_file_categories categories = desktop_file.categories();

	_total_parsed_files += 1;

	std::vector<amm::jwm::subcategory>::iterator subcategory;
	for (subcategory = _subcategories.begin(); subcategory != _subcategories.end(); ++subcategory) {
		if (categories.is_a(subcategory->classification_name())) {
			classified = true;
			subcategory->add_desktop_file(desktop_file);
		}
	}

	if (!classified) {
		_total_unclassified_parsed_files += 1;
		_unclassified_subcategory.add_desktop_file(desktop_file);
	}
}

std::vector<amm::jwm::subcategory>
amm::jwm::menu::subcategories() const
{
	return _subcategories;
}

size_t
amm::jwm::menu::total_parsed_files() const
{
	return _total_parsed_files;
}

size_t
amm::jwm::menu::total_unclassified_parsed_files() const
{
	return _total_unclassified_parsed_files;
}

std::vector<std::string>
amm::jwm::menu::unparsed_file_names() const
{
	return _unparsed_file_names;
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

	std::vector<amm::jwm::subcategory> menu_subcategories = menu.subcategories();
	std::vector<amm::jwm::subcategory>::iterator group;
	for (group = menu_subcategories.begin(); group != menu_subcategories.end(); ++group) {
		stream << *group;
	}

	stream << "</JWM>" << std::endl;

	return stream;
}
