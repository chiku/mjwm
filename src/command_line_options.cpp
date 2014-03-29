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
#include <vector>
#include <getopt.h>

#include "stringx.h"
#include "command_line_options.h"

amm::command_line_options::command_line_options()
{
	_is_help = false;
	_is_version = false;
	_output_file_name = "./automenu";
}

bool
amm::command_line_options::parse(int argc, char* const* argv)
{
	optind = 1; // Allow getopt_long() to be called multiple times
	// http://pubs.opengroup.org/onlinepubs/009696799/functions/getopt.html

	bool parsed = true;
	int option_index = 0;
	int help_flag = 0;
	int version_flag = 0;
	const char* short_options = "o:i:s:c:ahv";
	const option long_options[] =
	{
		{"help",            no_argument,       &help_flag   ,  1 },
		{"version",         no_argument,       &version_flag,  1 },
		{"output-file",     required_argument, 0,             'o'},
		{"input-directory", required_argument, 0,             'i'},
		{"category-file",   required_argument, 0,             'c'},
		{"append-png",      no_argument,       0,             'a'},
		{0,                 0,                 0,              0 },
	};

	int chosen_option;

	while ((chosen_option = getopt_long(argc, argv, short_options, long_options, &option_index)) != -1) {
		switch (chosen_option) {
			case 0:
				if (help_flag == 1) {
					_is_help = true;
				}
				if (version_flag == 1) {
					_is_version = true;
				}
				break;

			case 'o':
				_output_file_name = optarg;
				break;

			case 'i':
				_input_directory_names = amm::stringx(optarg).split(":");
				break;

			case 's':
				_input_directory_names = amm::stringx(optarg).split(":");
				_deprecations.push_back("-s is deprecated. Please use -i instead.");
				break;

			case 'c':
				_category_file_name = optarg;
				break;

			case 'a':
				_icon_extension = ".png";
				break;

			case 'h':
				_is_help = true;
				_deprecations.push_back("-h is deprecated. Please use --help instead.");
				break;

			case 'v':
				_is_version = true;
				_deprecations.push_back("-v is deprecated. Please use --version instead.");
				break;

			case '?':
				parsed = false;
				break;

			default:
				parsed = false;
				break;
		}
	}

	return parsed;
}

bool
amm::command_line_options::is_help() const
{
	return _is_help;
}

bool
amm::command_line_options::is_version() const
{
	return _is_version;
}

std::string
amm::command_line_options::output_file_name() const
{
	return _output_file_name;
}

std::vector<std::string>
amm::command_line_options::input_directory_names() const
{
	return _input_directory_names;
}

std::string
amm::command_line_options::category_file_name() const
{
	return _category_file_name;
}

std::string
amm::command_line_options::icon_extension() const
{
	return _icon_extension;
}

std::vector<std::string>
amm::command_line_options::deprecations() const
{
	return _deprecations;
}
