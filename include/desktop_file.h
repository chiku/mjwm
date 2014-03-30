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

#ifndef AMM_DESKTOP_FILE_H
#define AMM_DESKTOP_FILE_H

#include <string>
#include <vector>

namespace amm
{
	// Understands the representation of a FreeDesktop .desktop file
	class desktop_file
	{
	private:
		std::string _name;
		std::string _executable;
		std::string _icon;
		std::vector<std::string> _categories;
		bool _display;

	public:
		desktop_file();

		std::string name() const;
		std::string icon() const;
		std::string executable() const;
		std::vector<std::string> categories() const;
		bool display() const;

		bool operator < (const amm::desktop_file &other) const;
		bool operator > (const amm::desktop_file &other) const;
		bool operator == (const amm::desktop_file &other) const;
		bool operator != (const amm::desktop_file &other) const;

		bool is_valid() const;
		bool is_a(std::string type) const;
		bool is_any_of(std::vector<std::string> types) const;
		void populate(std::string line);
	};
}

#endif
