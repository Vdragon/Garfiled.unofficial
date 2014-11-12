/***************************************************************************/
/**                                                                       **/
/**                     Garfiled Garbage File Generator                   **/
/**                                                                       **/
/** ..................................................................... **/
/**                        Copyright 2004-2013 Elias Zacarias (Damnsoft)  **/
/**                                                                       **/
/** This program is free software: you can redistribute it and/or modify  **/
/** it under the terms of the GNU General Public License version 3 as     **/
/** published by the Free Software Foundation.                            **/
/**                                                                       **/
/** This program is distributed in the hope that it will be useful,       **/
/** but WITHOUT ANY WARRANTY; without even the implied warranty of        **/
/** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         **/
/** GNU General Public License for more details.                          **/
/**                                                                       **/
/** You should have received a copy of the GNU General Public License     **/
/** along with this program.  If not, see <http://www.gnu.org/licenses/>. **/
/**                                                                       **/
/***************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAJOR_VERSION	0
#define MINOR_VERSION	101


/***********************************************************************************
** help: Shows the Help information screen.                                       **
***********************************************************************************/
void help(){
	printf ("\n Garbage file generator v%d.%d by Elias Zacarias :: Damnsoft\n", MAJOR_VERSION, MINOR_VERSION);
	printf (" Usage:\n");
	printf ("  garfiled [options] filename\n");
	printf ("       Options:\n");
	printf ("           -cNNN: Specifies the byte used to fill the file.\n");
	printf ("                  0 <= NNN <= 255. Default is '?' (63)\n");
	printf ("                  -cr for random.\n");
	printf ("           -mNNN: Number of MBytes.\n");
	printf ("           -kNNN: Number of KBytes.\n");
	printf ("           -bNNN: Number of Bytes.\n");
	printf (" Example:\n");
	printf ("   garfiled -m5 -k100 -b50 dumpfile.ext\n\n");
	

}

/***********************************************************************************
** main: GarFiled's core :)                                                       **
***********************************************************************************/
int main(int argc, char *argv[]){
	FILE *fh;
	int i, n;
	int MBYTES = 0, KBYTES = 0, BYTES = 0, random = 0;
	unsigned char byte = '?', buff[64], *filename = NULL;
	unsigned long t, totalbytes = 0;


	/* Parse command line arguments */
	if (argc < 2) help();
	else {
		for (i=1;i<argc;i++){
			if (argv[i][0] == '-'){
				/* Used by arguments */
				strcpy(buff,&argv[i][2]);
				
				switch (argv[i][1]){
					case 'c':
					case 'C':
						if (!strcmp(buff,"r") || !strcmp(buff,"R")) random = 1;
						else {
							n = atoi(buff);
							if (n >= 0 && n <256) byte = n;
							else printf ("\nASCII out of range, defaulting to '?'\n");
						}
					break;

					case 'm':
					case 'M':
						MBYTES = atoi(buff);
					break;

					case 'k':
					case 'K':
						KBYTES = atoi(buff);
					break;

					case 'b':
					case 'B':
						BYTES  = atoi(buff);
				}
			}else filename = argv[i];
		}

		/* Create the file */
		fh = fopen(filename,"wb");
		if (!fh){
			printf ("\nERROR: Couldn't open file %s!\n",filename);
			return 1;
		}
		totalbytes = 1024 * (KBYTES + MBYTES * 1024) + BYTES;
		printf ("Generating file of %d bytes...\n", totalbytes);

		srand(time(0));
		for (t = 0; t<totalbytes;t++) {
			if (random) byte = rand() % 255;
			fputc(byte, fh);
		}
		printf ("Done!\n");
		fclose (fh);
	}
	
	return 0;
}
