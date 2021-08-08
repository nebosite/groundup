//
// MAIN.C
//
// Launching point for Flabbergasted
//
// Author:  Eric Jorgensen

#include <stdio.h>
#include <i86.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <dos.h>
#include <graph.h>
#include <ctype.h>
#include <string.h>
#include "util.h"
#include "math.h"
#include "\watcom\gug\lib1\gug.h"      // Load the GUG definitions etc
#include "\watcom\gug\lib1\colors.h"
#include "\watcom\gug\lib1\keydefs.h"
#include "\watcom\vat\vat.h"
#include "flabber.h"
#include "routine.h"
#include "pics\title.h"

#define PI 3.14159

char memorytest_prehunk[MEMTESTSIZE];
char *gTextPointer = (char *)0xB8000;
char musicfilename[250] = {"music.cfg"};

																			// Allocate 5 megs here to insure the
																			// demo takes up nearly the same room
																			// As the release will
#ifdef DEMOVERSION
BYTE memoryhunkachunk[DEMOMEMORYSIZE];
#endif

Palette palette[256];
//extern void far mccircle(void);
DWORD dateearly=19980101L;    // YYYYMMDD
DWORD datelate= 19980301L;

int maxx=320;
int maxy = 200;

char rblk[3][15000];
char palblk[15000];
char screendata[66000];
																// Registration/evaluation info
char gcEvData[256] = {"Zq1ff3qqtl*%1...#"
											"Unregistered Shareware Demo User\0"
											"0000 00 00\0"};
char *gcRegUser = gcEvData + 17;
char *gcRegDate = gcEvData + 50;

char gcUserName[256] = {"Unregistered User"};
int giDemoDays = -1;


RasterBlock *grbWorkSpace = NULL;
RasterBlock *grbTemp[3] = {NULL,NULL,NULL};
RasterBlock *grbPaletteBlock = NULL;

int giSaveScreen = FALSE;

int 	giNiceMouse = FALSE;
int		giMusicOn = TRUE;
int		giFXOn= TRUE;
int 	giVerbose = FALSE;
int 	giHardQuit = FALSE;
int		giStartWithMusic= FALSE;
int 	giEggMe = FALSE;
int 	giScreenSaverMode = FALSE;
int		giMouseX1;
int		giMouseY1;
int		giMouseW;
int		giMouseH;
int		giUseMouseCoords = FALSE;
int  	giMouseIsThere = 0;
int  	giMouseCursor= 0;
int   giBrushShape = brush_circle;
int 	giBrushSize = 8;
int 	giWorkingColor = 63;
BYTE 	gColorStack[10];
double   giScale[88];
int   giPalPut = FALSE;
int   giFloodFill = FALSE;
int		giDrawFrameCount = 0;
int		giWhitePalette = FALSE;
int		giMakeNoise = TRUE;
int		giSoundOn = TRUE;
double gfprealmousex=0,gfprealmousey=0;
CRoutine *gRoutineList = NULL;


MUSICNAME *gpMusicList = NULL,*gpMusicPointer = NULL, *gpMusicTail = NULL;
MOD *gpMyMod = NULL;
S3M *gpMyS3M = NULL;
MIDI *gpMyMidi = NULL;

signed char errstring[256];

FILE *gpKeyFile = NULL;
FILE *gpLogFile = NULL;
FILE *gpAutoFile = NULL;

char *memorytest_preallochunk = NULL;
char *memorytest_postallochunk = NULL;
char memorytest_posthunk[MEMTESTSIZE];

void *patchmemory;


// ------------------------- functions

int (*animfunc)(int signal) = NULL;
int (*brushfunc)(int signal) = NULL;
int (*gamefunc)(int signal) = NULL;

void setup(void);
void setcol(Palette *p,int r, int g, int b);



