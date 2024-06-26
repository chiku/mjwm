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
#include <vector>

#include "stringx.h"
#include "filex.h"
#include "directoryx.h"
#include "system_environment.h"
#include "xdg/icon_theme.h"
#include "qualified_icon_theme.h"

namespace amm {

QualifiedIconTheme::QualifiedIconTheme(const SystemEnvironment &environment, const std::string &theme_name) : theme_name_(theme_name)
{
    std::vector<std::string> theme_directories = environment.iconThemeDirectories();

    for (std::vector<std::string>::const_iterator dir = theme_directories.begin(); dir != theme_directories.end(); ++dir) {
        if (filex::exists(*dir)) {
            theme_search_paths_.push_back(*dir);
        }
    }
}

xdg::IconTheme QualifiedIconTheme::iconThemeFromName(const std::string &theme_name)
{
    for (std::vector<std::string>::iterator path = theme_search_paths_.begin(); path != theme_search_paths_.end(); ++path) {
        if (directoryx::isValid(*path)) {
            directoryx::Entries entries = directoryx::allEntries(*path);
            for (directoryx::Entries::iterator entry = entries.begin(); entry != entries.end(); ++entry) {
                std::string name = entry->name();
                if (entry->isDirectory() && name != "." && name != "..") {
                    std::string full_path = stringx::terminateWith(*path, "/") + stringx::terminateWith(entry->name(), "/") + "index.theme";
                    std::vector<std::string> lines;

                    if (filex::readLines(full_path, &lines)) {
                        xdg::IconTheme xdg_theme = xdg::IconTheme(lines).internalNameIs(entry->name());
                        if (xdg_theme.isNamed(theme_name)) {
                            return xdg_theme;
                        }
                    }
                }
            }
        }
    }

    std::vector<std::string> empty_lines;
    return xdg::IconTheme(empty_lines);
}

xdg::IconTheme QualifiedIconTheme::currentIconThemeFromName()
{
    return iconThemeFromName(theme_name_);
}

std::vector<xdg::IconTheme> QualifiedIconTheme::themeWithParent()
{
    std::vector<xdg::IconTheme> icon_themes;
    xdg::IconTheme icon_theme = currentIconThemeFromName();
    icon_themes.push_back(icon_theme);

    std::vector<std::string> parent_themes = icon_theme.parents();
    for (std::vector<std::string>::iterator iter = parent_themes.begin(); iter != parent_themes.end(); ++iter) {
        icon_themes.push_back(iconThemeFromName(*iter));
    }
    return icon_themes;
}

} // namespace amm
