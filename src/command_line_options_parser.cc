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

#include "command_line_options_parser.h"

#include <getopt.h>
#include <string>
#include <vector>

#include "stringx.h"
#include "amm_options.h"

namespace amm {

AmmOptions CommandLineOptionsParser::Parse(int argc, char* const* argv) {
  optind = 1; // Allow getopt_long() to be called multiple times
  // http://pubs.opengroup.org/onlinepubs/009696799/functions/getopt.html

  int option_index = 0;
  int help_flag = 0;
  int version_flag = 0;
  int iconize_flag = 0;
  const char* short_options = "o:i:s:c:";
  const option long_options[] = {
    {"help",            no_argument,       &help_flag   ,  1 },
    {"version",         no_argument,       &version_flag,  1 },
    {"iconize",         no_argument,       &iconize_flag,  1 },
    {"output-file",     required_argument, 0,             'o'},
    {"input-directory", required_argument, 0,             'i'},
    {"category-file",   required_argument, 0,             'c'},
    {0,                 0,                 0,              0 },
  };

  int chosen_option;

  AmmOptions amm_options;
  amm_options.is_parsed = true;

  while ((chosen_option = getopt_long(argc, argv, short_options, long_options, &option_index)) != -1) {
    switch (chosen_option) {
      case 0:
        if (help_flag == 1) {
          amm_options.is_help = true;
        }
        if (version_flag == 1) {
          amm_options.is_version = true;
        }
        if (iconize_flag == 1) {
          amm_options.is_iconize = true;
        }
        break;

      case 'o':
        amm_options.output_file_name = optarg;
        break;

      case 'i':
        amm_options.input_directory_names = StringX(optarg).Split(":");
        break;

      case 'c':
        amm_options.category_file_name = optarg;
        break;

      case '?':
        amm_options.is_parsed = false;
        break;

      default:
        amm_options.is_parsed = false;
        break;
    }
  }

  return amm_options;
}

} // namespace amm
