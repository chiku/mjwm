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

#ifndef AMM_ICON_SUBDIRECTORY_H_
#define AMM_ICON_SUBDIRECTORY_H_

#include <string>

namespace amm {
namespace xdg {

enum IconSubdirectoryType
{
    FIXED,
    SCALABLE,
    THRESHOLD,
    INVALID
};

// Understands the representation of a FreeDesktop .desktop file
class IconSubdirectory
{
public:
    IconSubdirectory();
    IconSubdirectory(std::string name, std::string size);

    std::string name() { return name_; }
    int size() { return size_; }
    IconSubdirectoryType type() { return type_; }
    int maxSize() { return max_size_; }
    int minSize() { return min_size_; }
    int threshold() { return threshold_; }
    std::string location() { return location_; }
    bool matches(int required_size);
    int distance(int required_size);

    IconSubdirectory& type(std::string max_size);
    IconSubdirectory& maxSize(std::string max_size);
    IconSubdirectory& minSize(std::string min_size);
    IconSubdirectory& threshold(std::string threshold);
    IconSubdirectory& location(std::string location);

private:
    std::string name_;
    IconSubdirectoryType type_;
    int size_;
    int max_size_;
    int min_size_;
    int threshold_;
    std::string location_;
};

} // namespace xdg
} // namespace amm

#endif // AMM_ICON_SUBDIRECTORY_H_
