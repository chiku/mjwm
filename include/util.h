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

#ifndef AMM_UTIL_H_
#define AMM_UTIL_H_

#include <string>
#include <vector>

// TODO : split into two files. /usr/include/utils.h (from cdparanoia) already exists

namespace amm {
// TODO : move methods with single use to their usage points
class StringX {
 public:
  StringX(std::string string);
  bool EndsWith(const std::string delimiter) const;
  std::string TerminateWith(const std::string end);
  std::string Encode() const;
  std::string Trim() const;
  std::vector<std::string> Split(const std::string delimiter) const;
 private:
  std::string string_;
};

// TODO : move methods with single use to their usage points
class VectorX {
 public:
  VectorX(std::vector<std::string> vector);

  std::string Join(std::string delimiter) const;
  std::vector<std::string> TerminateWith(std::string delimiter) const;
  std::vector<std::string> Unique() const;
 private:
  std::vector<std::string> vector_;
};
} // namespace amm

#endif // AMM_UTIL_H_