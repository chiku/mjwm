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

#include <stddef.h>
#include <string>
#include <vector>

#include "stringx.h"

namespace amm {
namespace stringx {

bool endsWith(const std::string &string, const std::string &delimeter)
{
    const size_t length = string.length();
    const size_t delimeter_length = delimeter.length();

    return ((length >= delimeter_length) && (string.compare(length - delimeter_length, delimeter_length, delimeter) == 0));
}

std::string terminateWith(const std::string &string, const std::string &delimeter)
{
    return endsWith(string, delimeter) ? string : string + delimeter;
}

std::string encode(const std::string &string)
{
    std::string result;
    result.reserve(string.size());

    for(size_t pos = 0; pos != string.size(); ++pos) {
        switch(string[pos]) {
            case '&' : result.append("&amp;");       break;
            case '\"': result.append("&quot;");      break;
            case '\'': result.append("&apos;");      break;
            case '<' : result.append("&lt;");        break;
            case '>' : result.append("&gt;");        break;
            default  : result.append(&string[pos], 1); break;
        }
    }

    return result;
}

std::string trim(const std::string &string)
{
    const std::string whitespace = " \t\n";
    const size_t begin = string.find_first_not_of(whitespace);

    if (begin == std::string::npos) {
        return "";
    }

    const size_t end = string.find_last_not_of(whitespace);
    const size_t range = end - begin + 1;

    return string.substr(begin, range);
}

std::vector<std::string> split(const std::string &string, const std::string &delimeter)
{
    std::string raw = string;
    size_t delimeter_length = delimeter.length();
    std::vector<std::string> result;

    raw = terminateWith(raw, delimeter);

    size_t start = 0U;
    size_t end = raw.find(delimeter);

    while (end != std::string::npos && end != 0) {
        result.push_back(raw.substr(start, end - start));
        start = end + delimeter_length;
        end = raw.find(delimeter, start);
    }

    return result;
}

} // namespace stringx
} // namespace amm
