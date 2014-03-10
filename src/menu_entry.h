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

#ifndef __mjwm_menu_entry__
#define __mjwm_menu_entry__

#include <fstream>
#include <string>

namespace mjwm
{
	class menu_entry
	{
	private:
		std::string _name;
		std::string _executable;
		std::string _icon;
		std::string _categories;

		std::string safe_parse() const;
		std::string encode(std::string data) const;
	public:
		menu_entry();

		std::string name() const;
		std::string icon() const;
		std::string executable() const;
		std::string categories() const;

		bool operator < (const mjwm::menu_entry &other) const;
		bool operator > (const mjwm::menu_entry &other) const;
		bool operator == (const mjwm::menu_entry &other) const;
		bool operator != (const mjwm::menu_entry &other) const;

		bool is_valid() const;
		void populate(std::string line);
		void write_to(std::ofstream &file, std::string icon_extension) const;
		void dump() const;
	};
}

#endif
