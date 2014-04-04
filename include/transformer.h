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

#ifndef AMM_TRANSFORMER_H_
#define AMM_TRANSFORMER_H_

#include <string>

#include "representation.h"

namespace amm {
namespace representation {
  // Forward declare classes to break circular dependency between amm::representation::* and amm::transformer::*
  class MenuStart;
  class MenuEnd;
  class SubcategoryStart;
  class SubcategoryEnd;
  class Program;
} // namespace representation

// TODO : rename file to transformer_interface.h to match the class name

class TransformerInterface {
  public:
    virtual std::string Transform(representation::MenuStart *entry) = 0;
    virtual std::string Transform(representation::MenuEnd *entry) = 0;
    virtual std::string Transform(representation::SubcategoryStart *entry) = 0;
    virtual std::string Transform(representation::SubcategoryEnd *entry) = 0;
    virtual std::string Transform(representation::Program *entry) = 0;
  };
} // namespace amm

#endif // AMM_TRANSFORMER_H_
