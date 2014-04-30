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

#include "xdg/entry.h"

#include <string>
#include <vector>
#include <map>

#include "xdg/entry_line.h"

namespace amm {
namespace xdg {

void Entry::Parse() {
  std::map< std::string, std::string > entry;
  EntryLine section(lines_[0]);
  for (std::vector<std::string>::iterator iter = lines_.begin() + 1; iter != lines_.end(); ++iter) {
    EntryLine line(*iter);
    entry[line.Key()] = line.Value();
  }
  result_[section.Declaration()] = entry;
}

std::string Entry::Under(std::string section, std::string key) {
  return result_[section][key];
}

} // namespace xdg
} // namespace amm
