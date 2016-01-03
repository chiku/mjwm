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

#ifndef AMM_VECTORX_H_
#define AMM_VECTORX_H_

#include <string>
#include <vector>

namespace amm {

class VectorX
{
public:
    explicit VectorX(const std::vector<std::string> &vector) : vector_(vector) { }

    std::string join(const std::string &delimiter) const;
    std::vector<std::string> terminateEachWith(const std::string &delimiter) const;
    std::vector<std::string> unique() const;
private:
    const std::vector<std::string> &vector_;
};
} // namespace amm

#endif // AMM_VECTORX_H_
