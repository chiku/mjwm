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

#include <string>
#include <sstream>
#include <vector>
#include <algorithm>

#include "vectorx.h"
#include "stats.h"

void
amm::stats::add_classified_file(std::string file)
{
	_classified_files.push_back(file);
}

void
amm::stats::add_unclassified_file(std::string file)
{
	_unclassified_files.push_back(file);
}

void
amm::stats::add_unparsed_file(std::string file)
{
	_unparsed_files.push_back(file);
}

void
amm::stats::add_unhandled_classifications(std::vector<std::string> classifications)
{
	_unhandled_classifications.insert(_unhandled_classifications.begin(), classifications.begin(), classifications.end());
}

size_t
amm::stats::total_desktop_files() const
{
	return _classified_files.size() + _unclassified_files.size() + _unparsed_files.size();
}

size_t
amm::stats::total_parsed_files() const
{
	return _classified_files.size() + _unclassified_files.size();
}

size_t
amm::stats::total_unclassified_files() const
{
	return _unclassified_files.size();
}

size_t
amm::stats::total_unparsed_files() const
{
	return _unparsed_files.size();
}

std::vector<std::string>
amm::stats::unparsed_files() const
{
	return _unparsed_files;
}

std::string
amm::stats::short_summary() const
{
	std::stringstream stream;
	stream << "Total desktop files: " << total_desktop_files() << std::endl;
	stream << "Parsed desktop files: " << total_parsed_files() << std::endl;
	stream << "Unparsed desktop files: " << total_unparsed_files() << std::endl;
	stream << "Unclassified desktop files: " << total_unclassified_files() << std::endl;
	return stream.str();
}

std::string
amm::stats::summary() const
{
	std::stringstream stream;
	stream << short_summary();

	if (total_unparsed_files() > 0) {
		stream << "List of unparsed files: " << amm::vectorx(_unparsed_files).join(", ") << std::endl;
	}

	return stream.str();
}

std::string
amm::stats::long_summary()
{
	std::stringstream stream;
	stream << summary();

	if (total_unclassified_files() > 0) {
		stream << "List of unclassified files: " << amm::vectorx(_unclassified_files).join(", ") << std::endl;
	}

	if (_unhandled_classifications.size() > 0) {
		std::sort(_unhandled_classifications.begin(), _unhandled_classifications.end());
		std::vector<std::string>::iterator it = std::unique(_unhandled_classifications.begin(), _unhandled_classifications.end());
		_unhandled_classifications.resize(std::distance(_unhandled_classifications.begin(), it));

		stream << "List of unhandled classifications: " << amm::vectorx(_unhandled_classifications).join(", ") << std::endl;
	}

	return stream.str();
}
