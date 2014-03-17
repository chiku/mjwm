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
#include <map>
#include <algorithm>
#include <dirent.h>

#include "menu_entry.h"
#include "menu_group.h"

mjwm::menu_group::group::group()
{
	menu_entries.reserve(NORMAL_RESERVE_SIZE);
}

mjwm::menu_group::group::group(std::string name_to_display, std::string icon_name)
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

	_menu_entries["AudioVideo"]  = mjwm::menu_group::group("Multimedia",  "multimedia");
	_menu_entries["Development"] = mjwm::menu_group::group("Development", "development");
	_menu_entries["Education"]   = mjwm::menu_group::group("Education",   "education");
	_menu_entries["Game"]        = mjwm::menu_group::group("Games",       "games");
	_menu_entries["Graphics"]    = mjwm::menu_group::group("Graphics",    "graphics");
	_menu_entries["Network"]     = mjwm::menu_group::group("Internet",    "internet");
	_menu_entries["Office"]      = mjwm::menu_group::group("Office",      "office");
	_menu_entries["Settings"]    = mjwm::menu_group::group("Settings",    "settings");
	_menu_entries["Science"]     = mjwm::menu_group::group("Science",     "science");
	_menu_entries["System"]      = mjwm::menu_group::group("System",      "system");
	_menu_entries["Utility"]     = mjwm::menu_group::group("Accessories", "accessories");
	_menu_entries["Others"]      = mjwm::menu_group::group("Others",      "others");

	_category_names.push_back("Settings");
	_category_names.push_back("Utility");
	_category_names.push_back("Development");
	_category_names.push_back("Education");
	_category_names.push_back("Game");
	_category_names.push_back("Graphics");
	_category_names.push_back("Network");
	_category_names.push_back("AudioVideo");
	_category_names.push_back("Office");
	_category_names.push_back("Science");
	_category_names.push_back("System");
	_category_names.push_back("Others");
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
			classify(entry);
		}

		file.close();
	}
	closedir(directory);

	if (!_parsed) {
		_error = "Doesn't have any valid .desktop files: " + _directory_name;
	}
}

void
mjwm::menu_group::classify(mjwm::menu_entry entry)
{
	mjwm::categories categories = entry.categories();
	bool classified = false;

	for (std::map<std::string, mjwm::menu_group::group>::iterator group = _menu_entries.begin(); group != _menu_entries.end(); ++group) {
		if (categories.is_a(group->first)) {
			classified = true;
			_menu_entries[group->first].menu_entries.push_back(entry);
		}
	}

	if (!classified) {
		_menu_entries["Others"].menu_entries.push_back(entry);
	}
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
	for (std::map<std::string, mjwm::menu_group::group>::iterator group = _menu_entries.begin(); group != _menu_entries.end(); ++group) {
		std::sort(group->second.menu_entries.begin(), group->second.menu_entries.end());
	}
}

void
mjwm::menu_group::write(std::string output_filename)
{
	std::ofstream file(output_filename.c_str());

	for (std::vector<std::string>::iterator name = _category_names.begin(); name != _category_names.end(); ++name) {
		mjwm::menu_group::group group = _menu_entries[*name];
		write(file, "label=\"" + group.pretty_name + "\" icon=\"" + group.icon + "\"", group.menu_entries);
	}

	file.close();
}

void
mjwm::menu_group::write(std::ofstream& file, std::string section, std::vector<mjwm::menu_entry> entries)
{
	if (entries.size() > 0) {
		file << "        <Menu " << section << ">" << std::endl;
		for(std::vector<mjwm::menu_entry>::iterator entry = entries.begin(); entry != entries.end(); ++entry) {
			(*entry).write_to(file, _icon_extension);
		}
		file << "        </Menu>" << std::endl;
	}
}
