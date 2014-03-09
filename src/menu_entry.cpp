/*
mjm2 creates jwm's menu from many (freedesktop) desktop files automatically
Including the generated file in the rootmenu section of your system.jwmrc
Copyright (C) 2010 insmyic <gminsm@gmail.com>
Copyright (C) 2013 Chirantan Mitra <chirantan.mitra@gmail.com>
*/

#include <iostream>
#include <fstream>

#include <string.h>

#include "menu_entry.h"

const std::string EXECUTABLE = "Exec";
const std::string ICON       = "Icon";
const std::string NAME       = "Name";
const std::string CATEGORIES = "Categories";

mjwm::menu_entry::menu_entry()
{
	name       = "";
	executable = "";
	icon       = "";
	category   = "";
}

bool
mjwm::menu_entry::is_valid() const
{
	return (executable.length() > 0) && (icon.length() > 0) && (name.length() > 0);
}

bool
mjwm::menu_entry::has_same_name(mjwm::menu_entry other) const
{
	return name == other.name;
}

void
mjwm::menu_entry::populate(char *line)
{
	std::string buffer = strtok(line, "=");

	if (buffer[0] != '\0') {
		if (buffer == EXECUTABLE) {
			executable = safe_parse();
		}
		if (buffer == ICON) {
			icon = safe_parse();
		}
		if (buffer == NAME) {
			name = safe_parse();
		}
		if (buffer == CATEGORIES) {
			category = safe_parse();
		}
	}
}

void
mjwm::menu_entry::write_to(std::ofstream &file, std::string icon_extension) const
{
	file << "<Program label=\"" << name << "\"icon=\"" << icon << icon_extension << "\"" << executable << "</Program>" << std::endl;
}

void
mjwm::menu_entry::dump() const
{
	std::cout << "Name: "       << name       << std::endl;
	std::cout << "Executable: " << executable << std::endl;
	std::cout << "Icon: "       << icon       << std::endl;
	std::cout << "Categories: " << category   << std::endl;
}

std::string
mjwm::menu_entry::safe_parse() const
{
	char *token = strtok(NULL, "\n");
	return token == NULL ? std::string("") : std::string(token);
}
