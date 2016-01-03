/*
  This file is part of mjwm.
  Copyright (C) 2014-2016  Chirantan Mitra <chirantan.mitra@gmail.com>

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

#ifndef AMM_STRINGX_H_
#define AMM_STRINGX_H_

#include <string>
#include <vector>

namespace amm {
class StringX
{
public:
    explicit StringX(const std::string &string) : string_(string) {}

    bool endsWith(const std::string &delimiter) const;
    std::string terminateWith(const std::string &end) const;
    std::string encode() const;
    std::string trim() const;
    std::vector<std::string> split(const std::string &delimiter) const;
private:
    const std::string string_;
};
} // namespace amm

#endif // AMM_STRINGX_H_
