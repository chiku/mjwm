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

#ifndef __amm_menu__
#define __amm_menu__

#include <string>
#include <vector>

#include "icon_service.h"
#include "subcategory.h"
#include "representation.h"

namespace amm
{
	// Understands a collection of desktop files divided in subcategories
	class menu
	{
	private:
		std::vector<std::string> _desktop_file_names;

		size_t _total_parsed_files;
		size_t _total_unclassified_parsed_files;
		std::vector<std::string> _unparsed_file_names;

		amm::icon_service _icon_service;
		std::vector<amm::subcategory> _subcategories;
		amm::subcategory _unclassified_subcategory;

		void classify(amm::desktop_file entry);
		void create_default_categories();

	public:
		menu();

		std::vector<amm::subcategory> subcategories() const;
		size_t total_parsed_files() const;
		size_t total_unclassified_parsed_files() const;
		std::vector<std::string> unparsed_file_names() const;

		void load_custom_categories(std::vector<std::string> lines);
		void register_icon_service(amm::icon_service icon_service);
		void populate(std::vector<std::string> desktop_file_names);
		void sort();
		std::vector<amm::representation::base*> representations() const;
	};
}

#endif
