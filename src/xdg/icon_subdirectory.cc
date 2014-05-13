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

#include "xdg/icon_subdirectory.h"

#include <cstdlib>
#include <climits>

namespace amm {
namespace xdg {

IconSubdirectory& IconSubdirectory::Name(std::string name) {
  name_ = name;
  return *this;
}

IconSubdirectory& IconSubdirectory::Type(std::string type) {
  type_ = type;
  return *this;
}

IconSubdirectory& IconSubdirectory::Size(int size) {
  size_ = size;
  max_size_ = size;
  min_size_ = size;
  return *this;
}

bool IconSubdirectory::Matches(int required_size) {
  if (type_ == "Fixed") {
    return size_ == required_size;
  }
  if (type_ == "Scaled") {
    return (min_size_ <= required_size) && (required_size <= max_size_);
  }
  if (type_ == "Threshold") {
    return (size_ - threshold_ <= required_size) && (required_size <= size_ + threshold_);
  }

  return false;
}

int IconSubdirectory::Distance(int required_size) {
  if (type_ == "Fixed") {
    return abs(size_ - required_size);
  }
  if (type_ == "Scaled") {
    if (required_size < min_size_) {
      return min_size_ - required_size;
    }
    if (required_size > max_size_) {
      return required_size - max_size_;
    }
    return 0;
  }
  if (type_ == "Threshold") {
    if (required_size < size_ - threshold_) {
      return min_size_ - required_size;
    }
    if (required_size > size_ + threshold_) {
      return required_size - max_size_;
    }
    return 0;
  }

  return INT_MAX;
}

} // namespace xdg
} // namespace amm
