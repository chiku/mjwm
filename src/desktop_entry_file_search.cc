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

#include "desktop_entry_file_search.h"

#include <dirent.h>
#include <cstdlib>
#include <string>
#include <vector>

#include "stringx.h"
#include "vectorx.h"
#include "environment_variable.h"

namespace amm {

static const std::string kDesktopExtension = ".desktop";
static const std::string kApplications = "applications";

static std::vector<std::string> DefaultDirectories() {
  EnvironmentVariable environment_variable;
  return environment_variable.ApplicationDirectories();
}

void DesktopEntryFileSearch::RegisterDefaultDirectories() {
  capture_bad_paths_ = false;
  RegisterDirectories(DefaultDirectories());
}

void DesktopEntryFileSearch::Resolve() {
  desktop_file_names_.clear();
  bad_paths_.clear();

  std::vector<std::string> terminated_names = VectorX(directory_names_).TerminateWith("/");
  std::vector<std::string> unique_names = VectorX(terminated_names).Unique();

  for (std::vector<std::string>::const_iterator name = unique_names.begin(); name != unique_names.end(); ++name) {
    Populate(*name);
  }
}

void DesktopEntryFileSearch::Populate(std::string directory_name) {
  DIR *directory = opendir(directory_name.c_str());

  if (directory) {
    dirent *entry;
    while((entry = readdir(directory)) != NULL) {
      std::string entry_name = entry->d_name;
      std::string full_path = StringX(directory_name).TerminateWith("/") + entry_name;

      if (StringX(entry_name).EndsWith(kDesktopExtension)) {
        desktop_file_names_.push_back(full_path);
      }

      if ((entry->d_type & DT_DIR) && entry_name != ".." && entry_name != "." && full_path.size() <= PATH_MAX) {
        Populate(full_path);
      }
    }
    closedir(directory);
  } else if (capture_bad_paths_) {
    bad_paths_.push_back(directory_name);
  }
}

} // namespace amm
