/**************************************************************************
	VATDEMO.C

	Written by:  Eric Jorgensen (Aug, 1995)

	This code was written using Turbo C.  It is intended to demonstrate the
	use of Varmint's Audio Tools and to provide a example code for programers
	who wish to use VAT.

													This code is FREEWARE

	You are free to distribute without any restrictions as long as you
	charge no fee.


**************************************************************************/


#include <stdio.h>
#include <conio.h>
#include <dos.h>
#include <math.h>
#include <time.h>
#include <ctype.h>
#include <string.h>
#include <STDARG.H>
#include <stdlib.h>
#include <io.h>
#include <alloc.h>
#include "vat.h"


#define getbit(x,y) ((x>>y) & 0x01)
#define setbit(x,y) x = x & (0x01<<y)
#define togbit(x,y) x = x ^ (0x01<<y)

																	// function prototypes
void fmdemo(void);
void mididemo(void);
void sb_intro(void);
void dspdemo(void);
void moddemo(void);
void s3mdemo(void);
void vsyncdemo(void);
void introtext(void);
void diagnostics(void);
void debugoptions(void);
void vcprintf(CHAR *string,...);
void usage(char *arg0);


																 // external functions

//-------------------------- external data -----------------------
																				// These variables are necessary to
																				// VAT, but are not normally needed
																				// outside of the library itself.  
																				// I've included them in the demo
																				// to help illustrate what is
																				// possible with VAT.

extern WORD         dma_bufferlen;
extern WORD         sample_rate;
extern WORD         io_addr;
extern WORD         intnr;
extern WORD         dma_ch;
extern WORD         card_id;
extern WORD         fm_addr;
extern WORD         dsp_vers;
extern WORD         vsync_toolong;
extern SHORT        sounds_in_queue;
extern BYTE         defaultpatchmap[16];
extern CHAR         vatdebugstring[];
extern VOICE        midi_voice[];
extern WORD					midi_mpuport;
extern LONG     		debugnum;
extern SHORT				mod_currenttick;
extern WORD 				mod_currentbyte;
extern SHORT				s3m_currenttick;
extern SHORT				mod_tablepos;
extern BYTE VFAR		*mod_pstop,*mod_pattern;
extern SHORT				s3m_currenttick;
extern SHORT				s3m_tablepos;
extern BYTE VFAR		*s3m_pstop,*s3m_pattern;
extern SHORT        s3m_order;
extern SHORT				s3m_divbytes;
extern BYTE         mod_channelselect[];
extern BYTE         s3m_channelselect[];
extern SHORT 				s3m_on,mod_on;



//-------------------------- DATA and Globals --------------------

																	// Instrument data
BYTE    inst[9][11] =
	{
		{ 0x03,0x01,0x00,0x00,0xF3,0xE4,0x64,0x35,0x00,0x01,0x00},  // Harpsichord
		{ 0x00,0x00,0x00,0x00,0x80,0x80,0x00,0x00,0x06,0x03,0x00},  // intro voice
		{ 0x02,0x06,0x94,0x0A,0x80,0x80,0x00,0x00,0x00,0x00,0x00},  // intro voice
		{ 0x00,0x04,0x00,0x00,0x80,0x80,0x00,0x00,0x00,0x00,0x00},
		{ 0x01,0x01,0x40,0x40,0x80,0x80,0x00,0x00,0x01,0x00,0x00},
		{ 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x03,0x01},
		{ 0xA5,0xB1,0xD2,0x80,0x81,0xF1,0x03,0x05,0x00,0x00,0x02},
		{ 0x72,0x62,0x1C,0x05,0x51,0x52,0x03,0x13,0x00,0x00,0x0E},
		{ 0x11,0x01,0x8A,0x40,0xF1,0xF1,0x11,0xB3,0x00,0x00,0x06}};

BYTE vints[8] = {1,2,1,2,1,2,1,2}; // voice defs for introduction
																	// Start/end frequencies for intro
WORD startfreq[8] = {58,117,165,233,466,660,932,1864};
WORD endfreq[8] =   {1760,880,660,440,220,165,110,55};

CHAR *regname[11] = {             // FM register name list
	"Amp mod/ vib/ eg type/ keyscale/ multiple 1",
	"Amp mod/ vib/ eg type/ keyscale/ multiple 2",
	"Key scale level / oper out level 1",
	"Key scale level / oper out level 2",
	"attack/decay rate 1",
	"attack/decay rate 2",
	"sustain level / release rate 1",
	"sustain level / release rate 2",
	"Feedback / Algorythm (oper 1&2)",
	"Wave Form  Select (oper 1)",
	"Wave Form  Select (oper 1)"
	};
char *s3meffects[] = {                    //effects of the S3m Type
                                       //unused effects are not used by vat.
     "---------",                      //0
     "Set Speed",                      //A
		 "Jump to Order",                  //B
     "Break Pattern",                  //C
     "Volume Slide",                   //D
     "Slide Pitch DN",                 //E
     "Slide Pitch UP",                 //F
     "Tone Portamento",                //G
     "Vibrato",                        //H
     "Tremor",                         //I
     "Arpeggio",                       //J
     "Vibrato + Vol",                  //K
     "Tone Port + Vol",                //L
     "Unused",                         //M
     "Unused",                         //N
     "Sample Offset",                  //O
     "Unused",                         //P
     "Retrig + Vol",                   //Q
     "Tremolo",                        //R
     "Special",                        //S
     "Tempo",                          //T
     "Fine Vibrato",                   //U
     "Global Vol",                     //V
     "Unused",                         //W
     "Unused",                         //X
     "Unused",                         //Y
     "Unused"};                        //Z

CHAR *effect_primary[] = {        // MOD command names
	"Arpeggio",
	"PortaM up",
	"PortaM down",
	"Porta NOTE",
	"Vibrato",
	"porta+vol",
	"Vib+vol",
	"Tremolo",
	"UNUSED",
	"Set offset",
	"Vol slide",
	"Postn Jmp",
	"Set Volume",
	"Pat Break",
	"special14",
	"Set Speed"};
CHAR *effect_secondary[] = {
	"Filter T/F",
	"Finesld up",
	"Finesld dn",
	"Gliss T/F",
	"Vibr WF",
	"Finetune WF",
	"Loop Pattrn",
	"Tremolo WF",
	"UNUSED",
	"Retrigger",
	"FineVolS up",
	"FineVolS Dn",
	"Cut Sample",
	"Delay Sampl",
	"Delay Pttrn",
	"Invert Loop"};
																					// Patchmap to work on really
																					// lame MIDI ouput devices.
BYTE mypatchmap[16] = {0,0,0,0,0,1,1,1,1,1,2,2,2,2,2,2};
																					// Initial FM patchmap to set
																					// tracks 1 and 2 to harpsichord
