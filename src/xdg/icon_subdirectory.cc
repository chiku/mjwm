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
#include <string>
#include <limits>
#include <algorithm>

namespace amm {
namespace xdg {

static int StringToInt(std::string str) {
  return atoi(str.c_str());
}

IconSubdirectory::IconSubdirectory(std::string name, std::string size) : name_(name) {
  size_ = StringToInt(size);
  type_ = THRESHOLD;
  max_size_ = size_;
  min_size_ = size_;
  threshold_ = 2;
}

IconSubdirectory& IconSubdirectory::Type(std::string type) {
  std::transform(type.begin(), type.end(), type.begin(), ::tolower);
  if (type == "fixed") {
    type_ = FIXED;
  } else if (type == "threshold" || type == "") {
    type_ = THRESHOLD;
  } else if (type == "scalable") {
    type_ = SCALABLE;
  } else {
    type_ = INVALID;
  }
  return *this;
}

IconSubdirectory& IconSubdirectory::MaxSize(std::string max_size) {
  if (max_size != "") {
    max_size_ = StringToInt(max_size);
  }
  return *this;
}

IconSubdirectory& IconSubdirectory::MinSize(std::string min_size) {
  if (min_size != "") {
    min_size_ = StringToInt(min_size);
  }
  return *this;
}

IconSubdirectory& IconSubdirectory::Threshold(std::string threshold) {
  if (threshold != "") {
    threshold_ = StringToInt(threshold);
  }
  return *this;
}

bool IconSubdirectory::Matches(int required_size) {
  if (type_ == FIXED) {
    return size_ == required_size;
  }
  if (type_ == SCALABLE) {
    return (min_size_ <= required_size) && (required_size <= max_size_);
  }
  if (type_ == THRESHOLD) {
    return (size_ - threshold_ <= required_size) && (required_size <= size_ + threshold_);
  }

  return false;
}

int IconSubdirectory::Distance(int required_size) {
  if (type_ == FIXED) {
    return abs(size_ - required_size);
  }
  if (type_ == SCALABLE) {
    if (required_size < min_size_) {
      return min_size_ - required_size;
    }
    if (required_size > max_size_) {
      return required_size - max_size_;
    }
    return 0;
  }
  if (type_ == THRESHOLD) {
    if (required_size < size_ - threshold_) {
      return min_size_ - required_size;
    }
    if (required_size > size_ + threshold_) {
      return required_size - max_size_;
    }
    return 0;
  }

  return std::numeric_limits<int>::max();
}

} // namespace xdg
} // namespace amm
