/*
mjm2 creates jwm's menu from many (freedesktop) desktop files automatically
Including the generated file in the rootmenu section of your system.jwmrc
Copyright (C) 2010 insmyic <gminsm@gmail.com>
Copyright (C) 2013 Chirantan Mitra <chirantan.mitra@gmail.com>
*/

#include <stdlib.h>

#include <iostream>
#include <string.h>

#include "menu_entry.h"


mjwm::menu_entry::menu_entry()
{
	name       = "";
	executable = "";
	icon       = "";
	category   = "";
}

void
mjwm::menu_entry::populate(char *line)
{
	static const char EXECUTABLE[] = "Exec";
	static const char ICON[]       = "Icon";
	static const char NAME[]       = "Name";
	static const char CATEGORIES[] = "Categories";

	char buffer[MENU_ENTRY_MAX_SIZE];
	strncpy(buffer, strtok(line, "="), MENU_ENTRY_MAX_SIZE);
	buffer[MENU_ENTRY_MAX_SIZE-1] = '\0';

	if (buffer[0] != '\0') {
		if (strncmp(buffer, EXECUTABLE, MENU_ENTRY_MAX_SIZE)==0) { 
			executable = strtok(NULL, "\n");
		}
		if (strncmp(buffer, ICON, MENU_ENTRY_MAX_SIZE)==0) { 
			icon = strtok(NULL, "\n");
		}
		if (strncmp(buffer, NAME,MENU_ENTRY_MAX_SIZE)==0) {
			name = strtok(NULL, "\n");
		}
		if (strncmp(buffer, CATEGORIES, MENU_ENTRY_MAX_SIZE)==0) {
			category = strtok(NULL, "\n");
		}
	}
}

void
mjwm::menu_entry::dump()
{
	std::cout << "Name: "       << name       << std::endl;
	std::cout << "Executable: " << executable << std::endl;
	std::cout << "Icon: "       << icon       << std::endl;
	std::cout << "Categories: " << category   << std::endl;
}
