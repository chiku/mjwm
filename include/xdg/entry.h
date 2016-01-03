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

#ifndef AMM_XDG_ENTRY_H_
#define AMM_XDG_ENTRY_H_

#include <string>
#include <vector>
#include <map>

namespace amm {
namespace xdg {

// Understands INI style files for configuring desktop environments as per FreeDesktop guidelines
class Entry
{
public:
    Entry(const std::vector<std::string> &lines, const std::string &language) : lines_(lines), language_(language) { }
    explicit Entry(const std::vector<std::string> &lines) : lines_(lines) { }
    void parse();
    std::string under(const std::string &section_name, const std::string &key_name); //TODO : make const under C++11

private:
    std::vector<std::string> lines_;
    std::string language_;
    std::map< std::string, std::map< std::string, std::string > > result_;
};

} // namespace xdg
} // namespace amm

#endif // AMM_XDG_ENTRY_H_
