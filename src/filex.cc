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

#include <sys/stat.h>
#include <cstdio>
#include <string>
#include <vector>
#include <fstream> // TODO : enable optional cstdio integration

#include "filex.h"

namespace amm {
namespace filex {

bool exists(const std::string file_name)
{
    struct stat st;
    return stat(file_name.c_str(), &st) == 0;
}

bool existsAsDirectory(const std::string file_name)
{
    struct stat st;
    int result = stat(file_name.c_str(), &st);
    return result == 0 && S_ISDIR(st.st_mode);
}

bool moveTo(const std::string file_name, const std::string &new_path)
{
    return rename(file_name.c_str(), new_path.c_str()) == 0;
}

bool readLines(const std::string file_name, std::vector<std::string> *lines)
{
    std::ifstream file(file_name.c_str());
    if (!file.good()) {
        return false;
    }

    lines->clear();
    std::string line;
    while (std::getline(file, line)) {
        lines->push_back(line);
    }
    file.close();
    return true;
}

bool writeLines(const std::string file_name, const std::vector<std::string> &lines)
{
    std::ofstream file(file_name.c_str());
    if (!file.good()) {
        return false;
    }

    for (std::vector<std::string>::const_iterator line = lines.begin(); line != lines.end(); ++line) {
        file << *line << '\n';
    }

    return true;
}

bool purge(const std::string file_name)
{
    return remove(file_name.c_str()) == 0;
}

} // namespace filex
} // namespace amm
