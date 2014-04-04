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
#include <sstream>
#include <vector>
#include <algorithm>

#include "vectorx.h"

namespace amm {

void Stats::AddUnhandledClassifications(std::vector<std::string> classifications) {
  unhandled_classifications_.insert(unhandled_classifications_.begin(), classifications.begin(), classifications.end());
}

size_t Stats::TotalFiles() const {
  return classified_files_.size() + unclassified_files_.size() + suppressed_files_.size() + unparsed_files_.size();
}

size_t Stats::TotalParsedFiles() const {
  return classified_files_.size() + unclassified_files_.size();
}

size_t Stats::TotalUnclassifiedFiles() const {
  return unclassified_files_.size();
}

size_t Stats::TotalSuppressedFiles() const {
  return suppressed_files_.size();
}

size_t Stats::TotalUnparsedFiles() const {
  return unparsed_files_.size();
}

std::vector<std::string> Stats::UnparsedFiles() const {
  return unparsed_files_;
}

std::vector<std::string> Stats::UnhandledClassifications() {
  if (unhandled_classifications_.size() > 1) {
    std::sort(unhandled_classifications_.begin(), unhandled_classifications_.end());
    std::vector<std::string>::iterator it = std::unique(unhandled_classifications_.begin(), unhandled_classifications_.end());
    unhandled_classifications_.resize(std::distance(unhandled_classifications_.begin(), it));
  }

  return unhandled_classifications_;
}

std::string Stats::ShortSummary() const {
  std::stringstream stream;
  stream << "Total desktop files: " << TotalFiles() << std::endl;
  stream << "Parsed desktop files: " << TotalParsedFiles() << std::endl;
  stream << "Unparsed desktop files: " << TotalUnparsedFiles() << std::endl;
  stream << "Suppressed desktop files (NoDisplay): " << TotalSuppressedFiles() << std::endl;
  stream << "Unclassified desktop files: " << TotalUnclassifiedFiles() << std::endl;
  return stream.str();
}

std::string Stats::NormalSummary() const {
  std::stringstream stream;
  stream << ShortSummary();

  if (TotalUnparsedFiles() > 0) {
    stream << "List of unparsed files: " << VectorX(unparsed_files_).Join(", ") << std::endl;
  }

  return stream.str();
}

std::string Stats::LongSummary() {
  std::stringstream stream;
  stream << NormalSummary();

  if (TotalSuppressedFiles() > 0) {
    stream << "List of suppressed files: " << VectorX(suppressed_files_).Join(", ") << std::endl;
  }

  if (TotalUnclassifiedFiles() > 0) {
    stream << "List of unclassified files: " << VectorX(unclassified_files_).Join(", ") << std::endl;
  }

  if (unhandled_classifications_.size() > 0) {
    stream << "List of unhandled classifications: " << VectorX(UnhandledClassifications()).Join(", ") << std::endl;
  }

  return stream.str();
}

} // namespace amm
