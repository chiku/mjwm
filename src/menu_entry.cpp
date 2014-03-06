/*
mjm2 creates jwm's menu from many (freedesktop) desktop files automatically
Including the generated file in the rootmenu section of your system.jwmrc
Copyright (C) 2010 insmyic <gminsm@gmail.com>
Copyright (C) 2013 Chirantan Mitra <chirantan.mitra@gmail.com>
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "menu_entry.h"

#define MENU_ENTRY_MAX_SIZE 1024

struct menu_entry {
	char name      [MENU_ENTRY_MAX_SIZE];
	char executable[MENU_ENTRY_MAX_SIZE];
	char icon      [MENU_ENTRY_MAX_SIZE];
	char category  [MENU_ENTRY_MAX_SIZE];
};

menu_entry*
menu_entry_create(int size)
{
	void *memory = malloc(sizeof(menu_entry) * size);

	if (memory == NULL) {
		fprintf(stderr, "malloc error");
		exit(1);
	}

	return (menu_entry*)memory;
}

void
menu_entry_destroy(menu_entry *self)
{
	free(self);
}

void
menu_entry_blank(menu_entry *self)
{
	strncpy(self->name,       "", MENU_ENTRY_MAX_SIZE);
	strncpy(self->executable, "", MENU_ENTRY_MAX_SIZE);
	strncpy(self->icon,       "", MENU_ENTRY_MAX_SIZE);
	strncpy(self->category,   "", MENU_ENTRY_MAX_SIZE);
}

void
menu_entry_populate(menu_entry *self, char *line)
{
	static const char EXECUTABLE[] = "Exec";
	static const char ICON[]       = "Icon";
	static const char NAME[]       = "Name";
	static const char CATEGORIES[] = "Categories";

	char buffer[MENU_ENTRY_MAX_SIZE];
	strncpy(buffer, strtok(line, "="), MENU_ENTRY_MAX_SIZE);
	buffer[MENU_ENTRY_MAX_SIZE-1] = '\0';

	if (buffer[0] != '\0') {
		if (strncmp(buffer, EXECUTABLE, MENU_ENTRY_MAX_SIZE)==0) { 
			strncpy(self->executable, strtok(NULL, "\n"), MENU_ENTRY_MAX_SIZE); 
			self->executable[MENU_ENTRY_MAX_SIZE-1] = '\0'; 
		}
		if (strncmp(buffer, ICON, MENU_ENTRY_MAX_SIZE)==0) { 
			strncpy(self->icon,strtok(NULL, "\n"), MENU_ENTRY_MAX_SIZE);
			self->icon[MENU_ENTRY_MAX_SIZE-1] = '\0';
		}
		if (strncmp(buffer, NAME,MENU_ENTRY_MAX_SIZE)==0) {
			strncpy(self->name,strtok(NULL, "\n"), MENU_ENTRY_MAX_SIZE);
			self->name[MENU_ENTRY_MAX_SIZE-1] = '\0';
		}
		if (strncmp(buffer, CATEGORIES, MENU_ENTRY_MAX_SIZE)==0) {
			strncpy(self->category, strtok(NULL, "\n"), MENU_ENTRY_MAX_SIZE);
			self->category[MENU_ENTRY_MAX_SIZE-1] = '\0';
		}
	}
}

void
menu_entry_dump(menu_entry* self)
{
	printf("Name: %s\n",       self->name);
	printf("Executable: %s\n", self->executable);
	printf("Icon: %s\n",       self->icon);
	printf("Categories: %s\n", self->category);
}
