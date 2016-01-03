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

#ifndef AMM_ICON_SEARCH_CACHING_SEARCH_H_
#define AMM_ICON_SEARCH_CACHING_SEARCH_H_

#include <string>
#include <map>

#include "icon_search_interface.h"

namespace amm {
namespace icon_search {
// Understands reusing older searches for icon names
class CachingSearch : public IconSearchInterface
{
public:
    explicit CachingSearch(IconSearchInterface &actual_searcher) : actual_searcher_(actual_searcher) { }
    std::string resolvedName(const std::string &icon_name) const
    {
        std::map<std::string, std::string>::const_iterator it = IteratorTo(icon_name);
        if (it != cache.end()) {
            return it->second;
        }
        std::string result = actual_searcher_.resolvedName(icon_name);
        cache.insert(std::pair<std::string, std::string>(icon_name, result));
        return result;
    }

    bool isCached(const std::string &icon_name) const { return IteratorTo(icon_name) != cache.end(); }

private:
    IconSearchInterface& actual_searcher_;
    mutable std::map<std::string, std::string> cache;
    std::map<std::string, std::string>::const_iterator IteratorTo(const std::string &icon_name) const { return cache.find(icon_name); }
};

} // namespace icon_search
} // namespace amm

#endif // AMM_ICON_SEARCH_CACHING_SEARCH_H_
