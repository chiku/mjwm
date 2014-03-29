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

#ifndef __amm_jwm_transformer__
#define __amm_jwm_transformer__

#include <string>

#include "../stringx.h"
#include "../vectorx.h"

#include "../icon_service.h"
#include "../desktop_file.h"
#include "../subcategory.h"
#include "../transformer.h"

namespace amm
{
	namespace transformer
	{
		class jwm : public base
		{
		private:
			std::string remove_field_code(std::string input) const;

		public:
			virtual std::string transform(amm::representation::menu_start *entry);
			virtual std::string transform(amm::representation::menu_end *entry);
			virtual std::string transform(amm::representation::subcategory_start *entry);
			virtual std::string transform(amm::representation::subcategory_end *entry);
			virtual std::string transform(amm::representation::menu_entry *entry);
		};
	}
}

#endif
