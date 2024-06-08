/*
  This file is part of mjwm.
  Copyright (C) 2014-2024  Chirantan Mitra <chirantan.mitra@gmail.com>

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

#include "stringx.h"
#include "vectorx.h"
#include "system_environment.h"
#include "terminal.h"
#include "transformer/jwm.h"
#include "representation/menu_end.h"
#include "representation/menu_start.h"
#include "representation/program.h"
#include "representation/subcategory_end.h"
#include "representation/subcategory_start.h"

namespace amm {
namespace transformer {

static std::string removeFieldCode(const std::string &input)
{
    std::vector<std::string> result;
    std::vector<std::string> tokens = stringx::split(input, " ");

    for (std::vector<std::string>::const_iterator iter = tokens.begin(); iter != tokens.end(); ++iter) {
        if (!(iter->size() >= 1 && (*iter)[0] == '%')) {
            result.push_back(*iter);
        }
    }

    return vectorx::join(result, " ");
}

static std::string withTerminal(const bool terminal, const std::string &exec, const std::string &name)
{
    if (!terminal) {
        return exec;
    }

    SystemEnvironment environment;
    std::string term = environment.term();

    return terminalCommand(term, exec, name);
}

std::string Jwm::transform(const representation::MenuStart &entry) const
{
    std::stringstream stream;
    stream << "<JWM>"
        << std::endl
        << "    <!--" << entry.name() << "-->";
    return stream.str();
}

std::string Jwm::transform(const representation::MenuEnd &entry) const
{
    std::stringstream stream;
    stream << "    <!--" << entry.name() << "-->"
        << std::endl
        << "</JWM>";
    return stream.str();
}

std::string Jwm::transform(const representation::SubcategoryStart &entry) const
{
    std::stringstream stream;
    stream << "    <Menu "
        << "label=\"" << stringx::encode(entry.name())
        << "\" icon=\"" << entry.icon()
        << "\">";
    return stream.str();
}

std::string Jwm::transform(const representation::SubcategoryEnd &entry) const
{
    std::stringstream stream;
    stream << "        <!--" << entry.name() << "-->"
        << std::endl
        << "    </Menu>";
    return stream.str();
}

std::string Jwm::transform(const representation::Program &entry) const
{
    std::string label = stringx::encode(entry.name());
    std::string icon = stringx::encode(entry.icon());
    std::string tooltip = stringx::encode(entry.comment());
    std::string executable = entry.executable();
    std::stringstream stream;
    stream << "        <Program "
        << "label=\"" << label
        << "\" icon=\"" << icon
        << "\" tooltip=\"" << tooltip
        << "\">"
        << withTerminal(entry.terminal(), removeFieldCode(executable), label)
        << "</Program>";
    return stream.str();
}

} // namespace transformer
} // namespace amm
