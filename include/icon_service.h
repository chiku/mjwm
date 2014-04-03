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

#ifndef AMM_ICON_SERVICE_H_
#define AMM_ICON_SERVICE_H_

#include <string>

namespace amm {
// Understands the way to search for the full path to a icon file
// Currently it returns the name of icon with an optional extension
class IconService {
private:
  std::string extension_;

public:
  void set_extension(std::string extension) { extension_ = extension; }

  std::string ResolvedName(std::string icon_name) const;
};
} // namespace amm

#endif // AMM_ICON_SERVICE_H_
