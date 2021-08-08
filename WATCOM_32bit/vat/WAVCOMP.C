// Wave compiler
// Written by Eric Jorgensen
//
//  This program takes a config file and compiles all the waves
// listed in it into a single file containing all the waves.

#include "vat.h"
#include "compat.h"
#include <stdio.h>
#include <conio.h>
#include <dos.h>
#include <malloc.h>
#include <graph.h>
#include <string.h>
#include <ctype.h>

int loadwaves(char *listfile);


WAVE *wavelist[2000];

/**************************************************************************
	void main(int argc, char *argv[])

	DESCRIPTION:

**************************************************************************/
void main(int argc, char *argv[])
{
	char errstring[256],string[1000];
	int i,j,ptotal,totalmem,usedmem;
	void *zoop;
	FILE *output;
																		// Clear the Wave table
	for(i = 0; i < 2000; i++) wavelist[i] = NULL;


	zoop = malloc(5000000);
	free(zoop);
	totalmem =  _memavl();
	printf("MEMORY: %d bytes\n",totalmem);

	ptotal = loadwaves(argv[1]);
	if(!ptotal) exit(1);

	usedmem = totalmem - _memavl();
	printf("MEMORY USED: %d bytes\n",usedmem);
	usedmem += 5120;

	getch();

	if(argc>2) output = fopen(argv[2],"wb");
	else output = fopen("wavglob.wvs","wb");
	if(!output) {
		printf("Error opening output file...\n");
		exit(1);
	}

	printf("Writing header...\n");
																		 // ID string.  40 characters
	sprintf(string,"FLABBERGASTED Wave Goop (tm) 1998.01%c",26);

	if(fwrite(string,1,40,output) < 40) { fclose(output); printf("File write error!\n"); exit(-1);}
	if(fwrite(&usedmem,1,sizeof(int),output) < sizeof(int)) { fclose(output); printf("File write error!\n"); exit(-1);}
	for(i = 0; i < ptotal; i++) {
		printf("Writing Wave %d...\n",i);
		if(fwrite(wavelist[i],1,sizeof(WAVE),output) < sizeof(WAVE)) { fclose(output); printf("File write error!\n"); exit(-1);}
		if(fwrite(wavelist[i]->data,1,wavelist[i]->chunk_size,output) < wavelist[i]->chunk_size) { fclose(output); printf("File write error!\n"); exit(-1);}
		FreeWave(wavelist[i]);
	}

	fclose(output);

}

/**************************************************************************
	void loadpatches(char *listfile)

	DESCRIPTION:

**************************************************************************/
int loadwaves(char *listfile)
{
	int i;
	FILE *input;
	char filename[1000],string[1000];
	char errstring[256];
	char *spot;
	int flag=1;
	char r;
	int ptotal = 0;
	int mapspot,mindex;

	printf("Loading Waves from %s...\n",listfile);

	input = fopen(listfile,"r");
	if(!input) {
		printf("ERROR:  could not open wave config file: %s\n",listfile);
		getch();
		return ptotal;
	}
																	// Load all the waves
	while(fgets(string,999,input)) {
		spot = strtok(string, " \t");
		strcpy(filename,spot);

		if(isalnum(filename[0]) || filename[0] == '\\') {
			printf("Loading Wave %s... ",filename);
			wavelist[ptotal] = LoadWave(filename,errstring);
			if(!wavelist[ptotal]) {
				printf("LoadWave Error: %s",errstring);
			}
			else {
				printf("Success.");
				ptotal++;
			}
			printf("\n");
		}
		if(ptotal > 1999) break;
	}
	fclose(input);


	if(!ptotal) printf("No wave files loaded. \n");

	return ptotal;
}
