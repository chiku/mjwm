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

#include "xdg/icon_theme.h"

#include <cstdlib>
#include <string>
#include <vector>
#include <algorithm>

#include "stringx.h"
#include "xdg/entry.h"
#include "xdg/icon_subdirectory.h"

namespace amm {
namespace xdg {

IconTheme::IconTheme(std::vector<std::string> lines) : internal_name_("") {
  Entry xdg_entry(lines);
  xdg_entry.Parse();

  name_ = xdg_entry.Under("Icon Theme", "Name");
  std::string lower_case_name = name_;
  std::transform(lower_case_name.begin(), lower_case_name.end(), lower_case_name.begin(), ::tolower);

  parents_ = StringX(xdg_entry.Under("Icon Theme", "Inherits")).Split(",");
  if (parents_.empty() && lower_case_name != "hicolor") {
    parents_.push_back("Hicolor");
  }

  std::vector<std::string> directory_names = StringX(xdg_entry.Under("Icon Theme", "Directories")).Split(",");
  for (std::vector<std::string>::const_iterator name = directory_names.begin(); name != directory_names.end(); ++name) {
    std::string type = xdg_entry.Under(*name, "Type");
    std::string size = xdg_entry.Under(*name, "Size");
    std::string maxsize = xdg_entry.Under(*name, "MaxSize");
    std::string minsize = xdg_entry.Under(*name, "MinSize");
    std::string threshold = xdg_entry.Under(*name, "Threshold");

    IconSubdirectory icon_subdirectory = IconSubdirectory(*name, size)
      .Type(type)
      .MaxSize(maxsize)
      .MinSize(minsize)
      .Threshold(threshold);
    directories_.push_back(icon_subdirectory);
  }
}

} // namespace xdg
} // namespace amm
