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

#ifndef __amm_menu_subcategory__
#define __amm_menu_subcategory__

#include <string>
#include <vector>

namespace amm
{
    // Understands how different sub-sections of menu would be constructed
	class menu_subcategory
	{
	private:
        std::string _name_in_desktop_file;
        std::string _name_to_display;
		std::string _icon_name;
		std::vector<amm::desktop_file> _desktop_files;

    public:
		menu_subcategory();
		menu_subcategory(std::string name_in_desktop_file, std::string name_to_display, std::string icon_name);

        std::string name() const;
        std::string pretty_name() const;
        std::string icon_name() const;
        void add_desktop_file(amm::desktop_file desktop_file);
	};
}

#endif
