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

#ifndef __amm_representation__
#define __amm_representation__

#include <string>

namespace amm
{
	namespace representation
	{
		class base
		{
		public:
			virtual std::string name() const = 0;
		};

		class menu_start : public base
		{
		public:
			std::string name() const;
		};

		class menu_end : public base
		{
		public:
			std::string name() const;
		};


		class subcategory_start : public base
		{
		private:
			std::string _display_name;
		public:
			subcategory_start(std::string display_name);
			std::string name() const;
		};

		class subcategory_end : public base
		{
		private:
			std::string _display_name;
		public:
			subcategory_end(std::string display_name);
			std::string name() const;
		};


		class menu_entry : public base
		{
		private:
			std::string _name;
		public:
			menu_entry(std::string name);
			std::string name() const;
		};
	};
}

#endif
