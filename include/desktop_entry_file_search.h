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

#ifndef AMM_DESKTOP_ENTRY_FILE_SEARCH_H_
#define AMM_DESKTOP_ENTRY_FILE_SEARCH_H_

#include <string>
#include <vector>

namespace amm {
// Understands search for .desktop files
class DesktopEntryFileSearch
{
public:
    void resolve();
    void registerDirectories(const std::vector<std::string> &directory_names) { directory_names_ = directory_names; }
    void registerDefaultDirectories();
    std::vector<std::string> desktopEntryFileNames() const { return desktop_file_names_; }
    std::vector<std::string> badPaths() const { return bad_paths_; }

private:
    void populate(const std::string &directory_name);

    std::vector<std::string> directory_names_;
    std::vector<std::string> desktop_file_names_;
    std::vector<std::string> bad_paths_;
};
} // namespace amm

#endif // AMM_DESKTOP_ENTRY_FILE_SEARCH_H_
