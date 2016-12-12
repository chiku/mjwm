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

#include "command_line_options_parser.h"

#include <getopt.h>
#include <string>
#include <vector>

#include "stringx.h"
#include "amm_options.h"

namespace amm {

AmmOptions CommandLineOptionsParser::parse(int argc, char* const* argv)
{
    allowMultipleEntries();
    AmmOptions amm_options = AmmOptions::Default(home_, language_);

    int option_index = 0;
    int help_flag = 0;
    int version_flag = 0;
    const char* short_options = "o:i:c:v";
    const option long_options[] = {
        {"help",            no_argument,       &help_flag   ,  1 },
        {"version",         no_argument,       &version_flag,  1 },
        {"verbose",         no_argument,       0,             'v'},
        {"iconize",         optional_argument, 0,              0 },
        {"no-backup",       optional_argument, 0,              0 },
        {"output-file",     required_argument, 0,             'o'},
        {"input-directory", required_argument, 0,             'i'},
        {"category-file",   required_argument, 0,             'c'},
        {"summary",         required_argument, 0,              0 },
        {"language",        required_argument, 0,              0 },
        {0,                 0,                 0,              0 },
    };

    int chosen_option;

    amm_options.is_parsed = true;

    while ((chosen_option = getopt_long(argc, argv, short_options, long_options, &option_index)) != -1) {
        if (chosen_option == 0) {
            if (help_flag == 1) {
                amm_options.is_help = true;
            }
            if (version_flag == 1) {
                amm_options.is_version = true;
            }
            std::string long_option_name = long_options[option_index].name;
            if (long_option_name == "iconize") {
                amm_options.is_iconize = true;
                if (optarg) {
                    amm_options.icon_theme_name = optarg;
                }
            }
            if (long_option_name == "summary") {
                amm_options.summary_type = optarg;
                amm_options.deprecations.push_back("--summary [SUMMARY TYPE] is deprecated. Use -v for verbose output instead.");
            }
            if (long_option_name == "language") {
                amm_options.language = optarg;
            }
            if (long_option_name == "no-backup") {
                amm_options.is_backup = false;
            }
        } else if (chosen_option == 'o') {
            amm_options.output_file_name = optarg;
        } else if (chosen_option == 'i') {
            amm_options.override_default_directories = true;
            amm_options.input_directory_names = StringX(optarg).split(":");
        } else if (chosen_option == 'c') {
            amm_options.category_file_name = optarg;
        } else if (chosen_option == 'v') {
            amm_options.summary_type = "long";
        } else {
            amm_options.is_parsed = false;
        }
    }

    return amm_options;
}

void CommandLineOptionsParser::allowMultipleEntries() const
{
    // Allow getopt_long() to be called multiple times
    // http://pubs.opengroup.org/onlinepubs/009696799/functions/getopt.html
    optind = 1;
}

} // namespace amm
