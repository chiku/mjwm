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
		std::string _name;
		std::string _executable;
		std::string _icon;
		std::string _categories;

		std::string safe_parse() const;
		std::string encode(std::string data) const;
	public:
		menu_entry();

		std::string name() const;
		std::string icon() const;
		std::string executable() const;
		std::string categories() const;

		bool is_valid() const;
		bool has_same_name(mjwm::menu_entry other) const;
		void populate(std::string line);
		void write_to(std::ofstream &file, std::string icon_extension) const;
		void dump() const;
	};
}

#endif
