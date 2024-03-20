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

#include <string>
#include <vector>
#include <algorithm>

#include "doctest.h"
#include "directoryx.h"

#define DO_QUOTE(X)       #X
#define QUOTE(X)          DO_QUOTE(X)

namespace amm {

void assertFileNamesAreCorrect(std::vector<std::string> names)
{
    std::sort(names.begin(), names.end());
    REQUIRE(names.size() == 8);
    CHECK(names[0] == "desktop.vlc");
    CHECK(names[1] == "htop.desktop");
    CHECK(names[2] == "missing.desktop");
    CHECK(names[3] == "mousepad.desktop");
    CHECK(names[4] == "suppressed.desktop");
    CHECK(names[5] == "suppressedinvalid.desktop");
    CHECK(names[6] == "unclassified.desktop");
    CHECK(names[7] == "vlc.desktop");
}

void assertDirectoryNamesAreCorrect(std::vector<std::string> names)
{
    std::sort(names.begin(), names.end());
    REQUIRE(names.size() == 4);
    CHECK(names[0] == ".");
    CHECK(names[1] == "..");
    CHECK(names[2] == "empty");
    CHECK(names[3] == "nested");
}

void assertNamesAreCorrect(std::vector<std::string> names)
{
    std::sort(names.begin(), names.end());
    REQUIRE(names.size() == 12);
    CHECK(names[0] == ".");
    CHECK(names[1] == "..");
    CHECK(names[2] == "desktop.vlc");
    CHECK(names[3] == "empty");
    CHECK(names[4] == "htop.desktop");
    CHECK(names[5] == "missing.desktop");
    CHECK(names[6] == "mousepad.desktop");
    CHECK(names[7] == "nested");
    CHECK(names[8] == "suppressed.desktop");
    CHECK(names[9] == "suppressedinvalid.desktop");
    CHECK(names[10] == "unclassified.desktop");
    CHECK(names[11] == "vlc.desktop");
}

SCENARIO("directoryx") {
    std::string fixture_dir = QUOTE(FIXTUREDIR);

    GIVEN("A directoryx") {
        WHEN("present") {
            THEN("it is valid") {
                CHECK(directoryx::isValid(fixture_dir + "applications"));
            }
        }

        WHEN("not present") {
            THEN("it is invalid") {
                CHECK_FALSE(directoryx::isValid("does-not-exist"));
            }
        }

        WHEN("it has files under itself") {
            directoryx::Entries entries = directoryx::allEntries(fixture_dir + "applications");
            WHEN("its contained files are retrieved one at a time") {
                THEN("the retrieved entry has the name of the file and knows if it is a directory") {
                    std::vector<std::string> file_names;
                    std::vector<std::string> directory_names;

                    for (int i = 0; i < 12; i++) {
                        directoryx::Entries::SearchResult result = entries.nextName();
                        CHECK(result.success);
                        (result.isDirectory ? directory_names : file_names).push_back(result.name);
                    }

                    assertFileNamesAreCorrect(file_names);
                    assertDirectoryNamesAreCorrect(directory_names);
                }
            }

            WHEN("its entries are iterated beyond range") {
                THEN("it fails") {
                    for (int i = 0; i < 12; i++) {
                        entries.nextName();
                    }
                    directoryx::Entries::SearchResult result = entries.nextName();

                    CHECK_FALSE(result.success);
                    CHECK_FALSE(result.isDirectory);
                    CHECK(result.name == "");
                }
            }

            WHEN("it is iterated for contained files (with prefix, indirection & not-equals)") {
                THEN("it has the contained file and sub-directory names") {
                    std::vector<std::string> file_names;
                    std::vector<std::string> directory_names;
                    for (directoryx::Entries::iterator entry = entries.begin(); entry != entries.end(); ++entry) {
                        (entry->isDirectory() ? directory_names : file_names).push_back(entry->name());
                    }

                    assertFileNamesAreCorrect(file_names);
                    assertDirectoryNamesAreCorrect(directory_names);
                }
            }

            WHEN("it is iterated for contained files (with postfix, access to pointer at & equals)") {
                THEN("it has the contained file and sub-directory names") {
                    std::vector<std::string> file_names;
                    std::vector<std::string> directory_names;
                    for (directoryx::Entries::iterator entry = entries.begin(); !(entry == entries.end()); entry++) {
                        (entry->isDirectory() ? directory_names : file_names).push_back(entry->name());
                    }

                    assertFileNamesAreCorrect(file_names);
                    assertDirectoryNamesAreCorrect(directory_names);
                }
            }
        }

        WHEN("iterated multiple times") {
            THEN("all iterations have the same results") {
                directoryx::Entries first_set = directoryx::allEntries(fixture_dir + "applications");
                directoryx::Entries second_set = directoryx::allEntries(fixture_dir + "applications");

                std::vector<std::string> first_set_names;
                for (directoryx::Entries::iterator entry = first_set.begin(); entry != first_set.end(); ++entry) {
                    first_set_names.push_back(entry->name());
                }

                std::vector<std::string> second_set_names;
                for (directoryx::Entries::iterator entry = second_set.begin(); entry != second_set.end(); ++entry) {
                    second_set_names.push_back(entry->name());
                }

                assertNamesAreCorrect(first_set_names);
                assertNamesAreCorrect(second_set_names);
            }
        }
    }
}

} // namespace amm
