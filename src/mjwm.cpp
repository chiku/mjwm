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
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

#include <dirent.h>
#include <stdlib.h>
#include <getopt.h>

#include "menu_entry.h"
#include "mjwm.h"

int main(int argc, char *argv[]) {
	std::string directory_to_scan("/usr/share/applications/");
	std::string output_filename("./automenu");
	std::string icon_extension("");

	const char* short_options = "ahs:f:";
	const option long_options[] =
	{
		{"output-file",     required_argument, 0, 'f'},
		{"input-directory", required_argument, 0, 's'},
		{"append-png",      no_argument,       0, 'a'},
		{"help",            no_argument,       0, 'h'},
		{0, 0, 0, 0}
	};

	int chosen_option;
	int option_index = 0;
	const int NORMAL_RESERVE_SIZE = 300;

	while ((chosen_option = getopt_long(argc, argv, short_options, long_options, &option_index)) != -1) {
		switch (chosen_option) {
			case 'f':
				output_filename = optarg;
				break;

			case 's':
				directory_to_scan = optarg;
				break;

			case 'a':
				icon_extension = ".png";
				break;

			case 'h':
				display_help();
				return 0;

			case '?':
				display_option_error(argv[0]);
				return 1;

			default:
				display_option_error(argv[0]);
				return 1;
		}
	}

	std::vector<mjwm::menu_entry> menu_entries;
	menu_entries.reserve(NORMAL_RESERVE_SIZE);
	Reader(directory_to_scan, menu_entries);
	Itmsrt(menu_entries);
	Rcwrite(menu_entries, output_filename, icon_extension);

	return 0;
}

void Reader(std::string directoryname, std::vector<mjwm::menu_entry> &menu_entries) {
	DIR *directory = opendir(directoryname.c_str());

	if (!directory) {
		std::cerr << "Couldn't open directory " << directoryname << std::endl;
		exit(1);
	}

	mjwm::menu_entry entry = mjwm::menu_entry();
	dirent *directory_entry;
	std::string line;

	for(directory_entry = readdir(directory); directory_entry != NULL; directory_entry = readdir(directory)) {
		std::string desktop_filename = directoryname + directory_entry->d_name;

		std::ifstream file(desktop_filename.c_str());
		if (!file.good()) {
			continue;
		}

		while (std::getline(file, line)) {
			entry.populate(line);
		}

		if (entry.is_valid()) {
			menu_entries.push_back(entry);
		}

		file.close();
	}
	closedir(directory);

	if (menu_entries.size() == 0) {
		std::cerr << directoryname << " doesn't have any valid .desktop files" << std::endl;
		exit(1);
	}
}

void Itmsrt(std::vector<mjwm::menu_entry> &menu_entries) {
	std::sort(menu_entries.begin(), menu_entries.end());
}

void Rcwrite(std::vector<mjwm::menu_entry> menu_entries, std::string output_filename, std::string icon_extension)
{
	std::ofstream file(output_filename.c_str());

	for(std::vector<mjwm::menu_entry>::iterator entry = menu_entries.begin(); entry != menu_entries.end(); ++entry) {
		(*entry).write_to(file, icon_extension);
	}

	file.close();
}

void display_help() {
	std::cout << "mjwm version 1.0, Copyright (C) 2014 Chirantan Mitra <chirantan.mitra@gmail.com>" << std::endl;
	std::cout << "mjwm comes with ABSOLUTELY NO WARRANTY; for details refer COPYING." << std::endl;
	std::cout << "This is free software, and you are welcome to redistribute it" << std::endl;
	std::cout << "under certain conditions; Refer COPYING for details." << std::endl;

	std::cout << "mjwm creates jwm's menu from (freedesktop) desktop files" << std::endl;
	std::cout << "  -o, --output-file       Outfile file [Default: ./automenu]" << std::endl;
	std::cout << "  -s, --input-directory   Directory to scan for '.desktop' files [Default: /usr/share/applications/]" << std::endl;
	std::cout << "  -a, --append-png        Add '.png' to icon filenames" << std::endl;
	std::cout << "  -h, --help              Show this help" << std::endl << std::endl;

	std::cout << "Include the generated file in the rootmenu section of your ~/.jwmrc" << std::endl;
	std::cout << "More information at http://github.com/chiku/mjwm" << std::endl;
}

void display_option_error(std::string program) {
	std::cerr << "Please run " << program << " -h to see options" << std::endl;
}
