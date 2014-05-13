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

// Understands the representation of a FreeDesktop .desktop file
class IconSubdirectory {
 public:
  IconSubdirectory() { }
  IconSubdirectory(
    std::string name,
    std::string type,
    int size,
    int max_size,
    int min_size,
    int threshold
  ) : name_(name), type_(type), size_(size), max_size_(max_size), min_size_(min_size), threshold_(threshold) { }

  std::string Name() { return name_; }
  int Size() { return size_; }
  std::string Type() { return type_; }
  int MaxSize() { return max_size_; }
  int MinSize() { return min_size_; }
  int Threshold() { return threshold_; }
  bool Matches(int required_size);
  int Distance(int required_size);

  IconSubdirectory& Name(std::string name);
  IconSubdirectory& Type(std::string type);
  IconSubdirectory& Size(int size);

 private:
  std::string name_;
  std::string type_;
  int size_;
  int max_size_;
  int min_size_;
  int threshold_;
};

} // namespace xdg
} // namespace amm

#endif // AMM_ICON_SUBDIRECTORY_H_
