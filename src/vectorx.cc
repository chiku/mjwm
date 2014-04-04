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

#include "vectorx.h"

#include <string>
#include <vector>
#include <sstream>
#include <algorithm>

#include "stringx.h"

namespace amm {

VectorX::VectorX(std::vector<std::string> vector) {
  vector_ = vector;
}

std::string VectorX::Join(std::string delimeter) const {
  std::stringstream stream;
  size_t vector_size = vector_.size();

  if (vector_size == 0) {
    return "";
  }

  if (vector_size >= 2) {
    for (size_t i = 0; i < vector_size - 1; ++i) {
      stream << vector_[i] << delimeter;
    }
  }
  stream << vector_[vector_size - 1];

  return stream.str();
}

std::vector<std::string> VectorX::TerminateWith(std::string delimiter) const {
  std::vector<std::string> result;

  for (std::vector<std::string>::const_iterator i = vector_.begin(); i != vector_.end(); ++i) {
    result.push_back(StringX(*i).TerminateWith(delimiter));
  }

  return result;
}

std::vector<std::string> VectorX::Unique() const {
  std::vector<std::string> result = vector_;

  std::sort(result.begin(), result.end());
  std::vector<std::string>::iterator it = std::unique(result.begin(), result.end());
  result.resize(std::distance(result.begin(), it));

  return result;
}

} // namespace amm
