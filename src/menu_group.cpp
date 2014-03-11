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
#include <cstdlib>
#include <dirent.h>

#include "menu_entry.h"
#include "menu_group.h"

mjwm::menu_group::menu_group(std::string directory_name, std::string icon_extension)
{
	_directory_name = directory_name;
	_icon_extension = icon_extension;
	_menu_entries.reserve(NORMAL_RESERVE_SIZE);
}

void
mjwm::menu_group::populate()
{
	DIR *directory = opendir(_directory_name.c_str());

	if (!directory) {
		std::cerr << "Couldn't open directory " << _directory_name << std::endl;
		exit(1);
	}

	mjwm::menu_entry entry = mjwm::menu_entry();
	dirent *directory_entry;
	std::string line;

	while((directory_entry = readdir(directory)) != NULL) {
		std::string desktop_filename = _directory_name + directory_entry->d_name;

		std::ifstream file(desktop_filename.c_str());
		if (!file.good()) {
			continue;
		}

		while (std::getline(file, line)) {
			entry.populate(line);
		}

		if (entry.is_valid()) {
			_menu_entries.push_back(entry);
		}

		file.close();
	}
	closedir(directory);

	if (_menu_entries.size() == 0) {
		std::cerr << _directory_name << " doesn't have any valid .desktop files" << std::endl;
		exit(1);
	}
}

void
mjwm::menu_group::sort()
{
	std::sort(_menu_entries.begin(), _menu_entries.end());
}

void
mjwm::menu_group::write(std::string output_filename)
{
	std::ofstream file(output_filename.c_str());

	for(std::vector<mjwm::menu_entry>::iterator entry = _menu_entries.begin(); entry != _menu_entries.end(); ++entry) {
		(*entry).write_to(file, _icon_extension);
	}

	file.close();
}
