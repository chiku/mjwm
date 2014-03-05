/*
mjm2 creates jwm's menu from many (freedesktop) desktop files automatically.
Including the generated file in the rootmenu section of your system.jwmrc.
Copyright (C) 2010 insmyic <gminsm@gmail.com>
Copyright (C) 2013 Chirantan Mitra <chirantan.mitra@gmail.com>
*/

typedef struct itm itm;

int Reader(char *scandir, itm *itms);
int Rcwrite(int iitm, itm *itms, char *outfile, int aexp);
int Itmsrt(int iitm, itm *itms);
void Dspout(void);
