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

#include "menu_entry.h"

int Reader(std::string directory_to_scan, mjwm::menu_entry *itms);
void Rcwrite(int iitm, mjwm::menu_entry *itms, std::string output_filename, std::string icon_extension);
int Itmsrt(int iitm, mjwm::menu_entry *itms);
void display_help();
void display_option_error(std::string program);

#endif
