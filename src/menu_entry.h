/*
mjm2 creates jwm's menu from many (freedesktop) desktop files automatically
Including the generated file in the rootmenu section of your system.jwmrc
Copyright (C) 2010 insmyic <gminsm@gmail.com>
Copyright (C) 2013 Chirantan Mitra <chirantan.mitra@gmail.com>
*/

typedef struct menu_entry menu_entry;

menu_entry* menu_entry_create(int size);
void menu_entry_destroy(menu_entry* self);

void menu_entry_blank(menu_entry* self);
void menu_entry_populate(menu_entry *self, char *line);
void menu_entry_dump(menu_entry* self);
