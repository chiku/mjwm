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

#ifndef AMM_COMMAND_LINE_OPTIONS_PARSER_H_
#define AMM_COMMAND_LINE_OPTIONS_PARSER_H_

#include "amm_options.h"

namespace amm {
// Understands parsing of user specified options supplied to the program
class CommandLineOptionsParser
{
public:
    CommandLineOptionsParser(const std::string &home, const std::string &language) : home_(home), language_(language) { }
    AmmOptions parse(int argc, char *const *argv);

private:
    void allowMultipleEntries() const;
    std::string home_;
    std::string language_;
};
} // namespace amm

#endif // AMM_COMMAND_LINE_OPTIONS_PARSER_H_
