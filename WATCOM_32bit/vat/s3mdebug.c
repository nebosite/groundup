/**************************************************************************
  VATDEMO.C

  A Ground Up Production
    Primary Authors: Bryan Wilkins (May 1996)
                     Eric Jorgensen (August 1995)

  This code was written using Watcom C.  It is intended to demonstrate the
  use of Varmint's Audio Tools and to provide a example code for programmers
  who wish to use VAT.

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
#include <malloc.h>
#include <mem.h>
#include <graph.h>
#include "vat.h"
#include "compat.h"
#include "doink.h"
#include "wooeep.h"
#include "rumble.h"

#define TESTSIZE 5
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
void introtext(void);
void diagnostics(void);
void debugoptions(void);
void vatcprintf(CHAR *string,...);
void usage(char *arg0);
WORD random(WORD num);

                                 // external functions

//-------------------------- external data -----------------------
                                        // These variables are necessary to
                                        // VAT, but are not normally needed
                                        // outside of the library itself.
                                        // I've included them in the demo
                                        // to help illustrate what is
                                        // possible with VAT.

extern SHORT           sounds_in_queue;
extern CHAR            vatdebugstring[];
extern VOICE           midi_voice[];
extern WORD            mpu_addr;

extern SHORT           mod_currenttick;
extern SHORT           mod_tablepos;
extern BYTE           *mod_pstop, *mod_pattern;

extern SHORT           s3m_currenttick;
extern SHORT           s3m_tablepos;
extern BYTE           *s3m_pstop, *s3m_pattern;

extern SHORT           s3m_order;
extern SHORT           s3m_divbytes;

extern BYTE           *midi_fmpatchmap;

extern volatile WORD   DSP_overhead;
extern volatile SHORT  debug_reverseflipflop;


//-------------------------- DATA and Globals --------------------

                                  // Instrument data

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

CHAR errstring[256];
WAVE *sound1,*sound2,*aha,*rumble_sound;
FILE *diagoutput= NULL;
DWORD memleft;
MIDI  *bachmidi  = NULL;
MOD  *mymod = NULL;
S3M  *mys3m = NULL;
CHAR midfilename[255] = {"sample4.mid"};
CHAR modfilename[255] = {"cutdry.mod"};
CHAR s3mfilename[255] = {"aryx.s3m"};
static CHANNEL       *chan;
DWORD flushearly = 0,mysamplerate = 45000;

void testmod(char *filename);
void tests3m(char *filename);
void inits3m(void);
void S3MPlayer(void);
extern DWORD       dma_bufferlen;
extern BYTE    *dma_buffer[2] = {NULL,NULL};

DWORD tickstop=0,orderstop=0,playstop=0;
extern VATSTATUS internal_status;

char testmem[TESTSIZE];

extern SHORT mod_printout;
SHORT buffer[50000];
extern SHORT *mix_buffer;

/**************************************************************************
	int checkmem(void)

	DESCRIPTION:

**************************************************************************/
int checkmem(char *message)
{
	int i;

	gotoxy(1,40);
	fprintf(stderr,"CHECKING--%s     ",message);

	for(i = 0; i < TESTSIZE; i++) {
		if(testmem[i]) {
			printf("Memory Error at %d\d",i);
			exit(1);
		}
	}

}

/**************************************************************************
	void main()

	DESCRIPTION:   Handles the main menu and sets things up

**************************************************************************/
void main(SHORT argc,CHAR *argv[])
{
	char r = 0;
	DWORD i=0;

	mix_buffer = buffer;
	memset(testmem,0,TESTSIZE);

	_clearscreen(0);

	internal_status = v_started;
	gotoxy(1,1);
	for(i = 0; i < 50; i++) {
		printf(
		"                                                                         \r\n");
	}

	if (argc < 2) {
		printf("Usage: %s (s3mfilename)\n",argv[0]);
		exit(0);
	}
//	checkmem("premod");
//	VATStartUp (22000, 70, v_true, v_detect);
	strupr(argv[1]);

	if(strstr(argv[1],"S3M")) tests3m(argv[1]);
	if(strstr(argv[1],"MOD")) testmod(argv[1]);
//	VATShutDown();
}


