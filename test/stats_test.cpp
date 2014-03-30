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

#include <iostream>
#include <string>
#include <vector>

#include "stats.h"

#include "QUnit.hpp"

namespace amm
{
	// Verifies the summary of populating a menu
	class stats_test
	{
		QUnit::UnitTest qunit;

		void test_stats_doesnt_report_any_entries_in_short_summary_by_default()
		{
			amm::stats stats;
			std::string expected = std::string("Total desktop files: 0\n") +
			                       std::string("Parsed desktop files: 0\n") +
			                       std::string("Unparsed desktop files: 0\n") +
			                       std::string("Unclassified desktop files: 0\n");
			QUNIT_IS_EQUAL(expected, stats.short_summary());
		}

		void test_stats_short_summary_includes_counts()
		{
			amm::stats stats = populated_stats();
			std::string expected = std::string("Total desktop files: 6\n") +
			                       std::string("Parsed desktop files: 5\n") +
			                       std::string("Unparsed desktop files: 1\n") +
			                       std::string("Unclassified desktop files: 2\n");
			QUNIT_IS_EQUAL(expected, stats.short_summary());
		}

		void test_stats_doesnt_report_any_entries_in_summary_by_default()
		{
			amm::stats stats;
			std::string expected = std::string("Total desktop files: 0\n") +
			                       std::string("Parsed desktop files: 0\n") +
			                       std::string("Unparsed desktop files: 0\n") +
			                       std::string("Unclassified desktop files: 0\n");
			QUNIT_IS_EQUAL(expected, stats.summary());
		}

		void test_stats_summary_includes_short_summary_with_list_of_unpasred_files()
		{
			amm::stats stats = populated_stats();
			std::string expected = std::string("Total desktop files: 6\n") +
			                       std::string("Parsed desktop files: 5\n") +
			                       std::string("Unparsed desktop files: 1\n") +
			                       std::string("Unclassified desktop files: 2\n") +
			                       std::string("List of unparsed files: daemon\n");
			QUNIT_IS_EQUAL(expected, stats.summary());
		}

		void test_stats_doesnt_report_any_entries_in_long_summary_by_default()
		{
			amm::stats stats;
			std::string expected = std::string("Total desktop files: 0\n") +
			                       std::string("Parsed desktop files: 0\n") +
			                       std::string("Unparsed desktop files: 0\n") +
			                       std::string("Unclassified desktop files: 0\n");
			QUNIT_IS_EQUAL(expected, stats.long_summary());
		}

		void test_stats_long_summary_includes_summary_with_list_of_unclassified_files()
		{
			amm::stats stats = populated_stats();
			std::string expected = std::string("Total desktop files: 6\n") +
			                       std::string("Parsed desktop files: 5\n") +
			                       std::string("Unparsed desktop files: 1\n") +
			                       std::string("Unclassified desktop files: 2\n") +
			                       std::string("List of unparsed files: daemon\n") +
			                       std::string("List of unclassified files: htop, NEdit\n");
			QUNIT_IS_EQUAL(expected, stats.long_summary());
		}

		void test_stats_long_summary_includes_list_of_unhandled_classfications_when_present()
		{
			amm::stats stats = populated_stats();
			stats.add_unhandled_classifications(unhandled_classification_first_set());
			stats.add_unhandled_classifications(unhandled_classification_second_set());
			std::string expected = std::string("Total desktop files: 6\n") +
			                       std::string("Parsed desktop files: 5\n") +
			                       std::string("Unparsed desktop files: 1\n") +
			                       std::string("Unclassified desktop files: 2\n") +
			                       std::string("List of unparsed files: daemon\n") +
			                       std::string("List of unclassified files: htop, NEdit\n") +
			                       std::string("List of unhandled classifications: Archiving, Browser, Calculator, Player, WordProcessor\n");
			QUNIT_IS_EQUAL(expected, stats.long_summary());
		}

		amm::stats populated_stats()
		{
			amm::stats stats;
			stats.add_classified_file("VLC");
			stats.add_classified_file("Mousepad");
			stats.add_classified_file("Firefox");
			stats.add_unclassified_file("htop");
			stats.add_unclassified_file("NEdit");
			stats.add_unparsed_file("daemon");
			return stats;
		}

		std::vector<std::string> unhandled_classification_first_set()
		{
			std::vector<std::string> classifications;
			classifications.push_back("Calculator");
			classifications.push_back("Player");
			classifications.push_back("Archiving");
			return classifications;
		}

		std::vector<std::string> unhandled_classification_second_set()
		{
			std::vector<std::string> classifications;
			classifications.push_back("Browser");
			classifications.push_back("Player");
			classifications.push_back("WordProcessor");
			classifications.push_back("Archiving");
			return classifications;
		}

	public:
		stats_test(std::ostream &out, int verbose_level) : qunit(out, verbose_level) {}

		int run()
		{
			test_stats_doesnt_report_any_entries_in_short_summary_by_default();
			test_stats_short_summary_includes_counts();

			test_stats_doesnt_report_any_entries_in_summary_by_default();
			test_stats_summary_includes_short_summary_with_list_of_unpasred_files();

			test_stats_doesnt_report_any_entries_in_long_summary_by_default();
			test_stats_long_summary_includes_summary_with_list_of_unclassified_files();
			test_stats_long_summary_includes_list_of_unhandled_classfications_when_present();

			return qunit.errors();
		}
	};
}


int main()
{
	return amm::stats_test(std::cerr, QUnit::normal).run();
}
