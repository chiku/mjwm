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

#include "filex.h"

#include <string>
#include <vector>
#include <fstream>

namespace amm {

bool FileX::Load(std::vector<std::string> *lines) const {
  std::ifstream file(name_.c_str());

  if (!file.good()) {
    return false;
  }

  lines->clear();
  std::string line;
  while (std::getline(file, line)) {
    lines->push_back(line);
  }
  file.close();
  return true;
}

} // namespace amm
