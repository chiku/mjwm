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

#include "service/icon/scan.h"

#include <string>
#include <vector>

#include "stringx.h"

namespace amm {
namespace service {
namespace icon {

Scan::Scan() {
  registered_extensions_.push_back(".png");
  registered_extensions_.push_back(".svg");
  registered_extensions_.push_back(".xpm");
}

std::string Scan::ResolvedName(std::string icon_name) const {
  return icon_name;
}

} // namespace icon
} // namespace service
} // namespace amm
