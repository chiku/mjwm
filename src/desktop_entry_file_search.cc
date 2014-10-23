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

#include <cstdlib>
#include <string>
#include <vector>

#include "stringx.h"
#include "vectorx.h"
#include "directoryx.h"
#include "system_environment.h"

namespace amm {

static std::vector<std::string> DefaultDirectories() {
  SystemEnvironment environment;
  return environment.ApplicationDirectories(); // TODO : filter directories that don't exist
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
  DirectoryX directory(directory_name);

  if (directory.IsValid()) {
    DirectoryX::Entries entries = directory.AllEntries();

    for (DirectoryX::Entries::iterator entry = entries.begin(); entry != entries.end(); ++entry) {
      std::string entry_name = entry->Name();
      std::string full_path = StringX(directory_name).TerminateWith("/") + entry_name;

      if (StringX(entry_name).EndsWith(".desktop")) {
        desktop_file_names_.push_back(full_path);
      }

      if (entry->isDirectory() && entry_name != ".." && entry_name != ".") {
        Populate(full_path);
      }
    }
  } else if (capture_bad_paths_) {
    bad_paths_.push_back(directory_name);
  }
}

} // namespace amm
