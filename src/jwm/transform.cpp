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
#include "transform.h"

amm::menu_entry::jwm
amm::transform::jwm::transform(amm::desktop_file desktop_file)
{
	std::string name = amm::stringx(desktop_file.name()).encode();
	std::string icon = amm::stringx(_icon_service.resolved_name(desktop_file.icon())).encode();
	std::string executable = remove_field_code(desktop_file.executable());

	return amm::menu_entry::jwm(name, icon, executable);
}

void
amm::transform::jwm::register_icon_service(amm::icon_service icon_service)
{
    _icon_service = icon_service;
}

std::string
amm::transform::jwm::remove_field_code(std::string input) const
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
