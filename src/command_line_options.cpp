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

#include "util.h"
#include "command_line_options.h"

amm::CommandLineOptions::CommandLineOptions()
{
  is_help_ = false;
  is_version_ = false;
  output_file_name_ = "./automenu";
}

bool
amm::CommandLineOptions::Parse(int argc, char* const* argv)
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
          is_help_ = true;
        }
        if (version_flag == 1) {
          is_version_ = true;
        }
        break;

      case 'o':
        output_file_name_ = optarg;
        break;

      case 'i':
        input_directory_names_ = amm::StringX(optarg).Split(":");
        break;

      case 's':
        input_directory_names_ = amm::StringX(optarg).Split(":");
        deprecations_.push_back("-s is deprecated. Please use -i instead.");
        break;

      case 'c':
        category_file_name_ = optarg;
        break;

      case 'a':
        icon_extension_ = ".png";
        break;

      case 'h':
        is_help_ = true;
        deprecations_.push_back("-h is deprecated. Please use --help instead.");
        break;

      case 'v':
        is_version_ = true;
        deprecations_.push_back("-v is deprecated. Please use --version instead.");
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
