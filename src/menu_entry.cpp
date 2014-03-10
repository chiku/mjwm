/*
mjwm creates jwm's menu from (freedesktop) desktop files
Include the generated file in the rootmenu section of your system.jwmrc
Based on work by insmyic <gminsm@gmail.com> http://sourceforge.net/projects/mjm
Copyright (C) 2014 Chirantan Mitra <chirantan.mitra@gmail.com>
*/

#include <iostream>
#include <fstream>

#include <string.h>

#include "menu_entry.h"

const std::string NAME       = "Name";
const std::string EXECUTABLE = "Exec";
const std::string ICON       = "Icon";
const std::string CATEGORIES = "Categories";

mjwm::menu_entry::menu_entry()
{
	_name       = "";
	_executable = "";
	_icon       = "";
	_categories   = "";
}

std::string
mjwm::menu_entry::name() const
{
	return _name;
}

bool
mjwm::menu_entry::is_valid() const
{
	return (_executable.length() > 0) && (_icon.length() > 0) && (name().length() > 0);
}

bool
mjwm::menu_entry::has_same_name(mjwm::menu_entry other) const
{
	return name() == other.name();
}

void
mjwm::menu_entry::populate(char *line) // TODO : pass std::string
{
	std::string buffer = strtok(strdup(line), "=");

	if (buffer[0] != '\0') {
		if (buffer == NAME) {
			_name = safe_parse();
		}
		if (buffer == ICON) {
			_icon = safe_parse();
		}
		if (buffer == EXECUTABLE) {
			_executable = safe_parse();
		}
		if (buffer == CATEGORIES) {
			_categories = safe_parse();
		}
	}
}

void
mjwm::menu_entry::write_to(std::ofstream &file, std::string _icon_extension) const
{
	file << "<Program label=\"" << name() << "\" icon=\"" << _icon << _icon_extension << "\">" << _executable << "</Program>" << std::endl;
}

void
mjwm::menu_entry::dump() const
{
	std::cout << "Name: "       << name()      << std::endl;
	std::cout << "Executable: " << _executable << std::endl;
	std::cout << "Icon: "       << _icon       << std::endl;
	std::cout << "Categories: " << _categories   << std::endl;
}

std::string
mjwm::menu_entry::safe_parse() const
{
	char *token = strtok(NULL, "\n");
	return token == NULL ? std::string("") : std::string(token);
}
