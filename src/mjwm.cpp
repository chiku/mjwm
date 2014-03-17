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
#include <getopt.h>

#include "menu_entry.h"
#include "menu_group.h"

static const std::string VERSION = "2.1.1";

static void display_help()
{
	std::cout << "mjwm version " << VERSION <<  ", Copyright (C) 2014 Chirantan Mitra <chirantan.mitra@gmail.com>" << std::endl;
	std::cout << "mjwm comes with ABSOLUTELY NO WARRANTY; for details refer COPYING." << std::endl;
	std::cout << "This is free software, and you are welcome to redistribute it" << std::endl;
	std::cout << "under certain conditions; Refer COPYING for details." << std::endl;

	std::cout << "mjwm creates jwm's menu from (freedesktop) desktop files" << std::endl;
	std::cout << "  -o, --output-file [FILE]           Outfile file [Default: ./automenu]" << std::endl;
	std::cout << "  -s, --input-directory [DIRECTORY]  Directory to scan for '.desktop' files [Default: /usr/share/applications/]" << std::endl;
	std::cout << "  -a, --append-png                   Add '.png' to icon filenames" << std::endl;
	std::cout << "  -v, --version                      Show version" << std::endl << std::endl;
	std::cout << "  -h, --help                         Show this help" << std::endl << std::endl;

	std::cout << "Include the generated file in the rootmenu section of your ~/.jwmrc" << std::endl;
	std::cout << "More information at http://github.com/chiku/mjwm" << std::endl;
}

static void display_version()
{
	std::cout << "mjwm " << VERSION << std::endl;
}

static void display_option_error()
{
	std::cerr << "Please run mjwm -h to see options" << std::endl;
}

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
				display_version();
				return 0;

			case 'h':
				display_help();
				return 0;

			case '?':
				display_option_error();
				return 1;

			default:
				display_option_error();
				return 1;
		}
	}

	mjwm::menu_group group(directory_to_scan, icon_extension);
	group.populate();
	if (!group.is_valid()) {
		std::cerr << group.error() << std::endl;
		return 1;
	}
	group.sort();
	group.write(output_filename);

	return 0;
}
