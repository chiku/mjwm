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

#ifndef AMM_DESKTOP_FILE_NAMES_H_
#define AMM_DESKTOP_FILE_NAMES_H_

#include <string>
#include <vector>
#include <dirent.h>

namespace amm
{
	const std::string DESKTOP_EXTENSION = ".desktop";

	// Understands search for .desktop files
	class desktop_file_names
	{
	private:
		std::vector<std::string> directory_names_;
		std::vector<std::string> desktop_file_names_;
		std::vector<std::string> bad_paths_;
		bool capture_bad_paths_;

		void populate(DIR* directory, std::string directory_name);

	public:
		desktop_file_names();

		void register_directories_with_default_fallback(std::vector<std::string> directory_names);
		void register_default_directories();
		void register_directories(std::vector<std::string> directory_names);
		void resolve();

		std::vector<std::string> all() const;
		std::vector<std::string> bad_paths() const;
	};
}

#endif // AMM_DESKTOP_FILE_NAMES_H_
