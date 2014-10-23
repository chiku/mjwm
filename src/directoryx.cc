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

#include "directoryx.h"

#include <dirent.h>
#include <string>

namespace amm {

bool DirectoryX::IsValid() const
{
    DIR* directory = opendir(path_.c_str());
    if (directory) {
        closedir(directory);
        return true;
    } else {
        return false;
    }
}

DirectoryX::Entries::Entries(std::string path)
{
    directory_ = opendir(path.c_str());
}

DirectoryX::Entries::~Entries()
{
    if (directory_ != NULL) {
        closedir(directory_);
    }
}

DirectoryX::Entries::SearchResult DirectoryX::Entries::NextName()
{
    dirent *entry_;
    while((entry_ = readdir(directory_)) != NULL) {
        current_result_ = SearchResult::Success(entry_->d_name, entry_->d_type == DT_DIR);
        return current_result_;
    }
    current_result_ = SearchResult::Bad();
    return current_result_;
}

DirectoryX::Entries::iterator DirectoryX::Entries::iterator::operator ++()
{
    result_ = subdirs_->NextName();
    terminate_ = !result_.success;
    return *this;
}

DirectoryX::Entries::iterator DirectoryX::Entries::iterator::operator ++(int)
{
    DirectoryX::Entries::iterator output = *this;
    result_ = subdirs_->NextName();
    terminate_ = !result_.success;
    return output;
}

} // namespace amm
