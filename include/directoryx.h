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

#ifndef AMM_DIRECTORYX_H_
#define AMM_DIRECTORYX_H_

#include <dirent.h>
#include <string>

namespace amm
{

class DirectoryX
{
public:
    DirectoryX(std::string path) : path_(path) {}
    bool isValid() const;

    class Entries
    {
    public:
        Entries(std::string path);
        ~Entries();

        struct SearchResult
        {
            std::string name;
            bool success;
            bool isDirectory;
            SearchResult() : name(""), success(false), isDirectory(false) { }
            SearchResult(std::string name_, bool success_, bool isDirectory_) : name(name_), success(success_), isDirectory(isDirectory_) {}
            static SearchResult Bad() { return SearchResult("", false, false); }
            static SearchResult Success(std::string name, bool is_directory_) { return SearchResult(name, true, is_directory_); }
        };

        class iterator
        {
        public:
            iterator(Entries *subdirs, bool terminate) : subdirs_(subdirs), terminate_(terminate) {}
            Entries* operator ->() { return subdirs_; }
            Entries& operator *() { return *subdirs_; }
            iterator operator ++();
            iterator operator ++(int);
            bool operator ==(const iterator& rhs) { return terminate_ == rhs.terminate_; }
            bool operator !=(const iterator& rhs) { return terminate_ != rhs.terminate_; }
        private:
            Entries *subdirs_;
            SearchResult result_;
            bool terminate_;
        };

        iterator begin() { nextName(); return iterator(this, false); }
        iterator end() { return iterator(this, true); }

        std::string name() const { return current_result_.name; }
        bool isDirectory() const { return current_result_.isDirectory; }
        SearchResult nextName();

    private:
        DIR *directory_;
        SearchResult current_result_;
    };

    Entries allEntries() { return Entries(path_); }

private:
    std::string path_;
};

} // namespace amm

#endif // AMM_DIRECTORYX_H_
