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

#ifndef AMM_STATS_H_
#define AMM_STATS_H_

#include <string>
#include <vector>

namespace amm {
// Understands the summary of populating a menu
class Stats
{
public:
    void addClassifiedFile(const std::string &file) { classified_files_.push_back(file); }
    void addUnclassifiedFile(const std::string &file) { unclassified_files_.push_back(file); }
    void addSuppressedFile(const std::string &file) { suppressed_files_.push_back(file); }
    void addUnparsedFile(const std::string &file) { unparsed_files_.push_back(file); }
    void addUnhandledClassifications(const std::vector<std::string> &classifications);

    size_t totalFiles() const;
    size_t totalParsedFiles() const;
    size_t totalUnclassifiedFiles() const;
    size_t totalSuppressedFiles() const;
    size_t totalUnparsedFiles() const;
    std::vector<std::string> unparsedFiles() const;
    std::vector<std::string> unhandledClassifications();

    std::string details(const std::string &summary_type);

private:
    std::vector<std::string> classified_files_;
    std::vector<std::string> unclassified_files_;
    std::vector<std::string> unparsed_files_;
    std::vector<std::string> suppressed_files_;
    std::vector<std::string> unhandled_classifications_;
};
} // namespace amm

#endif // AMM_STATS_H_
