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

#include "desktop_entry.h"

#include <string>
#include <vector>
#include <algorithm>

#include "stringx.h"
#include "desktop_file_line.h"

namespace amm {

DesktopEntry::DesktopEntry() : display_(true), populate_under_desktop_entry_(true) { }

bool DesktopEntry::operator < (const DesktopEntry &other) const {
  return name_ < other.name_;
}

bool DesktopEntry::operator > (const DesktopEntry &other) const {
  return name_ > other.name_;
}

bool DesktopEntry::operator == (const DesktopEntry &other) const {
  return name_ == other.name_ && executable_ == other.executable_;
}

bool DesktopEntry::operator != (const DesktopEntry &other) const {
  return !(*this == other);
}

bool DesktopEntry::IsValid() const {
  return (executable_.length() > 0) && (name_.length() > 0) && (icon_.length() > 0);
}

bool DesktopEntry::IsA(std::string type) const {
  return std::binary_search(categories_.begin(), categories_.end(), type);
}

bool DesktopEntry::IsAnyOf(std::vector<std::string> types) const {
  for (std::vector<std::string>::const_iterator type = types.begin(); type != types.end(); ++type) {
    if (IsA(*type)) {
      return true;
    }
  };
  return false;
}

void DesktopEntry::Populate(std::string line_raw) {
  DesktopFileLine line = DesktopFileLine(line_raw);

  if (line.IsDeclaration() && line.Declaration() != "Desktop Entry") {
    populate_under_desktop_entry_ = false;
  }

  if (!populate_under_desktop_entry_) {
    return;
  }

  line.AssignWhenPresent("Name", &name_);
  line.AssignWhenPresent("Icon", &icon_);
  line.AssignWhenPresent("Exec", &executable_);

  std::string categories_raw;
  if (line.AssignWhenPresent("Categories", &categories_raw) != "") {
    categories_ = StringX(categories_raw).Split(";");
    std::sort(categories_.begin(), categories_.end());
  }

  std::string display_raw;
  if (line.AssignWhenPresent("NoDisplay", &display_raw) != "") {
    display_ = display_raw != "true" && display_raw != "1";
  }
}

} // namespace amm
