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

#ifndef AMM_ICON_THEME_H_
#define AMM_ICON_THEME_H_

#include <string>
#include <vector>

#include "icon_subdirectory.h"

namespace amm {
namespace xdg {

// Understands the representation of a FreeDesktop .desktop file
class IconTheme {
 public:
  explicit IconTheme(std::vector<std::string> lines);

  std::string Name() const { return name_; }
  std::string InternalName() const { return internal_name_; }
  std::vector<std::string> Parents() const { return parents_; }
  std::vector<IconSubdirectory> Directories() const { return directories_; }
  IconTheme InternalNameIs(std::string internal_name) { internal_name_ = internal_name; return *this; }

  bool IsNamed(std::string name) { return name == name_ || name == internal_name_; }

 private:
  std::string name_;
  std::string internal_name_;
  std::vector<std::string> parents_;
  std::vector<IconSubdirectory> directories_;
};

} // namespace xdg
} // namespace amm

#endif // AMM_ICON_THEME_H_
