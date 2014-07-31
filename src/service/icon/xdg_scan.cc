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

#include "service/icon/xdg_scan.h"

#include <dirent.h>
#include <climits>
#include <string>
#include <vector>

#include "stringx.h"
#include "filex.h"
#include "system_environment.h"
#include "xdg/icon_subdirectory.h"
#include "xdg/icon_theme.h"

namespace amm {
namespace service {
namespace icon {

static std::vector<std::string> ThemeSearchPaths() {
  SystemEnvironment environment;
  std::vector<std::string> theme_directories = environment.IconThemeDirectories();
  std::vector<std::string> existing_theme_directories;

  for (std::vector<std::string>::const_iterator dir = theme_directories.begin(); dir != theme_directories.end(); ++dir) {
    if (FileX(*dir).Exists()) {
      existing_theme_directories.push_back(*dir);
    }
  }

  return existing_theme_directories;
}

static xdg::IconTheme IconThemeFromName(std::string theme_name) {
  std::vector<std::string> paths = ThemeSearchPaths();

  for (std::vector<std::string>::iterator path = paths.begin(); path != paths.end(); ++path) {
    DIR *directory = opendir(path->c_str());

    if (directory) {
      dirent *entry;
      while((entry = readdir(directory)) != NULL) {
        if (entry->d_type == DT_DIR) {
          std::string full_path = StringX(*path).TerminateWith("/") + StringX(entry->d_name).TerminateWith("/") + "index.theme";

          std::vector<std::string> lines;
          if (FileX(full_path).Load(&lines)) {
            xdg::IconTheme xdg_theme(lines);
            xdg_theme.InternalNameIs(entry->d_name);
            if (xdg_theme.IsNamed(theme_name)) {
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


static std::vector<xdg::IconTheme> IconThemesToSearchFromName(std::string theme) {
  std::vector<xdg::IconTheme> icon_themes;

  xdg::IconTheme icon_theme = IconThemeFromName(theme);
  icon_themes.push_back(icon_theme);

  std::vector<std::string> parent_themes = icon_theme.Parents();
  for (std::vector<std::string>::iterator iter = parent_themes.begin(); iter != parent_themes.end(); ++iter) {
    icon_themes.push_back(IconThemeFromName(*iter));
  }

  return icon_themes;
}

XdgScan::XdgScan(int size, std::string theme) : size_(size), theme_name_(theme) {
  registered_extensions_.push_back(".png");
  registered_extensions_.push_back(".svg");
  registered_extensions_.push_back(".xpm");
  theme_search_paths_ = ThemeSearchPaths();
  icon_themes_= IconThemesToSearchFromName(theme);
}

std::string XdgScan::ResolvedName(std::string icon_name) const {
  std::string file_name = NameInTheme(icon_name);
  if (file_name != "") {
    return file_name;
  }

  file_name = FallbackName(icon_name);
  if (file_name != "") {
    return file_name;
  }

  return icon_name;
}

std::string XdgScan::NameInTheme(std::string icon_name) const {
  std::vector<xdg::IconSubdirectory> search_locations = FindSearchLocations(icon_name);
  std::string file_name = LookupBySize(search_locations);

  return file_name;
}

std::vector<xdg::IconSubdirectory> XdgScan::FindSearchLocations(std::string icon_name) const {
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

std::string XdgScan::LookupBySize(std::vector<xdg::IconSubdirectory> search_locations) const {
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

std::string XdgScan::FallbackName(std::string icon_name) const {
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


} // namespace icon
} // namespace service
} // namespace amm
