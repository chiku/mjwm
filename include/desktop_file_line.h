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

#ifndef AMM_DESKTOP_FILE_LINE_H_
#define AMM_DESKTOP_FILE_LINE_H_

#include <string>
#include <iostream>

#include "stringx.h"

namespace amm {
// Understands a line in a FreeDesktop .desktop file
class DesktopFileLine {
 public:
  explicit DesktopFileLine(std::string content);

  bool IsComment() const;
  bool IsDeclaration() const;
  bool IsAssignment() const;
  std::string Declaration() const;
  std::string AssignmentFor(std::string key) const;

 private:
  std::string content_;
  std::string::size_type content_length_;
  std::string::size_type assignment_delim_location_;
};
} // namespace amm

#endif // AMM_DESKTOP_FILE_LINE_H_
