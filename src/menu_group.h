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

#include "menu_entry.h"

namespace amm
{
	const int NORMAL_RESERVE_SIZE = 30;

	struct qualified_menu_entry
	{
		std::string pretty_name;
		std::string icon;
		std::vector<amm::menu_entry> menu_entries;

		qualified_menu_entry();
		qualified_menu_entry(std::string pretty_name, std::string icon);
	};

	class menu_group
	{
	private:
		std::string _directory_name;
		std::string _icon_extension;
		std::string _error;
		bool _parsed;

		std::vector< std::pair<std::string, amm::qualified_menu_entry> > _menu_entries;
		amm::qualified_menu_entry _unclassified_entries;

		bool classify(amm::menu_entry entry);
		void write(std::ofstream& file, std::string section, std::vector<amm::menu_entry> entries);
		void construct_menu_entries(std::string name, std::string pretty_name, std::string icon);

	public:
		menu_group(std::string directory_name, std::string icon_extension);
		void populate();
		bool is_valid() const;
		std::string error() const;
		void sort();
		void write(std::string output_filename);
	};
}

#endif
