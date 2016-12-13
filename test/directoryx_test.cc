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

#define DO_QUOTE(X)       #X
#define QUOTE(X)          DO_QUOTE(X)

#include "directoryx.h"

#include <string>
#include <vector>
#include <algorithm>

#include "doctest.h"

namespace amm {

void assertFileNamesAreCorrect(std::vector<std::string> names)
{
    std::sort(names.begin(), names.end());
    REQUIRE(names.size() == 7);
    CHECK(names[0] == "desktop.vlc");
    CHECK(names[1] == "missing.desktop");
    CHECK(names[2] == "mousepad.desktop");
    CHECK(names[3] == "suppressed.desktop");
    CHECK(names[4] == "suppressedinvalid.desktop");
    CHECK(names[5] == "unclassified.desktop");
    CHECK(names[6] == "vlc.desktop");
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
    REQUIRE(names.size() == 11);
    CHECK(names[0] == ".");
    CHECK(names[1] == "..");
    CHECK(names[2] == "desktop.vlc");
    CHECK(names[3] == "empty");
    CHECK(names[4] == "missing.desktop");
    CHECK(names[5] == "mousepad.desktop");
    CHECK(names[6] == "nested");
    CHECK(names[7] == "suppressed.desktop");
    CHECK(names[8] == "suppressedinvalid.desktop");
    CHECK(names[9] == "unclassified.desktop");
    CHECK(names[10] == "vlc.desktop");
}

SCENARIO("DirectoryX") {
    std::string fixture_dir = QUOTE(FIXTUREDIR);

    GIVEN("A directoryx") {
        WHEN("present") {
            THEN("it is valid") {
                DirectoryX directory(fixture_dir + "applications");
                CHECK(directory.isValid());
            }
        }

        WHEN("not present") {
            DirectoryX directory("does-not-exist");
            THEN("it is invalid") {
                CHECK_FALSE(directory.isValid());
            }
        }

        WHEN("it has files under itself") {
            DirectoryX directory(fixture_dir + "applications");
            DirectoryX::Entries entries = directory.allEntries();
            WHEN("its contained files are retrieved one at a time") {
                THEN("the retrieved entry has the name of the file and knows if it is a directory") {
                    std::vector<std::string> file_names;
                    std::vector<std::string> directory_names;

                    for (int i = 0; i < 11; i++) {
                        DirectoryX::Entries::SearchResult result = entries.nextName();
                        CHECK(result.success);
                        (result.isDirectory ? directory_names : file_names).push_back(result.name);
                    }

                    assertFileNamesAreCorrect(file_names);
                    assertDirectoryNamesAreCorrect(directory_names);
                }
            }

            WHEN("its entries are iterated beyond range") {
                THEN("it fails") {
                    for (int i = 0; i < 11; i++) {
                        entries.nextName();
                    }
                    DirectoryX::Entries::SearchResult result = entries.nextName();

                    CHECK_FALSE(result.success);
                    CHECK_FALSE(result.isDirectory);
                    CHECK(result.name == "");
                }
            }

            WHEN("it is iterated for contained files (with prefix, indirection & not-equals)") {
                THEN("it has the contained file and sub-directory names") {
                    std::vector<std::string> file_names;
                    std::vector<std::string> directory_names;
                    for (DirectoryX::Entries::iterator entry = entries.begin(); entry != entries.end(); ++entry) {
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
                    for (DirectoryX::Entries::iterator entry = entries.begin(); !(entry == entries.end()); entry++) {
                        (entry->isDirectory() ? directory_names : file_names).push_back(entry->name());
                    }

                    assertFileNamesAreCorrect(file_names);
                    assertDirectoryNamesAreCorrect(directory_names);
                }
            }
        }

        WHEN("iterated multiple times") {
            THEN("all iterations have the same results") {
                DirectoryX directory(fixture_dir + "applications");
                DirectoryX::Entries first_set = directory.allEntries();
                DirectoryX::Entries second_set = directory.allEntries();

                std::vector<std::string> first_set_names;
                for (DirectoryX::Entries::iterator entry = first_set.begin(); entry != first_set.end(); ++entry) {
                    first_set_names.push_back(entry->name());
                }

                std::vector<std::string> second_set_names;
                for (DirectoryX::Entries::iterator entry = second_set.begin(); entry != second_set.end(); ++entry) {
                    second_set_names.push_back(entry->name());
                }

                assertNamesAreCorrect(first_set_names);
                assertNamesAreCorrect(second_set_names);
            }
        }
    }
}

} // namespace amm
