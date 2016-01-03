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

#ifndef AMM_ICON_THEME_H_
#define AMM_ICON_THEME_H_

#include <string>
#include <vector>

#include "icon_subdirectory.h"

namespace amm {
namespace xdg {

// Understands the representation of a FreeDesktop .desktop file
class IconTheme
{
public:
    explicit IconTheme(const std::vector<std::string> &lines);

    std::string name() const { return name_; }
    std::string internalName() const { return internal_name_; }
    std::vector<std::string> parents() const { return parents_; }
    std::vector<IconSubdirectory> directories() const { return directories_; }
    bool isNamed(const std::string &name) const { return name == name_ || name == internal_name_; }
    IconTheme internalNameIs(const std::string &internal_name) { internal_name_ = internal_name; return *this; }

private:
    std::string name_;
    std::string internal_name_;
    std::vector<std::string> parents_;
    std::vector<IconSubdirectory> directories_;
};

} // namespace xdg
} // namespace amm

#endif // AMM_ICON_THEME_H_
