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

/*
    Based on work by insmyic <gminsm@gmail.com> http://sourceforge.net/projects/mjm
*/


#ifndef __mjwm_mjwm__
#define __mjwm_mjwm__

#include <string>
#include <vector>

#include "menu_entry.h"

void Reader(std::string directoryname, std::vector<mjwm::menu_entry> &menu_entries);
void Itmsrt(std::vector<mjwm::menu_entry> &menu_entries);
void Rcwrite(std::vector<mjwm::menu_entry> menu_entries, std::string output_filename, std::string icon_extension);
void display_help();
void display_option_error(std::string program);

#endif
