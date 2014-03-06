/*
mjm2 creates jwm's menu from many (freedesktop) desktop files automatically
Including the generated file in the rootmenu section of your system.jwmrc
Copyright (C) 2010 insmyic <gminsm@gmail.com>
Copyright (C) 2013 Chirantan Mitra <chirantan.mitra@gmail.com>
*/

#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include <unistd.h>

#include "menu_entry.cpp"
#include "mjm.h"


int main(int argc, char *argv[]) {
	std::string directory_to_scan("/usr/share/applications/");
	std::string output_filename("./automenu");
	std::string icon_extension("");
	int iitm=0, i;
	mjwm::menu_entry *menu_entries;

	for (i=1; i<argc; i++) {
		if (strcmp(argv[i], "-o")==0 && i+1<argc) { output_filename = argv[i+1]; }
		if (strcmp(argv[i], "-s")==0 && i+1<argc) { directory_to_scan = argv[i+1] ;}
		if (strcmp(argv[i], "-a")==0 ) { icon_extension = ".png"; }
		if (strcmp(argv[i], "-h")==0 && i==1) { display_help(); exit(0); }
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
	exit(iitm);
}


int Reader(std::string directory_to_scan, mjwm::menu_entry *menu_entries) {
	DIR *dir;
	FILE *fp;
	struct dirent *dp;
	char sline[1024];
	std::string desktop_file;
	mjwm::menu_entry itmp;
	int ictr = 0, ectr = 0;

	dir=opendir(directory_to_scan.c_str());
	
	if (!dir) {
		ectr++;
	} else {
		itmp = mjwm::menu_entry();
		for(dp=readdir(dir);dp!=NULL;dp=readdir(dir)) {

		desktop_file = directory_to_scan;
		desktop_file.append(dp->d_name);

		if ((fp = fopen(desktop_file.c_str(), "r")) == NULL) {
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
	}
	if (ectr) {
		ictr = 0;
	}
	return ictr;
}


void Rcwrite(int iitm, mjwm::menu_entry *menu_entries, std::string output_filename, std::string icon_extension)
{
	std::ofstream file(output_filename.c_str());

	for (int i=0 ; i<iitm ; i++) {
		menu_entries[i].write_to(file, icon_extension);
	}
}


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
	printf("mjm2\n");
	printf("Version 1.0\n");
	printf("mjm creates jwm's menu from many (freedesktop) desktop files automatically\n");
	printf("  -o   Outfile file [Default: ./automenu]\n");
	printf("  -s   Directory to scan for '.desktop' files [Default: /usr/share/applications/]\n");
	printf("  -a   Add '.png' to icon filenames\n");
	printf("  -h   Show this help\n\n");
	printf("Including the generated file in the rootmenu section of your system.jwmrc\n");
	printf("more information -> http://github.com/chiku/mjm2\n");
}
