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
#include <algorithm>
#include <cstdlib>
#include <dirent.h>

#include "stringx.h"
#include "vectorx.h"
#include "application_directories.h"

static std::string
xdg_data_dirs()
{
	char *xdg_data_dirs = std::getenv("XDG_DATA_DIRS");
	if (xdg_data_dirs != NULL) {
		return xdg_data_dirs;
	}

	return "/usr/local/share:/usr/share";
}

static std::string
xdg_data_home()
{
	char *xdg_data_home = std::getenv("XDG_DATA_HOME");
	if (xdg_data_home != NULL) {
		return xdg_data_home;
	}

	char *home = std::getenv("HOME");
	if (home != NULL) {
		return std::string(home) + "/.local/share/applications";
	}

	return "";
}

void
amm::application_directories::resolve(std::vector<std::string> directory_names)
{
	std::vector<std::string> terminated_directory_names = amm::vectorx(directory_names).terminate_with("/");
	std::vector<std::string> unique_directory_names = amm::vectorx(terminated_directory_names).unique();

	std::vector<std::string>::const_iterator name;
	for (name = unique_directory_names.begin(); name != unique_directory_names.end(); ++name) {
		DIR *directory = opendir(name->c_str());

		if (!directory) {
			_bad_paths.push_back(*name);
		} else {
			populate_desktop_file_names(directory, *name);
			closedir(directory);
		}
	}
}

void
amm::application_directories::populate_desktop_file_names(DIR* directory, std::string directory_name)
{
	dirent *directory_entry;

	while((directory_entry = readdir(directory)) != NULL) {
		std::string file_name = directory_entry->d_name;
		if (amm::stringx(file_name).ends_with(DESKTOP_EXTENSION)) {
			_desktop_file_names.push_back(directory_name + file_name);
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

void
amm::application_directories::flush_bad_paths()
{
	_bad_paths.clear();
}

void
amm::application_directories::read_from_environment()
{
	std::vector<std::string> directory_bases = amm::stringx(xdg_data_dirs()).split(":");
	directory_bases.push_back(xdg_data_home());
	std::vector<std::string> directories;

	for (std::vector<std::string>::iterator iter = directory_bases.begin(); iter != directory_bases.end(); ++iter) {
		std::string directory = amm::stringx(*iter).terminate_with("/") + "applications";
		directories.push_back(directory);
	}

	resolve(directories);
	flush_bad_paths();
}
