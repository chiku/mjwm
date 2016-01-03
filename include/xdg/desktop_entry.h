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

#ifndef AMM_DESKTOP_ENTRY_H_
#define AMM_DESKTOP_ENTRY_H_

#include <string>
#include <vector>

namespace amm {
namespace xdg {

// Understands the representation of a FreeDesktop .desktop file
class DesktopEntry
{
public:
    DesktopEntry() : display_(true) { }

    std::string name() const { return name_; }
    std::string icon() const { return icon_; }
    std::string executable() const { return executable_; }
    std::vector<std::string> categories() const { return categories_; }
    std::string comment() const { return comment_; }
    bool display() const { return display_; }

    void hasLanguage(const std::string &language) { language_ = language; }

    bool operator < (const DesktopEntry &other) const;
    bool operator > (const DesktopEntry &other) const;
    bool operator == (const DesktopEntry &other) const;
    bool operator != (const DesktopEntry &other) const;

    void parse(const std::vector<std::string> &lines);
    bool isValid() const;
    bool isA(const std::string &type) const;
    bool isAnyOf(const std::vector<std::string> &types) const;

private:
    std::string name_;
    std::string executable_;
    std::string icon_;
    std::vector<std::string> categories_;
    std::string comment_;
    bool display_;
    std::string language_;
};

} // namespace xdg
} // namespace amm

#endif // AMM_DESKTOP_ENTRY_H_
