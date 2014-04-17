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

#ifndef AMM_STRING_H_
#define AMM_STRING_H_

#include <string>
#include <vector>

namespace amm {
// TODO : move methods with single use to their usage points
class StringX {
 public:
  explicit StringX(std::string string);

  bool EndsWith(const std::string delimiter) const; // FSS
  std::string TerminateWith(const std::string end); // FSS
  std::string Encode() const; // Transformer::JWM
  std::string Trim() const; // DesktopEntry
  std::vector<std::string> Split(const std::string delimiter) const; // Menu, Transformer::JWM, FSS, CLO
 private:
  const std::string string_;
};
} // namespace amm

#endif // AMM_UTIL_H_
