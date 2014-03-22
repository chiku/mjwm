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

#include "desktop_file.h"
#include "transform/jwm.h"
#include "subcategory.h"

amm::subcategory::subcategory()
{
}

amm::subcategory::subcategory(std::string classification_name, std::string display_name, std::string icon_name, std::string icon_extension)
{
	_classification_name = classification_name;
	_display_name = display_name;
	_icon_name = icon_name;
	_icon_extension = icon_extension;
}

std::string
amm::subcategory::classification_name() const
{
	return _classification_name;
}

std::string
amm::subcategory::display_name() const
{
	return _display_name;
}

std::string
amm::subcategory::icon_name() const
{
	return _icon_name;
}

std::string
amm::subcategory::icon_extension() const
{
	return _icon_extension;
}

std::vector<amm::desktop_file>
amm::subcategory::desktop_files() const
{
	return _desktop_files;
}

bool
amm::subcategory::has_entries() const
{
	return desktop_files().size() > 0;
}

void
amm::subcategory::add_desktop_file(amm::desktop_file desktop_file)
{
	_desktop_files.push_back(desktop_file);
}

void
amm::subcategory::sort_desktop_files()
{
	std::sort(_desktop_files.begin(), _desktop_files.end());
}

std::ostream&
amm::operator << (std::ostream& stream, const amm::subcategory& subcategory)
{
	if (subcategory.has_entries()) {
		amm::transform::jwm jwm_transformer; // TODO : inject from outside
		std::string section = "label=\"" + subcategory.display_name() + "\" icon=\"" + subcategory.icon_name() + subcategory.icon_extension() + "\"";

		stream << "  <Menu " << section << ">" << std::endl;

		std::vector<amm::desktop_file> desktop_files = subcategory.desktop_files();
		std::vector<amm::desktop_file>::iterator entry;
		for(entry = desktop_files.begin(); entry != desktop_files.end(); ++entry) {
			stream << "    " << jwm_transformer.transform(*entry, subcategory.icon_extension()) << std::endl;
		}

		stream << "  </Menu>" << std::endl;
	}

	return stream;
}
