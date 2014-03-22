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

/*
    Based on work by insmyic <gminsm@gmail.com> http://sourceforge.net/projects/mjm
*/


#include <iostream>
#include <string>
#include <vector>
#include <getopt.h>

#include "messages.h"
#include "desktop_file_search.h"
#include "menu_group.h"


int main(int argc, char *argv[])
{
	std::string directory_to_scan("/usr/share/applications/");
	std::string output_filename("./automenu");
	std::string icon_extension("");

	const char* short_options = "o:s:avh";
	const option long_options[] =
	{
		{"output-file",     required_argument, 0, 'o'},
		{"input-directory", required_argument, 0, 's'},
		{"append-png",      no_argument,       0, 'a'},
		{"version",         no_argument,       0, 'v'},
		{"help",            no_argument,       0, 'h'},
		{0, 0, 0, 0}
	};

	int chosen_option;
	int option_index = 0;

	while ((chosen_option = getopt_long(argc, argv, short_options, long_options, &option_index)) != -1) {
		switch (chosen_option) {
			case 'o':
				output_filename = optarg;
				break;

			case 's':
				directory_to_scan = optarg;
				break;

			case 'a':
				icon_extension = ".png";
				break;

			case 'v':
				amm::messages::display_version();
				return 0;

			case 'h':
				amm::messages::display_help();
				return 0;

			case '?':
				amm::messages::display_option_error();
				return 1;

			default:
				amm::messages::display_option_error();
				return 1;
		}
	}

	std::vector<std::string> directories_to_search;
	directories_to_search.push_back(directory_to_scan);

	std::vector<std::string> desktop_files = amm::desktop_file_search(directories_to_search).all();

	amm::menu_group group(desktop_files, icon_extension);
	group.populate();
	if (!group.is_valid()) {
		std::cerr << group.error() << std::endl;
		return 1;
	}
	group.sort();
	group.write(output_filename);

	return 0;
}
