/*
mjm2 creates jwm's menu from many (freedesktop) desktop files automatically
Including the generated file in the rootmenu section of your system.jwmrc
Copyright (C) 2010 insmyic <gminsm@gmail.com>
Copyright (C) 2013 Chirantan Mitra <chirantan.mitra@gmail.com>
*/

#ifndef __mjwm_menu_entry__
#define __mjwm_menu_entry__

#include <string>

const int MENU_ENTRY_MAX_SIZE=1024;

namespace mjwm
{
	class menu_entry
	{
	public:
		std::string name;
		std::string executable;
		std::string icon;
		std::string category;

	public:
		menu_entry();

		void populate(char *line);
		void dump();
	};
}

#endif