/**************************************************************************
	void regvalidate(char *valstr)

	DESCRIPTION: Validates the command-line registration string to confirm
							 that this code is being run from the right Windows executable.

	Format:  						-@ "Coded-string"
	Uncoded format:     FLABBERGASTED^Registered user name^Days left^checksum
	Checksum:						checksum = strlen(user_name) + totalascii + days left
	Coding:							nc = 158-oc;  // Reject nc < 32 && nc > 126

**************************************************************************/
int regvalidate(char *valstr)
{
	int i;
	char 	*flabbertoken = NULL,
				*nametoken = NULL,
				*daystoken = NULL,
				*checksumtoken = NULL,
				*nullstring={""};
	int days, checksum;
	int cs = 0;

	verbosef("Validating - %s\n",valstr);
																 // Decode the string
	for(i = 0; i < strlen(valstr); i++) {
		*(valstr + i) = 158 - *(valstr+i);
	}
	verbosef("S: %s\n",valstr);
																 // Grab tokens
	flabbertoken = strtok(valstr,"^");
	nametoken = strtok(NULL,"^");
	daystoken = strtok(NULL,"^");
	checksumtoken = strtok(NULL,"^");

	if(!flabbertoken || !nametoken || !daystoken || !checksumtoken) return 0;


																 // See if string is a flabbergasted key
	if(strcmp(flabbertoken,"FLABBERGASTED")) return 0;

	days = atoi(daystoken);
	checksum = atoi(checksumtoken);

	verbosef("D=%d, C=%d\n",days,checksum);

																 // Verify checksum
	cs = strlen(nametoken);
	verbosef("cs=%d\n",cs);
	for(i = 0; i < strlen(nametoken); i++) cs += *(nametoken+i);
	verbosef("cs=%d\n",cs);
	cs += days;
	verbosef("cs=%d\n",cs);


	if(cs != checksum) return 0;

																 // We made it!  Set the eveluation days
																 // and the username.
	giDemoDays = days;
	strcpy(gcUserName,nametoken);


	return 1;
}

/*===========================================================================
	void addsong(char *name)

	DESCRIPTION:

				NOTES:

	  REVISIONS:
				5/28/98		Eric Jorgensen		Initial Version

============================================================================*/
void addsong(char *name)
{
	VATMUSICTYPE mtype;
	MUSICNAME *mn,*mtemp;
	int zot = 1;

	mtype = ZotType(name);
	if(mtype == v_musictype_error || mtype == v_musictype_unknown) {
#ifdef DEMOVERSION
		return;
#endif
		mtype = GetMusicType(name,(char *)errstring);
		if(mtype == v_musictype_error || mtype == v_musictype_unknown) {
			verbosef("ERROR checking music type for %s\n",name);
			return;
		}
		else zot = 0;
	}
	
	mn = new MUSICNAME(name);
	if(mn) {
		mn->type = mtype;
		mn->iszot = zot;

		if(gpMusicList) {         // Normal link
			mn->next = gpMusicList;
			gpMusicList->prev = mn;
			mn->prev = gpMusicTail;
			gpMusicTail->next = mn;
			gpMusicList = mn;
		}
		else {                    // First Link, initialize list
			gpMusicList = mn;
			gpMusicTail = mn;
			mn->next = mn;
			mn->prev = mn;
		}
//					verbosef(".");
		//verbosef("-->%s\n",gpMusicList->path);
	}
	

}

