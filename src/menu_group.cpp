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

#include "menu_entry.h"
#include "menu_group.h"

mjwm::qualified_menu_entry::qualified_menu_entry()
{
	menu_entries.reserve(NORMAL_RESERVE_SIZE);
}

mjwm::qualified_menu_entry::qualified_menu_entry(std::string name_to_display, std::string icon_name)
{
	pretty_name = name_to_display;
	icon = icon_name;
	menu_entries.reserve(NORMAL_RESERVE_SIZE);
}

mjwm::menu_group::menu_group(std::string directory_name, std::string icon_extension)
{
	_directory_name = directory_name;
	_icon_extension = icon_extension;
	_parsed = false;
	_unclassified_entries = mjwm::qualified_menu_entry("Others", "others");


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
mjwm::menu_group::construct_menu_entries(std::string name, std::string pretty_name, std::string icon)
{
	std::pair<std::string, mjwm::qualified_menu_entry> entries;
	entries = std::make_pair(name, mjwm::qualified_menu_entry(pretty_name, icon));
	_menu_entries.push_back(entries);
}

void
mjwm::menu_group::populate()
{
	DIR *directory = opendir(_directory_name.c_str());

	if (!directory) {
		_error = "Couldn't open directory: " + _directory_name;
		return;
	}

	dirent *directory_entry;

	while((directory_entry = readdir(directory)) != NULL) {
		mjwm::menu_entry entry;
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
mjwm::menu_group::classify(mjwm::menu_entry entry)
{
	mjwm::categories categories = entry.categories();
	bool classified = false;

	std::vector< std::pair<std::string, mjwm::qualified_menu_entry> >::iterator group;
	for (group = _menu_entries.begin(); group != _menu_entries.end(); ++group) {
		if (categories.is_a(group->first)) {
			classified = true;
			group->second.menu_entries.push_back(entry);
		}
	}

	return classified;
}

bool
mjwm::menu_group::is_valid() const
{
	return _error == "";
}

std::string
mjwm::menu_group::error() const
{
	return _error;
}

void
mjwm::menu_group::sort()
{
	std::vector< std::pair<std::string, mjwm::qualified_menu_entry> >::iterator group;
	for (group = _menu_entries.begin(); group != _menu_entries.end(); ++group) {
		std::sort(group->second.menu_entries.begin(), group->second.menu_entries.end());
	}
}

void
mjwm::menu_group::write(std::string output_filename)
{
	std::ofstream file(output_filename.c_str());

	std::vector< std::pair<std::string, mjwm::qualified_menu_entry> >::iterator group;
	for (group = _menu_entries.begin(); group != _menu_entries.end(); ++group) {
		write(file, "label=\"" + group->second.pretty_name + "\" icon=\"" + group->second.icon + _icon_extension + "\"", group->second.menu_entries);
	}

	file.close();
}

void
mjwm::menu_group::write(std::ofstream& file, std::string section, std::vector<mjwm::menu_entry> entries)
{
	if (entries.size() > 0) {
		file << "        <Menu " << section << ">" << std::endl;

		std::vector<mjwm::menu_entry>::iterator entry;
		for(entry = entries.begin(); entry != entries.end(); ++entry) {
			file << "           <Program label=\"" << entry->name() << "\" icon=\"" << entry->icon() << _icon_extension << "\">" << entry->executable() << "</Program>" << std::endl;
		}

		file << "        </Menu>" << std::endl;
	}
}
