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

#include "representation.h"

std::string
amm::representation::menu_start::name() const
{
	return "Menu start";
}

std::string
amm::representation::menu_end::name() const
{
	return "Menu end";
}


amm::representation::subcategory_start::subcategory_start(std::string display_name)
{
	_display_name = display_name;
}

std::string
amm::representation::subcategory_start::name() const
{
	return _display_name;
}


amm::representation::subcategory_end::subcategory_end(std::string display_name)
{
	_display_name = display_name;
}

std::string
amm::representation::subcategory_end::name() const
{
	return _display_name + " end";
}


amm::representation::menu_entry::menu_entry(std::string name)
{
	_name = name;
}

std::string
amm::representation::menu_entry::name() const
{
	return _name;
}
