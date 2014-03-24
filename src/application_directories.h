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

#ifndef __amm_application_directories__
#define __amm_application_directories__

#include <string>
#include <vector>
#include <dirent.h>

namespace amm
{
	const std::string DESKTOP_EXTENSION = ".desktop";

	// Understands how to search .desktop files present in multiple locations
	class application_directories
	{
	private:
		std::vector<std::string> _desktop_file_names;
		std::vector<std::string> _bad_paths;

		void populate_desktop_file_names(DIR* directory, std::string directory_name);

	public:
		void resolve(std::vector<std::string> directory_names);
		void flush_bad_paths();

		std::vector<std::string> desktop_file_names() const;
		std::vector<std::string> bad_paths() const;
	};
}

#endif
