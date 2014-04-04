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

#include <string>
#include <sstream>
#include <vector>

#include "util.h"
#include "transformer/jwm.h"

namespace amm {
namespace transformer {

static std::string remove_field_code(std::string input) {
  std::vector<std::string> result;
  std::vector<std::string> tokens = StringX(input).Split(" ");

  for (std::vector<std::string>::const_iterator iter = tokens.begin(); iter != tokens.end(); ++iter) {
    if (!(iter->size() >= 1 && (*iter)[0] == '%')) {
      result.push_back(*iter);
    }
  }

  return VectorX(result).Join(" ");
}

std::string Jwm::Transform(const representation::MenuStart &entry) const {
  std::stringstream stream;
  stream << "<JWM>"
         << std::endl
         << "<!--" << entry.name() << "-->";
  return stream.str();
}

std::string Jwm::Transform(const representation::MenuEnd &entry) const {
  std::stringstream stream;
  stream << "<!--" << entry.name() << "-->"
         << std::endl
         << "</JWM>";
  return stream.str();
}

std::string Jwm::Transform(const representation::SubcategoryStart &entry) const {
  std::stringstream stream;
  stream << "    <Menu "
         << "label=\"" << StringX(entry.name()).Encode()
         << "\" icon=\"" << entry.icon()
         << "\">";
  return stream.str();
}

std::string Jwm::Transform(const representation::SubcategoryEnd &entry) const {
  std::stringstream stream;
  stream << "    <!--" << entry.name() << "-->"
         << std::endl
         << "    </Menu>";
  return stream.str();
}

std::string Jwm::Transform(const representation::Program &entry) const {
  std::stringstream stream;
  stream << "        <Program "
         << "label=\"" << StringX(entry.name()).Encode()
         << "\" icon=\"" << StringX(entry.icon()).Encode()
         << "\">"
         << remove_field_code(entry.executable())
         << "</Program>";
  return stream.str();
}

} // namespace transformer
} // namespace amm