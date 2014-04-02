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

#include <iostream>
#include <string>
#include <vector>

#include "catch.hpp"

#include "stats.h"

static amm::stats populated_stats()
{
  amm::stats stats;
  stats.add_classified_file("VLC");
  stats.add_classified_file("Mousepad");
  stats.add_classified_file("Firefox");
  stats.add_unclassified_file("htop");
  stats.add_unclassified_file("NEdit");
  stats.add_unparsed_file("daemon");
  stats.add_suppressed_file("mplayer");
  return stats;
}

static std::vector<std::string> unhandled_classification_first_set()
{
  std::vector<std::string> classifications;
  classifications.push_back("Calculator");
  classifications.push_back("Player");
  classifications.push_back("Archiving");
  return classifications;
}

static std::vector<std::string> unhandled_classification_second_set()
{
  std::vector<std::string> classifications;
  classifications.push_back("Browser");
  classifications.push_back("Player");
  classifications.push_back("WordProcessor");
  classifications.push_back("Archiving");
  return classifications;
}

static std::string expected_empty_summary()
{
  return "Total desktop files: 0\n"
         "Parsed desktop files: 0\n"
         "Unparsed desktop files: 0\n"
         "Suppressed desktop files (NoDisplay): 0\n"
         "Unclassified desktop files: 0\n";
}

static std::string expected_short_summary_with_values()
{
  return "Total desktop files: 7\n"
         "Parsed desktop files: 5\n"
         "Unparsed desktop files: 1\n"
         "Suppressed desktop files (NoDisplay): 1\n"
         "Unclassified desktop files: 2\n";
}

SCENARIO("amm::stats totals", "[stats]") {
  GIVEN("A stat") {
    amm::stats stats;

    WHEN("created") {
      THEN("it has no total files")        { REQUIRE(stats.total_files() == 0); }
      THEN("it has no parsed files")       { REQUIRE(stats.total_parsed_files() == 0); }
      THEN("it has no unclassified files") { REQUIRE(stats.total_unclassified_files() == 0); }
      THEN("it has no suppressed files")   { REQUIRE(stats.total_suppressed_files() == 0); }
      THEN("it has no unparsed files")     { REQUIRE(stats.total_unparsed_files() == 0); }

      THEN("is has no counts in short summary") {
        REQUIRE(stats.short_summary() == expected_empty_summary());
      }

      THEN("is has no counts in summary") {
        REQUIRE(stats.summary() == expected_empty_summary());
      }

      THEN("is has no counts in long summary") {
        REQUIRE(stats.long_summary() == expected_empty_summary());
      }
    }

    WHEN("a classified file is added") {
      stats.add_classified_file("file");

      THEN("it has one total file")        { REQUIRE(stats.total_files() == 1); }
      THEN("it has one parsed file")       { REQUIRE(stats.total_parsed_files() == 1); }
      THEN("it has no unclassified files") { REQUIRE(stats.total_unclassified_files() == 0); }
      THEN("it has no suppressed files")   { REQUIRE(stats.total_suppressed_files() == 0); }
      THEN("it has no unparsed files")     { REQUIRE(stats.total_unparsed_files() == 0); }
    }

    WHEN("an unclassified file is added") {
      stats.add_unclassified_file("file");

      THEN("it has one total file")        { REQUIRE(stats.total_files() == 1); }
      THEN("it has one parsed file")       { REQUIRE(stats.total_parsed_files() == 1); }
      THEN("it has one unclassified file") { REQUIRE(stats.total_unclassified_files() == 1); }
      THEN("it has no suppressed files")   { REQUIRE(stats.total_suppressed_files() == 0); }
      THEN("it has no unparsed files")     { REQUIRE(stats.total_unparsed_files() == 0); }
    }

    WHEN("a suppressed file is added") {
      stats.add_suppressed_file("file");

      THEN("it has one total file")        { REQUIRE(stats.total_files() == 1); }
      THEN("it has no parsed files")       { REQUIRE(stats.total_parsed_files() == 0); }
      THEN("it has no unclassified files") { REQUIRE(stats.total_unclassified_files() == 0); }
      THEN("it has one suppressed file")   { REQUIRE(stats.total_suppressed_files() == 1); }
      THEN("it has no unparsed files")     { REQUIRE(stats.total_unparsed_files() == 0); }
    }

    WHEN("an unparsed file is added") {
      stats.add_unparsed_file("file");

      THEN("it has one total file")        { REQUIRE(stats.total_files() == 1); }
      THEN("it has no parsed files")       { REQUIRE(stats.total_parsed_files() == 0); }
      THEN("it has no unclassified files") { REQUIRE(stats.total_unclassified_files() == 0); }
      THEN("it has no suppressed files")   { REQUIRE(stats.total_suppressed_files() == 0); }
      THEN("it has one unparsed files")    { REQUIRE(stats.total_unparsed_files() == 1); }
    }
  }
}


SCENARIO("amm::stats summaries", "[stats]") {
  GIVEN("A stat") {
    amm::stats stats;

    WHEN("different types of files are added") {
      amm::stats stats = populated_stats();

      THEN("short summary includes counts") {
        REQUIRE(stats.short_summary() == expected_short_summary_with_values());
      }

      THEN("summary includes short summary and a list of unparsed files") {
        std::string expected_summary = expected_short_summary_with_values() +
                                       "List of unparsed files: daemon\n";
        REQUIRE(stats.summary() == expected_summary);
      }

      THEN("long summary includes summary and lists of suppressed and unclassified files") {
        std::string expected_summary = expected_short_summary_with_values() +
                                       "List of unparsed files: daemon\n"
                                       "List of suppressed files: mplayer\n"
                                       "List of unclassified files: htop, NEdit\n";
        REQUIRE(stats.long_summary() == expected_summary);
      }
    }

    WHEN("unhandled classifications are added") {
      amm::stats stats = populated_stats();
      stats.add_unhandled_classifications(unhandled_classification_first_set());
      stats.add_unhandled_classifications(unhandled_classification_second_set());

      THEN("long summary includes the unhandled classifications") {
        std::string expected_summary = expected_short_summary_with_values() +
                                       "List of unparsed files: daemon\n"
                                       "List of suppressed files: mplayer\n"
                                       "List of unclassified files: htop, NEdit\n"
                                       "List of unhandled classifications: Archiving, Browser, Calculator, Player, WordProcessor\n";
        REQUIRE(stats.long_summary() == expected_summary);
      }
    }
  }
}
