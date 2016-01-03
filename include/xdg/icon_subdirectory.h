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
    IconSubdirectory(const std::string &name, const std::string &size);

    std::string name() const { return name_; }
    int size() const { return size_; }
    IconSubdirectoryType type() const { return type_; }
    int maxSize() const { return max_size_; }
    int minSize() const { return min_size_; }
    int threshold() const { return threshold_; }
    std::string location() const { return location_; }
    bool matches(int required_size) const;
    int distance(int required_size) const;

    IconSubdirectory& type(std::string max_size);
    IconSubdirectory& maxSize(const std::string &max_size);
    IconSubdirectory& minSize(const std::string &min_size);
    IconSubdirectory& threshold(const std::string &threshold);
    IconSubdirectory& location(const std::string &location);

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
