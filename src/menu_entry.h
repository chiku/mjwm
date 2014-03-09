/*
mjwm creates jwm's menu from (freedesktop) desktop files
Include the generated file in the rootmenu section of your system.jwmrc
Based on work by insmyic <gminsm@gmail.com> http://sourceforge.net/projects/mjm
Copyright (C) 2014 Chirantan Mitra <chirantan.mitra@gmail.com>
*/

#ifndef __mjwm_menu_entry__
#define __mjwm_menu_entry__

#include <fstream>
#include <string>

const int MENU_ENTRY_MAX_SIZE=1024;

namespace mjwm
{
	class menu_entry
	{
	private:
		std::string name;
		std::string executable;
		std::string icon;
		std::string category;

	public:
		menu_entry();

		bool is_valid() const;
		bool has_same_name(mjwm::menu_entry other) const;
		void populate(char *line);
		void write_to(std::ofstream &file, std::string icon_extension) const;
		void dump() const;
		std::string safe_parse() const;
	};
}

#endif