/**************************************************************************
	void pretext(void)

	DESCRIPTION:  Check date and tell user about the code.

**************************************************************************/
void pretext(void)
{
	DWORD date1;
	struct dosdate_t today;
	FILE *input;
	char string[256],*spot;
	int i,left,missed=1,songcount = 0;
	time_t tt;

	_clearscreen(0);

/*	_dos_getdate(&today);
	date1 = today.year*10000L + today.month * 100L + (DWORD)today.day;


	if(date1 < dateearly || date1 > datelate) {
		printf("\nThe current date is (%d/%d/%d).\n",
						(int)today.month,(int)today.day,(int)today.year );
		printf("This beta version has expired.  Please contact\n"
					 "Purple Planet Software for the most recent version:\n"
					 "\n"
					 "       www.purpleplanet.com\n"
					 "\n"
					 "Press any key...\n");
		getch();
		exit(2);
	}  */

//	verbosef("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
																		 // set up Memory testing buffers

	memorytest_preallochunk = (char *)malloc(MEMTESTSIZE);
	if(memorytest_preallochunk) memset(memorytest_preallochunk,0,MEMTESTSIZE);
	memset(memorytest_prehunk,0,MEMTESTSIZE);
	memset(memorytest_posthunk,0,MEMTESTSIZE);

/* ---------------------------------------------------------------

This code used to draw the cool text intro screen

	for(i = 0; i < ASC_TITLE_WIDTH*ASC_TITLE_HEIGHT*2; i++)
		*(gTextPointer+i) = random(256);

	while(missed) {
		missed = 0;
		spot = gTextPointer;
		for(i = 0; i < ASC_TITLE_WIDTH*ASC_TITLE_HEIGHT*2; i++) {
			if(*spot != *(ASC_TITLE_DATA+i)) {
				missed++;
				(*spot)++;
			}
			spot++;
		}
		sound(random(1500)+1000);
		delay(1);
		nosound();

	}


	sprintf(string,"Version %s",VERSION);
	left = 40-strlen(string)/2-1;
	for(i = 0; i < strlen(string); i++) {
		spot = gTextPointer + (i + left + 19*80)*2;
		*spot = string[i];
	}

 ---------------------------------------------------------------*/



/*	fprintf(stderr,"Flabbergasted!\n"
				 "Version %s \n"
				 "Copyright (C) 1997\n\n",VERSION);
	fprintf(stderr,"Author: Eric Jorgensen (varmint@itsnet.com)\n\n");
	fprintf(stderr,"This is a pre-release beta test of a shareware product.  Please\n"
				 "do not distribute without the express permission of the author.\n\n"
				 "Beta Testing URL:  www.itsnet.com/~varmint/flabber/beta.html\n");

//	printf("\nYOWSA!  You have: %d Kbytes left!\n\n",memleft()/1000);

	fprintf(stderr,"\n\nHOW TO EXIT:  Type 'qQ' to exit Flabbergasted.");
	fprintf(stderr,"\n\nPress any key to continue...\n");
*/	   
	time(&tt);
	for(i = tt%5000; i; i--) random(5);  // randomize

																		// Get paths to all mod and s3m files
	input = fopen(musicfilename,"r");
	if(input) {
//		verbosef("\nAdding Music \n");
		while(fgets(string,256,input)) {
			spot = strchr(string,'\n');
			if(spot) *spot = 0;
			if(isalnum(string[0]) || string[0] == '\\' || string[0] == '.') {
				songcount++;
				addsong(string);
			}
		}
		fclose(input);
								// Pick a random song to start with
		for(i = random(songcount); i > 0; i--) {
			if(gpMusicPointer) {
//				printf("%s\n",gpMusicPointer->path);
				gpMusicPointer = gpMusicPointer->next;
			}
			if(!gpMusicPointer) gpMusicPointer = gpMusicList;
		}
//		getch();
/*		mn = gpMusicList;
		do {
			printf("-->%s\n",mn->path);
			mn = mn->next;
		} while(mn != gpMusicList);
		getch();*/
		if(gpMusicTail) gpMusicTail->next = gpMusicList;
	}
	memorytest_postallochunk = (char *)malloc(MEMTESTSIZE);
	if(memorytest_postallochunk) memset(memorytest_postallochunk,0,MEMTESTSIZE);

//	if(!giScreenSaverMode) getch();

}

/**************************************************************************
	int setup(int argc, char* argv[])

	DESCRIPTION:  Sets up the whole thing

	RETURNS:  Video mode

**************************************************************************/
void setup(void)
{
																/* so many variables, so little time */
//	int mx,my, mb;
//	char r,lr,err[256];
//	int flag = 1,i,j,k,t,x,y;
//	double a,b,c;
	int i;
	double f;


	initutils();                       // Initialize my utilities


	f = 1.0;
	for(i = 44; i < 88; i++){
		giScale[i] = f;
		f *= CHROMATIC_RATIO;
	}
	f = 1.0;
	for(i = 44; i > 1; i--){
		giScale[i] = f;
		f /= CHROMATIC_RATIO;
	}



																			// Set up working buffers
	grbWorkSpace = (RasterBlock *)screendata;
	for(i = 0; i < 3; i++) {
		grbTemp[i] = (RasterBlock *)rblk[i];
	}
	grbPaletteBlock = (RasterBlock *)palblk;


	setuppalette();
																			// Draw some tings and play a sound

//	palbox(10,10);


	GUGPutFGSprite(maxx/2 - flabbersprite[0]->width/2,50,(char *)flabbersprite[0]);
	dosound(22);

	giMouseCursor = cursor_circle;
	giBrushShape = brush_circle;
	GUG_Sprite_Mouse = (char *)flabbersprite[giMouseCursor];
	GUGSMShow();

}



