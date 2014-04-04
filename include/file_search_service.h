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

#ifndef AMM_FILE_SEARCH_SERVICE_H_
#define AMM_FILE_SEARCH_SERVICE_H_

#include <dirent.h>
#include <string>
#include <vector>

namespace amm {
// Understands search for .desktop files
class FileSearchService {
 public:
  FileSearchService();

  void RegisterDirectoriesWithDefaultFallback(std::vector<std::string> directory_names);
  void RegisterDefaultDirectories();
  void Resolve();

  void RegisterDirectories(std::vector<std::string> directory_names) { directory_names_ = directory_names; }
  std::vector<std::string> DesktopFileNames() const { return desktop_file_names_; }
  std::vector<std::string> BadPaths() const { return bad_paths_; }

 private:
  std::vector<std::string> directory_names_;
  std::vector<std::string> desktop_file_names_;
  std::vector<std::string> bad_paths_;
  bool capture_bad_paths_;

  void Populate(DIR* directory, std::string directory_name);
};
}

#endif // AMM_FILE_SEARCH_SERVICE_H_
