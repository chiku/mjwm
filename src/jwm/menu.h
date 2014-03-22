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

#ifndef __amm_jwm_menu__
#define __amm_jwm_menu__

#include <iostream>
#include <string>
#include <vector>

#include "../desktop_file.h"
#include "subcategory.h"

namespace amm
{
	namespace jwm
	{
		// Understands convertion of a list of FreeDesktop .desktop files to a JWM menu
		class menu
		{
		private:
			std::vector<std::string> _desktop_file_names;
			std::string _icon_extension; // TODO : find using a icon service
			size_t _total_parsed_files;
			size_t _total_unclassified_parsed_files;
			std::string _error;

			std::vector<amm::jwm::subcategory> _subcategories;
			amm::jwm::subcategory _unclassified_subcategory;

			void classify(amm::desktop_file entry);
			void create_categories();

		public:
			menu(std::vector<std::string> desktop_file_names, std::string icon_extension);

			std::vector<amm::jwm::subcategory> subcategories() const;
			size_t total_parsed_files() const;
			size_t total_unclassified_parsed_files() const;
			bool is_valid() const; // TODO : replace with stats - caller decides on error message
			std::string error() const;  // TODO : replace with stats - caller decides on error message

			void populate();
			void sort();
		};

		std::ostream& operator << (std::ostream& stream, const amm::jwm::menu& menu);
	}
}

#endif
