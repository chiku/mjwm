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

#include "xdg/icon_subdirectory.h"

#include <cstdlib>
#include <string>
#include <limits>
#include <algorithm>

namespace amm {
namespace xdg {

inline static int stringToInt(const std::string &str)
{
    return atoi(str.c_str());
}

IconSubdirectory::IconSubdirectory()
{
    type_ = INVALID;
}

IconSubdirectory::IconSubdirectory(const std::string &name, const std::string &size) : name_(name)
{
    size_ = stringToInt(size);
    type_ = THRESHOLD;
    max_size_ = size_;
    min_size_ = size_;
    threshold_ = 2;
}

IconSubdirectory& IconSubdirectory::type(std::string type)
{
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

IconSubdirectory& IconSubdirectory::maxSize(const std::string &max_size)
{
    if (max_size != "") {
        max_size_ = stringToInt(max_size);
    }
    return *this;
}

IconSubdirectory& IconSubdirectory::minSize(const std::string &min_size)
{
    if (min_size != "") {
        min_size_ = stringToInt(min_size);
    }
    return *this;
}

IconSubdirectory& IconSubdirectory::threshold(const std::string &threshold)
{
    if (threshold != "") {
        threshold_ = stringToInt(threshold);
    }
    return *this;
}

IconSubdirectory& IconSubdirectory::location(const std::string &location)
{
    if (location != "") {
        location_ = location;
    }
    return *this;
}

bool IconSubdirectory::matches(int required_size) const
{
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

int IconSubdirectory::distance(int required_size) const
{
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
