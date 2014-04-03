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

#include "file_search_service.h"

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

#include "catch.hpp"

namespace amm {

static bool present_in(std::string item, std::vector<std::string> list) {
  return std::find(list.begin(), list.end(), item) != list.end();
}

static void assert_files_are_present_in_list(std::vector<std::string> file_names) {
  REQUIRE(file_names.size() == 6);

  REQUIRE(present_in("test/fixtures/missing.desktop", file_names));
  REQUIRE(present_in("test/fixtures/mousepad.desktop", file_names));
  REQUIRE(present_in("test/fixtures/unclassified.desktop", file_names));
  REQUIRE(present_in("test/fixtures/vlc.desktop", file_names));
  REQUIRE(present_in("test/fixtures/suppressed.desktop", file_names));
  REQUIRE(present_in("test/fixtures/suppressedinvalid.desktop", file_names));
}


SCENARIO("FileSearchService", "[filesearchservice]") {
  GIVEN("A file search service with one directory") {
    std::vector<std::string> directory_names;
    directory_names.push_back("test/fixtures/");
    FileSearchService service;
    service.set_directory_names(directory_names);

    WHEN("resolved") {
      service.Resolve();

      THEN("it has a list of files with extension 'desktop' inside the directory") {
        assert_files_are_present_in_list(service.desktop_file_names());
      }
    }
  }

  GIVEN("A file search service with repeated directory") {
    std::vector<std::string> directory_names;
    directory_names.push_back("test/fixtures/");
    directory_names.push_back("test/fixtures");
    FileSearchService service;
    service.set_directory_names(directory_names);

    WHEN("resolved") {
      service.Resolve();

      THEN("it ignores duplicates") {
        assert_files_are_present_in_list(service.desktop_file_names());
      }
    }
  }

  GIVEN("A file search service with one existing directory and one missing directory") {
    std::vector<std::string> directory_names;
    directory_names.push_back("test/fixtures");
    directory_names.push_back("test/does-not-exist");
    FileSearchService service;
    service.set_directory_names(directory_names);

    WHEN("resolved") {
      service.Resolve();

      THEN("it has a list of files with extension 'desktop' in the directory that exists") {
        assert_files_are_present_in_list(service.desktop_file_names());
      }

      THEN("it tracks the directory that doesn't exist") {
        std::vector<std::string> bad_paths = service.bad_paths();
        REQUIRE(bad_paths.size() == 1);
        REQUIRE(bad_paths[0] == "test/does-not-exist/");
      }
    }
  }
}

} // namespace amm
