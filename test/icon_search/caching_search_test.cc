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

#include "icon_search/caching_search.h"

#include <string>
#include "../doctest.h"
#include "icon_search/icon_search_interface.h"

namespace amm {
namespace icon_search {

class TestSearch : public IconSearchInterface
{
public:
    TestSearch() : extension_(".png") { }
    std::string resolvedName(const std::string &icon_name) const { return icon_name + extension_; }
    void extensionIs(const std::string &extension) { extension_ = extension; }
private:
    std::string extension_;
};

SCENARIO("icon_search::CachingSearch") {
    TestSearch *actual_searcher = new TestSearch;

    GIVEN("An icon search that caches results") {
        CachingSearch caching_searcher(*actual_searcher);

        WHEN("retrieving an unsearched item") {
            THEN("the item is absent from the cache") {
                CHECK_FALSE(caching_searcher.isCached("vlc"));
            }
        }

        WHEN("retrieving a searched item") {
            caching_searcher.resolvedName("vlc");
            THEN("the item is present in the cache") {
                CHECK(caching_searcher.isCached("vlc"));
            }

            THEN("the item is same as the original item") {
                CHECK(caching_searcher.resolvedName("vlc") == "vlc.png");
            }

            WHEN("the underlying implementation returns a different item") {
                caching_searcher.resolvedName("vlc");
                actual_searcher->extensionIs(".svg");
                THEN("the original entry is retrieved") {
                    CHECK(caching_searcher.resolvedName("vlc") == "vlc.png");
                }
            }
        }
    }
}

} // namespace icon_search
} // namespace amm
