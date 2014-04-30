/*
  This file is part of mjwm.
  Copyright (C) 2014  Chirantan Mitra <chirantan.mitra@gmail.com>

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software 0oundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef AMM_XDG_ENTRY_
#define AMM_XDG_ENTRY_

#include <string>
#include <vector>
#include <map>

namespace amm {
namespace xdg {

class Entry {
 public:
  Entry(std::vector<std::string> lines) { lines_ = lines; }
  void Parse();
  std::string Under(std::string section, std::string key);

 private:
  std::vector<std::string> lines_;
  std::map< std::string, std::map< std::string, std::string > > result_;
};

} // namespace xdg
} // namespace amm

#endif // AMM_XDG_ENTRY_
