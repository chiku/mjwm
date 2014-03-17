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

	_groups["AudioVideo"]  = mjwm::menu_group::group("Multimedia",  "multimedia");
	_groups["Development"] = mjwm::menu_group::group("Development", "development");
	_groups["Education"]   = mjwm::menu_group::group("Education",   "education");
	_groups["Game"]        = mjwm::menu_group::group("Games",       "games");
	_groups["Graphics"]    = mjwm::menu_group::group("Graphics",    "graphics");
	_groups["Network"]     = mjwm::menu_group::group("Internet",    "internet");
	_groups["Office"]      = mjwm::menu_group::group("Office",      "office");
	_groups["Science"]     = mjwm::menu_group::group("Science",     "science");
	_groups["Settings"]    = mjwm::menu_group::group("Settings",    "settings");
	_groups["System"]      = mjwm::menu_group::group("System",      "system");
	_groups["Utility"]     = mjwm::menu_group::group("Accessories", "accessories");
	_groups["Others"]      = mjwm::menu_group::group("Others",      "others");
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

	for (std::map<std::string, mjwm::menu_group::group>::iterator iter = _groups.begin(); iter != _groups.end(); ++iter) {
		if (categories.is_a(iter->first)) {
			classified = true;
			_groups[iter->first].menu_entries.push_back(entry);
		}
	}

	if (!classified) {
		_groups["Others"].menu_entries.push_back(entry);
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
	for (std::map<std::string, mjwm::menu_group::group>::iterator iter = _groups.begin(); iter != _groups.end(); ++iter) {
		std::sort(iter->second.menu_entries.begin(), iter->second.menu_entries.end());
	}
}

void
mjwm::menu_group::write(std::string output_filename)
{
	std::ofstream file(output_filename.c_str());

	for (std::map<std::string, mjwm::menu_group::group>::iterator iter = _groups.begin(); iter != _groups.end(); ++iter) {
		write(file, "label=\"" + iter->second.pretty_name + "\" icon=\"" + iter->second.icon + "\"", iter->second.menu_entries);
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
