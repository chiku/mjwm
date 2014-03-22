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

#include <iostream>
#include <string>

#include "menu_entry.h"

amm::menu_entry::jwm::jwm(std::string name, std::string icon, std::string executable)
{
	_name = name;
	_icon = icon;
	_executable = executable;
}

std::string
amm::menu_entry::jwm::name() const
{
	return _name;
}

std::string
amm::menu_entry::jwm::icon() const
{
	return _icon;
}

std::string
amm::menu_entry::jwm::executable() const
{
	return _executable;
}

std::ostream&
amm::menu_entry::operator << (std::ostream& stream, const amm::menu_entry::jwm& jwm_menu_entry)
{
	stream << "<Program "
	       << "label=\"" << jwm_menu_entry.name() << "\" "
	       << "icon=\"" << jwm_menu_entry.icon() << "\">"
	       << jwm_menu_entry.executable()
	       << "</Program>";

	return stream;
}