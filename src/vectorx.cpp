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

#include <string>
#include <vector>
#include <sstream>

#include "vectorx.h"

amm::vectorx::vectorx(std::vector<std::string> vector)
{
	_vector = vector;
}

std::string
amm::vectorx::join(const std::string delimeter)
{
	std::stringstream stream;
	size_t vector_size = _vector.size();

	if (vector_size == 0) {
		return "";
	}

	if (vector_size >= 2) {
		for (size_t i = 0; i < vector_size - 1; ++i) {
			stream << _vector[i] << delimeter;
		}
	}
	stream << _vector[vector_size - 1];

	return stream.str();
}