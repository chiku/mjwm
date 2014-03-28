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

#ifndef __amm_desktop_file__
#define __amm_desktop_file__

#include <fstream>
#include <string>
#include <vector>

namespace amm
{
	// Understands a FreeDesktop .desktop file representation
	class desktop_file
	{
	private:
		std::string _name;
		std::string _executable;
		std::string _icon;
		std::vector<std::string> _categories;

	public:
		desktop_file();

		std::string name() const;
		std::string icon() const;
		std::string executable() const;
		std::vector<std::string> categories() const;

		bool operator < (const amm::desktop_file &other) const;
		bool operator > (const amm::desktop_file &other) const;
		bool operator == (const amm::desktop_file &other) const;
		bool operator != (const amm::desktop_file &other) const;

		bool is_valid() const;
		bool is_a(std::string type) const;
		void populate(std::string line);
	};
}

#endif
