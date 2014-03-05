/*
mjm2 creates jwm's menu from many (freedesktop) desktop files automatically
Including the generated file in the rootmenu section of your system.jwmrc
Copyright (C) 2010 insmyic <gminsm@gmail.com>
Copyright (C) 2013 Chirantan Mitra <chirantan.mitra@gmail.com>
*/

#include <stdlib.h>

#include "menu_entry.h"

struct menu_entry {
	char name[256];
	char executable[256];
	char icon[256];
	char category[256];
};

menu_entry*
menu_entry_create(int size)
{
	return (menu_entry*)malloc(sizeof(menu_entry) * size);
}
