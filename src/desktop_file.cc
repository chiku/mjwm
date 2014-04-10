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

#include "desktop_file.h"

#include <string>
#include <vector>
#include <algorithm>

#include "stringx.h"
#include "desktop_file_line.h"

namespace amm {

static const std::string NAME       = "Name";
static const std::string EXECUTABLE = "Exec";
static const std::string ICON       = "Icon";
static const std::string CATEGORIES = "Categories";
static const std::string NO_DISPLAY = "NoDisplay";

DesktopFile::DesktopFile() {
  display_ = true;
}

bool DesktopFile::operator < (const DesktopFile &other) const {
  return name_ < other.name_;
}

bool DesktopFile::operator > (const DesktopFile &other) const {
  return name_ > other.name_;
}

bool DesktopFile::operator == (const DesktopFile &other) const {
  return name_ == other.name_;
}

bool DesktopFile::operator != (const DesktopFile &other) const {
  return name_ != other.name_;
}

bool DesktopFile::IsValid() const {
  return (executable_.length() > 0) && (name_.length() > 0) && (icon_.length() > 0);
}

bool DesktopFile::IsA(std::string type) const {
  return std::binary_search(categories_.begin(), categories_.end(), type);
}

bool DesktopFile::IsAnyOf(std::vector<std::string> types) const {
  for (std::vector<std::string>::const_iterator type = types.begin(); type != types.end(); ++type) {
    if (IsA(*type)) {
      return true;
    }
  };
  return false;
}

void DesktopFile::Populate(std::string line_raw) {
  DesktopFileLine line = DesktopFileLine(line_raw);
  std::string categories_raw, display_raw;

  line.AssignWhenPresent(NAME, &name_);
  line.AssignWhenPresent(ICON, &icon_);
  line.AssignWhenPresent(EXECUTABLE, &executable_);

  if (line.AssignWhenPresent(CATEGORIES, &categories_raw) != "") {
    categories_ = StringX(categories_raw).Split(";");
    std::sort(categories_.begin(), categories_.end());
  }

  if (line.AssignWhenPresent(NO_DISPLAY, &display_raw) != "") {
    display_ = display_raw != "true" && display_raw != "1";
  }
}

} // namespace amm
