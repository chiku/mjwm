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

#include <dirent.h>
#include <string>

#include "directoryx.h"
#include "stringx.h"
#include "filex.h"

namespace amm {
namespace directoryx {

bool isValid(const std::string path)
{
    DIR* directory = opendir(path.c_str());
    if (directory) {
        closedir(directory);
        return true;
    } else {
        return false;
    }
}

Entries::Entries(const std::string &path) : path_(path)
{
    directory_ = opendir(path.c_str());
}

Entries::~Entries()
{
    if (directory_ != NULL) {
        closedir(directory_);
    }
}

Entries::SearchResult Entries::nextName()
{
    dirent *entry_;
    while((entry_ = readdir(directory_)) != NULL) {
        std::string full_path = stringx::terminateWith(path_, "/") + entry_->d_name;
        current_result_ = SearchResult::Success(entry_->d_name, filex::existsAsDirectory(full_path));
        return current_result_;
    }
    current_result_ = SearchResult::Bad();
    return current_result_;
}

Entries::iterator Entries::iterator::operator ++()
{
    Entries::iterator output = *this;
    if (!subdirs_->nextName().success) {
        subdirs_ = NULL;
    }
    return output;
}

Entries::iterator Entries::iterator::operator ++(int)
{
    if (!subdirs_->nextName().success) {
        subdirs_ = NULL;
    }
    return *this;
}

Entries allEntries(const std::string path)
{
    return Entries(path);
}

} // namespace directoryx
} // namespace amm
