#include "vat.h"
#include "compat.h"
#include <stdio.h>
#include <conio.h>
#include <dos.h>
#include <malloc.h>
#include <graph.h>
#include <string.h>
#include <ctype.h>

#define SND 1
#define VIDEOREFRESH 70

void patchtest(char *patchname);
void notetest(PATCH *testpatch);
void miditest(char *filename);
int memcheck( void );
int loadpatches(char *listfile);
void shorttest();
void noteplayer(void);


void initnote(void);



extern VATSTATUS internal_status;
extern volatile WORD   DSP_overhead;
extern PATCH					defaultinstrument;
extern PATCH					defaultdrum;

PATCH *plist[128];
PATCH *quickp;
int ptotal = 0;




/**************************************************************************
	void mcheck(char *filename)

	DESCRIPTION: Quick check fo music file type

**************************************************************************/
void mcheck(char *filename)
{
	VATMUSICTYPE mt;
	char errstring[256];

	mt = GetMusicTyper(filename,errstring);
	switch(mt) {
	case v_musictype_error :
		printf("ERROR: %s\n",errstring);
		break;
	case v_musictype_unknown :
		printf("Unknown type\n");
		break;
	case v_musictype_mod :
		printf("It's a MOD\n");
		break;
	case v_musictype_midi :
		printf("It's a MIDI\n");
		break;
	case v_musictype_s3m :
		printf("It's a S3M\n");
		break;

	}
}

/**************************************************************************
	void main(int argc, char *argv[])

	DESCRIPTION:

**************************************************************************/
void main(int argc, char *argv[])
{
	char errstring[256];
	size_t avl,max,size;
	void *zoop=NULL;
	WAVE *wtest;
	MOD *mtest;
	S3M *stest;

//	mcheck(argv[1]);
//	return;

/*	memcheck();
	printf("AVL: %d\n",_memavl());
	zoop = malloc(1000000);
	free(zoop);
	printf("AVL: %d\n",_memavl());
	zoop = malloc(500000);
	printf("AVL: %d\n",_memavl());
	getch(); */
																			// Show a banner, start up sound, etc.
	clrscr();
	printf(	"\nVAT Patch test (C++ Ver 1.0). \n\n");

	_setcursortype(_NOCURSOR);

	if(SND) {
		if(!SBSetUp (44000, VIDEOREFRESH)) {
			printf("Egad!  Vat choked!\n");
			exit(1);
		}
		GoVarmint ();
	}

/*	wtest = LoadWave("wooeep.wav",errstring);
	if(wtest) {
		PlayWave(wtest,v_false,v_pan);
		getch();
	}
	mtest = LoadMod("cutdry.mod",errstring);
	if(mtest) {
		PlayMod(mtest);
		getch();
	}
	stest = LoadS3M("aryx.s3m",errstring);
	if(stest) {
		PlayS3M(stest);
		getch();
	}  */
																			// Call testing functions.
																			// ptest.cfg is just a list of
																			// patch files
	printf("starting\n");
	if(argc == 1) patchtest("ptest.cfg");
	else if(strstr(argv[1],"mid")) miditest(argv[1]);
	else patchtest(argv[1]);

	//shorttest();

	if(SND) {
		DropDeadVarmint ();
		SBCleanUp ();
	}

	_setcursortype(_NORMALCURSOR);
}



/**************************************************************************
	void shorttest()

	DESCRIPTION:	Quick check of debugnum with VAT is going

**************************************************************************/
void shorttest()
{
	extern LONG debugnum;

	while(!kbhit()) {
		printf("D:%d\n",debugnum);
//		noteplayer();
	}
	getch();
	return;
}

