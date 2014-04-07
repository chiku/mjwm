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

#include "service/icon/scan.h"

#include <sys/stat.h>
#include <string>
#include <vector>

#include "stringx.h"
#include "service/environment_variable.h"

namespace amm {
namespace service {
namespace icon {

static bool DoesPathExist(std::string path) {
  struct stat st;
  return stat(path.c_str(), &st) == 0;
}

Scan::Scan() {
  registered_extensions_.push_back(".png");
  registered_extensions_.push_back(".svg");
  registered_extensions_.push_back(".xpm");

  std::string home = environment_variable.Home();
  std::vector<std::string> xdg_data_dirs = environment_variable.XdgDataDirectories();

  if (home != "") {
    Scan::RegisterLookupDirectory(home + "./icons/");
  }
  for (std::vector<std::string>::const_iterator dir = xdg_data_dirs.begin(); dir != xdg_data_dirs.end(); ++dir) {
    Scan::RegisterLookupDirectory(std::string(*dir) + "icons/");
    Scan::RegisterLookupDirectory(std::string(*dir) + "icons/Faenza/apps/48/");
    Scan::RegisterLookupDirectory(std::string(*dir) + "icons/Faenza/actions/48/");
    Scan::RegisterLookupDirectory(std::string(*dir) + "icons/hicolor/48x48/apps/");
    Scan::RegisterLookupDirectory(std::string(*dir) + "icons/hicolor/48x48/actions/");
  }
  Scan::RegisterLookupDirectory("/usr/share/pixmaps");
}

void Scan::RegisterLookupDirectory(std::string path) {
  struct stat st;
  int result = stat(path.c_str(), &st);
  if (result == 0 && S_ISDIR(st.st_mode)) {
    search_locations_.push_back(path);
  }
}

std::string Scan::ResolvedName(std::string icon_name) const {
  return DoesPathExist(icon_name) ? icon_name : SearchedFileName(icon_name);
}

std::string Scan::SearchedFileName(std::string icon_name) const {
  std::vector<std::string> extensions = ViableExtensions(icon_name);

  for (std::vector<std::string>::const_iterator location = search_locations_.begin(); location != search_locations_.end(); ++location) {
    for (std::vector<std::string>::const_iterator extension = extensions.begin(); extension != extensions.end(); ++extension) {
      std::string full_name = (*location) + icon_name + (*extension);
      if (DoesPathExist(full_name)) {
        return full_name;
      }
    }
  }

  return icon_name;
}

std::vector<std::string> Scan::ViableExtensions(std::string icon_name) const {
  std::vector<std::string> extensions;
  if (ShouldAppendExtension(icon_name)) {
    extensions = registered_extensions_;
  } else {
    extensions.push_back("");
  }

  return extensions;
}

bool Scan::ShouldAppendExtension(std::string icon_name) const {
  for (std::vector<std::string>::const_iterator extension = registered_extensions_.begin(); extension != registered_extensions_.end(); ++extension) {
    if (StringX(icon_name).EndsWith(*extension)) {
      return false;
    }
  }

  return true;
}

} // namespace icon
} // namespace service
} // namespace amm
