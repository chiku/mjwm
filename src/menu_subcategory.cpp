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

#include <string>

#include "desktop_file.h"
#include "menu_subcategory.h"

amm::menu_subcategory::menu_subcategory()
{
}

amm::menu_subcategory::menu_subcategory(std::string name_in_desktop_file, std::string name_to_display, std::string icon_name)
{
	_name_in_desktop_file = name_in_desktop_file;
	_name_to_display = name_to_display;
	_icon_name = icon_name;
}

std::string
amm::menu_subcategory::name() const
{
	return _name_in_desktop_file;
}

std::string
amm::menu_subcategory::pretty_name() const
{
	return _name_to_display;
}

std::string
amm::menu_subcategory::icon_name() const
{
	return _icon_name;
}

void
amm::menu_subcategory::add_desktop_file(amm::desktop_file desktop_file)
{
	_desktop_files.push_back(desktop_file);
}
