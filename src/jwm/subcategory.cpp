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
#include <vector>
#include <algorithm>

#include "../desktop_file.h"
#include "transform.h"
#include "subcategory.h"

amm::jwm::subcategory::subcategory()
{
}

amm::jwm::subcategory::subcategory(std::string classification_name, std::string display_name, std::string icon_name, amm::icon_service icon_service)
{
	_classification_name = classification_name;
	_display_name = display_name;
	_icon_name = icon_name;
	_icon_service = icon_service;
}

void
amm::jwm::subcategory::register_icon_service(amm::icon_service icon_service)
{
	_icon_service = icon_service;
}

amm::icon_service
amm::jwm::subcategory::icon_service() const
{
	return _icon_service;
}

std::string
amm::jwm::subcategory::classification_name() const
{
	return _classification_name;
}

std::string
amm::jwm::subcategory::first_line() const
{
	std::string line = "<Menu ";
	line += "label=\"" + _display_name + "\" icon=\"" + _icon_service.resolved_name(_icon_name) + "\">";
	return line;
}

std::string
amm::jwm::subcategory::last_line() const
{
	return "</Menu>";
}

std::vector<amm::desktop_file>
amm::jwm::subcategory::desktop_files() const
{
	return _desktop_files;
}

bool
amm::jwm::subcategory::has_entries() const
{
	return desktop_files().size() > 0;
}

void
amm::jwm::subcategory::add_desktop_file(amm::desktop_file desktop_file)
{
	_desktop_files.push_back(desktop_file);
}

void
amm::jwm::subcategory::sort_desktop_files()
{
	std::sort(_desktop_files.begin(), _desktop_files.end());
}

std::ostream&
amm::jwm::operator << (std::ostream& stream, const amm::jwm::subcategory& subcategory)
{
	if (subcategory.has_entries()) {
		amm::transform::jwm jwm_transformer;
		amm::icon_service icon_service = subcategory.icon_service();

		stream << "  " << subcategory.first_line() << std::endl;

		std::vector<amm::desktop_file> desktop_files = subcategory.desktop_files();
		std::vector<amm::desktop_file>::iterator entry;
		for(entry = desktop_files.begin(); entry != desktop_files.end(); ++entry) {
			stream << "    " << jwm_transformer.transform(*entry, icon_service) << std::endl;
		}

		stream << "  " << subcategory.last_line() << std::endl;
	}

	return stream;
}
