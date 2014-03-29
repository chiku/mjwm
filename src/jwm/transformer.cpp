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
#include <sstream>
#include <vector>

#include "../stringx.h"
#include "../vectorx.h"
#include "../icon_service.h"
#include "../desktop_file.h"
#include "transformer.h"

std::string
amm::transformer::jwm::remove_field_code(std::string input) const
{
	std::vector<std::string> result;
	std::vector<std::string> tokens = amm::stringx(input).split(" ");

	for (std::vector<std::string>::iterator iter = tokens.begin(); iter != tokens.end(); ++iter) {
		if (!(iter->size() >= 1 && (*iter)[0] == '%')) {
			result.push_back(*iter);
		}
	}

	return amm::vectorx(result).join(" ");
}

std::string
amm::transformer::jwm::transform(amm::representation::menu_start *entry)
{
	return "<JWM>";
}

std::string
amm::transformer::jwm::transform(amm::representation::menu_end *entry)
{
	return "</JWM>";
}

std::string
amm::transformer::jwm::transform(amm::representation::subcategory_start *entry)
{
	std::string result("  <Menu label=\"");
	result = result + amm::stringx(entry->name()).encode() + "\" icon=\"" + amm::stringx(entry->icon()).encode() + "\">";
	return result;
}

std::string
amm::transformer::jwm::transform(amm::representation::subcategory_end *entry)
{
	return "  </Menu>";
}

std::string
amm::transformer::jwm::transform(amm::representation::menu_entry *entry)
{
	std::string result("    <Program label=\"");
	result = result + amm::stringx(entry->name()).encode() + "\" icon=\"" + amm::stringx(entry->icon()).encode() + "\">" + remove_field_code(entry->executable()) + "</Program>";
	return result;
}
