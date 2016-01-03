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

#ifndef AMM_QUALIFIED_ICON_THEME_H_
#define AMM_QUALIFIED_ICON_THEME_H_

#include <string>
#include <vector>

#include "system_environment.h"
#include "xdg/icon_theme.h"

namespace amm {

// Understands how an icon-theme exists out in the file-system
class QualifiedIconTheme
{
public:
    QualifiedIconTheme(const SystemEnvironment &environment, const std::string &theme_name);
    std::vector<std::string> themeSearchPaths() { return theme_search_paths_; }
    std::vector<xdg::IconTheme> themeWithParent();

private:
    std::string theme_name_;
    std::vector<std::string> theme_search_paths_;
    xdg::IconTheme currentIconThemeFromName();
    xdg::IconTheme iconThemeFromName(const std::string &theme_name);
};

}

#endif // AMM_QUALIFIED_ICON_THEME_H_