/**************************************************************************
	void loadpatches(char *filename)

	DESCRIPTION:  Loads a bnch of patches from a music Goop file

**************************************************************************/
void loadpatches(char *filename)
{
	char errstring[256],string[1000];
	int i,j,ptotal,totalmem,usedmem;
	FILE *input;
	PATCHSAMPLE *psamp;
	BYTE patchmap[256][20];
	PATCH *patchlist[256];
	BYTE *mempointer;
	int readmem = 0;
																	// Zero out patch list
	for(i = 0; i < 256; i++) patchlist[i] = NULL;
																	// Get handle to compiled patch file
	input = fopen(filename,"rb");
	if(!input) {
		verbosef("Error opening patch input file: %s\n",filename);
		return;
	}
																	// Read in and verify ID string
	verbosef("Reading patches...\n");

	if(fread(string,1,40,input) < 40) {
		fclose(input);
		verbosef("File Read error!\n");
		return;
	}
	if(!strstr(string,"FLABBERGASTED Music Goop")) {
		fclose(input);
		verbosef("Not a Music Goop file!\n");
		return;
	}
																	// Ask how much memory we need, then
																	// attempt to allocate it.
	if(fread(&usedmem,1,sizeof(int),input) < sizeof(int)) {
		fclose(input);
		verbosef("File Read error!\n");
		return;
	}

	patchmemory = flabmalloc(usedmem);
	if(!patchmemory) {
		fclose(input);
		verbosef("Out of memory!\n");
		return;
	}
																	// Read the file in by chunks until
																	// we have it all.
	mempointer = (BYTE *)patchmemory;
	while(readmem < usedmem) {
		verbosef(".");
		if(fread(mempointer+readmem,1,50000,input) < 50000) break;
		readmem += 50000;
	}


	verbosef("  Patches loaded into raw memory.  Processing...\n");

																	// Load the patchmap.  The number of
																	// patched in the file is contained in
																	// the very last variable of the patchmap.
	memcpy(patchmap,patchmemory,5120);
	ptotal = patchmap[255][19];
	verbosef("Ptotal = %d\n",ptotal);

																	// Walk through the memory and set up
																	// patch pointers.
	mempointer = (BYTE *)patchmemory + 5120;
	for(i = 0; i < ptotal; i++) {
																	// Point to patch struct
		patchlist[i] = (PATCH *)mempointer;
		mempointer += sizeof(PATCH);
		verbosef("Processing Instrument %s.\n",patchlist[i]->name);

																	// Point to first sample
		patchlist[i]->samplelist = (PATCHSAMPLE *)mempointer;
		mempointer += sizeof(PATCHSAMPLE);

		psamp = patchlist[i]->samplelist;
		psamp->data = (SAMPLE *)mempointer;
		mempointer += psamp->size;
																	// process any additional samples
		while(psamp->next) {
			psamp->next = (PATCHSAMPLE *)mempointer;
			mempointer += sizeof(PATCHSAMPLE);
			psamp = psamp->next;
			psamp->data = (SAMPLE *)mempointer;
			mempointer += psamp->size;
		}
																		// Tell VAT about the new patch
		for(j = 0; j < 20; j++) {
			if(patchmap[i][j] < 128) {
				MidiSetInstrumentPatch(patchmap[i][j],patchlist[i]);
			}
			else if(patchmap[i][j] < 255) {
				MidiSetPercussionPatch(patchmap[i][j]-128,patchlist[i]);
			}

		}
	}

	fclose(input);


}

/**************************************************************************
	void usage(void)

	DESCRIPTION:

**************************************************************************/
void usage(void)
{
	printf(
		"USAGE:  flabber (options)\n"
		"\n"
		"OPTIONS:\n"
		"  -K (filename)  Log keystrokes (and mouse motions) to (filename)\n"
		"  -L (filename)  Log general information to (filename)\n"
		"  -A (filename)  Automate using keystroke file (filename)\n"
		"  -M (filename)  Specify music config file (default = music.cfg)\n"
		"  -U             Start with music on.\n"
		"  -H             Hard quit: Use Qq instead of just q to quit.\n"
		"  -N             Nice Mouse.  (Disables reverse mouse key)\n"
		"  -S             Screensave mode.\n"
		"  -V             Verbose mode.\n"
		"  -O #           Sound option (0:none 1:music 2:FX 3:Music+FX)\n"
		"  -4             Set mixing rate to 44 Khz (better music sound)\n"
		"  -1             Set mixing rate to 11 Khz (helps slow machines)\n"
		"  -P             Save preview screens mode\n"
		"  -?,-X,-H       Show this help screen\n"
		"\n");
	exit(0);
}

