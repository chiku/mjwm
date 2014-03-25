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

#ifndef __amm_vectorx__
#define __amm_vectorx__

#include <string>
#include <vector>

namespace amm
{
	class vectorx
	{
	private:
		std::vector<std::string> _vector;

	public:
		vectorx(std::vector<std::string> vector);

		std::string join(std::string delimiter) const;
		std::vector<std::string> terminate_with(std::string delimiter) const;
		std::vector<std::string> unique() const;
	};
}

#endif
