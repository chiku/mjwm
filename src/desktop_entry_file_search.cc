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
#include "vectorx.h"
#include "directoryx.h"
#include "system_environment.h"
#include "desktop_entry_file_search.h"

namespace amm {

static std::vector<std::string> defaultDirectories()
{
    std::vector<std::string> existing_directories;
    std::vector<std::string> directories = SystemEnvironment().applicationDirectories();
    for (std::vector<std::string>::iterator directory = directories.begin(); directory != directories.end(); ++directory) {
        if (directoryx::isValid(*directory)) {
            existing_directories.push_back(*directory);
        }
    }
    return existing_directories;
}

void DesktopEntryFileSearch::registerDefaultDirectories()
{
    registerDirectories(defaultDirectories());
}

void DesktopEntryFileSearch::resolve()
{
    desktop_file_names_.clear();
    bad_paths_.clear();

    std::vector<std::string> terminated_names = vectorx::terminateEachWith(directory_names_, "/");
    std::vector<std::string> unique_names = vectorx::unique(terminated_names);

    for (std::vector<std::string>::const_iterator name = unique_names.begin(); name != unique_names.end(); ++name) {
        populate(*name);
    }
}

void DesktopEntryFileSearch::populate(const std::string &directory_name)
{
    if (!directoryx::isValid(directory_name)) {
        bad_paths_.push_back(directory_name);
        return;
    }

    directoryx::Entries entries = directoryx::allEntries(directory_name);

    for (directoryx::Entries::iterator entry = entries.begin(); entry != entries.end(); ++entry) {
        std::string entry_name = entry->name();
        std::string full_path = stringx::terminateWith(directory_name, "/") + entry_name;

        if (stringx::endsWith(entry_name, ".desktop")) {
            desktop_file_names_.push_back(full_path);
        }

        if (entry->isDirectory() && entry_name != ".." && entry_name != ".") {
            populate(full_path);
        }
    }
}
} // namespace amm
