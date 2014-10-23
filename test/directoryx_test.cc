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

#define CATCH_CONFIG_MAIN

#include "directoryx.h"

#include <string>
#include <vector>
#include <algorithm>

#include "catch.hpp"

namespace amm {

void assertFileNamesAreCorrect(std::vector<std::string> names)
{
    std::sort(names.begin(), names.end());
    REQUIRE(names.size() == 7);
    REQUIRE(names[0] == "desktop.vlc");
    REQUIRE(names[1] == "missing.desktop");
    REQUIRE(names[2] == "mousepad.desktop");
    REQUIRE(names[3] == "suppressed.desktop");
    REQUIRE(names[4] == "suppressedinvalid.desktop");
    REQUIRE(names[5] == "unclassified.desktop");
    REQUIRE(names[6] == "vlc.desktop");
}

void assertDirectoryNamesAreCorrect(std::vector<std::string> names)
{
    std::sort(names.begin(), names.end());
    REQUIRE(names.size() == 4);
    REQUIRE(names[0] == ".");
    REQUIRE(names[1] == "..");
    REQUIRE(names[2] == "empty");
    REQUIRE(names[3] == "nested");
}

void assertNamesAreCorrect(std::vector<std::string> names)
{
    std::sort(names.begin(), names.end());
    REQUIRE(names.size() == 11);
    REQUIRE(names[0] == ".");
    REQUIRE(names[1] == "..");
    REQUIRE(names[2] == "desktop.vlc");
    REQUIRE(names[3] == "empty");
    REQUIRE(names[4] == "missing.desktop");
    REQUIRE(names[5] == "mousepad.desktop");
    REQUIRE(names[6] == "nested");
    REQUIRE(names[7] == "suppressed.desktop");
    REQUIRE(names[8] == "suppressedinvalid.desktop");
    REQUIRE(names[9] == "unclassified.desktop");
    REQUIRE(names[10] == "vlc.desktop");
}

SCENARIO("DirectoryX", "[directoryx]") {
    GIVEN("A directoryx") {
        WHEN("it exists") {
            THEN("it is valid") {
                DirectoryX directory("test/fixtures/applications");
                REQUIRE(directory.IsValid());
            }
        }

        WHEN("it doesn't exist") {
            DirectoryX directory("does-not-exist");
            THEN("it is invalid") {
                REQUIRE(!directory.IsValid());
            }
        }

        WHEN("containing files") {
            DirectoryX directory("test/fixtures/applications");
            DirectoryX::Entries entries = directory.AllEntries();
            WHEN("its contained files are retrieved") {
                THEN("it has the name of the file") {
                    std::vector<std::string> file_names;
                    std::vector<std::string> directory_names;

                    for (int i = 0; i < 11; i++) {
                        DirectoryX::Entries::SearchResult result = entries.NextName();
                        REQUIRE(result.success);
                        (result.isDirectory ? directory_names : file_names).push_back(result.name);
                    }

                    assertFileNamesAreCorrect(file_names);
                    assertDirectoryNamesAreCorrect(directory_names);
                }
            }

            WHEN("its entries are iterated beyond range") {
                THEN("it fails") {
                    for (int i = 0; i < 11; i++) {
                        entries.NextName();
                    }
                    DirectoryX::Entries::SearchResult result = entries.NextName();

                    REQUIRE(!result.success);
                    REQUIRE(!result.isDirectory);
                    REQUIRE(result.name == "");
                }
            }

            WHEN("it is iterated for contained files (with prefix, indirection & not-equals)") {
                THEN("it has the contained file and sub-directory names") {
                    std::vector<std::string> file_names;
                    std::vector<std::string> directory_names;
                    for (DirectoryX::Entries::iterator entry = entries.begin(); entry != entries.end(); ++entry) {
                        (entry->isDirectory() ? directory_names : file_names).push_back(entry->Name());
                    }

                    assertFileNamesAreCorrect(file_names);
                    assertDirectoryNamesAreCorrect(directory_names);
                }
            }

            WHEN("it is iterated for contained files (with postfix, value at & equals)") {
                THEN("it has the contained file and sub-directory names") {
                    std::vector<std::string> file_names;
                    std::vector<std::string> directory_names;
                    for (DirectoryX::Entries::iterator entry = entries.begin(); !(entry == entries.end()); entry++) {
                        (entry->isDirectory() ? directory_names : file_names).push_back(entry->Name());
                    }

                    assertFileNamesAreCorrect(file_names);
                    assertDirectoryNamesAreCorrect(directory_names);
                }
            }
        }

        WHEN("iterated multiple times") {
            THEN("all iterations have results") {
                DirectoryX directory("test/fixtures/applications");
                DirectoryX::Entries first_set = directory.AllEntries();
                DirectoryX::Entries second_set = directory.AllEntries();
                std::vector<std::string> first_set_names;
                std::vector<std::string> second_set_names;

                for (DirectoryX::Entries::iterator entry = first_set.begin(); entry != first_set.end(); ++entry) {
                    first_set_names.push_back(entry->Name());
                }

                for (DirectoryX::Entries::iterator entry = second_set.begin(); entry != second_set.end(); ++entry) {
                    second_set_names.push_back(entry->Name());
                }

                assertNamesAreCorrect(first_set_names);
                assertNamesAreCorrect(second_set_names);
            }
        }
    }
}

} // namespace amm
