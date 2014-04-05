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

#include "service/file_search_service.h"

#include <dirent.h>
#include <limits.h>
#include <cstdlib>
#include <string>
#include <vector>

#include "stringx.h"
#include "vectorx.h"

namespace amm {

static const std::string kDesktopExtension = ".desktop";
static const std::string kApplications = "applications";

static void AppendXdgDataHome(std::vector<std::string> *output) {
  char *xdg_data_home = std::getenv("XDG_DATA_HOME");
  char *home = std::getenv("HOME");

  if (xdg_data_home != NULL) {
    output->push_back(StringX(xdg_data_home).TerminateWith("/"));
  } else if (home != NULL) {
    output->push_back(std::string(home) + "/.local/share/");
  }
}

static void AppendXdgDataDirs(std::vector<std::string> *output) {
  char *xdg_data_dirs = std::getenv("XDG_DATA_DIRS");
  if (xdg_data_dirs != NULL) {
    std::vector<std::string> directories = StringX(xdg_data_dirs).Split(":");
    for (std::vector<std::string>::const_iterator directory = directories.begin(); directory != directories.end(); ++directory) {
      output->push_back(StringX(*directory).TerminateWith("/"));
    }
  } else {
    output->push_back("/usr/local/share/");
    output->push_back("/usr/share/");
  }
}

static std::vector<std::string> DefaultDirectories() {
  std::vector<std::string> directory_bases;
  AppendXdgDataHome(&directory_bases);
  AppendXdgDataDirs(&directory_bases);

  std::vector<std::string> directory_names;
  for (std::vector<std::string>::const_iterator base = directory_bases.begin(); base != directory_bases.end(); ++base) {
    directory_names.push_back(std::string(*base) + kApplications);
  }

  return directory_names;
}

FileSearchService::FileSearchService() {
  capture_bad_paths_ = true;
}

void FileSearchService::RegisterDirectoriesWithFallback(std::vector<std::string> directory_names) {
  if (directory_names.size() <= 0) {
    capture_bad_paths_ = false;
    directory_names = DefaultDirectories();
  }
  RegisterDirectories(directory_names);
}

void FileSearchService::Resolve() {
  desktop_file_names_.clear();
  bad_paths_.clear();

  std::vector<std::string> terminated_names = VectorX(directory_names_).TerminateWith("/");
  std::vector<std::string> unique_names = VectorX(terminated_names).Unique();

  for (std::vector<std::string>::const_iterator name = unique_names.begin(); name != unique_names.end(); ++name) {
    Populate(*name);
  }
}

void FileSearchService::Populate(std::string directory_name) {
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
        FileSearchService::Populate(full_path);
      }
    }
    closedir(directory);
  } else if (capture_bad_paths_) {
    bad_paths_.push_back(directory_name);
  }
}

} // namespace amm
