/*
  This file is part of mjwm.
  Copyright (C) 2014  Chirantan Mitra <chirantan.mitra@gmail.com>

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

#include "icon_search/xdg_search.h"

#include <climits>
#include <string>
#include <vector>

#include "stringx.h"
#include "filex.h"
#include "system_environment.h"
#include "xdg/icon_subdirectory.h"
#include "xdg/icon_theme.h"
#include "qualified_icon_theme.h"

namespace amm {
namespace icon_search {

XdgSearch::XdgSearch(int size, std::string theme) : size_(size)
{
    SystemEnvironment environment;
    registered_extensions_.push_back(".png");
    registered_extensions_.push_back(".svg");
    registered_extensions_.push_back(".xpm");
    QualifiedIconTheme qualified_icon_theme = QualifiedIconTheme(environment, theme);
    theme_search_paths_ = qualified_icon_theme.ThemeSearchPaths();
    icon_themes_ = qualified_icon_theme.ParentThemes();
}

std::string XdgSearch::resolvedName(std::string icon_name) const
{
    std::string file_name = nameInTheme(icon_name);
    if (file_name != "") {
        return file_name;
    }

    file_name = fallbackName(icon_name);
    if (file_name != "") {
        return file_name;
    }

    return icon_name;
}

std::string XdgSearch::nameInTheme(std::string icon_name) const
{
    std::vector<xdg::IconSubdirectory> search_locations = findSearchLocations(icon_name);
    std::string file_name = lookupBySize(search_locations);

    return file_name;
}

std::vector<xdg::IconSubdirectory> XdgSearch::findSearchLocations(std::string icon_name) const
{
    std::vector<xdg::IconSubdirectory> search_locations;

    for (std::vector<xdg::IconTheme>::const_iterator icon_theme = icon_themes_.begin(); icon_theme != icon_themes_.end(); ++icon_theme) {
        std::vector<xdg::IconSubdirectory> theme_subdirs = icon_theme->Directories();

        for (std::vector<xdg::IconSubdirectory>::iterator subdir = theme_subdirs.begin(); subdir != theme_subdirs.end(); ++subdir) {
            for (std::vector<std::string>::const_iterator search_path = theme_search_paths_.begin(); search_path != theme_search_paths_.end(); ++search_path) {
                for (std::vector<std::string>::const_iterator extension = registered_extensions_.begin(); extension != registered_extensions_.end(); ++extension) {
                    std::string file_name = StringX(*search_path + "/" + icon_theme->InternalName() + "/" + subdir->Name() + "/" + icon_name).TerminateWith(*extension);
                    if (FileX(file_name).Exists()) {
                        search_locations.push_back(xdg::IconSubdirectory(subdir->Location(file_name)));
                    }
                }
            }
        }
    }

    return search_locations;
}

std::string XdgSearch::lookupBySize(std::vector<xdg::IconSubdirectory> search_locations) const
{
    for (std::vector<xdg::IconSubdirectory>::iterator subdir = search_locations.begin(); subdir != search_locations.end(); ++subdir) {
        if (subdir->Matches(size_)) {
            return subdir->Location();
        }
    }

    int minimal_size = INT_MAX;
    std::string closest_file_name = "";
    for (std::vector<xdg::IconSubdirectory>::iterator subdir = search_locations.begin(); subdir != search_locations.end(); ++subdir) {
        int distance = subdir->Distance(size_);
        if (distance < minimal_size) {
            closest_file_name = subdir->Location();
            minimal_size = distance;
        }
    }

    return closest_file_name;
}

std::string XdgSearch::fallbackName(std::string icon_name) const
{
    for (std::vector<std::string>::const_iterator directory = theme_search_paths_.begin(); directory != theme_search_paths_.end(); ++directory) {
        for (std::vector<std::string>::const_iterator extension = registered_extensions_.begin(); extension != registered_extensions_.end(); ++extension) {
            std::string file_name = amm::StringX(amm::StringX(*directory).TerminateWith("/") + icon_name).TerminateWith(*extension);
            if (FileX(file_name).Exists()) {
                return file_name;
            }
        }
    }

    return "";
}

} // namespace icon_search
} // namespace amm
