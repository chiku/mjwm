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

#ifndef __amm_menu_entry__
#define __amm_menu_entry__

#include <fstream>
#include <string>
#include <vector>

#include "categories.h"

namespace amm
{
	class menu_entry
	{
	private:
		std::string _name;
		std::string _executable;
		std::string _icon;
		amm::categories _categories;

		std::string encode(std::string data) const;
		std::string trim(std::string input) const;

	public:
		menu_entry();

		std::string name() const;
		std::string icon() const;
		std::string executable() const;
		amm::categories categories() const;

		bool operator < (const amm::menu_entry &other) const;
		bool operator > (const amm::menu_entry &other) const;
		bool operator == (const amm::menu_entry &other) const;
		bool operator != (const amm::menu_entry &other) const;

		bool is_valid() const;
		void populate(std::string line);
		void dump() const;
	};
}

#endif
