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
#include <utility>
#include <algorithm>
#include <dirent.h>

#include "desktop_file.h"
#include "menu_group.h"

amm::qualified_desktop_file::qualified_desktop_file()
{
	menu_entries.reserve(NORMAL_RESERVE_SIZE);
}

amm::qualified_desktop_file::qualified_desktop_file(std::string name_to_display, std::string icon_name)
{
	pretty_name = name_to_display;
	icon = icon_name;
	menu_entries.reserve(NORMAL_RESERVE_SIZE);
}

amm::menu_group::menu_group(std::string directory_name, std::string icon_extension)
{
	_directory_name = directory_name;
	_icon_extension = icon_extension;
	_parsed = false;
	_unclassified_entries = amm::qualified_desktop_file("Others", "others");


	construct_menu_entries("Settings",    "Settings",    "settings");
	construct_menu_entries("Utility",     "Accessories", "accessories");
	construct_menu_entries("Development", "Development", "development");
	construct_menu_entries("Education",   "Education",   "education");
	construct_menu_entries("Game",        "Games",       "games");
	construct_menu_entries("Graphics",    "Graphics",    "graphics");
	construct_menu_entries("Network",     "Internet",    "internet");
	construct_menu_entries("AudioVideo",  "Multimedia",  "multimedia");
	construct_menu_entries("Office",      "Office",      "office");
	construct_menu_entries("Science",     "Science",     "science");
	construct_menu_entries("System",      "System",      "system");
}

void
amm::menu_group::construct_menu_entries(std::string name, std::string pretty_name, std::string icon)
{
	amm::qualified_desktop_file qualified_desktop_file = amm::qualified_desktop_file(pretty_name, icon);
	_menu_entries.push_back(std::make_pair(name, qualified_desktop_file));
}

void
amm::menu_group::populate()
{
	DIR *directory = opendir(_directory_name.c_str());

	if (!directory) {
		_error = "Couldn't open directory: " + _directory_name;
		return;
	}

	dirent *directory_entry;

	while((directory_entry = readdir(directory)) != NULL) {
		amm::desktop_file entry;
		std::string line;
		std::string desktop_filename = _directory_name + directory_entry->d_name;

		std::ifstream file(desktop_filename.c_str());
		if (!file.good()) {
			continue;
		}

		while (std::getline(file, line)) {
			entry.populate(line);
		}

		if (entry.is_valid()) {
			_parsed = true;
			if (!classify(entry)) {
				_unclassified_entries.menu_entries.push_back(entry);
			}
		}

		file.close();
	}
	closedir(directory);

	_menu_entries.push_back(std::make_pair("Others", _unclassified_entries));

	if (!_parsed) {
		_error = "Doesn't have any valid .desktop files: " + _directory_name;
	}
}

bool
amm::menu_group::classify(amm::desktop_file entry)
{
	amm::categories categories = entry.categories();
	bool classified = false;

	std::vector< std::pair<std::string, amm::qualified_desktop_file> >::iterator group;
	for (group = _menu_entries.begin(); group != _menu_entries.end(); ++group) {
		if (categories.is_a(group->first)) {
			classified = true;
			group->second.menu_entries.push_back(entry);
		}
	}

	return classified;
}

bool
amm::menu_group::is_valid() const
{
	return _error == "";
}

std::string
amm::menu_group::error() const
{
	return _error;
}

void
amm::menu_group::sort()
{
	std::vector< std::pair<std::string, amm::qualified_desktop_file> >::iterator group;
	for (group = _menu_entries.begin(); group != _menu_entries.end(); ++group) {
		std::sort(group->second.menu_entries.begin(), group->second.menu_entries.end());
	}
}

void
amm::menu_group::write(std::string output_filename)
{
	std::ofstream file(output_filename.c_str());

	file << "<JWM>" << std::endl;

	std::vector< std::pair<std::string, amm::qualified_desktop_file> >::iterator group;
	for (group = _menu_entries.begin(); group != _menu_entries.end(); ++group) {
		write(file, "label=\"" + group->second.pretty_name + "\" icon=\"" + group->second.icon + _icon_extension + "\"", group->second.menu_entries);
	}

	file << "</JWM>" << std::endl;

	file.close();
}

void
amm::menu_group::write(std::ofstream& file, std::string section, std::vector<amm::desktop_file> entries)
{
	if (entries.size() > 0) {
		file << "  <Menu " << section << ">" << std::endl;

		std::vector<amm::desktop_file>::iterator entry;
		for(entry = entries.begin(); entry != entries.end(); ++entry) {
			file << "    " << _jwm_transformer.transform(*entry, _icon_extension) << std::endl;
		}

		file << "  </Menu>" << std::endl;
	}
}
