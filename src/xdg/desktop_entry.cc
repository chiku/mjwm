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

#include "xdg/desktop_entry.h"

#include <string>
#include <vector>
#include <algorithm>

#include "stringx.h"
#include "xdg/entry.h"

namespace amm {
namespace xdg {

void DesktopEntry::parse(const std::vector<std::string> &lines)
{
    Entry xdg_entry(lines, language_);
    xdg_entry.parse();
    name_ = xdg_entry.under("Desktop Entry", "Name");
    icon_ = xdg_entry.under("Desktop Entry", "Icon");
    executable_ = xdg_entry.under("Desktop Entry", "Exec");
    categories_ = StringX(xdg_entry.under("Desktop Entry", "Categories")).split(";");
    comment_ = xdg_entry.under("Desktop Entry", "Comment");
    std::string display_raw = xdg_entry.under("Desktop Entry", "NoDisplay");
    display_ = display_raw != "true" && display_raw != "1";
    std::sort(categories_.begin(), categories_.end());
}

bool DesktopEntry::operator < (const DesktopEntry &other) const
{
    return name_ < other.name_;
}

bool DesktopEntry::operator > (const DesktopEntry &other) const
{
    return name_ > other.name_;
}

bool DesktopEntry::operator == (const DesktopEntry &other) const
{
    return name_ == other.name_ && executable_ == other.executable_;
}

bool DesktopEntry::operator != (const DesktopEntry &other) const
{
    return !(*this == other);
}

bool DesktopEntry::isValid() const
{
    return !executable_.empty() && !name_.empty() && !icon_.empty();
}

bool DesktopEntry::isA(const std::string &type) const
{
    return std::binary_search(categories_.begin(), categories_.end(), type);
}

bool DesktopEntry::isAnyOf(const std::vector<std::string> &types) const
{
    for (std::vector<std::string>::const_iterator type = types.begin(); type != types.end(); ++type) {
        if (isA(*type)) {
            return true;
        }
    };
    return false;
}

} // namespace xdg
} // namespace amm
