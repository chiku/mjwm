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

	_audiovideo_menu_entries.reserve(NORMAL_RESERVE_SIZE);
	_development_menu_entries.reserve(NORMAL_RESERVE_SIZE);
	_education_menu_entries.reserve(NORMAL_RESERVE_SIZE);
	_game_menu_entries.reserve(NORMAL_RESERVE_SIZE);
	_graphics_menu_entries.reserve(NORMAL_RESERVE_SIZE);
	_network_menu_entries.reserve(NORMAL_RESERVE_SIZE);
	_office_menu_entries.reserve(NORMAL_RESERVE_SIZE);
	_science_menu_entries.reserve(NORMAL_RESERVE_SIZE);
	_settings_menu_entries.reserve(NORMAL_RESERVE_SIZE);
	_system_menu_entries.reserve(NORMAL_RESERVE_SIZE);
	_utility_menu_entries.reserve(NORMAL_RESERVE_SIZE);
	_other_menu_entries.reserve(NORMAL_RESERVE_SIZE);
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

	if(categories.is_audiovideo()) {
		_audiovideo_menu_entries.push_back(entry);
	} else if(categories.is_development()) {
		_development_menu_entries.push_back(entry);
	} else if(categories.is_education()) {
		_education_menu_entries.push_back(entry);
	} else if(categories.is_game()) {
		_game_menu_entries.push_back(entry);
	} else if(categories.is_graphics()) {
		_graphics_menu_entries.push_back(entry);
	} else if(categories.is_network()) {
		_network_menu_entries.push_back(entry);
	} else if(categories.is_office()) {
		_office_menu_entries.push_back(entry);
	} else if(categories.is_science()) {
		_science_menu_entries.push_back(entry);
	} else if(categories.is_settings()) {
		_settings_menu_entries.push_back(entry);
	} else if(categories.is_system()) {
		_system_menu_entries.push_back(entry);
	} else if(categories.is_utility()) {
		_utility_menu_entries.push_back(entry);
	} else {
		_other_menu_entries.push_back(entry);
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
	std::sort(_audiovideo_menu_entries.begin(),  _audiovideo_menu_entries.end());
	std::sort(_development_menu_entries.begin(), _development_menu_entries.end());
	std::sort(_education_menu_entries.begin(),   _education_menu_entries.end());
	std::sort(_game_menu_entries.begin(),        _game_menu_entries.end());
	std::sort(_graphics_menu_entries.begin(),    _graphics_menu_entries.end());
	std::sort(_network_menu_entries.begin(),     _network_menu_entries.end());
	std::sort(_office_menu_entries.begin(),      _office_menu_entries.end());
	std::sort(_science_menu_entries.begin(),     _science_menu_entries.end());
	std::sort(_settings_menu_entries.begin(),    _settings_menu_entries.end());
	std::sort(_system_menu_entries.begin(),      _system_menu_entries.end());
	std::sort(_utility_menu_entries.begin(),     _utility_menu_entries.end());
	std::sort(_other_menu_entries.begin(),       _other_menu_entries.end());
}

void
mjwm::menu_group::write(std::string output_filename)
{
	std::ofstream file(output_filename.c_str());

	write(file, "label=\"Multimedia\" icon=\"multimedia\"",   _audiovideo_menu_entries);
	write(file, "label=\"Development\" icon=\"development\"", _development_menu_entries);
	write(file, "label=\"Educaction\" icon=\"education\"",    _education_menu_entries);
	write(file, "label=\"Games\" icon=\"games\"",             _game_menu_entries);
	write(file, "label=\"Graphics\" icon=\"graphics\"",       _graphics_menu_entries);
	write(file, "label=\"Internet\" icon=\"internet\"",       _network_menu_entries);
	write(file, "label=\"Office\" icon=\"office\"",           _office_menu_entries);
	write(file, "label=\"Science\" icon=\"science\"",         _science_menu_entries);
	write(file, "label=\"Settings\" icon=\"settings\"",       _settings_menu_entries);
	write(file, "label=\"System\" icon=\"system\"",           _system_menu_entries);
	write(file, "label=\"Utilities\" icon=\"utility\"",       _utility_menu_entries);
	write(file, "label=\"Others\" icon=\"others\"",           _other_menu_entries);

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
