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

#ifndef __amm_categories__
#define __amm_categories__

#include <string>
#include <vector>

namespace amm
{
	const std::string DESKTOP_FILE_CATEGORY_DELIM = ";";

	class desktop_file_categories;

	std::ostream& operator <<(std::ostream& stream, const amm::desktop_file_categories& desktop_file_categories);

	// Understands what sub-section should a single desktop file entry belong to as per FreeDesktop guidelines
	class desktop_file_categories
	{
	private:
		std::string _raw;
		std::vector<std::string> _categories;

		void parse();
		void sort();

	public:
		desktop_file_categories();
		desktop_file_categories(std::string raw);

		bool is_a(std::string type) const;

		friend std::ostream& operator << (std::ostream& stream, const amm::desktop_file_categories& desktop_file_categories);
	};
}

#endif
