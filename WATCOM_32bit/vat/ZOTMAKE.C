// ZOT music compiler  (Zorg's Omnifarious Tunage)
// Written by Eric Jorgensen
//
//  This program takes a MOD, S3m, or MIDI file and converts it to a
// proprietary ZOT format to protect from redistribution.

#include "vat.h"
#include "compat.h"
#include <stdio.h>
#include <conio.h>
#include <dos.h>
#include <malloc.h>
#include <graph.h>
#include <string.h>
#include <ctype.h>

void exportmod(char *infilename,char *outfilename);
void exports3m(char *infilename,char *outfilename);
void exportmidi(char *infilename,char *outfilename);

/**************************************************************************
	void main(int argc, char *argv[])

	DESCRIPTION:

**************************************************************************/
void main(int argc, char *argv[])
{
	char errstring[256],string[1000],rootname[100],*spot;
	VATMUSICTYPE mtype;

	printf("ZOTMAKE version 1.00\n");

	if(argc < 2) {
		printf("Usage:  ZOTMAKE (filename) [(outputfilename)]\n");
		exit(1);
	}

	if(argc < 3) {
																		// Make the rootname
		spot = strchr(argv[1],'\\');
		if(!spot) spot = strchr(argv[1],':');
		if(spot) strcpy(rootname,spot+1);
		else strcpy(rootname,argv[1]);
		spot = strchr(rootname,'.');
		if(spot) *spot = 0;
		strcat(rootname,".ZOT");
	}
	else strcpy(rootname,argv[2]);

	mtype = GetMusicType(argv[1],errstring);
	switch(mtype) {
		case v_musictype_mod:
			exportmod(argv[1],rootname);
			break;
		case v_musictype_s3m:
			exports3m(argv[1],rootname);
			break;
		case v_musictype_midi:
			exportmidi(argv[1],rootname);
			break;
		case v_musictype_unknown:
			printf("Not a recognized music type.\n");
			break;
		case v_musictype_error:
			printf("ERROR: %s\n",errstring);
			break;
	}

}



/**************************************************************************
	void exportmod(char *infilename,char *outfilename)

	DESCRIPTION:

**************************************************************************/
void exportmod(char *infilename,char *outfilename)
{
	int i,j,usedmem;
	void *zoop;
	char errstring[256],string[256];
	MOD *thismod;
	int totalmem;
	FILE *output;

	zoop = malloc(2000000);
	free(zoop);
	totalmem =  _memavl();
	printf("MEMORY: %d bytes\n",totalmem);

	thismod = LoadMod(infilename,errstring);
	if(!thismod) {
		printf("ERROR: %s\n",errstring);
		return;
	}

	usedmem = totalmem - _memavl();
	printf("MEMORY USED: %d bytes\n",usedmem);


	output = fopen(outfilename,"wb");
	if(!output) {
		printf("Error opening output file...\n");
		exit(1);
	}

	printf("Writing header...\n");
																		 // ID string.  40 characters
	sprintf(string,"Zorg's Omnifarious Tunage (tm) 1.00%c",26);
	if(fwrite(string,1,40,output) < 40) { fclose(output); printf("File write error!\n"); return;}
	sprintf(string,"mod");
	if(fwrite(string,1,3,output) < 3) { fclose(output); printf("File write error!\n"); return;}
	if(fwrite(&usedmem,1,sizeof(int),output) < sizeof(int)) { fclose(output); printf("File write error!\n"); return;}

	printf("Writing Music information...\n");

	if(fwrite(thismod,1,sizeof(MOD),output) < sizeof(MOD)) { fclose(output); printf("File write error!\n"); return;}
	for(i = 0; i < 32; i++) {
		if(thismod->slength[i]) {
			if(fwrite(thismod->sdata[i],1,thismod->slength[i],output) < thismod->slength[i]) { fclose(output); printf("File write error!\n"); return;}
		}
	}
	for(i = 0; i < 128; i++) {
		if(thismod->pattern_data[i]) {
			if(fwrite(thismod->pattern_data[i],1,1024,output) < 1024) { fclose(output); printf("File write error!\n"); return;}
		}
	}

	FreeMod(thismod);


	fclose(output);

}

