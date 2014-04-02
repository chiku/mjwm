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

#ifndef AMM_STATS_H_
#define AMM_STATS_H_

#include <string>
#include <vector>

namespace amm
{
	// Understands the summary of populating a menu
	class stats
	{
	private:
		std::vector<std::string> classified_files_;
		std::vector<std::string> unclassified_files_;
		std::vector<std::string> unparsed_files_;
		std::vector<std::string> suppressed_files_;
		std::vector<std::string> unhandled_classifications_;

	public:
		void add_classified_file(std::string file);
		void add_unclassified_file(std::string file);
		void add_suppressed_file(std::string file);
		void add_unparsed_file(std::string file);
		void add_unhandled_classifications(std::vector<std::string> classifications);

		size_t total_files() const;
		size_t total_parsed_files() const;
		size_t total_unclassified_files() const;
		size_t total_suppressed_files() const;
		size_t total_unparsed_files() const;
		std::vector<std::string> unparsed_files() const;
		std::vector<std::string> unhandled_classifications();

		std::string short_summary() const;
		std::string summary() const;
		std::string long_summary();
	};
}

#endif // AMM_STATS_H_
