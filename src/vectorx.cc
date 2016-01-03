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

#include "vectorx.h"

#include <string>
#include <vector>
#include <sstream>
#include <algorithm>

#include "stringx.h"

namespace amm {

std::string VectorX::join(const std::string &delimeter) const
{
    std::stringstream stream;
    size_t vector_size = vector_.size();

    if (vector_size == 0) {
        return "";
    }

    if (vector_size >= 2) {
        for (std::vector<std::string>::const_iterator iterator = vector_.begin(); iterator != vector_.end()-1; ++iterator) {
            stream << *iterator << delimeter;
        }
    }
    stream << vector_.back();

    return stream.str();
}

std::vector<std::string> VectorX::terminateEachWith(const std::string &delimiter) const
{
    std::vector<std::string> result;

    for (std::vector<std::string>::const_iterator i = vector_.begin(); i != vector_.end(); ++i) {
        result.push_back(StringX(*i).terminateWith(delimiter));
    }

    return result;
}

std::vector<std::string> VectorX::unique() const
{
    std::vector<std::string> result = vector_;

    std::sort(result.begin(), result.end());
    std::vector<std::string>::iterator it = std::unique(result.begin(), result.end());
    result.resize(std::distance(result.begin(), it));

    return result;
}

} // namespace amm
