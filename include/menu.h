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

#ifndef AMM_MENU_H_
#define AMM_MENU_H_

#include <string>
#include <vector>

#include "icon_service.h"
#include "subcategory.h"
#include "representation.h"
#include "stats.h"

namespace amm
{
	// Understands a collection of desktop files divided in subcategories
	class menu
	{
	private:
		std::vector<std::string> desktop_file_names_;

		amm::Stats stats_;

		amm::IconService icon_service_;
		std::vector<amm::Subcategory> subcategories_;
		amm::Subcategory unclassified_subcategory_;

		void classify(amm::DesktopFile entry, std::string file_name);
		void create_default_categories();

	public:
		menu();

		std::vector<amm::Subcategory> subcategories() const;
		amm::Stats stats() const;

		void load_custom_categories(std::vector<std::string> lines);
		void register_icon_service(amm::IconService icon_service);
		void populate(std::vector<std::string> desktop_file_names);
		void sort();
		std::vector<amm::representation::base*> representations() const;
	};
}

#endif // AMM_MENU_H_
