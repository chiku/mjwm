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

#ifndef AMM_SERVICE_ICON_MIRROR_H_
#define AMM_SERVICE_ICON_MIRROR_H_

#include <string>
#include <vector>

#include "service/icon_service_interface.h"

namespace amm {
namespace service {
namespace icon {
// Understands returning the input file-name as the output
class Mirror : public IconServiceInterface {
 public:
  std::string ResolvedName(std::string icon_name) const { return icon_name; }

 private:
};
} // namespace icon
} // namespace service
} // namespace amm

#endif // AMM_SERVICE_ICON_MIRROR_H_
