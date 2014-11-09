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

#include "stats.h"

#include <string>
#include <vector>
#include <sstream>
#include <algorithm>

#include "vectorx.h"

namespace amm {

void Stats::addUnhandledClassifications(std::vector<std::string> classifications)
{
    unhandled_classifications_.insert(unhandled_classifications_.begin(), classifications.begin(), classifications.end());
}

size_t Stats::totalFiles() const
{
    return classified_files_.size() + unclassified_files_.size() + suppressed_files_.size() + unparsed_files_.size();
}

size_t Stats::totalParsedFiles() const
{
    return classified_files_.size() + unclassified_files_.size();
}

size_t Stats::totalUnclassifiedFiles() const
{
    return unclassified_files_.size();
}

size_t Stats::totalSuppressedFiles() const
{
    return suppressed_files_.size();
}

size_t Stats::totalUnparsedFiles() const
{
    return unparsed_files_.size();
}

std::vector<std::string> Stats::unparsedFiles() const
{
    return unparsed_files_;
}

std::vector<std::string> Stats::unhandledClassifications()
{
    if (unhandled_classifications_.size() > 1) {
        std::sort(unhandled_classifications_.begin(), unhandled_classifications_.end());
        std::vector<std::string>::iterator it = std::unique(unhandled_classifications_.begin(), unhandled_classifications_.end());
        unhandled_classifications_.resize(std::distance(unhandled_classifications_.begin(), it));
    }

    return unhandled_classifications_;
}

std::string Stats::details(std::string summary_type)
{
    std::stringstream stream;
    stream << "Total desktop files: " << totalFiles() << " ["
           << totalParsedFiles() << " Parsed, "
           << totalUnparsedFiles()  << " Unparsed, "
           << totalSuppressedFiles() << " Suppressed"
           << "]\n";
    stream << "Unclassified files: " << totalUnclassifiedFiles() << std::endl;

    if (summary_type == "normal" || summary_type == "long") {
        if (totalUnparsedFiles() > 0) {
            stream << "Unparsed files: " << VectorX(unparsed_files_).join(", ") << std::endl;
        }
    }

    if (summary_type == "long") {
        if (totalSuppressedFiles() > 0) {
            stream << "Suppressed files: " << VectorX(suppressed_files_).join(", ") << std::endl;
        }

        if (totalUnclassifiedFiles() > 0) {
            stream << "Unclassified files: " << VectorX(unclassified_files_).join(", ") << std::endl;
        }

        if (unhandled_classifications_.size() > 0) {
            stream << "Unhandled classifications: " << VectorX(unhandledClassifications()).join(", ") << std::endl;
        }
    }

    return stream.str();
}

} // namespace amm
