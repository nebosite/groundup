

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
#include "vatfree.h"

																	// function prototypes
void dspdemo(void);
void moddemo(void);
void s3mdemo(void);
void vcprintf(CHAR *string,...);
void usage(char *arg0);

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
extern WORD         dsp_vers;
extern WORD         vsync_toolong;
extern SHORT        sounds_in_queue;
extern BYTE         defaultpatchmap[16];
extern CHAR         vatdebugstring[];
extern LONG     		debugnum;
extern SHORT				mod_currenttick;
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

CHAR hexchar[16] = {"0123456789ABCDEF"};  //  hexidecimal character list

CHAR errstring[256];
WAVE *sound1,*sound2,*aha,*rumble;
FILE *diagoutput= NULL;
DWORD memleft;
MOD VFAR *mymod = NULL;
S3M VFAR *mys3m = NULL;
CHAR midfilename[255] = {"bach.mid"};
CHAR modfilename[255] = {"cutdry.mod"};
CHAR s3mfilename[255] = {"class_9a.s3m"};
static CHANNEL      VFAR *chan;
int flushearly = 0,mysamplerate = 11000;

/**************************************************************************
	void main()

	DESCRIPTION:   Handles the main menu and sets things up

**************************************************************************/
void main(SHORT argc,CHAR *argv[])
{
	SHORT i= 0,k;
	CHAR r = 0,twirl[6]  = "|/-\\";
	LONG mycore,s3mmem,j;


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

																				// Load MOD file
	mymod = LoadMod(modfilename,(CHAR *)errstring);
	if(!mymod) {
		printf("LoadMod err: %s\n",errstring);
	}
	else mymod->repeatmusic = -1;

	s3mmem = farcoreleft();
																				// Load S3M file
	mys3m = LoadS3M(s3mfilename,(CHAR *)errstring);
	if(!mys3m) {
		printf("LoadS3M err: %s\n",errstring);
	}
	else mys3m->repeatmusic = -1;
	printf("S3M Memory change: %d Kb", (s3mmem - farcoreleft())/1000);
	getch();
																			// Grab a keystroke if  there

																				// were any errors.
	if(!sound1 || !sound2 || !aha || !rumble ||!mymod || !mys3m) {
		printf("Press any key\n");
		getch();
	}


	memleft = farcoreleft();              // Keep a tab on memory for debugging
																				// purposes.
	if(SBSetUp()) {
		SetSampleRate(mysamplerate);



		GoVarmint();                            // Install  Varmint's tools


		while(kbhit()) getch();
		while(r != 'Q') {                       // Main input loop

			clrscr();                             // CLear screen and draw menu

			textcolor(WHITE);
			gotoxy(20,4);
			vcprintf("MIDI-free demo:  Varmint's Audio Tools (%s)\n\n",VAT_VERSION);
			textcolor(YELLOW);
			gotoxy(35,8);
			vcprintf("1) Sounds");
			gotoxy(35,9);
			vcprintf("2) MOD");
			gotoxy(35,10);
			vcprintf("3) S3M");
			gotoxy(35,11);
			vcprintf("4) Reload MOD");
			gotoxy(35,12);
			vcprintf("5) Reload S3M");
			gotoxy(35,17);
			vcprintf("Q) quit");


			while(!kbhit()) {                     // Draw a twirling thing while
																						// we wait for a keypress.
				textcolor(LIGHTRED);
				gotoxy(40,15);
				vcprintf("%c",twirl[++i%4]);
				MilliDelay(50);
			}
			r = toupper(getch());                 // grab some input

			if(r == '1') dspdemo();
			else if(r == '2') moddemo();
			else if(r == '3') s3mdemo();
			else if(r == '4') {
																							// Load MOD file
				FreeMod(mymod);
				mymod = LoadMod("cutdry.mod",(CHAR *)errstring);
				if(!mymod) {
					printf("LoadMod err: %s\n",errstring);
				}
			}
			else if(r == '5') {
																							// Load S3M file
				FreeS3M(mys3m);
				mys3m = LoadS3M(s3mfilename,(CHAR *)errstring);
				if(!mys3m) {
					printf("LoadS3M err: %s\n",errstring);
				}
			}
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
	if(mymod) 		FreeMod(mymod);
	if(mys3m) 		FreeS3M(mys3m);


	gotoxy(1,24);
	textcolor(LIGHTGRAY);
	_setcursortype(_NORMALCURSOR);           // Brings cursor back
}


/**************************************************************************
	void usage(char *arg0)

	DESCRIPTION:

**************************************************************************/
void usage(char *arg0)
{
	printf("Usage: vatfree -s3m [s3mname] -mod [modname] -rate [hz]\n");
	exit(1);
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
				if(chan[i].effect != 14)
						 vcprintf("%s       ",effect_primary[chan[i].effect]);
				else vcprintf("%s (E)      ",effect_secondary[chan[i].x]);
			}
			else vcprintf("                  ");

			gotoxy(42,18+i);
			vcprintf("%ld",chan[i].period);

			gotoxy(52,18+i);
			vcprintf("%d",chan[i].volume);
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