/**************************************************************************
	main()

	DESCRIPTION:

**************************************************************************/
void main(int argc, char *argv[])
{
	int   status,button,n;
	int argnum = 1;
	int samplerate = 22000;
	LONG notehandle[256],i,j;
//void testfft(void);


//testfft();

//return;

	printf("FLABBERGASTED!  Version %s\n",VERSION);
	while(argnum < argc ) {
		switch(toupper(*(argv[argnum]+1))) {
			case 'K':
				argnum++;
				if(argnum >= argc) usage();
				gpKeyFile = fopen(argv[argnum],"wb");
				if(!gpKeyFile) {
					verbosef("ERROR opening file %s for writing.\n",argv[argnum]);
					exit(1);
				}
				break;
			case 'L':
				argnum++;
				if(argnum >= argc) usage();
				gpLogFile = fopen(argv[argnum],"w");
				if(!gpLogFile) {
					verbosef("ERROR opening file %s for writing.\n",argv[argnum]);
					exit(1);
				}
				break;
			case 'A':
				argnum++;
				if(argnum >= argc) usage();
				gpAutoFile = fopen(argv[argnum],"rb");
				if(!gpAutoFile) {
					verbosef("ERROR opening file %s for writing.\n",argv[argnum]);
					exit(1);
				}
				break;
			case 'M':
				argnum++;
				if(argnum >= argc) usage();
				strcpy(musicfilename,argv[argnum]);
				break;
			case '@':
				argnum++;
				if(argnum >= argc) exit(100);
				if(regvalidate(argv[argnum])) verbosef("Success!!\n");
				else verbosef("Validation failed\n");
				break;
			case '4':
				samplerate = 44000;
				break;
			case '1':
				samplerate = 11000;
				break;
			case 'H':
				giHardQuit = TRUE;
				break;
			case 'U':
				giStartWithMusic = TRUE;
				break;
			case 'V':													  
				giVerbose = TRUE;
				break;
			case 'S':
				giScreenSaverMode = 1;
				break;
			case 'N':
				giNiceMouse = TRUE;
				break;
			case 'P':
				giSaveScreen = TRUE;
				break;
			case 'O':
				argnum++;
				if(argnum >= argc) usage();
				n = atoi(argv[argnum]);
				if(!n) giSoundOn = FALSE;
				giMusicOn = n&0x01;
				giFXOn = n&0x02;
				break;
			default:
				usage();
				break;
		}
		argnum++;
	}

	if(giDemoDays < 0) exit(101);      // Gentle protection from pirating.

	pretext();

	loadsounds();
	loadsprites();


	if(giSoundOn) giSoundOn = SBSetUp(samplerate,135);
	if(giSoundOn) {
		GoVarmint();
		MidiSetting(v_volume,25);
		ModSetting(v_volume,40);
		S3MSetting(v_volume,40);
	}

	loadpatches("patglob.pts");
/*	for(i = 0; i < 127; i++) {
		printf("%d]%s ",i,MidiGetInstrumentPatch(i)->name);
		for(j = 1; j < 100; j+=12) {
			printf(".");
			notehandle[j] = PlayNote(j,MidiGetInstrumentPatch(i));
			MilliDelay(50);
		}
		MilliDelay(200);
		for(j = 1; j < 100; j+=12) {
			NoteCommand(notehandle[j],v_stop);
			MilliDelay(50);
		}
	}
	getch();  */

//	getch();
																				// Set up a buffer in VAT so
																				// we can do FFT stuff
	SetLongBuffer((BYTE *)bigbuffer,BIGBUFFERSIZE);
	if(giVerbose) {
		verbosef("Press any key...\n");
		getch();
	}
																				// Start GUG
	if (GUGInitialize()) {
		GUGMouseReset((int *)&status,(unsigned int *)&button);
		giMouseIsThere = status;

		GUGClearDisplay();

		setup();
		if(giVerbose) {
			verbosef("Press any key...\n");
			getch();
		}

		flabber();

		GUGMouseReset((int *)&status,(unsigned int *)&button);
		GUGEnd();
	}
	else	{
		verbosef("GUG was not able to initialize.\n");
		if(!giScreenSaverMode) getch();
	}


																				// Clean up
	if(giSoundOn) {
		DropDeadVarmint();
		SBCleanUp();
	}
//	freesounds();
	fcloseall();
}