/**************************************************************************
	void miditest(void)

	DESCRIPTION:	Set up patch instruments and play a MIDI file

**************************************************************************/
void miditest(char *filename)
{
	MIDI *music;
	char errstring[256];
	LONG notehandle[256];
	void initmid(void);
	void midiplayer(void);
	extern VATSTATUS     internal_status;
	extern DWORD mididebugtimer;
	int i,j;
	char r;
/*
acbass.pat     2
acguitar.pat   3
acpiano.pat    4
distgtr.pat    5
glocken.pat    6
hrpschrd.pat   7
jazzgtr.pat    8
marimba.pat    9
musicbox.pat   10
trumpet.pat    11
tuba.pat       12
tubebell.pat   13
vibes.pat      14
viola.pat      15
violin.pat     16
xylophon.pat   17
*/
																// Load patches an initialize VAT's
																// internal patch list.
	if(!loadpatches("ptest.cfg")) return;
	MidiSetInstrumentPatch(32,plist[2]);
	MidiSetInstrumentPatch(25,plist[3]);
	MidiSetInstrumentPatch(0,plist[4]);
	MidiSetInstrumentPatch(30,plist[5]);
	MidiSetInstrumentPatch(9,plist[6]);
	MidiSetInstrumentPatch(6,plist[7]);
	MidiSetInstrumentPatch(26,plist[8]);
	MidiSetInstrumentPatch(12,plist[9]);
	MidiSetInstrumentPatch(10,plist[10]);
	MidiSetInstrumentPatch(56,plist[11]);
	MidiSetInstrumentPatch(58,plist[12]);
	MidiSetInstrumentPatch(14,plist[13]);
	MidiSetInstrumentPatch(11,plist[14]);
	MidiSetInstrumentPatch(41,plist[15]);
	MidiSetInstrumentPatch(40,plist[16]);
	MidiSetInstrumentPatch(13,plist[17]);

	if(!SND) internal_status = v_started;

/*	for(i = 0; i < 0; i++) {
		fprintf(stderr,"%d]%s ",i,MidiGetInstrumentPatch(i)->name);
		for(j = 1; j < 100; j+=13) {
			fprintf(stderr,".");
			notehandle[j] = PlayNote(j,MidiGetInstrumentPatch(i));
			MilliDelay(100);
		}
		MilliDelay(500);
		for(j = 1; j < 100; j+=13) {
			NoteCommand(notehandle[j],v_stop);
			MilliDelay(100);
		}
		fprintf(stderr,"\n");
		if(kbhit()) break;
	}
	getch();
return;  */
																	// Load the MIDI
	MidiSetting(v_volume,32);
	music = LoadMidi(filename,errstring);
	if(!music) {
		fprintf(stderr,"ERROR:  %s\n",errstring);
		return;
	}

																	// Initilize player by hand if
																	// VAT is not started.
	if(!SND) {
		fprintf(stderr,"Initializing...\n");
		initmid();
	}
	else internal_status = v_started;

																	// Crank up the music
	fprintf(stderr,"Starting...\n");
	PlayMidi(music);
																	// Watch for keystrokes while we
																	// dump debug info.
	fprintf(stderr,"Playing...(%d)\n", MidiStatus());
	while(r != 'q' && r != 27) {
		//fprintf(stderr,"neep (%d)\n",MidiStatus());
		mididebugtimer = 0;
		//midiplayer();
		if(mididebugtimer > -100) {
			printf("Time: %d\n",mididebugtimer);
			r = getch();
		}
		if(mididebugtimer < 4 && kbhit()) r = getch();
//		if(MidiStatus() == v_stopped) r = 'q';
	}
	getch();
}



/**************************************************************************
	void loadpatches(char *listfile)

	DESCRIPTION:	Load a bunch of patches from a config file.

**************************************************************************/
int loadpatches(char *listfile)
{
	int i;
	FILE *input;
	char string[1000];
	char errstring[256];
	char *spot;
	int flag=1;
	char r;
																// First patches just set to VAT's internal
																// defaults.
	plist[ptotal++] = &defaultinstrument;
	plist[ptotal++] = &defaultdrum;

	printf("Loading Patches from %s...\n",listfile);

	input = fopen(listfile,"r");
	if(!input) {
		printf("ERROR:  could not open patch config file: %s\n",listfile);
		getch();
		return ptotal;
	}
																	// Load all the patches
	while(fgets(string,999,input)) {
		spot = strchr(string,'\n');
		if(spot) *spot = 0;
		if(isalnum(string[0]) || string[0] == '\\') {
			printf("Loading Patch %s... ",string);
			plist[ptotal] = LoadPatch(string,errstring);
			if(!plist[ptotal]) {
				printf(errstring);
			}
			else {
				printf("Success.");
				ptotal++;
			}
			printf("\n");
		}
		if(ptotal > 20) break;
	}

	if(!ptotal) printf("No patch files loaded. \n");

	getch();
	return ptotal;
}