/**************************************************************************
	void testmod(char *filename)

	DESCRIPTION:

**************************************************************************/
void testmod(char *filename)
{
	char r = 0;
	DWORD i=0;

//	mod_printout = v_true;

	mymod = LoadMod(filename,(CHAR *)errstring);
	if(!mymod) {
		printf("LoadMod err: %s\n",errstring);
		exit(0);
	}

	initmod();

	PlayMod(mymod);
	chan = ModChannels();

	checkmem("postplay");

	gotoxy(1,5);
	cprintf("q = quit\r\n");
	cprintf("p = toggle playstop\r\n");
	cprintf("o = toggle orderstop\r\n");
	cprintf("t = toggle tickstop\r\n");
	cprintf("j = jump forward 1 order\r\n");

	while(ModStatus() == v_started && r != 'q') {
		if(kbhit() || playstop || orderstop || tickstop) {
			if(playstop || orderstop || tickstop) {
				gotoxy(1,15);
				cprintf("Cmnd :");
			}
			r = getch();
			if(r == 'j') mod_tablepos++;
			if(r == 'p') playstop ^= 1;
			if(r == 'o') orderstop ^= 1;
			if(r == 't') tickstop ^= 1;
		}

		if(playstop) r = getch();
		ModPlayer();
		gotoxy(12,10);

		cprintf("POS: %d/%d ",mod_tablepos,mymod->num_positions);
		gotoxy(12,11);
		cprintf("D: %ld ",(long)(mod_pstop-mod_pattern)/16);
	}

//	checkmem("prefree");

	if(mys3m)     FreeS3M(mys3m);
//	checkmem("postfree");

																					 // Dump debug info to survey.txt
	gotoxy(1,24);
	textcolor(LIGHTGRAY);
	_setcursortype(_NORMALCURSOR);           // Brings cursor back
}

/**************************************************************************
	void tests3m(char *filename)

	DESCRIPTION:

**************************************************************************/
void tests3m(char *filename)
{
	char r = 0;
	DWORD i=0;
	int lastorder = -1;

	printf("Loading s3m...\n");
	mys3m = LoadS3M(filename,(CHAR *)errstring);
return;
	if(!mys3m) {
		printf("LoadS3M err: %s\n",errstring);
		exit(0);
	}

	inits3m();

	PlayS3M(mys3m);
	chan = S3MChannels();

	gotoxy(1,5);
	cprintf("q = quit\r\n");
	cprintf("p = toggle playstop\r\n");
	cprintf("o = toggle orderstop\r\n");
	cprintf("t = toggle tickstop\r\n");
	cprintf("j = jump forward 1 order\r\n");
	while(S3MStatus() == v_started && r != 'q') {
		if(kbhit() || playstop || orderstop || tickstop) {
			if(playstop || orderstop || tickstop) {
				gotoxy(1,15);
				cprintf("Cmnd :");
			}
			r = getch();
			if(r == 'j') s3m_order++;
			if(r == 'p') playstop ^= 1;
			if(r == 'o') orderstop ^= 1;
			if(r == 't') tickstop ^= 1;
		}

		if(playstop) r = getch();
		S3MPlayer();
		if(s3m_order != lastorder) {
			gotoxy(12,10);
			cprintf("O: %d/%d (P:%d) ",s3m_order,mys3m->orders,mys3m->order[s3m_order]);
			lastorder = s3m_order;
		}
		gotoxy(12,11);
		cprintf("D: %ld ",64-(long)(s3m_pstop-s3m_pattern)/s3m_divbytes);
	}

/*	if (VATStartUp (mysamplerate, 70, v_true, v_detect)) {

		PlayS3M (mys3m);

		while(r != 'Q' && r != 'q') {
			if(kbhit()) {
				r = getch();
			}
		}
		S3MCommand (v_stop);

		VATShutDown ();
		textcolor(_NORMALCURSOR);
		clrscr();                               // Clear the screen
	}
	else {
		printf("SB_Setup returned this error: %s \n",errname[sberr]);
	}
*/
	if(mys3m)     FreeS3M(mys3m);

																					 // Dump debug info to survey.txt
	gotoxy(1,24);
	textcolor(LIGHTGRAY);
	_setcursortype(_NORMALCURSOR);           // Brings cursor back
}
