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

#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>

#include "menu_entry.h"
#include "mjwm.h"

int main(int argc, char *argv[]) {
	std::string directory_to_scan("/usr/share/applications/");
	std::string output_filename("./automenu");
	std::string icon_extension("");
	int iitm=0, i;
	mjwm::menu_entry *menu_entries;

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

	iitm = Reader(directory_to_scan, NULL);
	if (iitm) {
		menu_entries = new mjwm::menu_entry[iitm];
		if (menu_entries) {
			iitm = Reader(directory_to_scan, menu_entries);
			Itmsrt(iitm, menu_entries);
			Rcwrite(iitm, menu_entries, output_filename, icon_extension);
			delete[] menu_entries;
		}
	} else {
		printf("read err...\n");
	}

	return 0;
}

// TODO : Avoid double entry to the function
int Reader(std::string directory_to_scan, mjwm::menu_entry *menu_entries) {
	DIR *dir;
	FILE *fp;
	dirent *dp;
	char sline[1024];
	std::string desktop_filename;
	mjwm::menu_entry itmp;
	int ictr = 0, ectr = 0;

	dir = opendir(directory_to_scan.c_str());

	if (!dir) {
		std::cerr << "Couldn't open directory " << directory_to_scan << std::endl;
		exit(1);
	}

	itmp = mjwm::menu_entry();
	for(dp = readdir(dir); dp != NULL; dp = readdir(dir)) {
		desktop_filename = directory_to_scan + dp->d_name;

		if ((fp = fopen(desktop_filename.c_str(), "r")) == NULL) {
			ectr++;
			break;
		}

		while (fgets(sline, 1024, fp) != NULL) {
			itmp.populate(sline);
		}

		if (itmp.is_valid()) {
			ictr++;
			if (menu_entries) {
				menu_entries[ictr-1] = itmp;
			}
		}

		fclose(fp);
	}
	closedir(dir);

	if (ectr) {
		ictr = 0;
	}
	return ictr;
}

// TODO : pass menu_entries as a vector
void Rcwrite(int iitm, mjwm::menu_entry *menu_entries, std::string output_filename, std::string icon_extension)
{
	std::ofstream file(output_filename.c_str());

	for (int i=0 ; i<iitm ; i++) {
		menu_entries[i].write_to(file, icon_extension);
	}
}


// TODO : pass menu_entries as a vector
int Itmsrt(int iitm, mjwm::menu_entry *menu_entries) {
	int i, j;
	mjwm::menu_entry stmp;

	for (i=0; i<iitm-1; i++) {
		for (j=i+1; j<iitm; j++) {
			if (!menu_entries[j].has_same_name(menu_entries[i])) {
				stmp = menu_entries[i];
				menu_entries[i] = menu_entries[j];
				menu_entries[j] = stmp;
			}
		}
	}
	return 0;
}


void display_help() {
	std::cout << "mjwm" << std::endl;
	std::cout << "Version 1.0" << std::endl;
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
