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

#include "filex.h"

#include <sys/stat.h>
#include <cstdio>
#include <string>
#include <vector>
#include <fstream> // TODO : enable optional cstdio integration

namespace amm {

bool FileX::exists() const
{
    struct stat st;
    return stat(name_.c_str(), &st) == 0;
}

bool FileX::existsAsDirectory() const
{
    struct stat st;
    int result = stat(name_.c_str(), &st);
    return result == 0 && S_ISDIR(st.st_mode);
}

bool FileX::moveTo(const std::string &new_path) const
{
    return rename(name_.c_str(), new_path.c_str()) == 0;
}

bool FileX::readLines(std::vector<std::string> *lines) const
{
    std::ifstream file(name_.c_str());
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

bool FileX::writeLines(const std::vector<std::string> &lines) const
{
    if (exists()) {
        return false;
    }

    std::ofstream file(name_.c_str());
    if (!file.good()) {
        return false;
    }

    for (std::vector<std::string>::const_iterator line = lines.begin(); line != lines.end(); ++line) {
        file << *line << '\n';
    }

    return true;
}

bool FileX::purge() const
{
    return remove(name_.c_str()) == 0;
}

} // namespace amm
