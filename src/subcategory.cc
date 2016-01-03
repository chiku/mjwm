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

#include "subcategory.h"

#include <string>
#include <vector>
#include <algorithm>

#include "xdg/desktop_entry.h"

namespace amm {

Subcategory::Subcategory(const std::string &display_name, const std::string &icon_name, const std::string &classification_name) :
        display_name_(display_name), icon_name_(icon_name)
{
    classification_names_.push_back(classification_name);
}

Subcategory::Subcategory(const std::string &display_name, const std::string &icon_name, const std::vector<std::string> &classification_names) :
        display_name_(display_name), icon_name_(icon_name), classification_names_(classification_names) {}

bool Subcategory::hasEntries() const
{
    return !desktopEntries().empty();
}

void Subcategory::addDesktopEntry(const xdg::DesktopEntry &desktop_entry)
{
    desktop_entries_.push_back(desktop_entry);
}

void Subcategory::sortDesktopEntries()
{
    std::sort(desktop_entries_.begin(), desktop_entries_.end());
    std::vector<xdg::DesktopEntry>::iterator it = std::unique(desktop_entries_.begin(), desktop_entries_.end());
    desktop_entries_.resize(std::distance(desktop_entries_.begin(), it));
}

} // namespace amm
