// Varmint's EITTRIS
// Copyright (C) 1996-2000, Purple Planet Software

#include "stdafx.h"
#include "eittris.h"
#include <string.h>

char filenamechar[] = {"_^$~!#%&-{}@`'().:\\"};

/**************************************************************************
	int isfilechar(char c)

  DESCRIPTION: Returns a boolean to say wether character c is an allowed
  						 character in a filename.

**************************************************************************/
int isfilechar(char c)
{
	unsigned int i;

	if(isalnum(c)) return 1;

	for(i = 0; i < strlen(filenamechar); i++) {
		if(c == filenamechar[i]) return 1;
	}

	return 0;
}

/**************************************************************************
	void readconfig(void)

  DESCRIPTION:  Reads in the player configuration.

**************************************************************************/
void readconfig(void)
{
	FILE *input;
	int i,j,spot=-1;
	char string[1000],id[255];
	CString msg;

	input = fopen(configfilename,"r");
	if(input) {
		while(fgets(string,999,input)) {    // Read each line...
	                                        // Look for lines that start with
				                            // letters or numbers.
			if(isalnum(string[0])) {
                                        // Find token name and get it
				i = 0;
				while(i < 999 && isalnum(string[i])) i++;
				string[i] = 0;
				strcpy(id,string);
                                        // Capitalize it!
				for(j = 0; j < (int)strlen(id); j++) {
					id[j] = toupper(id[j]);
				}

				i++;
				if(!strcmp(id,"MOD")) {
					while(string[i] != 0 && i < 999) {
														// grab a filename
						while(!isalnum(string[i]) && i < 999 && string[i]) i++;
						if(!string[i] || i == 999) break;
						spot = i;
						while(isfilechar(string[i]) && i < 999) i++;
						string[i] = 0;
																				// Add to music list
						//printf("Got MOD filename: %s\n",&string[spot]);
						tune[numtunes].name = (char *)malloc(strlen(&string[spot])+2);
						if(tune[numtunes].name) {
							strcpy(tune[numtunes].name,&string[spot]);
							tune[numtunes].type = 'O';
							numtunes++;
						}
						i++;
					}
				}                               // Process other parameters
				else if(!strcmp(id,"S3M")) {
					while(string[i] != 0 && i < 999) {
						// grab a filename
						while(!isalnum(string[i]) && i < 999 && string[i]) i++;
						if(!string[i] || i == 999) break;
						spot = i;
						while(isfilechar(string[i]) && i < 999) i++;
						string[i] = 0;
						// Add to music list
						//printf("Got S3M filename: %s\n",&string[spot]);
						tune[numtunes].name = (char *)malloc(strlen(&string[spot])+2);
						if(tune[numtunes].name) {
							strcpy(tune[numtunes].name,&string[spot]);
							tune[numtunes].type = 'S';
							numtunes++;
						}
						i++;
					}
				}                               // Process other parameters
				else if(!strcmp(id,"MUSICVOLUME")) {
					while(!isdigit(string[i]) && string[i]) i++;
					if(string[i]) sscanf(&string[i],"%d",&musicvolume);
					if(musicvolume < 0) musicvolume = 0;
					if(musicvolume > 99) musicvolume = 99;
				}
				else if(!strcmp(id,"STARTSPEED")) {
					while(!isdigit(string[i]) && string[i]) i++;
					if(string[i]) sscanf(&string[i],"%d",&startspeed);
					highscoreson = FALSE;
				}
				else if(!strcmp(id,"FRAMESBETWEENSPEEDUPS")) {
					while(!isdigit(string[i]) && string[i]) i++;
					if(string[i]) sscanf(&string[i],"%d",&frames_per_speedup);
					highscoreson = FALSE;
				}
				else if(!strcmp(id,"PERCENTSPEEDUP")) {
					while(!isdigit(string[i]) && string[i]) i++;
					if(string[i]) {
						sscanf(&string[i],"%d",&j);
						speedup = 1.0 - j/100.0;
					}
					highscoreson = FALSE;
				}
				else if(!strcmp(id,"SPECIALLIFETIME")) {
					while(!isdigit(string[i]) && string[i]) i++;
					if(string[i]) sscanf(&string[i],"%d",&special_lifetime);
					highscoreson = FALSE;
				}
				else if(!strcmp(id,"MAXTIMETOSPECIAL")) {
					while(!isdigit(string[i]) && string[i]) i++;
					if(string[i]) sscanf(&string[i],"%d",&maxtime_to_special);
					highscoreson = FALSE;
				}
				else if(!strcmp(id,"TETRISSPECIAL")) {
					while(!isdigit(string[i]) && string[i]) i++;
					if(string[i]) sscanf(&string[i],"%d",&tetrisspecial);
					highscoreson = FALSE;
				}
				else if(!strcmp(id,"ANTEDOTEFREQUENCY")) {
					while(!isdigit(string[i]) && string[i]) i++;
					if(string[i]) sscanf(&string[i],"%d",&antedote_probability);
					highscoreson = FALSE;
				}
				else if(!strcmp(id,"NUMROUNDS")) {
					while(!isdigit(string[i]) && string[i]) i++;
					if(string[i]) sscanf(&string[i],"%d",&totalrounds);
				}
				else if(!strcmp(id,"GAMESPEED")) {
					while(!isdigit(string[i]) && string[i]) i++;
					if(string[i]) sscanf(&string[i],"%d",&gamespeed);
					highscoreson = FALSE;
				}
				else if(!strcmp(id,"SAMPLERATE")) {
					while(!isdigit(string[i]) && string[i]) i++;
					if(string[i]) sscanf(&string[i],"%u",&tetrissamplerate);
				}
				else if(!strcmp(id,"STRESSMODE")) {
					stressmode = TRUE;
				}
				else if(!strcmp(id,"SNAPSHOTMODE")) {
					snapshotmode = TRUE;
				}
				else {
					msg.Format("ERROR- Unknown option in config file: %s\n\r",id);
					AfxMessageBox(msg);
				}
			}
		}
		fclose(input);
	}
}