/**************************************************************************
	void exports3m(char *infilename,char *outfilename)

	DESCRIPTION:

**************************************************************************/
void exports3m(char *infilename,char *outfilename)
{
	int i,j,usedmem;
	void *zoop;
	char errstring[256],string[256];
	S3M *thiss3m;
	int totalmem;
	FILE *output;
	int patternsize;

	zoop = malloc(2000000);
	free(zoop);
	totalmem =  _memavl();
	printf("MEMORY: %d bytes\n",totalmem);

	thiss3m = LoadS3M(infilename,errstring);
	if(!thiss3m) {
		printf("ERROR: %s\n",errstring);
		return;
	}
	usedmem = totalmem - _memavl();
	printf("MEMORY USED: %d bytes\n",usedmem);


	output = fopen(outfilename,"wb");
	if(!output) {
		printf("Error opening output file...\n");
		exit(1);
	}

	printf("Writing header...\n");
																		 // ID string.  40 characters
	sprintf(string,"Zorg's Omnifarious Tunage (tm) 1.00%c",26);
	if(fwrite(string,1,40,output) < 40) { fclose(output); printf("File write error!\n"); return;}
	sprintf(string,"s3m");
	if(fwrite(string,1,3,output) < 3) { fclose(output); printf("File write error!\n"); return;}
	if(fwrite(&usedmem,1,sizeof(int),output) < sizeof(int)) { fclose(output); printf("File write error!\n"); return;}

	printf("Writing Music information...\n");

	if(fwrite(thiss3m,1,sizeof(S3M),output) < sizeof(S3M)) { fclose(output); printf("File write error!\n"); return;}
	for(i = 0; i < 100; i++) {
		if(thiss3m->slength[i]) {
			if(fwrite(thiss3m->sdata[i],1,thiss3m->slength[i],output) < thiss3m->slength[i]) { fclose(output); printf("File write error!\n"); return;}
		}
	}

	patternsize = thiss3m->channelnum * 5 * 64;

	for(i = 0; i < 256; i++) {
		if(thiss3m->pattern_data[i]) {
			if(fwrite(thiss3m->pattern_data[i],1,patternsize,output) < patternsize) { fclose(output); printf("File write error!\n"); return;}
		}
	}

	FreeS3M(thiss3m);


	fclose(output);

}
/**************************************************************************
	void exportmidi(char *infilename,char *outfilename)

	DESCRIPTION:

**************************************************************************/
void exportmidi(char *infilename,char *outfilename)
{
	int i,j,usedmem;
	void *zoop;
	char errstring[256],string[256];
	MIDI *thismidi;
	int totalmem;
	FILE *output;

	zoop = malloc(2000000);
	free(zoop);
	totalmem =  _memavl();
	printf("MEMORY: %d bytes\n",totalmem);

	thismidi = LoadMidi(infilename,errstring);
	if(!thismidi) {
		printf("ERROR: %s\n",errstring);
		return;
	}

	usedmem = totalmem - _memavl();
	printf("MEMORY USED: %d bytes\n",usedmem);


	output = fopen(outfilename,"wb");
	if(!output) {
		printf("Error opening output file...\n");
		exit(1);
	}

	printf("Writing header...\n");
																		 // ID string.  40 characters
	sprintf(string,"Zorg's Omnifarious Tunage (tm) 1.00%c",26);
	if(fwrite(string,1,40,output) < 40) { fclose(output); printf("File write error!\n"); return;}
	sprintf(string,"mid");
	if(fwrite(string,1,3,output) < 3) { fclose(output); printf("File write error!\n"); return;}
	if(fwrite(&usedmem,1,sizeof(int),output) < sizeof(int)) { fclose(output); printf("File write error!\n"); return;}

	printf("Writing Music information...\n");

	if(fwrite(thismidi,1,sizeof(MIDI),output) < sizeof(MOD)) { fclose(output); printf("File write error!\n"); return;}
	for(i = 0; i < MAXMIDITRACKS; i++) {
		if(thismidi->track[i]) {
			if(fwrite(thismidi->track[i],1,thismidi->tracksize[i],output) < thismidi->tracksize[i]) { fclose(output); printf("File write error!\n"); return;}
		}
	}

	FreeMidi(thismidi);


	fclose(output);

}
