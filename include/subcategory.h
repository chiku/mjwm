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

#ifndef __amm_subcategory__
#define __amm_subcategory__

#include <iostream>
#include <string>
#include <vector>

#include "desktop_file.h"

namespace amm
{
	// Understands a collection of desktop files belonging to the same category
	class subcategory
	{
	private:
		std::string _display_name;
		std::vector<std::string> _classification_names;
		std::string _icon_name;
		std::vector<amm::desktop_file> _desktop_files;

	public:
		subcategory();
		subcategory(std::string display_name, std::string icon_name, std::string classification_name);
		subcategory(std::string display_name, std::string icon_name, std::vector<std::string> classification_names);

		std::string display_name() const;
		std::vector<std::string> classification_names() const;
		std::string icon_name() const;
		std::vector<amm::desktop_file> desktop_files() const;
		bool has_entries() const;

		void add_desktop_file(amm::desktop_file desktop_file);
		void sort_desktop_files();
	};
}

#endif
