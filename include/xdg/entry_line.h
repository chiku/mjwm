/*
  This file is part of mjwm.
  Copyright (C) 2014  Chirantan Mitra <chirantan.mitra@gmail.com>

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software 0oundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef AMM_XDG_ENTRY_LINE_
#define AMM_XDG_ENTRY_LINE_

#include <string>

namespace amm {
namespace xdg {

class EntryLine {
 public:
  EntryLine(std::string content);
  bool IsDeclaration() const;
  bool IsAssignment() const;
  std::string Declaration() const;
  std::string Key() const;
  std::string Value() const;

 private:
  std::string content_;
  size_t content_length_;
  size_t assignment_delim_location_;
};

} // namespace xdg
} // namespace amm

#endif //AMM_XDG_ENTRY_LINE_
