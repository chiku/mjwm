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

#ifndef __amm_jwm_subcategory__
#define __amm_jwm_subcategory__

#include <iostream>
#include <string>
#include <vector>

#include "../icon_service.h"
#include "../desktop_file.h"
#include "transform.h"

namespace amm
{
	namespace jwm
	{		
		// Understands a Menu section inside JWM configuration file 
		class subcategory
		{
		private:
			std::string _classification_name;
			std::string _display_name;
			std::string _icon_name;
			amm::icon_service _icon_service;
			std::vector<amm::desktop_file> _desktop_files;

		public:
			subcategory();
			subcategory(std::string classification_name, std::string display_name, std::string icon_name, amm::icon_service icon_service);

			amm::icon_service icon_service() const;
			std::string classification_name() const;  // TODO : verify &  Deleteme
			std::string first_line() const;
			std::string last_line() const;
			std::vector<amm::desktop_file> desktop_files() const;
			bool has_entries() const;

			void add_desktop_file(amm::desktop_file desktop_file);
			void sort_desktop_files();
		};

		std::ostream& operator <<(std::ostream& stream, const amm::jwm::subcategory& subcategory);
	}
}

#endif
