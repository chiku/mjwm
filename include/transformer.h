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

#ifndef __amm_transformer__
#define __amm_transformer__

#include <string>

#include "representation.h"

namespace amm
{
	namespace representation
	{
		class base;
		class menu_start;
		class menu_end;
		class subcategory_start;
		class subcategory_end;
		class menu_entry;
	}

	namespace transformer
	{
		class base
		{
		public:
			virtual std::string transform(amm::representation::menu_start *entry) = 0;
			virtual std::string transform(amm::representation::menu_end *entry) = 0;
			virtual std::string transform(amm::representation::subcategory_start *entry) = 0;
			virtual std::string transform(amm::representation::subcategory_end *entry) = 0;
			virtual std::string transform(amm::representation::menu_entry *entry) = 0;
		};
	}
}

#endif
