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

#ifndef AMM_REPRESENTATION_MENU_START_H_
#define AMM_REPRESENTATION_MENU_START_H_

#include <string>

#include "representation/representation_interface.h"
#include "transformer/transformer_interface.h"

namespace amm {
namespace representation {

class MenuStart : public RepresentationInterface
{
public:
    virtual ~MenuStart() {}
    virtual std::string name() const { return "Menu start"; }
    virtual std::string visit(const transformer::TransformerInterface &transformer) const { return transformer.transform(*this); }
};

} // namespace representation
} // namespace amm

#endif // AMM_REPRESENTATION_MENU_START_H_
