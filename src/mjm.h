/*
mjm makes jwm's menu from many (freedesktop)desktop files automatically.
use it including the made file in the rootmenu section of your system.jwmrc.
Copyright (C) 2010 insmyic <gminsm@gmail.com>
*/

typedef struct itm itm;

int Reader(char *scandir, itm *itms);
int Rcwrite(int iitm, itm *itms, char *outfile, int aexp);
int Itmsrt(int iitm, itm *itms);
void Dspout(void);
