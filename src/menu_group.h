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

#ifndef __amm_menu_group__
#define __amm_menu_group__

#include <iostream>
#include <string>
#include <vector>
#include <utility>

#include "desktop_file.h"
#include "transform/jwm.h"

namespace amm
{
	const int NORMAL_RESERVE_SIZE = 30;

	struct qualified_desktop_file
	{
		std::string pretty_name;
		std::string icon;
		std::vector<amm::desktop_file> menu_entries;

		qualified_desktop_file();
		qualified_desktop_file(std::string pretty_name, std::string icon);
	};

	// Understands how a directory with FreeDesktop .desktop files is converted to a JWM menu section
	// TODO - multiple responsibilities - split class
	class menu_group
	{
	private:
		amm::transform::jwm _jwm_transformer;
		std::vector<std::string> _desktop_file_names;
		std::string _icon_extension;
		std::string _error;
		bool _parsed;

		std::vector< std::pair<std::string, amm::qualified_desktop_file> > _menu_entries;
		amm::qualified_desktop_file _unclassified_entries;

		bool classify(amm::desktop_file entry);
		void write(std::ofstream& file, std::string section, std::vector<amm::desktop_file> entries);
		void construct_menu_entries(std::string name, std::string pretty_name, std::string icon);
		void create_categories();

	public:
		menu_group(std::vector<std::string> desktop_file_names, std::string icon_extension);
		void populate();
		bool is_valid() const;
		std::string error() const;
		void sort();
		void write(std::string output_filename);
	};
}

#endif
