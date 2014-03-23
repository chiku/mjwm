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

#include <string>
#include <vector>
#include <dirent.h>

#include "stringx.h"
#include "application_directories.h"

amm::application_directories::application_directories(std::vector<std::string> directory_names)
{
	_directory_names = directory_names;
	resolve();
}

void
amm::application_directories::resolve()
{
	std::vector<std::string>::iterator iter;
	for (iter = _directory_names.begin(); iter != _directory_names.end(); ++iter) {
		std::string name = *iter;

		name = amm::stringx(name).terminate_with("/");

		DIR *directory = opendir(name.c_str());

		if (!directory) {
			_bad_paths.push_back(name);
		} else {
			dirent *directory_entry;

			while((directory_entry = readdir(directory)) != NULL) {
				std::string file_name = directory_entry->d_name;
				if (amm::stringx(file_name).ends_with(DESKTOP_EXTENSION)) {
					_desktop_file_names.push_back(name + file_name);
				}
			}

			closedir(directory);
		}

	}
}

std::vector<std::string>
amm::application_directories::desktop_file_names() const
{
	return _desktop_file_names;
}

std::vector<std::string>
amm::application_directories::bad_paths() const
{
	return _bad_paths;
}
