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

#include "transformer.h"

namespace amm
{
	namespace representation
	{
		class base
		{
		public:
			virtual std::string name() = 0;
			virtual std::string visit(amm::transformer::base &transformer) = 0;
		};

		class menu_start : public base
		{
		public:
			virtual std::string name();
			virtual std::string visit(amm::transformer::base &transformer);
		};

		class menu_end : public base
		{
		public:
			virtual std::string name();
			virtual std::string visit(amm::transformer::base &transformer);
		};


		class subcategory_start : public base
		{
		private:
			std::string _name;
			std::string _icon;
		public:
			subcategory_start(std::string name, std::string icon);
			virtual std::string name();
			virtual std::string icon();
			virtual std::string visit(amm::transformer::base &transformer);
		};

		class subcategory_end : public base
		{
		private:
			std::string _name;
		public:
			subcategory_end(std::string name);
			virtual std::string name();
			virtual std::string visit(amm::transformer::base &transformer);
		};


		class menu_entry : public base
		{
		private:
			std::string _name;
			std::string _icon;
			std::string _executable;
		public:
			menu_entry(std::string name, std::string icon, std::string executable);
			virtual std::string name();
			virtual std::string icon();
			virtual std::string executable();
			virtual std::string visit(amm::transformer::base &transformer);
		};
	};
}

#endif
