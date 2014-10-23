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

#include "stats.h"

#include <string>
#include <vector>

#include "catch.hpp"

namespace amm {

static Stats populatedStats() {
    Stats stats;
    stats.AddClassifiedFile("VLC");
    stats.AddClassifiedFile("Mousepad");
    stats.AddClassifiedFile("Firefox");
    stats.AddUnclassifiedFile("htop");
    stats.AddUnclassifiedFile("NEdit");
    stats.AddUnparsedFile("daemon");
    stats.AddSuppressedFile("mplayer");
    return stats;
}

static std::vector<std::string> unhandledClassificationFirstSet() {
    std::vector<std::string> classifications;
    classifications.push_back("Calculator");
    classifications.push_back("Player");
    classifications.push_back("Archiving");
    return classifications;
}

static std::vector<std::string> unhandledClassificationSecondSet() {
    std::vector<std::string> classifications;
    classifications.push_back("Browser");
    classifications.push_back("Player");
    classifications.push_back("WordProcessor");
    classifications.push_back("Archiving");
    return classifications;
}

static std::string expectedEmptydetails() {
    return "Total desktop files: 0\n"
                 "Parsed desktop files: 0\n"
                 "Unparsed desktop files: 0\n"
                 "Suppressed desktop files (NoDisplay): 0\n"
                 "Unclassified desktop files: 0\n";
}

static std::string expectedShortdetailsWithValues() {
    return "Total desktop files: 7\n"
                 "Parsed desktop files: 5\n"
                 "Unparsed desktop files: 1\n"
                 "Suppressed desktop files (NoDisplay): 1\n"
                 "Unclassified desktop files: 2\n";
}

SCENARIO("Stats totals", "[stats]") {
    GIVEN("A stat") {
        Stats stats;

        WHEN("created") {
            THEN("it has no total files")        { REQUIRE(stats.TotalFiles() == 0); }
            THEN("it has no parsed files")       { REQUIRE(stats.TotalParsedFiles() == 0); }
            THEN("it has no unclassified files") { REQUIRE(stats.TotalUnclassifiedFiles() == 0); }
            THEN("it has no suppressed files")   { REQUIRE(stats.TotalSuppressedFiles() == 0); }
            THEN("it has no unparsed files")     { REQUIRE(stats.TotalUnparsedFiles() == 0); }

            THEN("is has no counts in short details") {
                REQUIRE(stats.Details("short") == expectedEmptydetails());
            }

            THEN("is has no counts in details") {
                REQUIRE(stats.Details("normal") == expectedEmptydetails());
            }

            THEN("is has no counts in long details") {
                REQUIRE(stats.Details("long") == expectedEmptydetails());
            }
        }

        WHEN("a classified file is added") {
            stats.AddClassifiedFile("file");

            THEN("it has one total file")        { REQUIRE(stats.TotalFiles() == 1); }
            THEN("it has one parsed file")       { REQUIRE(stats.TotalParsedFiles() == 1); }
            THEN("it has no unclassified files") { REQUIRE(stats.TotalUnclassifiedFiles() == 0); }
            THEN("it has no suppressed files")   { REQUIRE(stats.TotalSuppressedFiles() == 0); }
            THEN("it has no unparsed files")     { REQUIRE(stats.TotalUnparsedFiles() == 0); }
        }

        WHEN("an unclassified file is added") {
            stats.AddUnclassifiedFile("file");

            THEN("it has one total file")        { REQUIRE(stats.TotalFiles() == 1); }
            THEN("it has one parsed file")       { REQUIRE(stats.TotalParsedFiles() == 1); }
            THEN("it has one unclassified file") { REQUIRE(stats.TotalUnclassifiedFiles() == 1); }
            THEN("it has no suppressed files")   { REQUIRE(stats.TotalSuppressedFiles() == 0); }
            THEN("it has no unparsed files")     { REQUIRE(stats.TotalUnparsedFiles() == 0); }
        }

        WHEN("a suppressed file is added") {
            stats.AddSuppressedFile("file");

            THEN("it has one total file")        { REQUIRE(stats.TotalFiles() == 1); }
            THEN("it has no parsed files")       { REQUIRE(stats.TotalParsedFiles() == 0); }
            THEN("it has no unclassified files") { REQUIRE(stats.TotalUnclassifiedFiles() == 0); }
            THEN("it has one suppressed file")   { REQUIRE(stats.TotalSuppressedFiles() == 1); }
            THEN("it has no unparsed files")     { REQUIRE(stats.TotalUnparsedFiles() == 0); }
        }

        WHEN("an unparsed file is added") {
            stats.AddUnparsedFile("file");

            THEN("it has one total file")        { REQUIRE(stats.TotalFiles() == 1); }
            THEN("it has no parsed files")       { REQUIRE(stats.TotalParsedFiles() == 0); }
            THEN("it has no unclassified files") { REQUIRE(stats.TotalUnclassifiedFiles() == 0); }
            THEN("it has no suppressed files")   { REQUIRE(stats.TotalSuppressedFiles() == 0); }
            THEN("it has one unparsed files")    { REQUIRE(stats.TotalUnparsedFiles() == 1); }
        }
    }
}


SCENARIO("Stats summaries", "[stats]") {
    GIVEN("A stat") {
        Stats stats;

        WHEN("different types of files are added") {
            Stats stats = populatedStats();

            THEN("short details includes counts") {
                REQUIRE(stats.Details("short") == expectedShortdetailsWithValues());
            }

            THEN("details includes short details and a list of unparsed files") {
                std::string expected_details = expectedShortdetailsWithValues() + "List of unparsed files: daemon\n";
                REQUIRE(stats.Details("normal") == expected_details);
            }

            THEN("long details includes details and lists of suppressed and unclassified files") {
                std::string expected_details = expectedShortdetailsWithValues() +
                                                "List of unparsed files: daemon\n"
                                                "List of suppressed files: mplayer\n"
                                                "List of unclassified files: htop, NEdit\n";
                REQUIRE(stats.Details("long") == expected_details);
            }
        }

        WHEN("unhandled classifications are added") {
            Stats stats = populatedStats();
            stats.AddUnhandledClassifications(unhandledClassificationFirstSet());
            stats.AddUnhandledClassifications(unhandledClassificationSecondSet());

            THEN("long details includes the unhandled classifications") {
                std::string expected_details = expectedShortdetailsWithValues() +
                                                "List of unparsed files: daemon\n"
                                                "List of suppressed files: mplayer\n"
                                                "List of unclassified files: htop, NEdit\n"
                                                "List of unhandled classifications: Archiving, Browser, Calculator, Player, WordProcessor\n";
                REQUIRE(stats.Details("long") == expected_details);
            }
        }
    }
}

} // namespace amm
