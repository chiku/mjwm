/*
mjm2 creates jwm's menu from many (freedesktop) desktop files automatically.
Including the generated file in the rootmenu section of your system.jwmrc.
Copyright (C) 2010 insmyic <gminsm@gmail.com>
Copyright (C) 2013 Chirantan Mitra <chirantan.mitra@gmail.com>
*/

#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#include "menu_entry.c"
#include "mjm.h"


int main(int argc, char *argv[]) {

	char *scandir = "/usr/share/applications/";
	char *outfile = "./automenu";
	int iitm=0, i, aexp=0;
	menu_entry *itms;


	for (i=1; i<argc; i++) {
		if (strcmp(argv[i], "-o")==0 && i+1<argc) {outfile = argv[i+1];}
		if (strcmp(argv[i], "-s")==0 && i+1<argc) {scandir = argv[i+1];}
		if (strcmp(argv[i], "-a")==0 ) {aexp = 1;}
		if (strcmp(argv[i], "-h")==0 && i==1) {display_help(); exit(0);}
	}


	iitm = Reader(scandir, NULL);
	if (iitm) {
		itms = menu_entry_create(iitm);
		if (itms) {
			iitm = Reader(scandir, itms);
			Itmsrt(iitm, itms);
			if (Rcwrite(iitm, itms, outfile, aexp)) {
			 printf("write err...\n");
			}
			free(itms);
			} else {
					printf("malloc err...\n");
			}
	} else {
			printf("read err...\n");
	}
	exit(iitm);
}


int Reader(char *scandir, menu_entry *itms) {

	DIR *dir;
	FILE *fp;
	struct dirent *dp;
	char *sexec = "Exec", *sicon = "Icon", *sname = "Name", *scate = "Categories";
	char sline[1024], stmp[1024];
	char *sbuff;
	menu_entry *itmp;
	int ictr = 0, ectr = 0;
	
	dir=opendir(scandir);
	
	if (!dir) {
			ectr++;
	} else {
		itmp = menu_entry_create(1);
		if (!itmp) {
				ectr++;
		} else {
			for(dp=readdir(dir);dp!=NULL;dp=readdir(dir)){

			strcpy(stmp, "");
			strcat(stmp, scandir);
			strcat(stmp, dp->d_name);

			if ((fp = fopen(stmp, "r")) == NULL) {
				ectr++;
				break;
			}
			
			strcpy(itmp->executable, "");
			strcpy(itmp->icon, "");
			strcpy(itmp->name, "");
			strcpy(itmp->category, "");
			
			while (fgets(sline, 256, fp) != NULL) {
				sbuff = NULL;
				sbuff = strtok(sline, "=");
				if (sbuff) {
				if (strcmp(sbuff, sexec)==0) { strcpy(itmp->executable, strtok(NULL, "\n")); }
				if (strcmp(sbuff, sicon)==0) { strcpy(itmp->icon, strtok(NULL, "\n")); }
				if (strcmp(sbuff, sname)==0) { strcpy(itmp->name, strtok(NULL, "\n")); }
				if (strcmp(sbuff, scate)==0) { strcpy(itmp->category, strtok(NULL, "\n")); }
				}
			}

			if (strlen(itmp->executable) && strlen(itmp->icon) && strlen(itmp->name)) {
				ictr++;
				if (itms) {
					strcpy((itms+ictr-1)->executable, itmp->executable);
					strcpy((itms+ictr-1)->icon, itmp->icon);
					strcpy((itms+ictr-1)->name, itmp->name);
					strcpy((itms+ictr-1)->category, itmp->category);
				} 
			}
			
			fclose(fp);
			}
			closedir(dir);
			free(itmp);
		}
	}
	if (ectr) {
		ictr = 0;
	}
	return ictr;
}


int Rcwrite(int iitm, menu_entry *itms, char *outfile, int aexp) {

	FILE *wfp;
	int i, rslt;
	char *sprt;

	if (aexp) {
		sprt="<Program label=\"%s\" icon=\"%s.png\">%s</Program>\n";
	} else {
		sprt="<Program label=\"%s\" icon=\"%s\">%s</Program>\n";
	}

		if ((wfp=fopen(outfile, "w")) == NULL) {
			rslt = 1;
		} else {
			for (i=0 ; i<iitm ; i++) {
			fprintf(wfp, sprt, (itms+i)->name, (itms+i)->icon, (itms+i)->executable);
			}
			fclose(wfp);
			rslt = 0;
		}
		return rslt;
}


int Itmsrt(int iitm, menu_entry *itms) {

	int i, j;
	menu_entry stmp;

	for (i=0; i<iitm-1; i++) {
			for (j=i+1; j<iitm; j++) {
					if ((strcmp((itms+j)->name, (itms+i)->name)) < 0) {
						stmp = itms[i];
						itms[i] = itms[j];
						itms[j] = stmp;
					}
			}
	}
	return 0;
}


void display_help() {
	printf("mjm2\n");
	printf("Version 1.0\n");
	printf("mjm creates jwm's menu from many (freedesktop) desktop files automatically\n");
	printf("  -o   Define outfile [Default: ./automenu]\n");
	printf("  -s   Define scanning directry [Default: /usr/share/applications/]\n");
	printf("  -a   Add '.png' to icon filenames\n");
	printf("  -h   Show this help\n\n");
	printf("use it including the made file in the rootmenu section of your system.jwmrc\n");
	printf("more information -> http://mjm.sourceforge.net/ and http://insm.cocolog-nifty.com/\n");
}
