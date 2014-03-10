/*
mjwm creates jwm's menu from (freedesktop) desktop files
Include the generated file in the rootmenu section of your ~/.jwmrc
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
	_categories = "";
}

std::string
mjwm::menu_entry::name() const
{
	return _name;
}

std::string
mjwm::menu_entry::icon() const
{
	return _icon;
}

std::string
mjwm::menu_entry::executable() const
{
	return _executable;
}

std::string
mjwm::menu_entry::categories() const
{
	return _categories;
}

bool
mjwm::menu_entry::is_valid() const
{
	return (executable().length() > 0) && (icon().length() > 0) && (name().length() > 0);
}

bool
mjwm::menu_entry::has_same_name(mjwm::menu_entry other) const
{
	return name() == other.name();
}

void
mjwm::menu_entry::populate(std::string line)
{
	std::string buffer = strtok(strdup(line.c_str()), "=");

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
	file << "<Program label=\"" << name() << "\" icon=\"" << icon() << _icon_extension << "\">" << executable() << "</Program>" << std::endl;
}

void
mjwm::menu_entry::dump() const
{
	std::cout << "Name: "       << name()       << std::endl;
	std::cout << "Executable: " << executable() << std::endl;
	std::cout << "Icon: "       << icon()       << std::endl;
	std::cout << "Categories: " << categories() << std::endl;
}

std::string
mjwm::menu_entry::safe_parse() const
{
	char *token = strtok(NULL, "\n");
	return token == NULL ? std::string("") : encode(std::string(token));
}

// based on http://stackoverflow.com/questions/5665231/most-efficient-way-to-escape-xml-html-in-c-string#answer-5665377
std::string
mjwm::menu_entry::encode(std::string data) const
{
	std::string buffer;
	buffer.reserve(data.size());
	for(size_t pos = 0; pos != data.size(); ++pos) {
		switch(data[pos]) {
			case '&':  buffer.append("&amp;");       break;
			case '\"': buffer.append("&quot;");      break;
			case '\'': buffer.append("&apos;");      break;
			case '<':  buffer.append("&lt;");        break;
			case '>':  buffer.append("&gt;");        break;
			default:   buffer.append(&data[pos], 1); break;
		}
	}
	return buffer;
}