/**************************************************************************
	void patchtest(char *patchname)

	DESCRIPTION: 	Displays a list of patches, then lets the user pick
								which patch to play with.

**************************************************************************/
void patchtest(char *listfile)
{
	int flag = 1,i;
	char r;

	if(!loadpatches(listfile)) return;
	if(!SND) initnote();

	clrscr();
	while(flag) {
		for(i = 0; i < ptotal; i++) {
			gotoxy(1,i+2);
			cprintf("%c] %s  \n",i+'A',plist[i]->name);
		}

		r = toupper(getch());
		if(r >= 'A' && r < 'A'+ptotal) {
			notetest(plist[r-'A']);
			clrscr();
		}
		else if( r == 27) flag = 0;
	}

	for(i = 2; i < ptotal; i++) {
		FreePatch(plist[i]);
	}

}



/**************************************************************************
	void notetest(PATCH *testpatch)

	DESCRIPTION:		Lets you play patches with the keyboard.  Top row of
									letters and numbers work like piano keys.

**************************************************************************/
void notetest(PATCH *testpatch)
{
	int i,j,k;
	PATCHSAMPLE *psamp;
	char r=0;
	static int initialized= 0;
	static LONG notehandle[50];
	static LONG notedelay[50];
	void initnote(void);
	int notebase = 4;
	int donote,delay;
	double averagedohead = 0.0,ohead = 0.0;

	DSP_overhead = 1;

	if(!initialized) {
		for(i = 0; i < 50; i++) {
			notehandle[i] = 0;
			notedelay[i] = 0;
		}
		initialized = 1;
	}

	clrscr();
	printf("Master Volume: %d\n",testpatch->master_volume);
	j = 5;
	gotoxy(1,j);
	cprintf("Envelope Data");
	gotoxy(35,j);
	cprintf("Trem/Vib");
	gotoxy(70,j);
	cprintf("Switches");
	j++;
	psamp = testpatch->samplelist;
															// Quickly dump internal information about
															// each patch.
	while(psamp) {
		for(i = 0; i < 6; i++) {
			gotoxy(i*5+1,j);
			cprintf("%.1lf ",psamp->envelope_rate[i]/10000.0);
			gotoxy(i*5+1,j+1);
			cprintf("%.1lf%",psamp->envelope_offset[i]/655.36);
		}

		gotoxy(35,j);
		cprintf("%2X ",psamp->tremolo_sweep);
		gotoxy(38,j);
		cprintf("%2X ",psamp->tremolo_rate);
		gotoxy(41,j);
		cprintf("%2X ",psamp->tremolo_depth);
		gotoxy(35,j+1);
		cprintf("%2X ",psamp->vibrato_sweep);
		gotoxy(38,j+1);
		cprintf("%2X ",psamp->vibrato_rate);
		gotoxy(41,j+1);
		cprintf("%2X ",psamp->vibrato_depth);

		gotoxy(45,j);
		cprintf("%5d ",psamp->size);
		gotoxy(45,j+1);
		cprintf("%5d ",psamp->loop_start);
		gotoxy(51,j+1);
		cprintf("%5d ",psamp->loop_end);


		gotoxy(70,j);
		cprintf("l%s ",psamp->mode_looping ? "+" : "." );
		gotoxy(73,j);
		cprintf("B%s ",psamp->mode_bi_dir_looping ? "+" : "." );
		gotoxy(76,j);
		cprintf("-%s ",psamp->mode_backward_looping ? "+" : "." );
		gotoxy(70,j+1);
		cprintf("S%s ",psamp->mode_sustain ? "+" : "." );
		gotoxy(73,j+1);
		cprintf("E%s ",psamp->mode_envelopes ? "+" : "." );
		gotoxy(76,j+1);
		cprintf("c%s ",psamp->mode_clamped_release ? "+" : "." );

/*		gotoxy(1,j);
		cprintf("%d/%d",psamp->start_fraction,psamp->start_fraction);
		gotoxy(8,j);
		cprintf("%d",psamp->sample_rate);
		gotoxy(16,j);
		cprintf("%d(%d)%d",psamp->low_frequency,psamp->root_frequency,psamp->high_frequency);
		gotoxy(40,j);
		cprintf("%d",psamp->tune);
		gotoxy(48,j);
		cprintf("%d(%d)",psamp->scale_factor,psamp->scale_frequency);
		*/
		j+= 3;
		psamp= psamp->next;
	}


	getch();
	clrscr();
//	initnote();
																// Piano-playing input loop
	while(r != 27) {
		for(i = 0; i < 17; i++) {
			gotoxy(1,i+3);
			cprintf("%d] %d,%d   ",i,notehandle[i],notedelay[i]);
			if(notehandle[i]) {
				notedelay[i]--;
				if(notedelay[i] < 1) {
					notedelay[i] = 0;
					NoteCommand(notehandle[i],v_stop);
					notehandle[i] = 0;
				}
			}
		}
		gotoxy(40,5);
		cprintf("Note base: C-%d  ", notebase);
		gotoxy(40,6);
		cprintf("Clock: %d  ",vclock);
		gotoxy(40,7);
		ohead = (double)DSP_overhead/1.193/(1000000.0/(VIDEOREFRESH*4.0))*100.0;
		averagedohead *=.95;
		averagedohead += ohead/20.0;
		cprintf("Overhead: %.2lf  ",averagedohead);
		gotoxy(40,8);
		cprintf("  (raw): %d  ",DSP_overhead);

		gotoxy(1,22);
		cprintf("<> change the note base  \n");

		if(kbhit()) {
			r = getch();
			delay = 0;
			switch(r) {
			case 'q': donote = 0; delay = 10; break;
			case 'Q': donote = 0; delay = 9999; break;
			case '2': donote = 1; delay = 10; break;
			case '@': donote = 1; delay = 9999; break;
			case 'w': donote = 2; delay = 10; break;
			case 'W': donote = 2; delay = 9999; break;
			case '3': donote = 3; delay = 10; break;
			case '#': donote = 3; delay = 9999; break;
			case 'e': donote = 4; delay = 10; break;
			case 'E': donote = 4; delay = 9999; break;
			case 'r': donote = 5; delay = 10; break;
			case 'R': donote = 5; delay = 9999; break;
			case '5': donote = 6; delay = 10; break;
			case '%': donote = 6; delay = 9999; break;
			case 't': donote = 7; delay = 10; break;
			case 'T': donote = 7; delay = 9999; break;
			case '6': donote = 8; delay = 10; break;
			case '^': donote = 8; delay = 9999; break;
			case 'y': donote = 9; delay = 10; break;
			case 'Y': donote = 9; delay = 9999; break;
			case '7': donote = 10; delay = 10; break;
			case '&': donote = 10; delay = 9999; break;
			case 'u': donote = 11; delay = 10; break;
			case 'U': donote = 11; delay = 9999; break;
			case 'i': donote = 12; delay = 10; break;
			case 'I': donote = 12; delay = 9999; break;
			case '9': donote = 13; delay = 10; break;
			case '(': donote = 13; delay = 9999; break;
			case 'o': donote = 14; delay = 10; break;
			case 'O': donote = 14; delay = 9999; break;
			case '0': donote = 15; delay = 10; break;
			case ')': donote = 15; delay = 9999; break;
			case 'p': donote = 16; delay = 10; break;
			case 'P': donote = 16; delay = 9999; break;
			case ',':
			case '<':
				notebase--;
				if(notebase < 0) notebase = 0;
				break;
			case '.':
			case '>':
				notebase++;
				if(notebase >9) notebase = 9;
				break;
			default:
				break;
			}

			if(delay) {
				if(notehandle[donote]) NoteCommand(notehandle[donote],v_remove);
				notehandle[donote] = PlayNote(donote+notebase*12+12,testpatch);
				notedelay[donote] = delay;
			}

		}
	}




}


/**************************************************************************
	int memcheck( void )

	DESCRIPTION:

**************************************************************************/
int memcheck( void )
{
	 struct _heapinfo hi;

	 hi._pentry = NULL;
	 printf( "   Size        Status\n" );
	 printf( "   ----        ------\n" );
	 while( _heapwalk( &hi ) == _HEAPOK )
	 printf( "   %7u    %s\n", hi._size, hi._useflag ? "free" : "used" );

   return 0;
}

