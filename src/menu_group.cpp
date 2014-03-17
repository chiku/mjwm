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
#include <algorithm>
#include <dirent.h>

#include "menu_entry.h"
#include "menu_group.h"

mjwm::menu_group::menu_group(std::string directory_name, std::string icon_extension)
{
	_directory_name = directory_name;
	_icon_extension = icon_extension;
	_parsed = false;

	_all_name_to_pretty_name["AudioVideo"]  = "Multimedia";
	_all_name_to_pretty_name["Development"] = "Development";
	_all_name_to_pretty_name["Education"]   = "Education";
	_all_name_to_pretty_name["Game"]        = "Games";
	_all_name_to_pretty_name["Graphics"]    = "Graphics";
	_all_name_to_pretty_name["Network"]     = "Internet";
	_all_name_to_pretty_name["Office"]      = "Office";
	_all_name_to_pretty_name["Science"]     = "Science";
	_all_name_to_pretty_name["Settings"]    = "Settings";
	_all_name_to_pretty_name["System"]      = "System";
	_all_name_to_pretty_name["Utility"]     = "Accessories";
	_all_name_to_pretty_name["Others"]      = "Others";

	_all_name_to_icon["AudioVideo"]  = "multimedia";
	_all_name_to_icon["Development"] = "development";
	_all_name_to_icon["Education"]   = "education";
	_all_name_to_icon["Game"]        = "games";
	_all_name_to_icon["Graphics"]    = "graphics";
	_all_name_to_icon["Network"]     = "internet";
	_all_name_to_icon["Office"]      = "office";
	_all_name_to_icon["Science"]     = "science";
	_all_name_to_icon["Settings"]    = "settings";
	_all_name_to_icon["System"]      = "system";
	_all_name_to_icon["Utility"]     = "accessories";
	_all_name_to_icon["Others"]      = "others";
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

	for (std::map<std::string, std::string>::iterator iter = _all_name_to_pretty_name.begin(); iter != _all_name_to_pretty_name.end(); ++iter) {
		if (categories.is_a(iter->first)) {
			classified = true;
			_all_name_to_menu_entry[iter->first].push_back(entry);
		}
	}

	if (!classified) {
		_all_name_to_menu_entry["Others"].push_back(entry);
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
	for (std::map<std::string, std::vector<mjwm::menu_entry> >::iterator iter = _all_name_to_menu_entry.begin(); iter != _all_name_to_menu_entry.end(); ++iter) {
		std::sort(iter->second.begin(), iter->second.end());
	}
}

void
mjwm::menu_group::write(std::string output_filename)
{
	std::ofstream file(output_filename.c_str());

	for (std::map<std::string, std::string>::iterator iter = _all_name_to_pretty_name.begin(); iter != _all_name_to_pretty_name.end(); ++iter) {
		write(file, "label=\"" + iter->second + "\" icon=\"" + _all_name_to_icon[iter->first] + "\"", _all_name_to_menu_entry[iter->first]);
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
