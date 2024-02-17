/*
  This file is part of mjwm.
  Copyright (C) 2024  Chirantan Mitra <chirantan.mitra@gmail.com>

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

#include "terminal.h"

#include <string>
#include <sstream>

namespace amm {

std::string terminalCommand(const std::string &term, const std::string& exec, const std::string& name)
{
    std::stringstream stream;

    if (term == "alacritty") {
        stream << "alacritty --title \"" << name << "\" --class \"" << name << "\" -e " << exec;
    } else if (term == "sakura") {
        stream << "sakura --name \"" << name << "\" --class \"" << name << "\" -e " << exec;
    } else {
        stream << "xterm -class \"" << name << "\" " << exec;
    }

    return stream.str();
}

} // namespace amm
