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
#include <vector>
#include <sstream>
#include <algorithm>

#include "utils.h"

amm::stringx::stringx(std::string string)
{
  string_ = string;
}

bool
amm::stringx::ends_with(const std::string delimeter) const
{
  const size_t length = string_.length();
  const size_t delimeter_length = delimeter.length();

  return ((length >= delimeter_length) && (string_.compare(length - delimeter_length, delimeter_length, delimeter) == 0));
}

std::string
amm::stringx::terminate_with(std::string delimeter)
{
  return ends_with(delimeter) ? string_ : string_ + delimeter;
}

std::string
amm::stringx::encode() const
{
  std::string result;
  result.reserve(string_.size());

  for(size_t pos = 0; pos != string_.size(); ++pos) {
    switch(string_[pos]) {
      case '&' : result.append("&amp;");       break;
      case '\"': result.append("&quot;");      break;
      case '\'': result.append("&apos;");      break;
      case '<' : result.append("&lt;");        break;
      case '>' : result.append("&gt;");        break;
      default  : result.append(&string_[pos], 1); break;
    }
  }

  return result;
}

std::string
amm::stringx::trim() const
{
  const std::string whitespace = " \t\n";
  const size_t begin = string_.find_first_not_of(whitespace);

  if (begin == std::string::npos) {
    return "";
  }

  const size_t end = string_.find_last_not_of(whitespace);
  const size_t range = end - begin + 1;

  return string_.substr(begin, range);
}

std::vector<std::string>
amm::stringx::split(const std::string delimeter) const
{
  std::string raw = string_;
  size_t delimeter_length = delimeter.length();
  std::vector<std::string> result;

  raw = amm::stringx(raw).terminate_with(delimeter);

  size_t start = 0U;
  size_t end = raw.find(delimeter);

  while (end != std::string::npos) {
    result.push_back(raw.substr(start, end - start));
    start = end + delimeter_length;
    end = raw.find(delimeter, start);
  }

  return result;
}


amm::vectorx::vectorx(std::vector<std::string> vector)
{
  vector_ = vector;
}

std::string
amm::vectorx::join(std::string delimeter) const
{
  std::stringstream stream;
  size_t vector_size = vector_.size();

  if (vector_size == 0) {
    return "";
  }

  if (vector_size >= 2) {
    for (size_t i = 0; i < vector_size - 1; ++i) {
      stream << vector_[i] << delimeter;
    }
  }
  stream << vector_[vector_size - 1];

  return stream.str();
}

std::vector<std::string>
amm::vectorx::terminate_with(std::string delimiter) const
{
  std::vector<std::string> result;

  for (std::vector<std::string>::const_iterator i = vector_.begin(); i != vector_.end(); ++i) {
    result.push_back(amm::stringx(*i).terminate_with(delimiter));
  }

  return result;
}

std::vector<std::string>
amm::vectorx::unique() const
{
  std::vector<std::string> result = vector_;

  std::sort(result.begin(), result.end());
  std::vector<std::string>::iterator it = std::unique(result.begin(), result.end());
  result.resize(std::distance(result.begin(), it));

  return result;
}
