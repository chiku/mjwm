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

#ifndef __amm_menu_entry_jwm__
#define __amm_menu_entry_jwm__

#include <iostream>
#include <string>

namespace amm
{
	namespace menu_entry
	{
		class jwm;

		std::ostream& operator <<(std::ostream& stream, const amm::menu_entry::jwm& jwm_menu_entry);

		// Understands a Program entry in RootMenu section of JWM configuration file
		class jwm
		{
		private:
			std::string _name;
			std::string _icon;
			std::string _executable;

		public:
			jwm(std::string name, std::string icon, std::string executable);

			std::string name() const;
			std::string icon() const;
			std::string executable() const;

			friend std::ostream& operator <<(std::ostream& stream, const amm::menu_entry::jwm& jwm_menu_entry);
		};
	}
}

#endif
