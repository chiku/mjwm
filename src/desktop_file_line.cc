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

#include "desktop_file_line.h"

#include <string>

#include "stringx.h"

namespace amm {

const std::string kAssignmentDelim = "=";

DesktopFileLine::DesktopFileLine(std::string content) :
    content_(StringX(content).Trim()),
    content_length_(content_.size()),
    assignment_delim_location_(content_.find(kAssignmentDelim)) {}

bool DesktopFileLine::IsComment() const {
  return content_[0] == '#';
}

bool DesktopFileLine::IsDeclaration() const {
  return content_[0] == '[' && content_[content_.length() - 1] == ']';
}

bool DesktopFileLine::IsAssignment() const {
  return assignment_delim_location_ != std::string::npos;
}

std::string DesktopFileLine::Declaration() const {
  if (!IsDeclaration()) {
    return "";
  }

  std::string::size_type start = content_.find("[") + 1;
  std::string::size_type end = content_.find("]");
  return content_.substr(start, end - start);
}

std::string DesktopFileLine::AssignWhenPresent(std::string key, std::string *slot) const {
  if (!IsAssignment() || StringX(content_.substr(0, assignment_delim_location_)).Trim() != key) {
    return "";
  }

  std::string result = StringX(content_.substr(assignment_delim_location_ + 1, content_.length())).Trim();
  *slot = result;
  return result;
}

} // namespace amm
