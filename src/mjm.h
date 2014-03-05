/*
mjm2 creates jwm's menu from many (freedesktop) desktop files automatically.
Including the generated file in the rootmenu section of your system.jwmrc.
Copyright (C) 2010 insmyic <gminsm@gmail.com>
Copyright (C) 2013 Chirantan Mitra <chirantan.mitra@gmail.com>
*/

typedef struct entry entry;

int Reader(char *scandir, entry *itms);
int Rcwrite(int iitm, entry *itms, char *outfile, int aexp);
int Itmsrt(int iitm, entry *itms);
void display_help(void);
