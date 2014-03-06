/*
mjm2 creates jwm's menu from many (freedesktop) desktop files automatically
Including the generated file in the rootmenu section of your system.jwmrc
Copyright (C) 2010 insmyic <gminsm@gmail.com>
Copyright (C) 2013 Chirantan Mitra <chirantan.mitra@gmail.com>
*/

#ifndef __mjwm_mjwm__
#define __mjwm_mjwm__

#include <string>

#include "menu_entry.h"

int Reader(std::string directory_to_scan, mjwm::menu_entry *itms);
void Rcwrite(int iitm, mjwm::menu_entry *itms, std::string output_filename, std::string icon_extension);
int Itmsrt(int iitm, mjwm::menu_entry *itms);
void display_help(void);

#endif
