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

#ifndef AMM_ICON_SEARCH_XDG_SEARCH_H_
#define AMM_ICON_SEARCH_XDG_SEARCH_H_

#include <string>
#include <vector>

#include "xdg/icon_theme.h"
#include "icon_search/icon_search_interface.h"
#include "qualified_icon_theme.h"

namespace amm {
namespace icon_search {

// Understands returning icon file-name based on a file-system search based on XDG standards
class XdgSearch : public IconSearchInterface
{
public:
    XdgSearch(int size, QualifiedIconTheme qualified_icon_theme);
    std::string resolvedName(const std::string &icon_name) const;

private:
    int size_;
    std::vector<std::string> registered_extensions_;
    std::vector<std::string> theme_search_paths_;
    std::vector<xdg::IconTheme> icon_themes_;

    std::vector<xdg::IconSubdirectory> findSearchLocations(const std::string &icon_name) const;
    std::string nameInTheme(const std::string &icon_name) const;
    std::string lookupBySize(const std::vector<xdg::IconSubdirectory> &search_locations) const;
    std::string fallbackName(const std::string &icon_name) const;
};
} // namespace icon_search
} // namespace amm

#endif // AMM_ICON_SEARCH_XDG_SEARCH_H_
