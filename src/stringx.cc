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

#include "stringx.h"

#include <string>
#include <vector>
#include <sstream>
#include <algorithm>

namespace amm {

bool StringX::endsWith(const std::string &delimeter) const
{
    const size_t length = string_.length();
    const size_t delimeter_length = delimeter.length();

    return ((length >= delimeter_length) && (string_.compare(length - delimeter_length, delimeter_length, delimeter) == 0));
}

std::string StringX::terminateWith(const std::string &delimeter) const
{
    return endsWith(delimeter) ? string_ : string_ + delimeter;
}

std::string StringX::encode() const
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

std::string StringX::trim() const
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

std::vector<std::string> StringX::split(const std::string &delimeter) const
{
    std::string raw = string_;
    size_t delimeter_length = delimeter.length();
    std::vector<std::string> result;

    raw = StringX(raw).terminateWith(delimeter);

    size_t start = 0U;
    size_t end = raw.find(delimeter);

    while (end != std::string::npos && end != 0) {
        result.push_back(raw.substr(start, end - start));
        start = end + delimeter_length;
        end = raw.find(delimeter, start);
    }

    return result;
}

} // namespace amm
