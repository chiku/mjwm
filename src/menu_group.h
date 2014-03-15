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

#ifndef __mjwm_menu_group__
#define __mjwm_menu_group__

#include <iostream>
#include <string>
#include <vector>

#include "menu_entry.h"

namespace mjwm
{
	const int NORMAL_RESERVE_SIZE = 30;

	class menu_group
	{
	private:
		std::string _directory_name;
		std::string _icon_extension;
		std::string _error;
		bool _parsed;

		std::vector<mjwm::menu_entry> _audiovideo_menu_entries;
		std::vector<mjwm::menu_entry> _development_menu_entries;
		std::vector<mjwm::menu_entry> _education_menu_entries;
		std::vector<mjwm::menu_entry> _game_menu_entries;
		std::vector<mjwm::menu_entry> _graphics_menu_entries;
		std::vector<mjwm::menu_entry> _network_menu_entries;
		std::vector<mjwm::menu_entry> _office_menu_entries;
		std::vector<mjwm::menu_entry> _science_menu_entries;
		std::vector<mjwm::menu_entry> _settings_menu_entries;
		std::vector<mjwm::menu_entry> _system_menu_entries;
		std::vector<mjwm::menu_entry> _utility_menu_entries;
		std::vector<mjwm::menu_entry> _other_menu_entries;

		void classify(mjwm::menu_entry entry);
		void write(std::ofstream& file, std::string section, std::vector<mjwm::menu_entry> entries);

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