BYTE myfmpatchmap[32] = {0,6,6,0,0,0,0,0,0,0,0,0,0,0,0,0,
													 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
CHAR *instname[16] = {"ACGPIANO","ACPiano","ELGPIANO","HONKTONK","ELPIANO1",
				"ElPiano2","HARPSCHD","CLAVICHD","CELESTA","GLOCK","MUSICBOX",
				"VIBES","MARIMBA","XYLOPHON","TUBEBELL","Dulcimer"};


CHAR hexchar[16] = {"0123456789ABCDEF"};  //  hexidecimal character list

CHAR errstring[256];
WAVE *sound1,*sound2,*aha,*rumble;
FILE *diagoutput= NULL;
DWORD memleft;
MIDI VFAR *bachmidi  = NULL;
MOD VFAR *mymod = NULL;
S3M VFAR *mys3m = NULL;
CHAR midfilename[255] = {"bach.mid"};
CHAR modfilename[255] = {"cutdry.mod"};
CHAR s3mfilename[255] = {"grimdead.s3m"};
static CHANNEL      VFAR *chan;
int flushearly = 0,mysamplerate = 11000;

// ECODE
void midiplayer();
void initmid();
void initmod();
void modplayer(void);

/**************************************************************************
	void main()

	DESCRIPTION:   Handles the main menu and sets things up

**************************************************************************/
void main(SHORT argc,CHAR *argv[])
{
	SHORT i= 0,k;
	CHAR r = 0,twirl[6]  = "|/-\\";
	LONG mycore,j;


	for(i = 1; i < argc ; i++) {      //  convert arguments to lower case
		for(k = 0; k < strlen(argv[i]); k++) {
			*(argv[i]+k) = tolower(*(argv[i]+k));
		}
	}

	i = 1;                            // Read the rest of the arguments
	while(i < argc) {
		if(!strcmp(argv[i],"-debug")) flushearly = 1;
		else if(!strcmp(argv[i],"-mod")) {
			i++;
			strcpy(modfilename,argv[i]);
		}
		else if(!strcmp(argv[i],"-s3m")) {
			i++;
			strcpy(s3mfilename,argv[i]);
		}
		else if(!strcmp(argv[i],"-mid")) {
			i++;
			strcpy(midfilename,argv[i]);
		}
		else if(!strcmp(argv[i],"-rate")) {
			i++;
			mysamplerate = atoi(argv[i]);
		}
		else if(!strcmp(argv[i],"-x") || !strcmp(argv[i],"-h") || !strcmp(argv[i],"-?")) {
			usage(argv[0]);
			exit(1);
		}
		else {
			printf("ERROR:  Unrecognized option: %s\n\n",argv[i]);
			usage(argv[0]);
			exit(1);
		}
    i++;
  }


	mycore = farcoreleft();


	_setcursortype(_NOCURSOR);             // eliminates flashing text

																				 // Load up our sound effects
	sound1 = LoadWave("doink.wav",errstring);
	if(!sound1) printf("LoadWave err: %s\n",errstring);

	sound2 = LoadWave("wooeep.wav",errstring);
	if(!sound2) printf("LoadWave err: %s\n",errstring);

	aha = LoadWave("aha.wav",errstring);
	if(!aha) printf("LoadWave err: %s\n",errstring);

	rumble = LoadWave("rumble.wav",errstring);
	if(!aha) printf("LoadWave err: %s\n",errstring);

																							// load a midi file

	bachmidi = LoadMidi(midfilename,(CHAR *)errstring);
	if(!bachmidi) {
		printf("LoadMidi err: %s\n",errstring);
	}
																				// Load MOD file
	mymod = LoadMod(modfilename,(CHAR *)errstring);
	if(!mymod) {
		printf("LoadMod err: %s\n",errstring);
	}
	else mymod->repeatmusic = -1;


																				// Load S3M file
	mys3m = LoadS3M(s3mfilename,(CHAR *)errstring);
	if(!mys3m) {
		printf("LoadS3M err: %s\n",errstring);
	}
	else mys3m->repeatmusic = -1;
																			// Grab a keystroke if  there
																				// were any errors.
	if(!sound1 || !sound2 || !aha || !rumble || !bachmidi ||!mymod || !mys3m) {
		printf("Press any key\n");
		getch();
	}

	//introtext();
	//diagnostics();

																			 // THis is a little snippet of code
																			 // Thad adds useful info to the
																			 // Survey.txt file.
/*	if(diagoutput) {
		if(!sound1 || !sound2 || !aha) {
			fprintf(diagoutput,"Error loading sounds\n");
		}
		fflush(diagoutput);
		fclose(diagoutput);
		diagoutput = NULL;
	}
*/
	memleft = farcoreleft();              // Keep a tab on memory for debugging
																				// purposes.
	if(SBSetUp()) {

		SetSampleRate(mysamplerate);


		if(flushearly) {
																				// for deugging. If any -d argument is
																				// Passed to main,  debugging info
																				// Will be dumped to survey.txt
			diagoutput = fopen("survey.txt","a");
			if(diagoutput) {
				fprintf(diagoutput,"%s",vatdebugstring);
				fflush(diagoutput);
				fclose(diagoutput);
			}
		}


		TimeVSync();                        // Check the length of the vertical
																				// Retrace so VarmintVSync will
																				// Work Properly.

		GoVarmint();                            // Install  Varmint's tools

		sb_intro();                             // Get someone's attention

		while(kbhit()) getch();
		while(r != 'Q') {                       // Main input loop

			clrscr();                             // CLear screen and draw menu

			textcolor(WHITE);
			gotoxy(20,4);
			vcprintf("Demonstration:  Varmint's Audio Tools (%s)\n\n",VAT_VERSION);
			textcolor(YELLOW);
			gotoxy(35,6);
			vcprintf("1) FM voice");
			gotoxy(35,7);
			vcprintf("2) MIDI");
			gotoxy(35,8);
			vcprintf("3) Sounds");
			gotoxy(35,9);
			vcprintf("4) MOD");
			gotoxy(35,10);
			vcprintf("5) S3M");
			gotoxy(35,11);
			vcprintf("6) VSYNC");
			gotoxy(35,12);
			vcprintf("7) DEBUGGING");
			gotoxy(35,13);
			vcprintf("8) INTRO");
			gotoxy(35,17);
			vcprintf("Q) quit");

			textcolor(LIGHTMAGENTA);
			gotoxy(20,20);
			vcprintf("Authors: Eric Jorgensen and Bryan Wilkins");
			gotoxy(27,21);
			vcprintf("VAT is a Ground Up product");
			gotoxy(17,23);
			vcprintf("(http://www.rt66.com/smeagol/html/groundup.html)");

			while(!kbhit()) {                     // Draw a twirling thing while
																						// we wait for a keypress.
				textcolor(LIGHTRED);
				gotoxy(40,15);
				vcprintf("%c",twirl[++i%4]);
				MilliDelay(50);
			}
			r = toupper(getch());                 // grab some input

			if(r == '1') fmdemo();                // Do something with it
			else if(r == '2') mididemo();
			else if(r == '3') dspdemo();
			else if(r == '4') moddemo();
			else if(r == '5') s3mdemo();
			else if(r == '6') vsyncdemo();
			else if(r == '7') debugoptions();
			else if(r == '8') sb_intro();
		}
		DropDeadVarmint();                     // Release Varmint's interrupt
		SBCleanUp();                           // Clean house before we go.
		clrscr();                               // Clear the screen
	}
	else {
		printf("SB_Setup returned this error: %s \n",errname[sberr]);
	}

	if(sound1) 		FreeWave(sound1);              // Free up used memory
	if(sound2) 		FreeWave(sound2);
	if(aha) 			FreeWave(aha);
	if(rumble) 		FreeWave(rumble);
	if(bachmidi) 	FreeMidi(bachmidi);
	if(mymod) 		FreeMod(mymod);
	if(mys3m) 		FreeS3M(mys3m);

																					 // Dump debug info to survey.txt
	diagoutput = fopen("survey.txt","a");
	if(diagoutput) {
		fprintf(diagoutput,"End Core left: %lu\n",farcoreleft());
		fprintf(diagoutput,"End Core delta: %lu\n",mycore-farcoreleft());
		fprintf(diagoutput,"%s",vatdebugstring);
		fflush(diagoutput);
		fclose(diagoutput);
	}

	gotoxy(1,24);
	textcolor(LIGHTGRAY);
	_setcursortype(_NORMALCURSOR);           // Brings cursor back
}

/**************************************************************************
	void usage(char *arg0)

  DESCRIPTION: Prints the function usage page

**************************************************************************/
void usage(char *arg0)
{
	printf("USAGE:\n");
	printf("     %s [options]\n\n",arg0);

	printf("Options:\n\n");

	printf("-debug            Flush debug output early (in case of crashes).\n");
	printf("-mod [filename]   Specify a mod file to load.\n");
	printf("-s3m [filename]   Specify a s3m file to load.\n");
	printf("-mid [filename]   Specify a midi file to load.\n");
	printf("-rate [number]    Specify sample rate in Hertz.\n");
	printf("-x, -h, -?        Get command line help.\n");
}

/**************************************************************************
	void vsyncdemo(void)

	DESCRIPTION: The demonstrates the use of VarmintVSync() for animation

**************************************************************************/
void vsyncdemo(void)
{
	SHORT x=5;
	CHAR *drawme = {"HONIG"};
	CHAR r=0;

	bytes_per_synccheck = 8;

	clrscr();

																		// Display intro text.
	gotoxy(2,16);
	textcolor(CYAN);
	vcprintf("VAT's mixing kernel can interfere with ordinary functions that\r\n");
	vcprintf("monitor the vertical retrace bit, causing `jerky' animation.\r\n");
	vcprintf("With sync checking off, the animation above will jerk badly\r\n");
	vcprintf("when you play sounds.  (This does not work well when the CPU\r\n");
	vcprintf("overhead goes over 50%)\r\n\n");
	textcolor(LIGHTGRAY);
	vcprintf("Press 1,2, or 3 to play sounds.\r\n");
	vcprintf("Press <space> to toggle sync checking, 'Q' to quit");

	gotoxy(60,23);                    // Display status of sync_on
	textcolor(YELLOW);
	if(sync_on) vcprintf("SYNC ON  ");
	else vcprintf("SYNC OFF ");

	while(toupper(r) != 'Q') {        // Input/animation loop
		if(kbhit()) {                   // Key stroke waiting?
			r = getch();
			if(r == ' ') {                // toggle sync checking
				sync_on ^= TRUE;
				gotoxy(60,23);
				if(sync_on) vcprintf("SYNC ON  ");
				else vcprintf("SYNC OFF ");
			}                             // Play sounds
			else if(r == '1') PlaySound(sound1,v_plain);
			else if(r == '2') PlaySound(sound2,v_plain);
			else if(r == '3') PlaySound(aha,v_plain);
		}

																		// Animate a little bit of text
		gotoxy(x,4);
		vcprintf("     ");

		x++;
		if(x>74) x= 1;

		gotoxy(x,4);
		vcprintf("%s",drawme);

		VarmintVSync();                 // Wait for a retrace to finish

	}
}


/**************************************************************************
	s3mdemo(void)

	DESCRIPTION: Demo for playing s3m files

**************************************************************************/
void s3mdemo(void)
{
	SHORT i,playme = 0;
	CHAR r=0;
	DWORD count=0,total=0;
	SHORT mychan = 0;
	double oh;
	static WAVE iwave;

	iwave.id= -10000000L;                 // Fill dummy wave struct
	iwave.data = NULL;
	iwave.chunk_size = 0;
	iwave.sample_size = 0;
	iwave.next = NULL;
	iwave.head = &iwave;

	clrscr();                             // Clear the screen

	chan = S3MChannels();
	s3m_data = mys3m;

	DSP_overhead = 1;                     // Turn on overhead checking

	textcolor(WHITE);
	gotoxy(4,1);
	vcprintf("S3M demo menu");                 // Draw the menu
	textcolor(CYAN);
	gotoxy(41,1);
	vcprintf("1 - Start");
	gotoxy(41,2);
	vcprintf("2 - Stop");
	gotoxy(41,3);
	vcprintf("3 - Pause");
	gotoxy(61,1);
	vcprintf("4 - Resume");
	gotoxy(61,2);
	vcprintf("5 - Rewind");
	gotoxy(4,3);
	vcprintf("V,v   - Change volume");
	gotoxy(4,4);
	vcprintf("T,t   - Change tempo");
	gotoxy(4,5);
	vcprintf("<Spc> - Play Current sample");
	gotoxy(4,6);
	vcprintf("S     - Select sample");
	gotoxy(61,3);
	vcprintf("Q - Quit");

	textcolor(LIGHTMAGENTA);
	gotoxy(2,8);
	vcprintf("S3M Title: %s  (From file: %s)",mys3m->title,s3mfilename);

	textcolor(LIGHTGRAY);

	gotoxy(2,10);                                    // Running stats labels
	vcprintf("Pos left:  ");
	gotoxy(2,11);
	vcprintf("Pos spot:  ");
	gotoxy(2,13);
	vcprintf("CPU Overhead: ");

	gotoxy(29,3);                                     // SHow current volume
	vcprintf("(%d)  ",s3m_volume);
	gotoxy(29,4);                                     // Show the tempo
	vcprintf("(%d)  ",s3m_bytespertick);
	gotoxy(29,6);                                    // Show current sample
	vcprintf("%d] (%s)          ",playme+1,mys3m->sample_name[playme]);


	while(toupper(r) != 'Q') {                        // Input Loop
		if(kbhit()) {                                   // Keyboard have input?
			r = getch();                                  // Grab the key
			if(r == 'v') {                                // Volume louder
				s3m_volume--;
				if(s3m_volume < 0) s3m_volume = 0;
				textcolor(LIGHTGRAY);
				gotoxy(29,3);                               // SHow current volume
				vcprintf("(%d)  ",s3m_volume);
			}
			else if(r == 'V') {                           // Volume softer
				s3m_volume++;
				if(s3m_volume > 99) s3m_volume = 99;
				textcolor(LIGHTGRAY);
				gotoxy(29,3);                               // SHow current volume
				vcprintf("(%d)  ",s3m_volume);
			}
			else if(r == 'T') {                           // Tempo faster
				s3m_bytespertick-=10;
				if(s3m_bytespertick < dma_bufferlen) s3m_bytespertick = dma_bufferlen;
				textcolor(LIGHTGRAY);
				gotoxy(29,4);                               // Show the tempo
				vcprintf("(%d)  ",s3m_bytespertick);
			}
			else if(r == 't') {                           // Tempo slower
				s3m_bytespertick+=10;
				if(s3m_bytespertick > 10000) s3m_bytespertick = 10000;
				textcolor(LIGHTGRAY);
				gotoxy(29,4);                               // Show the tempo
				vcprintf("(%d)  ",s3m_bytespertick);
			}
			else if(r == '1') S3MCommand(v_play);
			else if(r == '2') S3MCommand(v_stop);
			else if(r == '3') S3MCommand(v_pause);
			else if(r == '4') S3MCommand(v_resume);
			else if(r == '5') S3MCommand(v_rewind);
			else if(r == 'i') {                           // change channel by -1
				mychan--;
				if(mychan< 0) mychan = s3m_data->channelnum;
			}
			else if(r == 'k') {                           // change channel by 1
				mychan++;
				if(mychan>=s3m_data->channelnum) mychan = 0;
			}
			else if(toupper(r) == 'O') s3m_channelselect[mychan] ^= 1;
			else if(toupper(r) == 'S') {                  // Cycle through samples
				playme++;
				while(!mys3m->sdata[playme]) {
					playme++;
					if(playme>99) playme = 0;
				}
				textcolor(LIGHTGRAY);
				gotoxy(29,6);                              // Show current sample
				vcprintf("%d] %s {%lu}                                              ",
									playme+1,mys3m->sample_name[playme],mys3m->slength[playme]);
			}                                             // Play current sample
			else if(r == ' ') {
				iwave.data = mys3m->sdata[playme];
				iwave.chunk_size = mys3m->slength[playme];
				PlaySound(&iwave,v_plain);
			}
		}

		MilliDelay(10);                      // Wait a little bit to make the
																				 // DSP overhead average more
																				 // meaningful.

		for(i = 0; i < mys3m->channelnum; i++) {
			textcolor(WHITE);
			gotoxy(28,9+i);
			if(mychan != i) vcprintf(" ");
			else vcprintf(">");

			textcolor(LIGHTGRAY);
			gotoxy(30,9+i);
			vcprintf("%d] ",i+1);

			textcolor(YELLOW);
			if(!chan[i].volume || *chan[i].pos > chan[i].end) textcolor(BROWN);
			if(!s3m_on) textcolor(BROWN);
			if(!s3m_channelselect[i]) textcolor(BLUE);

			gotoxy(33,9+i);                   // Print sample number
			if(*chan[i].pos <= chan[i].end) {
				vcprintf("%d",(SHORT)chan[i].sample_number+1);
			}
			else vcprintf("   ");

			gotoxy(36,9+i);                   // Show current effect
			if(*chan[i].pos <= chan[i].end) {
				vcprintf("%s       ",s3meffects[chan[i].effect]);
			}
			else vcprintf("                  ");

			gotoxy(56,9+i);                   // Draw tuning period and volume
			vcprintf("%d  ",chan[i].period);

			gotoxy(65,9+i);
			vcprintf("%d  ",chan[i].volume);
			gotoxy(70,9+i);
			vcprintf("%d  ",chan[i].pinc);
		}
																						// Show where we are in the mod
		textcolor(WHITE);
		gotoxy(12,10);
		vcprintf("%d ",mys3m->orders - s3m_order);
		gotoxy(12,11);
		vcprintf("%ld ",(long)(s3m_pstop-s3m_pattern)/s3m_divbytes);

																						// Show the CPU overhead
		count++;
		total+=DSP_overhead;
		if(count == 10) {
			oh = PercentOverhead((WORD)(total/count))/10.0;
			gotoxy(16,13);
			vcprintf("%.2lf%% ",oh);
			total = 0;
			count = 0;
		}
	}

}
/**************************************************************************
	moddemo(void)

	DESCRIPTION: Demo for playing MOD files

**************************************************************************/
void moddemo(void)
{
	SHORT i,playme = 0;
	CHAR r=0;
	DWORD count=0,total=0;
	double oh;
	static WAVE iwave;

	iwave.id= -10000000L;                 // Fill dummy wave struct
	iwave.data = NULL;
	iwave.chunk_size = 0;
	iwave.sample_size = 0;
	iwave.next = NULL;
	iwave.head = &iwave;

	clrscr();                             // Clear the screen

	mod_data = mymod;
	chan = ModChannels();


	DSP_overhead = 1;                     // Turn on overhead checking

	textcolor(WHITE);
	gotoxy(4,1);
	vcprintf("MOD demo menu");                 // Draw the menu
	textcolor(CYAN);
	gotoxy(4,3);
	vcprintf("1       - Start music");
	gotoxy(4,4);
	vcprintf("2       - Stop music");
	gotoxy(4,5);
	vcprintf("3       - Pause music");
	gotoxy(4,6);
	vcprintf("4       - Resume music");
	gotoxy(4,7);
	vcprintf("5       - Rewind music");
	gotoxy(4,8);
	vcprintf("V,v     - Change music volume");
	gotoxy(4,9);
	vcprintf("T,t     - Change music tempo");
	gotoxy(4,10);
	vcprintf("S       - Select sample");
	gotoxy(4,11);
	vcprintf("<Space> - Play Current sample");
	gotoxy(4,13);
	vcprintf("Q       - Quit");

	textcolor(LIGHTMAGENTA);
	gotoxy(2,16);
	vcprintf("MOD Title: %s ",mymod->title);

	for(i = 0; i < 4; i++) {
			gotoxy(2,18+i);                               // Print Channel labels
			vcprintf("CHANNEL%d:",i+1);
	}

	textcolor(LIGHTGRAY);

  gotoxy(40,14);                                    // Running stats labels
	vcprintf("Positions left:  ");
  gotoxy(40,15);
	vcprintf("Position spot:  ");
	gotoxy(4,23);
	vcprintf("CPU Overhead: ");

	gotoxy(35,8);                                     // SHow current volume
	vcprintf("VOLUME: %d  ",mod_volume);
	gotoxy(35,9);                                     // Show the tempo
	vcprintf("TEMPO: %d  ",mod_bytespertick);
	gotoxy(35,10);                                    // Show current sample
	vcprintf("%d] (%s)          ",playme+1,mymod->sample_name[playme]);

	while(toupper(r) != 'Q') {                        // Input Loop
		if(kbhit()) {                                   // Keyboard have input?
			r = getch();                                  // Grab the key
			if(r == 'v') {                                // Volume louder
				mod_volume--;
				if(mod_volume < 0) mod_volume = 0;
				textcolor(LIGHTGRAY);
				gotoxy(35,8);                               // SHow current volume
				vcprintf("VOLUME: %d  ",mod_volume);
			}
			else if(r == 'V') {                           // Volume softer
				mod_volume++;
				if(mod_volume > 99) mod_volume = 99;
				textcolor(LIGHTGRAY);
				gotoxy(35,8);                               // SHow current volume
				vcprintf("VOLUME: %d  ",mod_volume);
			}
			else if(r == 'T') {                           // Tempo faster
				mod_bytespertick-=10;
				if(mod_bytespertick < dma_bufferlen) mod_bytespertick = dma_bufferlen;
				textcolor(LIGHTGRAY);
				gotoxy(35,9);                               // Show the tempo
				vcprintf("TEMPO: %d  ",mod_bytespertick);
			}
			else if(r == 't') {                           // Tempo slower
				mod_bytespertick+=10;
				if(mod_bytespertick > 10000) mod_bytespertick = 10000;
				textcolor(LIGHTGRAY);
				gotoxy(35,9);                               // Show the tempo
				vcprintf("TEMPO: %d  ",mod_bytespertick);
			}
			else if(r == '1') ModCommand(v_play);
			else if(r == '2') ModCommand(v_stop);
			else if(r == '3') ModCommand(v_pause);
			else if(r == '4') ModCommand(v_resume);
			else if(r == '5') ModCommand(v_rewind);
			else if(r == '!') mod_channelselect[0] ^= 0x01;
			else if(r == '@') mod_channelselect[1] ^= 0x01;
			else if(r == '#') mod_channelselect[2] ^= 0x01;
			else if(r == '$') mod_channelselect[3] ^= 0x01;

			else if(toupper(r) == 'S') {                  // Cycle through samples
				playme++;
				while(!mymod->sdata[playme]) {
					playme++;
					if(playme>31) playme = 0;
				}
				textcolor(LIGHTGRAY);
				gotoxy(35,10);                              // Show current sample
				vcprintf("                                      ",playme+1,mymod->sample_name[playme]);
				gotoxy(35,10);                              // Show current sample
				vcprintf("%d] (%s)   ",playme+1,mymod->sample_name[playme]);
			}                                             // Play current sample
			else if(r == ' ') {
				iwave.data = mymod->sdata[playme];
				iwave.chunk_size = mymod->slength[playme];
				PlaySound(&iwave,v_plain);
			}
		}


		for(i = 0; i < 4; i++) {
			textcolor(YELLOW);


			gotoxy(16,18+i);                   // Print sample number
			if(*chan[i].pos <= chan[i].end) {
				vcprintf("%d",(SHORT)chan[i].sample_number);
			}
			else vcprintf("   ");

			textcolor(YELLOW);

			gotoxy(22,18+i);
			if(!chan[i].volume || *chan[i].pos > chan[i].end || !mod_on)
				textcolor(BROWN);

			if(*chan[i].pos <=  chan[i].end  ) {
				if(chan[i].effect != 14) vcprintf("%s       ",effect_primary[chan[i].effect]);
				else vcprintf("%s (E)      ",effect_secondary[chan[i].x]);
			}
			else vcprintf("                  ");
// ECODE
			gotoxy(42,18+i);
			vcprintf("%lu,%lu    ",(DWORD)chan[i].end,
				(DWORD)*chan[i].pos);
//			vcprintf("%d",chan[i].period);

			gotoxy(52,18+i);
//			vcprintf("%d",chan[i].volume);
			vcprintf("(%u)(%u)(%u)       ",
				mymod->slength[(SHORT)chan[i].sample_number-1],
				mymod->offset[(SHORT)chan[i].sample_number-1],
				mymod->repeat[(SHORT)chan[i].sample_number-1]);
				//vcprintf("%d",chan[i].volume);
		}
                                            // Show where we are in the mod
    textcolor(WHITE);
  	gotoxy(57,14);
		vcprintf("%d ",mymod->num_positions - mod_tablepos);
		gotoxy(57,15);
		vcprintf("%ld ",(long)(mod_pstop-mod_pattern)/16);
		//ECODE
		gotoxy(57,16);
		vcprintf("%d ",mod_on);

																						// Show the CPU overhead
    MilliDelay(10);	                        // Wait 10 milliseconds so that
                                            // we can be sure we aren't
                                            // measuring the same overhead
                                            // repeatedly.
		count++;
		total+=DSP_overhead;
		if(count == 30) {
		  oh = PercentOverhead((WORD)(total/count))/10.0;
			gotoxy(18,23);
			vcprintf("%.2lf%% ",oh);
			total = 0;
			count = 0;
		}
	}

}


/**************************************************************************
	void dspdemo(void)

	DESCRIPTION:  Plays sound effects with Varmint's Audio Tools

**************************************************************************/
void dspdemo(void)
{
	CHAR r = 0;
	DWORD tot = 0,num = 0,id;
	static DWORD loopid;
	static SHORT loop=0;
	SHORT i;
	double oh;

	DSP_overhead = 1;                           // turn on overhead checking

	clrscr();                                   // Clear screen and draw a menu
	textcolor(GREEN);
	gotoxy(10,8);
	vcprintf("Sound effects demo menu");
	textcolor(YELLOW);
	gotoxy(10,10);
	vcprintf("       1,2,3 - Play a sound with the v_plain command");
	gotoxy(10,11);
	vcprintf("<shift>1,2,3 - Play a sound with the v_fancy command");
	gotoxy(10,12);
	vcprintf("           L - Toggle Looping Demo (rumble sound)");
	gotoxy(10,13);
	vcprintf("           D - Frequency and Volume Demo");
	gotoxy(10,14);
	vcprintf("           C - Chain Demo");
	gotoxy(10 ,17);
	vcprintf("           Q - Quit");
	gotoxy(1,20);
	textcolor(CYAN);
	vcprintf("    Fancy sounds use up more CPU overhead than plain sounds,\r\n");
	vcprintf("but you can control the volume and frequency of fancy sounds.");

	gotoxy(1,1);
	vcprintf("CPU OVERHEAD: \r\nSOUNDS IN QUEUE: ");
	textcolor(WHITE);
	while(toupper(r) != 'Q') {         // input loop
		while(!kbhit()) {                // Wait for keystroke
			MilliDelay(7);
			tot+= DSP_overhead;            // take an average every 40 interrupts
			num++;
			if(num == 40) {
				gotoxy(15,1);
				oh = PercentOverhead((SHORT)(tot/num))/10.0;
				vcprintf("%2.2lf%%  ",oh); // Show overhead
				gotoxy(19,2);
				vcprintf("%d \n",sounds_in_queue);       // Show # sounds playing
				num = 0;
				tot = 0;
			}
		}
		r = getch();                      // Get keystroke and act accordingly
																			// Simple play commands
		if(r == '1') PlaySound(sound1,v_plain);
		else if(r == '2') PlaySound(sound2,v_plain);
		else if(r == '3') PlaySound(aha,v_plain);
		else if(r == '!') PlaySound(sound1,v_fancy);
		else if(r == '@') PlaySound(sound2,v_fancy);
		else if(r == '#') PlaySound(aha,v_fancy);
		else if(toupper(r) == 'L') {      // Looping demo- loop a rumble sound
			if(!loop) {
				loopid = PlaySound(rumble,v_fancy);
				AlterSoundEffect(loopid,v_setrepeat,-1);
				AlterSoundEffect(loopid,v_setvolume,32);
				loop = TRUE;
			}
			else {
				AlterSoundEffect(loopid,v_stop,0);
				loop = FALSE;
			}
		}                                 // Volume/frequncy demo
		else if(toupper(r) == 'D') {
			for(i = 1; i <16; i++ ) {       // Volume quiet->loud
				id = PlaySound(sound1,v_fancy);
				AlterSoundEffect(id,v_setvolume,i*4);
				gotoxy(1,5);
				vcprintf("Volume: %d   ",i*4);
				MilliDelay(150);
				if(kbhit()) {
					getch();
					i = 16;
				}
			}
			for(i = 1; i <16; i++ ) {       // Frequency slow->fast
				id = PlaySound(sound1,v_fancy);
				AlterSoundEffect(id,v_setrate,i*32);
				gotoxy(1,5);
				vcprintf("Rate: %d   ",i*32);
				MilliDelay(150* 8.0/i);
				if(kbhit()) {
					getch();
					i = 16;
				}
			}
			gotoxy(1,5);
			vcprintf("                 ");    // Hide the status line

		}
		else if(toupper(r) == 'C') {      // Chain demo
			id = PlaySound(sound1,v_plain);
			id = ChainSoundEffect(sound2,v_plain,id);
			id = ChainSoundEffect(aha,v_plain,id);
		}

	}
}

/**************************************************************************
	void sb_intro(void)

	DESCRIPTION:  Cool introduction sith sound blaster music and sounds

**************************************************************************/
void sb_intro(void)
{
	SHORT i,j;
	double fr;
	WORD f;
	DWORD id;

	clrscr();
	gotoxy(18,12);
	textcolor(LIGHTGRAY);
	vcprintf("Varmint's Audio Tools  (Version: %s)",VAT_VERSION);
	textcolor(RED);
	MilliDelay(500);

																			// Cool introduction
	FMReset();
	for(i = 0; i < 3; i++) {            // "Audio Hardware Activated"
		id = PlaySound(aha,v_fancy);
		if(i) AlterSoundEffect(id,v_setvolume,32-i*10);
		MilliDelay(300);
	}

	for(i = 0; i < 8; i++) {            // initialize music voices
		FMSetVoice(i,inst[vints[i]]);
		FMSetFrequency(i,startfreq[i]);
		FMSetVolume(i,0x00);
		FMKeyOn(i);
	}
	for(i = 0; i < 1000; i+= 1) {       // morph a big chord

		fr = i/1000.0;
		for(j = 0; j < 8; j++) {
			gotoxy(j*10+1,10);
			f = startfreq[j]+((double)endfreq[j]-(double)startfreq[j]) * fr;
			vcprintf("%X  ",f);
			FMSetFrequency(j,f);
			FMSetVolume(j,fr*0x3f );
			FMKeyOn(j);
		}
		MilliDelay(4);
		if(kbhit()) i = 1000;
	}

	if(!kbhit()) {
		for(i = 0; i < 8; i++) {          // Make sure all the notes are right
			FMSetFrequency(i,endfreq[i]);
			FMKeyOn(i);
		}

		for(i = 0x3f ; i >= 0; i-= 1) {   // quiet down slowly
			for(j = 0; j < 8; j++) {
				FMSetVolume(j,i);
			}
			MilliDelay(i*2+40);
			if(kbhit() & i) i = 1;
		}
	}

	for(i = 0; i < 9; i++) {            // Silence them all
		FMSetVolume(i,0);                   // volume off
		FMSetVoice(i,inst[0]);           // this instrument has a decay, so it
																			// gets all the way quiet
		FMSetFrequency(i,1);                  // Low freq = quiet
	}

	if(kbhit()) getch();
}
/**************************************************************************
	void mididemo(void)

	DESCRIPTION: Example function that loads and "plays" a  midi file

**************************************************************************/
void mididemo(void)
{
	SHORT i;
	CHAR r=0;

	clrscr();                                   // clear screen

	FMReset();

	midi_fmpatchmap = myfmpatchmap;
	midi_data = bachmidi;


	textcolor(MAGENTA);
	gotoxy(30,2);
	vcprintf("MIDI demo menu");
	textcolor(CYAN);
	gotoxy(30,3);
	vcprintf("1   - Start music");
	gotoxy(30,4);
	vcprintf("2   - Stop music");
	gotoxy(30,5);
	vcprintf("3   - Pause music");
	gotoxy(30,6);
	vcprintf("4   - Resume music");
	gotoxy(30,7);
	vcprintf("5   - Rewind music");
	gotoxy(30,8);
	vcprintf("V,v - Change music volume");
	gotoxy(30,9);
	vcprintf("T,t - Change music tempo");
	gotoxy(30,10);
	vcprintf("F   - Toggle FM output: ");
	if(midi_fmout) vcprintf("ON  ");
	else vcprintf("OFF ");
	gotoxy(30,11);
	vcprintf("U   - Toggle MPU output: ");
	if(midi_mpuout) vcprintf("ON  ");
	else vcprintf("OFF ");
	gotoxy(30,12);
	vcprintf("P   - Change MPU port address: %X",midi_mpuport);
	gotoxy(30,13);
	vcprintf("A   - Toggle MIDI patchmap ");
	if(midi_patchmap == defaultpatchmap) vcprintf("(16 channel)");
	else vcprintf("( 3 channel)");
	gotoxy(30,16);
	vcprintf("Q   - Quit");

  textcolor(LIGHTMAGENTA);
  gotoxy(3,18);
  vcprintf(
	"- SB16 users: If MPU401 output causes a lockup, you will need to run the");
	gotoxy(3,19);
	vcprintf(
	"  included patch from creative labs before running the demo. Type this at");
	gotoxy(3,20);
	vcprintf(
	"  the DOS prompt:   mpufix /e");
	gotoxy(3,21);
	vcprintf(
  "- If MPU401 output does not produce any sounds on your MIDI device, try");
	gotoxy(3,22);
	vcprintf(
  "  toggling the MIDI pathcmap.");


	while(toupper(r) != 'Q') {                  // MAIN LOOP
		gotoxy(1,15);                             // print temppo and volume stats
		textcolor(WHITE);
		vcprintf("Music Volume: %d  ",midi_volume);
		gotoxy(1,16);
		vcprintf("Music Tempo:  %d ",midi_usertempo);


		while(!kbhit()) {                         // handle the keyboard
			if(mpu_checked) {
				// ECODE
				gotoxy(1,17);
				vcprintf("timeout:  %d ",mpu_timeout);

				gotoxy(1,1);
				textcolor(GREEN);
				vcprintf("%s",mpu_available?"MPU Init Worked   ":"MPU Init Failed   ");
				if(mpu_available) {
					gotoxy(1,2);
					if(mpu_timeout) {
						vcprintf("%s",
							 (mpu_timeout == TIMEOUT)?"MPU Timing out   ":"MPU Working   ");
					}
					else vcprintf("                        ");
				}
			}
			for(i = 0; i < 9; i++) {
				gotoxy(1,5+i);
				if(midi_voice[i].active) textcolor(YELLOW);
				else textcolor(BROWN);
				vcprintf("Voice %d:  %d %d %d  ",i,midi_voice[i].note,
										midi_voice[i].owner_track,midi_voice[i].owner_channel);
			}
		}
		r = getch();                              // get keystroke

		if(r == 'V') {                            // Handle keystrokes
			midi_volume++;
			if(midi_volume > 0x3f) midi_volume = 0x3f;
		}
		else if(r == 'v') {
			if(midi_volume > 0) midi_volume--;
		}
		else if(r == '1') MidiCommand(v_play);
		else if(r == '2') MidiCommand(v_stop);
		else if(r == '3') MidiCommand(v_pause);
		else if(r == '4') MidiCommand(v_resume);
		else if(r == '5') MidiCommand(v_rewind);
		else if(toupper(r) == 'A') {              // Toggle midi patchmap
			if(midi_patchmap == mypatchmap) midi_patchmap = defaultpatchmap;
			else midi_patchmap = mypatchmap;
			gotoxy(57,13);
			if(midi_patchmap == defaultpatchmap) vcprintf("(16 channel)");
			else vcprintf("( 3 channel)");
		}
		else if(r == 'T') {
			midi_usertempo *= 1.1;
			if(midi_usertempo > 1000) midi_usertempo = 1000;
		}
		else if(r == 't') {
			midi_usertempo *= 0.9;
			if(midi_usertempo < 10) midi_usertempo = 10;
		}
		else if(toupper(r) == 'F') {               // Toggle output
			midi_fmout ^= TRUE;
			textcolor(CYAN);
			gotoxy(54,10);
			if(midi_fmout) vcprintf("ON  ");
			else vcprintf("OFF ");
		}
		else if(toupper(r) == 'U') { 							// Toggle MPU output
			midi_mpuout ^= TRUE;
      if(midi_mpuout && !mpu_checked) MPUEnter();
      if(!midi_mpuout) {
				gotoxy(1,1);
        vcprintf("                        \n\r                      ");
      }
			textcolor(CYAN);
			gotoxy(55,11);
			if(midi_mpuout) vcprintf("ON   ");
			else vcprintf("OFF ");
		}
		else if(toupper(r) == 'P') { 							// Change MIDI port
      gotoxy(6,24);
      vcprintf("Enter new port address in hex values [%x]: ",midi_mpuport);
      gets(errstring);
      if(strlen(errstring)) sscanf(errstring,"%x",&midi_mpuport);
                                               // check for accidents
      if(midi_mpuport < 0x200 || midi_mpuport > 0x360) midi_mpuport = 0x330;
      MPUEnter();
      gotoxy(6,24);
      vcprintf("                                                    ");
      mpu_timeout = 0;
    }

	}
}


/**************************************************************************
	void bitprint(CHAR byte)

	DESCRIPTION:  Prints individual bits and then a HEX value

**************************************************************************/
void bitprint(BYTE byte)
{
	SHORT i;

	vcprintf("  ");
																		// go through bits
	for(i = 7; i >= 0; i--) {
		if(getbit(byte,i)) {            // 1's are yellow
			textcolor(YELLOW);
			vcprintf("1");
		}
		else {                          // 0's are dark grey
			textcolor(DARKGRAY);
			vcprintf("0");
		}
	}

	textcolor(LIGHTBLUE);             // print the hex value
	vcprintf("  %c%c",hexchar[byte/16],hexchar[byte%16]);
	textcolor(WHITE);
}



/**************************************************************************
	void fmdemo()

	DESCRIPTION:  Allows th user to mess around with instruments and
								play a few notes.


**************************************************************************/
void fmdemo(void)
{
	WORD i,cx,cy,voice=0,instrument = 0;
	SHORT drawvoice = 1,rythm = 0,vol;
	CHAR r = 0;

	vol = midi_volume *8;
	if(vol > 63) vol = 63;

	clrscr();                          // clear screen
	vcprintf("FM demonstration screen");

	gotoxy(1,16);
	vcprintf("IJKL = cursor movement\r\n");
	vcprintf("<space> = toggle bit\r\n");
	vcprintf("numbers = play notes\r\n");
	vcprintf("v = change voice\r\n");
	vcprintf("n = Change instrument\r\n");
	vcprintf("r = toggle rythm mode\r\n");
	vcprintf("q = quit");

	_setcursortype(_SOLIDCURSOR);
	FMReset();
	for( i = 0; i < 8; i++) {          // initialize voices
		FMSetVoice ( i,inst[instrument]) ;
		FMKeyOff(i);
		FMSetVolume(i,0);
	}

	cx = 54;cy = 5;                    // init cursor position

	for(i = 0; i < 11; i++) {          // print register names
		gotoxy(50-strlen(regname[i]),i+5);
		textcolor(MAGENTA);
		vcprintf("%s",regname[i]);
	}


	while(r != 'Q') {                  // main input loop
		if(drawvoice) {
			for(i = 0; i < 11; i++) {      // display instrument data
				gotoxy(52,i+5);
				bitprint(inst[instrument][i]);
			}
			for(i = 0; i < 9; i++) {
				FMSetVoice ( i,inst[instrument]) ; // initialize new voice
			}
			drawvoice = 0;
			textcolor(LIGHTGRAY);
			gotoxy(52,4);
			vcprintf("Instrument #%d ",instrument);
		}

		gotoxy(cx,cy);                   // put cursor in right spot

		while(!kbhit());

		r = toupper(getch());
		if(r >= '0' && r <= '9') {
			FMKeyOff(voice);
			FMSetVoice(voice,inst[instrument]);
			FMSetNote ( voice, (r-'0'+3) * 8) ;
			FMSetVolume(voice,vol);
			FMKeyOn(voice);
		}
		else if(r == 'I') {              // i,j,k,l = cursor movement
			cy = cy -1;
			if(cy<5) cy = 5;
		}
		else if(r == 'K') {
			cy = cy +1;
			if(cy >15) cy = 15;
		}
		else if(r == 'J') {
			cx = cx -1;
			if(cx<54) cx = 54;
		}
		else if(r == 'L') {
			cx = cx +1;
			if(cx>61) cx = 61;
		}
		else if(r == ' ') {              // space = toggle bit
			togbit(inst[instrument][cy-5],(7-(cx-54)));
			drawvoice = 1;
		}
		else if(r == 'N') {              // I = change instrument
			instrument++;
			if(instrument > 8) instrument = 0;
			drawvoice = 1;
		}
		else if(r == 'R') {              // r = toggle rythm mode
			if(rythm) rythm = 0;
			else rythm = 1;
			FMSetRythmMode(rythm);           // do it
			FMRythmOn(FM_HIHAT);
			gotoxy(1,2);                   // tell the user
			if(rythm) vcprintf("Rythm Mode ON  (voices 6,7,8 only) ");
			else      vcprintf("Rythm Mode OFF                     ");
		}
		else if(r == 'V') {              //  v = change voice
			FMKeyOff(voice);
			FMSetVolume(voice,0);
			voice ++;
			if(voice > 8) voice = 0;
			gotoxy(1,3);
			vcprintf("Voice: %d ",voice);
		}

	}
	for(i = 0; i < 9; i++) {
		FMSetVolume(i,0);
	}
	_setcursortype(_NOCURSOR);

}



/**************************************************************************
	void tprintf(char *s)

	DESCRIPTION:  Simple print function for colors on the title screen

**************************************************************************/
void tprintf(char *s)
{
	int i;
	char p[2]={"+"};

	for(i = 0; i < strlen(s); i++) {

		*p = *(s+i);
		if(*p == '-') {
			textcolor(DARKGRAY);
		}
		else if(*p == '#') {
			textcolor(WHITE);
			*p = 178;
		}
		else if(*p == '+') {
			textcolor(MAGENTA);
			*p = 178;
		}
		else if(*p == '+') {
			textcolor(BLACK);
			textbackground(BLACK);
		}
		else {
			textcolor(YELLOW);
			textbackground(DARKGRAY);
		}
		cprintf(p);
	}
	textbackground(BLACK);
}
/**************************************************************************
	void introtext(void)

	DESCRIPTION: Display introduction text for the user.


**************************************************************************/
void introtext(void)
{
	clrscr();
	textcolor(MAGENTA);
	tprintf("------------------------------------------------------------------------------\n\r");
	tprintf("-----------------------###-------------####-------------################# ----\n\r");
	tprintf("------####+ ----------##+++  --------####+  -----------##+++++++++++++++  ----\n\r");
	tprintf("----####+++  ---------##+++ --------##+++++  ---------##+++++++++++++++  -----\n\r");
	tprintf("----#+++++++  -------##++  ---------##++++++  -------##      ++++       ------\n\r");
	tprintf("----##+++++++  -----##++  ---------##++++++++  --------------#++ -------------\n\r");
	tprintf("-----###+++++++ ---##++  ---------##+  #+++++++  ------------#++ -------------\n\r");
	tprintf("-------##+++++++ -##++  ---------##++-##++++++++  -----------#++  ------------\n\r");
	tprintf("--------###++++++++++  ---------##+++++++++++++++  ----------#++  ------------\n\r");
	tprintf("----------##++++++++  ---------##+++++++++++++++++  ---------#+++  -----------\n\r");
	tprintf("-----------##++++++  ----------##++        #+++++++  --------#+++  -----------\n\r");
	tprintf("-------------##+++  ----------##+++ --------#+++++++  -------#+++  -----------\n\r");
	tprintf("--------------##+  ARMINT'S--##++  ----------#        UDIO---#++  OOLS--------\n\r");
	tprintf("---------------#  ----------##++  ---------------------------#  --------------\n\r");
	tprintf("------------------------------------------------------------------------------\n\r");
	textcolor(LIGHTGRAY);
	vcprintf("\nThanks for trying out VAT!\r\n");
	vcprintf("This demo has command line options. Run as 'VATDEMO -?' for details. \r\n\n");
	textcolor(YELLOW);

	vcprintf("Please edit the file survey.txt and return it to:  smeagol@rt66.com\r\n");
	printf("\n");
	printf("Press the space bar to continue...");

	while(!kbhit());
	getch();
}


/**************************************************************************
	void diagnostics(void)

	DESCRIPTION:  This prepares survey.txt to receive diagnostic information
								and writes a few introductory things in that file.

**************************************************************************/
void diagnostics(void)
{
	static CHAR *e;

	diagoutput = fopen("survey.txt","w");    // Open survey file
	if(!diagoutput) return;

	printf("\nTesting and recording system configuration.\n");
																					 // Write the survey
	fprintf(diagoutput,"Survey for Varmint's Audio tools.\n");
	fprintf(diagoutput,"\n");
	fprintf(diagoutput,"Please email the completed survey to smeagol@rt66.com\n");
	fprintf(diagoutput,"Please do not send this file back bin-hexxed.  My whimpy mailer\n");
	fprintf(diagoutput,"can't handle bin-hexxed files.\n");
	fprintf(diagoutput,"-----------------------------------------------------------------------------\n");
	fprintf(diagoutput,"VERSION %s\n",VAT_VERSION);
	fprintf(diagoutput,"\n");
	fprintf(diagoutput,"1) What's your name and email address?\n");
	fprintf(diagoutput,"\n");
	fprintf(diagoutput,"\n");
	fprintf(diagoutput,"2) How did you hear about Varmint's Audio tools and where did you find\n");
	fprintf(diagoutput,"	 this copy?\n");
	fprintf(diagoutput,"\n");
	fprintf(diagoutput,"\n");
	fprintf(diagoutput,"3) Did the demo work on your computer?  If not, please describe what happened.\n");
	fprintf(diagoutput,"\n");
	fprintf(diagoutput,"\n");
	fprintf(diagoutput,"4) Have you tried earlier versions of VAT?  What versions?  Did the demos work?\n");
	fprintf(diagoutput,"\n");
	fprintf(diagoutput,"\n");
	fprintf(diagoutput,"5) Have you been able to use VAT in your own programs?  What features made\n");
	fprintf(diagoutput,"	 it easy or difficult to do so?\n");
	fprintf(diagoutput,"\n");
	fprintf(diagoutput,"\n");
	fprintf(diagoutput,"6) Please describe your computer system:\n");
	fprintf(diagoutput,"\n");
	fprintf(diagoutput,"                CPU (eg: 386,486,Pentium):\n");
	fprintf(diagoutput,"\n");
	fprintf(diagoutput,"          Internal clock speed (eg:66Mhz):\n");
	fprintf(diagoutput,"\n");
	fprintf(diagoutput,"        Memory Manager (eg: QEMM, EMM386):\n");
	fprintf(diagoutput,"\n");
	fprintf(diagoutput,"  Operating system(eg: DOS/Windows, OS/2):\n");
	fprintf(diagoutput,"\n");
	fprintf(diagoutput,"        Sound card (eg: PAS16, GUS, SB16):\n");
	fprintf(diagoutput,"\n");
	fprintf(diagoutput,"\n");
	fprintf(diagoutput,"7) Please add any additional praise or chastisement of Varmint's Audio Tools:\n");

																						// Print some autodiag info
	fprintf(diagoutput,"\n---------- AUTO DIAGNOSTIC INFORMATION ---------\n");
	fprintf(diagoutput,"Everything below here was written automatically by\n");
	fprintf(diagoutput,"the VAT demo.  Please do not delete these lines.\n");
	fprintf(diagoutput,"-------------------------------------------------\n\n");

	e = getenv("BLASTER");                    // Record BLASTER variable
	if(e) fprintf(diagoutput,"BLASTER env variable: %s\n",e);


																						// Check available memory
	fprintf(diagoutput,"Start Core left: %lu\n",farcoreleft());
	fflush(diagoutput);
}


/**************************************************************************
	void debugoptions(void)

	DESCRIPTION: Allows the user to set certain debug options.  These debug
							 options will eventually be removed from the code when it
							 is debugged.

**************************************************************************/
void debugoptions(void)
{
	CHAR r = 0;
	SHORT i,j;

	clrscr();                                 // Set up the screen

	textcolor(YELLOW);
	gotoxy(32,1);
	vcprintf("VAT debug options\n\r");
	textcolor(LIGHTGRAY);
	vcprintf("The only problem seen these days with VAT is static on a very few\r\n");
	vcprintf("systems.  If you hear static in this demo, these tests will help to\r\n");
	vcprintf("determine the source of the static.  You will need make sure a \r\n");
	vcprintf("MOD is playing in the background while trying these tests.\r\n");

	textcolor(LIGHTGREEN);

	gotoxy(10,7);                             // show options
	vcprintf("1) Reverse DMA flipflop (kills static on some systems)");
	gotoxy(5,7);
	vcprintf("%s", debug_reverseflipflop?"ON ":"OFF");
	gotoxy(10,8);
	vcprintf("2) Static Source test. (Tests for some causes of static)");


	gotoxy(5,22);
	vcprintf("Press a number to toggle an option, or Q to quit.");

																					 // input loop
	textcolor(WHITE);
	while(tolower(r) != 'q') {
		r = toupper(getch());
		if(r == '1') {                         // change the flipflop
			debug_reverseflipflop ^= TRUE;
			gotoxy(5,7);
			if(debug_reverseflipflop) vcprintf("ON  ");
			else vcprintf("OFF ");
		}                                      // key/screen test
		else if(r == '2') {
			gotoxy(1,10);
																				// clear part of the screen
			for(i = 1; i < 81; i++){
				for(j = 10; j < 21; j++) {
					gotoxy(i,j);
					vcprintf(" ");
				}
			}
																				// print information
			gotoxy(1,10);
			textcolor(LIGHTGRAY);
			vcprintf("STATIC SOURCE TEST.  This will help determine if the keyboard handler\r\n");
			vcprintf("or video card are causing static.  This test will last about\r\n");
			vcprintf("10 seconds.  Press <SPACE> to begin...\r\n");

			while(!kbhit());                  // wait for a keystroke
																				// begin testing
			textcolor(LIGHTMAGENTA);
			vcprintf("\nTEST1:  Updating the screen only.\r\n");
			for(i = 0; i < 600; i++) {
				gotoxy(36,14);
				vcprintf("%c",random(80)+32);
				MilliDelay(5);
			}
			vcprintf("\r\nTEST2:  Checking the keyboard only.\r\n");
			for(i = 0; i < 500; i++) {
				kbhit();
				MilliDelay(5);
			}
			vcprintf("TEST3:  No activity.\r\n");
			for(i = 0; i < 600; i++) {
				MilliDelay(5);
			}
			textcolor(LIGHTGRAY);
			vcprintf("\nTest completed.  Did these tests have any effect on static? Please\r\n");
			vcprintf("fill out the survey.txt file and report these results to\r\n");
			vcprintf("Eric Jorgensen  (smeagol@rt66.com).\r\n");
		}
	}
}



CHAR vatoutstring[255];

/**************************************************************************
	void vcprintf(CHAR *string,...)

	DESCRIPTION:  Special printf function that disables interrupts.  There is
								some concern that interrupting a printf may cause some
								systems to crash.  This is an experimental precaution.

**************************************************************************/
void vcprintf(CHAR *string,...)
{
	va_list ap;

	_disable();

	va_start(ap, string);                  // sort out variable argument list
	vsprintf(vatoutstring,string,ap);      // dump output to a string
	cprintf("%s",vatoutstring);            // dump string to screen
	va_end(ap);                            // clean up
	_enable();
}
