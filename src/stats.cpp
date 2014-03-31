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

#include <string>
#include <sstream>
#include <vector>
#include <algorithm>

#include "utils.h"
#include "stats.h"

void
amm::stats::add_classified_file(std::string file)
{
  classified_files_.push_back(file);
}

void
amm::stats::add_unclassified_file(std::string file)
{
  unclassified_files_.push_back(file);
}

void
amm::stats::add_suppressed_file(std::string file)
{
  suppressed_files_.push_back(file);
}

void
amm::stats::add_unparsed_file(std::string file)
{
  unparsed_files_.push_back(file);
}

void
amm::stats::add_unhandled_classifications(std::vector<std::string> classifications)
{
  unhandled_classifications_.insert(unhandled_classifications_.begin(), classifications.begin(), classifications.end());
}

size_t
amm::stats::total_files() const
{
  return classified_files_.size() + unclassified_files_.size() + suppressed_files_.size() + unparsed_files_.size();
}

size_t
amm::stats::total_parsed_files() const
{
  return classified_files_.size() + unclassified_files_.size();
}

size_t
amm::stats::total_unclassified_files() const
{
  return unclassified_files_.size();
}

size_t
amm::stats::total_suppressed_files() const
{
  return suppressed_files_.size();
}

size_t
amm::stats::total_unparsed_files() const
{
  return unparsed_files_.size();
}

std::vector<std::string>
amm::stats::unparsed_files() const
{
  return unparsed_files_;
}

std::vector<std::string>
amm::stats::unhandled_classifications()
{
  if (unhandled_classifications_.size() > 1) {
    std::sort(unhandled_classifications_.begin(), unhandled_classifications_.end());
    std::vector<std::string>::iterator it = std::unique(unhandled_classifications_.begin(), unhandled_classifications_.end());
    unhandled_classifications_.resize(std::distance(unhandled_classifications_.begin(), it));
  }

  return unhandled_classifications_;
}

std::string
amm::stats::short_summary() const
{
  std::stringstream stream;
  stream << "Total desktop files: " << total_files() << std::endl;
  stream << "Parsed desktop files: " << total_parsed_files() << std::endl;
  stream << "Unparsed desktop files: " << total_unparsed_files() << std::endl;
  stream << "Suppressed desktop files (NoDisplay): " << total_suppressed_files() << std::endl;
  stream << "Unclassified desktop files: " << total_unclassified_files() << std::endl;
  return stream.str();
}

std::string
amm::stats::summary() const
{
  std::stringstream stream;
  stream << short_summary();

  if (total_unparsed_files() > 0) {
    stream << "List of unparsed files: " << amm::vectorx(unparsed_files_).join(", ") << std::endl;
  }

  return stream.str();
}

std::string
amm::stats::long_summary()
{
  std::stringstream stream;
  stream << summary();

  if (total_suppressed_files() > 0) {
    stream << "List of suppressed files: " << amm::vectorx(suppressed_files_).join(", ") << std::endl;
  }

  if (total_unclassified_files() > 0) {
    stream << "List of unclassified files: " << amm::vectorx(unclassified_files_).join(", ") << std::endl;
  }

  if (unhandled_classifications_.size() > 0) {
    stream << "List of unhandled classifications: " << amm::vectorx(unhandled_classifications()).join(", ") << std::endl;
  }

  return stream.str();
}
