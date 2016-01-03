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

#ifndef AMM_DIRECTORYX_H_
#define AMM_DIRECTORYX_H_

#include <dirent.h>
#include <string>

namespace amm
{

class DirectoryX
{
public:
    explicit DirectoryX(const std::string &path) : path_(path) {}
    bool isValid() const;

    class Entries
    {
    public:
        Entries(const std::string &path);
        ~Entries();

        class SearchResult
        {
        public:
            std::string name;
            bool success;
            bool isDirectory;
            SearchResult() : name(""), success(false), isDirectory(false) { }
            static SearchResult Bad() { return SearchResult("", false, false); }
            static SearchResult Success(const std::string &name, bool is_directory_) { return SearchResult(name, true, is_directory_); }
        private:
            SearchResult(const std::string &name_, bool success_, bool isDirectory_) : name(name_), success(success_), isDirectory(isDirectory_) {}
        };

        class iterator
        {
        public:
            iterator(Entries *subdirs) : subdirs_(subdirs) { }
            Entries* operator ->() const { return subdirs_; }
            Entries& operator *() const { return *subdirs_; }
            iterator operator ++();
            iterator operator ++(int);
            bool operator ==(const iterator& rhs) const { return subdirs_ == rhs.subdirs_; }
            bool operator !=(const iterator& rhs) const { return subdirs_ != rhs.subdirs_; }
        private:
            Entries *subdirs_;
        };

        iterator begin() { nextName(); return iterator(this); }
        iterator end() { return iterator(NULL); }

        std::string name() const { return current_result_.name; }
        bool isDirectory() const { return current_result_.isDirectory; }
        SearchResult nextName();

    private:
        std::string path_;
        DIR *directory_;
        SearchResult current_result_;
    };

    Entries allEntries() { return Entries(path_); }

private:
    std::string path_;
};

} // namespace amm

#endif // AMM_DIRECTORYX_H_
