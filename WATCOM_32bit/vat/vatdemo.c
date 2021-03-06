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
#include <graph.h>
#include "vat.h"
#include "compat.h"
#include "doink.h"
#include "wooeep.h"
#include "rumble.h"

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
  "Feedback / Algorithm (oper 1&2)",
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
      mysamplerate = (DWORD)atoi(argv[i]);
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

  _setcursortype(_NOCURSOR);             // eliminates flashing text

                                         // Load up our sound effects
  sound1 = doink;
  if(!sound1) printf("LoadWave err: %s\n",errstring);

  sound2 = wooeep;
  if(!sound2) printf("LoadWave err: %s\n",errstring);

  aha = LoadWave("aha.wav",errstring);
  if(!aha) printf("LoadWave err: %s\n",errstring);

  rumble_sound = rumble;
  if(!rumble_sound) printf("LoadWave err: %s\n",errstring);

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
  if(!sound1 || !sound2 || !aha || !rumble_sound || !bachmidi ||!mymod || !mys3m) {
    printf("Press any key\n");
    getch();
  }

  introtext();
  diagnostics();

                                       // This is a little snippet of code
                                       // That adds useful info to the
                                       // Survey.txt file.
  if(diagoutput) {
    if(!sound1 || !sound2 || !aha) {
      fprintf(diagoutput,"Error loading sounds\n");
    }
    fflush(diagoutput);
    fclose(diagoutput);
    diagoutput = NULL;
  }
  getch();

//  if(SBSetUp(mysamplerate,70)) {
  if (VATStartUp (mysamplerate, 70, v_true, v_detect)) {

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

//    GoVarmint();                            // Install  Varmint's tools

    //sb_intro();                             // Get someone's attention

    while(kbhit()) getch();
    while(r != 'Q') {                       // Main input loop

      clrscr();                             // Clear screen and draw menu

      textcolor(WHITE);
      gotoxy(20,4);
      vatcprintf("Demonstration:  Varmint's Audio Tools (%s)\n\n",VAT_VERSION);
      textcolor(YELLOW);
      gotoxy(35,6);
      vatcprintf("1) FM voice");
      gotoxy(35,7);
      vatcprintf("2) MIDI");
      gotoxy(35,8);
      vatcprintf("3) Sounds");
      gotoxy(35,9);
      vatcprintf("4) MOD");
      gotoxy(35,10);
      vatcprintf("5) S3M");
      gotoxy(35,11);
      vatcprintf("6) DEBUGGING");
      gotoxy(35,12);
      vatcprintf("7) INTRO");
      gotoxy(35,17);
      vatcprintf("Q) quit");

      textcolor(LIGHTMAGENTA);
      gotoxy(20,20);
      vatcprintf("Authors: Bryan Wilkins & Eric Jorgenson");
      gotoxy(27,21);
      vatcprintf("VAT is a Ground Up product");
      gotoxy(27,23);
      vatcprintf("(http://www.groundup.com)");

      while(!kbhit()) {                     // Draw a twirling thing while
                                            // we wait for a keypress.
        textcolor(LIGHTRED);
        gotoxy(40,15);
        vatcprintf("%c",twirl[++i%4]);
        MilliDelay(50);
      }
      r = toupper(getch());                 // grab some input

      if(r == '1') fmdemo();                // Do something with it
      else if(r == '2') mididemo();
      else if(r == '3') dspdemo();
      else if(r == '4') moddemo();
      else if(r == '5') s3mdemo();
      else if(r == '6') debugoptions();
      else if(r == '7') sb_intro();
    }
//    DropDeadVarmint();                     // Release Varmint's interrupt
//    SBCleanUp();                           // Clean house before we go.
    VATShutDown ();
    textcolor(_NORMALCURSOR);
    clrscr();                               // Clear the screen
  }
  else {
    printf("SB_Setup returned this error: %s \n",errname[sberr]);
  }

  if(sound1)    FreeWave(sound1);              // Free up used memory
  if(sound2)    FreeWave(sound2);
  if(aha)       FreeWave(aha);
  if(rumble_sound)    FreeWave(rumble_sound);
  if(bachmidi)  FreeMidi(bachmidi);
  if(mymod)     FreeMod(mymod);
  if(mys3m)     FreeS3M(mys3m);

                                           // Dump debug info to survey.txt
  diagoutput = fopen("survey.txt","a");
  if(diagoutput) {
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
  s3mdemo(void)

  DESCRIPTION: Demo for playing s3m files

**************************************************************************/
void s3mdemo(void)
{
  SHORT i,playme = 0, volume, tempo;
  CHAR r=0;
  DWORD count=0,total=0;
  SHORT mychan = 0;
  LONG mask;
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
  PlayS3M (mys3m);
  S3MCommand (v_stop);

  DSP_overhead = 1;                     // Turn on overhead checking

  textcolor(WHITE);
  gotoxy(4,1);
  vatcprintf("S3M demo menu");                 // Draw the menu
  textcolor(CYAN);
  gotoxy(41,1);
  vatcprintf("1 - Start");
  gotoxy(41,2);
  vatcprintf("2 - Stop");
  gotoxy(41,3);
  vatcprintf("3 - Pause");
  gotoxy(61,1);
  vatcprintf("4 - Resume");
  gotoxy(61,2);
  vatcprintf("5 - Rewind");
  gotoxy(4,3);
  vatcprintf("V,v   - Change volume");
  gotoxy(4,4);
  vatcprintf("T,t   - Change tempo");
  gotoxy(4,5);
  vatcprintf("<Spc> - Play Current sample");
  gotoxy(4,6);
  vatcprintf("S     - Select sample");
  gotoxy(61,3);
  vatcprintf("Q - Quit");

  textcolor(LIGHTMAGENTA);
  gotoxy(2,8);
  vatcprintf("S3M Title: %s  (From file: %s)",mys3m->title,s3mfilename);

  textcolor(LIGHTGRAY);

  gotoxy(2,10);                                    // Running stats labels
  vatcprintf("Pos left:  ");
  gotoxy(2,11);
  vatcprintf("Pos spot:  ");
  gotoxy(2,13);
  vatcprintf("CPU Overhead: ");

  gotoxy(29,3);                                     // SHow current volume
  volume = S3MSetting (v_volume, GET_SETTING);
  vatcprintf("(%d)  ", volume);
  gotoxy(29,4);                                     // Show the tempo
	vatcprintf("(%d)  ", tempo);
  gotoxy(29,6);                                    // Show current sample
  vatcprintf("%d] (%s)          ",playme+1,mys3m->sample_name[playme]);


  while(toupper(r) != 'Q') {                        // Input Loop
		tempo = S3MSetting (v_rate, GET_SETTING);
		if(kbhit()) {                                   // Keyboard have input?
      r = getch();                                  // Grab the key
      if(r == 'v') {                                // Volume louder
        volume = S3MSetting (v_volume, volume-1);
        textcolor(LIGHTGRAY);
        gotoxy(29,3);                               // SHow current volume
        vatcprintf("(%d)  ", volume);
      }
      else if(r == 'V') {                           // Volume softer
        volume = S3MSetting (v_volume, volume+1);
        textcolor(LIGHTGRAY);
        gotoxy(29,3);                               // SHow current volume
        vatcprintf("(%d)  ", volume);
      }
      else if(r == 'T') {                           // Tempo faster
				tempo = S3MSetting (v_rate, tempo * .8 );
				textcolor(LIGHTGRAY);
				gotoxy(29,4);                               // Show the tempo
				vatcprintf("(%d)  ", tempo);
			}
			else if(r == 't') {                           // Tempo slower
				tempo = S3MSetting (v_rate, tempo * 1.25);
        textcolor(LIGHTGRAY);
        gotoxy(29,4);                               // Show the tempo
        vatcprintf("(%d)  ", tempo);
      } else if (r == '1')
        S3MCommand(v_play);
      else if (r == '2')
        S3MCommand(v_stop);
      else if (r == '3')
        S3MCommand(v_pause);
      else if (r == '4')
        S3MCommand(v_resume);
      else if (r == '5')
        S3MCommand(v_rewind);
      else if (r == 'i') {                           // change channel by -1
        mychan--;
        if (mychan < 0)
          mychan = mys3m->channelnum-1;
      } else if (r == 'k') {                           // change channel by 1
        mychan++;
        if (mychan >= mys3m->channelnum)
          mychan = 0;
      } else if (toupper(r) == 'O') {
        mask = S3MChannelMask (GET_SETTING);
        if (mask & (1<<mychan))
          mask &= ~(1<<mychan);
        else
          mask |= (1<<mychan);
        S3MChannelMask (mask);
      }
      else if(toupper(r) == 'S') {                  // Cycle through samples
        playme++;
        while(!mys3m->sdata[playme]) {
          playme++;
          if(playme>99) playme = 0;
        }
        textcolor(LIGHTGRAY);
        gotoxy(29,6);                              // Show current sample
        vatcprintf("%d] %s {%lu}                                              ",
                  playme+1,mys3m->sample_name[playme],mys3m->slength[playme]);
      }                                             // Play current sample
      else if(r == ' ') {
        iwave.data = mys3m->sdata[playme];
        iwave.chunk_size = mys3m->slength[playme];
        PlaySound(&iwave,0,v_plain);
      }
    }

    gotoxy(29,4);                               // Show the tempo
    vatcprintf ("(%d)  ", S3MSetting (v_rate, GET_SETTING));

    for (i=0; i<mys3m->channelnum; i++) {
      textcolor(WHITE);
      gotoxy(28,9+i);
      if(mychan != i) vatcprintf(" ");
      else vatcprintf(">");

      textcolor (LIGHTGRAY);
      gotoxy (30,9+i);
      vatcprintf ("%d] ",i+1);

      textcolor (YELLOW);
      if (!chan[i].volume || *chan[i].pos > chan[i].end)
        textcolor (BROWN);
      if (S3MStatus () == v_stopped || S3MStatus () == v_nonexist)
        textcolor (BROWN);
      mask = S3MChannelMask (GET_SETTING);
      if (!(mask & (1<<i)))
        textcolor (BLUE);

      gotoxy(33,9+i);                   // Print sample number
      if(*chan[i].pos <= chan[i].end)
        vatcprintf("%d",(SHORT)chan[i].sample_number+1);
      else vatcprintf("   ");

      gotoxy(36,9+i);                   // Show current effect
      if(*chan[i].pos <= chan[i].end) {
        vatcprintf("%s       ",s3meffects[chan[i].effect]);
      }
      else vatcprintf("                  ");

      gotoxy(56,9+i);                   // Draw tuning period and volume
      vatcprintf("%d  ",chan[i].period);

      gotoxy(65,9+i);
      vatcprintf("%d  ",chan[i].volume);
      gotoxy(70,9+i);
      vatcprintf("%d  ",chan[i].pinc);
    }
                                            // Show where we are in the mod
    textcolor(WHITE);
    gotoxy(12,10);
    vatcprintf("%d ",mys3m->orders - s3m_order);
    gotoxy(12,11);
    vatcprintf("%ld ",(long)(s3m_pstop-s3m_pattern)/s3m_divbytes);

                                            // Show the CPU overhead
    count++;
    total+=DSP_overhead;
    if(count == 10) {
      oh = PercentOverhead((WORD)(total/count))/10.0;
      gotoxy(16,13);
      vatcprintf("%.2lf%% ",oh);
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
  SHORT i,playme = 0, volume, tempo;
  CHAR r=0;
  DWORD count=0,total=0;
  LONG mask=(1<<4)-1;
  double oh;
  static WAVE iwave;

  iwave.id= -10000000L;                 // Fill dummy wave struct
  iwave.data = NULL;
  iwave.chunk_size = 0;
  iwave.sample_size = 0;
  iwave.next = NULL;
  iwave.head = &iwave;

  clrscr();                             // Clear the screen

  chan = ModChannels();
  PlayMod (mymod);
  ModCommand (v_stop);


  DSP_overhead = 1;                     // Turn on overhead checking

  textcolor(WHITE);
  gotoxy(4,1);
  vatcprintf("MOD demo menu");                 // Draw the menu
  textcolor(CYAN);
  gotoxy(4,3);
  vatcprintf("1       - Start music");
  gotoxy(4,4);
  vatcprintf("2       - Stop music");
  gotoxy(4,5);
  vatcprintf("3       - Pause music");
  gotoxy(4,6);
  vatcprintf("4       - Resume music");
  gotoxy(4,7);
  vatcprintf("5       - Rewind music");
  gotoxy(4,8);
  vatcprintf("V,v     - Change music volume");
  gotoxy(4,9);
  vatcprintf("T,t     - Change music tempo");
  gotoxy(4,10);
  vatcprintf("S       - Select sample");
  gotoxy(4,11);
  vatcprintf("<Space> - Play Current sample");
  gotoxy(4,13);
  vatcprintf("Q       - Quit");

  textcolor(LIGHTMAGENTA);
  gotoxy(2,16);
  vatcprintf("MOD Title: %s ",mymod->title);

  for(i = 0; i < 4; i++) {
      gotoxy(2,18+i);                               // Print Channel labels
      vatcprintf("CHANNEL%d:",i+1);
  }

  textcolor(LIGHTGRAY);

  gotoxy(40,14);                                    // Running stats labels
  vatcprintf("Positions left:  ");
  gotoxy(40,15);
  vatcprintf("Position spot:  ");
  gotoxy(4,23);
  vatcprintf("CPU Overhead: ");

  gotoxy(35,8);                                     // SHow current volume
  volume = ModSetting (v_volume, GET_SETTING);
  vatcprintf("VOLUME: %d  ", volume);
  gotoxy(35,9);                                     // Show the tempo
	vatcprintf("TEMPO: %d  ", tempo);
  gotoxy(35,10);                                    // Show current sample
  vatcprintf("%d] (%s)          ",playme+1,mymod->sample_name[playme]);

  while(toupper(r) != 'Q') {                        // Input Loop
		tempo = ModSetting (v_rate, GET_SETTING);
		if(kbhit()) {                                   // Keyboard have input?
      r = getch();                                  // Grab the key
      if(r == 'v') {                                // Volume louder
        volume = ModSetting (v_volume, volume-1);
        textcolor(LIGHTGRAY);
        gotoxy(35,8);                               // SHow current volume
        vatcprintf("VOLUME: %d  ", volume);
      }
      else if(r == 'V') {                           // Volume softer
        volume = ModSetting (v_volume, volume+1);
        textcolor(LIGHTGRAY);
        gotoxy(35,8);                               // SHow current volume
        vatcprintf("VOLUME: %d  ", volume);
      }
      else if(r == 'T') {                           // Tempo faster
				tempo = ModSetting (v_rate, tempo * 0.75);
        textcolor(LIGHTGRAY);
        gotoxy(35,9);                               // Show the tempo
        vatcprintf("TEMPO: %d  ", tempo);
      }
      else if(r == 't') {                           // Tempo slower
				tempo = ModSetting (v_rate, tempo * 1.33);
        textcolor(LIGHTGRAY);
        gotoxy(35,9);                               // Show the tempo
        vatcprintf("TEMPO: %d  ", tempo);
      } else if (r == '1')
        ModCommand (v_play);
      else if (r == '2')
        ModCommand (v_stop);
      else if (r == '3')
        ModCommand (v_pause);
      else if (r == '4')
        ModCommand (v_resume);
      else if (r == '5')
        ModCommand (v_rewind);
      else if (r == '!') {
        if (mask & (1<<0))
          mask &= ~(1<<0);
        else
          mask |= (1<<0);
        ModChannelMask (mask);
      } else if (r == '@') {
        if (mask & (1<<1))
          mask &= ~(1<<1);
        else
          mask |= (1<<1);
        ModChannelMask (mask);
      } else if (r == '#') {
        if (mask & (1<<3))
          mask &= ~(1<<3);  // reversed for stereo
        else
          mask |= (1<<3);
        ModChannelMask (mask);
      } else if (r == '$') {
        if (mask & (1<<2))
          mask &= ~(1<<2);
        else
          mask |= (1<<2);
        ModChannelMask (mask);
      } else if(toupper(r) == 'S') {                // Cycle through samples
        playme++;
        while(!mymod->sdata[playme]) {
          playme++;
          if(playme>31) playme = 0;
        }
        textcolor(LIGHTGRAY);
        gotoxy(35,10);                              // Show current sample
        vatcprintf("                                      ",playme+1,mymod->sample_name[playme]);
        gotoxy(35,10);                              // Show current sample
        vatcprintf("%d] (%s)   ",playme+1,mymod->sample_name[playme]);
      }                                             // Play current sample
      else if(r == ' ') {
        iwave.data = mymod->sdata[playme];
        iwave.chunk_size = mymod->slength[playme];
        PlaySound(&iwave,0,v_plain);
      }
    }

    gotoxy(35,9);                               // Show the tempo
    vatcprintf("TEMPO: %d  ", ModSetting (v_rate, GET_SETTING));

    for(i = 0; i < 4; i++) {
      textcolor(YELLOW);


      gotoxy(16,18+i);                   // Print sample number
      if(i==2)gotoxy(16,18+3);           //
      if(i==3)gotoxy(16,18+2);           // These 2 lines are for stereo support
                                         // I load channel 3 and 4 reversed for
                                         // speed reasons.
      if(*chan[i].pos <= chan[i].end) {
        vatcprintf("%d",(SHORT)chan[i].sample_number);
      }
      else vatcprintf("   ");

      textcolor(YELLOW);

      gotoxy(22,18+i);
      if(i==2)gotoxy(22,18+3);           //
      if(i==3)gotoxy(22,18+2);           //
      if(!chan[i].volume || *chan[i].pos > chan[i].end ||
         ModStatus () == v_stopped || ModStatus () == v_nonexist)
        textcolor(BROWN);

      if(*chan[i].pos <=  chan[i].end  ) {
        if(chan[i].effect != 14) vatcprintf("%s       ",effect_primary[chan[i].effect]);
        else vatcprintf("%s (E)      ",effect_secondary[chan[i].x]);
      }
      else vatcprintf("                  ");

      gotoxy(42,18+i);
      if(i==2)gotoxy(42,18+3);           //
      if(i==3)gotoxy(42,18+2);           //
      vatcprintf("%d",chan[i].period);

      gotoxy(52,18+i);
      if(i==2)gotoxy(52,18+3);           //
      if(i==3)gotoxy(52,18+2);           //
      vatcprintf("%d",chan[i].volume);
    }
                                            // Show where we are in the mod
    textcolor(WHITE);
    gotoxy(57,14);
    vatcprintf("%d ",mymod->num_positions - mod_tablepos);
    gotoxy(57,15);
    vatcprintf("%ld ",(long)(mod_pstop-mod_pattern)/16);

    count++;
    total+=DSP_overhead;
    if(count == 10) {
      oh = PercentOverhead((WORD)(total/count))/10.0;
      gotoxy(18,23);
      vatcprintf("%.2lf%% ",oh);
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
  int i;
  double oh;

  DSP_overhead = 1;                           // turn on overhead checking

  clrscr();                                   // Clear screen and draw a menu
  textcolor(GREEN);
  gotoxy(10,8);
  vatcprintf("Sound effects demo menu");
  textcolor(YELLOW);
  gotoxy(10,10);
  vatcprintf("       1,2,3 - Basic play demo");
  gotoxy(10,11);
  vatcprintf("       4,5,6 - Frequency correction demo");
  gotoxy(10,12);
  vatcprintf("       7,8,9 - Panning demo");
  gotoxy(10,14);
  vatcprintf("           L - Toggle Looping Demo (rumble sound)");
  gotoxy(10,15);
  vatcprintf("           D - Frequency and Volume Demo");
  gotoxy(10,16);
  vatcprintf("           C - Chain Demo");
  gotoxy(10 ,18);
  vatcprintf("           Q - Quit");
  gotoxy(1,20);
  textcolor(CYAN);
  vatcprintf("    Fancy sounds use up more CPU overhead than plain sounds,\r\n");
  vatcprintf("but you can control the volume and frequency of fancy sounds.\n");
  vatcprintf("Pan sounds you can Pan if your card is stereo.");

  gotoxy(1,1);
  vatcprintf("CPU OVERHEAD: \r\nSOUNDS IN QUEUE: ");
  textcolor(WHITE);
  while(toupper(r) != 'Q') {         // input loop
    while(!kbhit()) {                // Wait for keystroke
      MilliDelay(7);
      tot+= DSP_overhead;            // take an average every 40 interrupts
      num++;
      if(num == 10) {
        gotoxy(15,1);
        oh = PercentOverhead((WORD)(tot/num))/10.0;
        vatcprintf("%2.2lf%%  ",oh); // Show overhead
        gotoxy(19,2);
        vatcprintf("%d \n",sounds_in_queue);       // Show # sounds playing
        num = 0;
        tot = 0;
      }
    }
    r = getch();                      // Get keystroke and act accordingly
                                      // Simple play commands
    switch (r) {
    case '1':
      PlaySound (sound1, 0, v_plain);
      break;
    case '2':
      PlaySound (sound2, 0, v_plain);
      break;
    case '3':
      PlaySound (aha, 0, v_plain);
      break;
    case '4':
      PlaySound (sound1, 0, v_fancy);
      break;
    case '5':
      PlaySound (sound2, 0, v_fancy);
      break;
    case '6':
      PlaySound (aha, 0, v_fancy);
      break;
    case '7':
      WaveSetting (PlaySound (aha, 0, v_pan), v_panpos, 1);
      break;
    case '8':
      WaveSetting (PlaySound (aha, 0, v_pan), v_panpos, 30);
      break;
    case '9':
      WaveSetting (PlaySound (aha, 0, v_pan), v_panpos, 59);
      break;
    case 'l':
    case 'L':      // Looping demo- loop a rumble sound
      if(!loop) {
        loopid = PlaySound (rumble_sound, 0, v_fancy);
        WaveSetting (loopid, v_repeat, -1);
        WaveSetting (loopid, v_volume, 32);
        loop = v_true;
      } else {
        WaveCommand (loopid, v_stop);
        loop = v_false;
      }
      break;
    case 'd':
    case 'D':      // Volume/frequncy demo
      for (i=7; i<64; i+=8) {       // Volume quiet->loud
        id = PlaySound (sound1, 0, v_fancy);
        WaveSetting (id, v_volume, i);
        gotoxy (1,5);
        vatcprintf ("Volume: %d ", i);
        while (WaveStatus (id) != v_nonexist);
        if (kbhit ()) {
          getch ();
          i = 64;
        }
      }
      for (i=5000; i<=45000; i+=5000) {       // Frequency slow->fast
        id = PlaySound (sound1, 0, v_fancy);
        WaveSetting (id, v_rate, i);
        gotoxy (1,5);
        vatcprintf ("Rate: %d   ", i);
        while (WaveStatus (id) != v_nonexist);
        if (kbhit ()) {
          getch ();
          i = 45001;
        }
      }
      gotoxy (1,5);
      vatcprintf ("                 ");    // Hide the status line
      break;
    case 'c':
    case 'C':      // Chain demo
      id = PlaySound (sound1, 0, v_fancy);
      id = WaveChain (id, sound2, v_fancy);
      WaveChain (id, aha, v_fancy);
      break;
    }
  }
}

/**************************************************************************
  void sb_intro(void)

  DESCRIPTION:  Cool introduction sith sound blaster music and sounds

**************************************************************************/
void sb_intro(void)
{
  LONG handle;
  SHORT i,j;
  double fr;
  WORD f;

  clrscr ();
  gotoxy (18,12);
  textcolor (LIGHTGRAY);
  vatcprintf ("Varmint's Audio Tools  (Version: %s)",VAT_VERSION);
  textcolor (RED);
  MilliDelay (500);

                                      // Cool introduction
  for (i=0; i<3; i++) {               // "Audio Hardware Activated"
    WaveSetting (PlaySound (aha, 0, v_fancy), v_volume, 43-i*20);
    MilliDelay (300);
  }

  for (i=0; i<8; i++) {               // initialize music voices
    FMKeyOff (i);
    FMSetVoice (i, inst[vints[i]]);
    FMFrequency (i, startfreq[i]);
    FMVolume (i, 0);
    FMKeyOn (i);
  }

  for (i=0; i<1000; i++) {            // morph a big chord
    if (kbhit ())
      i = 1000;
    fr = i/1000.0;
    for (j=0; j<8; j++) {
      gotoxy (j*10+1,10);
      f = startfreq[j] + ((double)endfreq[j]-(double)startfreq[j]) * fr;
      vatcprintf ("%X  ", f);
//      FMKeyOff (j);
      FMFrequency (j, f);
      FMVolume (j, fr*0x3f);
      FMKeyOn (j);
    }
    MilliDelay(4);
  }

  if (!kbhit ()) {
    for (i=0; i<8; i++) {             // Make sure all the notes are right
      FMKeyOff (i);
      FMFrequency (i, endfreq[i]);
      FMKeyOn (i);
    }
    for (i=63; i>=0; i--) {           // quiet down slowly
      if (kbhit ())
        i = 0;
      for (j=0; j<8; j++)
        FMVolume (j, i);
      MilliDelay (i*2+40);
    }
  }

  for (i=0; i<9; i++) {               // Silence them all
    FMVolume (i, 0);                  // volume off
    FMSetVoice (i, inst[0]);          // this instrument has a decay, so it
                                       // gets all the way quiet
    FMFrequency (i, 1);               // Low freq = quiet
  }

  if (kbhit ())
    getch ();
}

/**************************************************************************
  void mididemo(void)

  DESCRIPTION: Example function that loads and "plays" a  midi file

**************************************************************************/
void mididemo(void)
{
  SHORT i, volume, tempo;
  CHAR r=0;
  static BYTE *def_patchmap=NULL;

  if (!def_patchmap)
    def_patchmap = MidiPatchmap (GET_PATCHMAP);

  clrscr();                                   // clear screen

  PlayMidi (bachmidi);
  MidiCommand (v_stop);
  midi_fmpatchmap = myfmpatchmap;

  textcolor (MAGENTA);
  gotoxy (30,2);
  vatcprintf ("MIDI demo menu");
  textcolor (CYAN);
  gotoxy (30,3);
  vatcprintf ("1   - Start music");
  gotoxy (30,4);
  vatcprintf ("2   - Stop music");
  gotoxy (30,5);
  vatcprintf ("3   - Pause music");
  gotoxy (30,6);
  vatcprintf ("4   - Resume music");
  gotoxy (30,7);
  vatcprintf ("5   - Rewind music");
  gotoxy (30,8);
  vatcprintf ("V,v - Change music volume");
  gotoxy (30,9);
  vatcprintf ("T,t - Change music tempo");
  gotoxy (30,10);
  vatcprintf ("F   - Toggle FM output: ");
  if (FMStatus () == v_started)
    vatcprintf ("ON  ");
  else
    vatcprintf ("OFF ");
  gotoxy (30,11);
  vatcprintf ("U   - Toggle MPU output: ");
  if (MPUStatus () == v_started)
    vatcprintf ("ON  ");
  else
    vatcprintf ("OFF ");
  gotoxy (30,12);
  vatcprintf ("P   - Change MPU port address: %X", mpu_addr);
  gotoxy (30,13);
  vatcprintf ("A   - Toggle MIDI patchmap ");
  if (MidiPatchmap (GET_PATCHMAP) == def_patchmap)
    vatcprintf ("(16 channel)");
  else
    vatcprintf ("( 3 channel)");
  gotoxy (30,16);
  vatcprintf ("Q   - Quit");

  textcolor (LIGHTMAGENTA);
  gotoxy (3,18);
  vatcprintf (
  "- SB16 users: If MPU401 output causes a lockup, you will need to run the");
  gotoxy (3,19);
  vatcprintf (
  "  included patch from creative labs before running the demo. Type this at");
  gotoxy (3,20);
  vatcprintf (
  "  the DOS prompt:   mpufix /e");
  gotoxy (3,21);
  vatcprintf (
  "- If MPU401 output does not produce any sounds on your MIDI device, try");
  gotoxy (3,22);
  vatcprintf (
  "  toggling the MIDI patchmap.");


  while(toupper(r) != 'Q') {                  // MAIN LOOP
    gotoxy(1,15);                             // print temppo and volume stats
    textcolor(WHITE);
    volume = MidiSetting (v_volume, GET_SETTING);
    vatcprintf("Music Volume: %d  ", volume);
    gotoxy(1,16);
    tempo = MidiSetting (v_rate, GET_SETTING);
    vatcprintf("Music Tempo:  %d ", tempo);


    while (!kbhit ()) {                       // handle the keyboard
      if (MPUStatus () != v_nonexist) {
        gotoxy (1,1);
        textcolor (GREEN);
        if (MPUStatus () == v_unavail)
          vatcprintf ("MPU Init Failed   ");
        else
          vatcprintf ("MPU Init Worked   ");
      }
      for(i = 0; i < 9; i++) {
        gotoxy(1,5+i);
        if(midi_voice[i].active) textcolor(YELLOW);
        else textcolor(BROWN);
        vatcprintf("Voice %d:  %d %d %d",i,midi_voice[i].note,
                    midi_voice[i].owner_track,midi_voice[i].owner_channel);
      }
    }
    r = getch();                              // get keystroke

    if (r == '1')                             // Handle keystrokes
      MidiCommand(v_play);
    else if (r == '2')
      MidiCommand(v_stop);
    else if (r == '3')
      MidiCommand(v_pause);
    else if (r == '4')
      MidiCommand(v_resume);
    else if (r == '5')
      MidiCommand(v_rewind);
    else if (toupper(r) == 'A') {              // Toggle midi patchmap
      if (MidiPatchmap (GET_PATCHMAP) == mypatchmap)
        MidiPatchmap (NULL);
      else
        MidiPatchmap (mypatchmap);
      gotoxy(57,13);
      if (MidiPatchmap (GET_PATCHMAP) == def_patchmap)
        vatcprintf ("(16 channel)");
      else
        vatcprintf ("( 3 channel)");
    } else if (r == 'V')
      volume = MidiSetting (v_volume, volume+1);
    else if (r == 'v')
      volume = MidiSetting (v_volume, volume-1);
    else if (r == 'T')
      tempo = MidiSetting (v_rate, tempo * 1.1);
    else if (r == 't')
      tempo = MidiSetting (v_rate, tempo * 0.9);
    else if(toupper(r) == 'F') {               // Toggle output
      if (FMStatus () == v_started)
        FMDisable ();
      else
        FMEnable ();
      textcolor (CYAN);
      gotoxy (54,10);
      if (FMStatus () == v_started)
        vatcprintf ("ON  ");
      else
        vatcprintf ("OFF ");
    } else if (toupper (r) == 'U') {           // Toggle MPU output
      if (MPUStatus () != v_unavail) {
        if (MPUStatus () == v_started)
          MPUDisable ();
        else {
          MPUEnable ();
          if (MPUStatus () != v_unavail) {
            gotoxy (1,1);
            vatcprintf ("                        \n\r                      ");
          }
        }
      }
      textcolor (CYAN);
      gotoxy (55,11);
      if (MPUStatus () == v_started)
        vatcprintf ("ON   ");
      else
        vatcprintf ("OFF ");
    }
    else if(toupper(r) == 'P') {              // Change MIDI port
      gotoxy(6,24);
      vatcprintf("Enter new port address in hex values [%x]: ", mpu_addr);
      gets(errstring);
      if(strlen(errstring)) sscanf(errstring,"%x", &mpu_addr);
                                               // check for accidents
      if (mpu_addr < 0x200 || mpu_addr > 0x360) mpu_addr = 0x330;
      mpu_reset ();
      MPUEnable ();
      gotoxy(6,24);
      vatcprintf("                                                    ");
//      mpu_timeout = 0;
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

  vatcprintf("  ");
                                    // go through bits
  for(i = 7; i >= 0; i--) {
    if(getbit(byte,i)) {            // 1's are yellow
      textcolor(YELLOW);
      vatcprintf("1");
    }
    else {                          // 0's are dark grey
      textcolor(DARKGRAY);
      vatcprintf("0");
    }
  }

  textcolor(LIGHTBLUE);             // print the hex value
  vatcprintf("   %02X", byte);
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
  SHORT drawvoice = 1,rhythm = 0,vol;
  CHAR r = 0;

  vol = MidiSetting (v_volume, GET_SETTING) * 8;
  if(vol > 63) vol = 63;

  clrscr();                          // clear screen
  vatcprintf("FM demonstration screen");

  gotoxy(1,16);
  vatcprintf("IJKL = cursor movement\r\n");
  vatcprintf("<space> = toggle bit\r\n");
  vatcprintf("numbers = play notes\r\n");
  vatcprintf("v = change voice\r\n");
  vatcprintf("n = Change instrument\r\n");
  vatcprintf("r = toggle rhythm mode\r\n");
  vatcprintf("q = quit");

  _setcursortype(_SOLIDCURSOR);
  for( i = 0; i < 8; i++) {          // initialize voices
    FMSetVoice (i, inst[instrument]) ;
    FMKeyOff (i);
    FMVolume (i, 0);
  }

  cx = 53;cy = 5;                    // init cursor position

  for(i = 0; i < 11; i++) {          // print register names
    gotoxy(50-strlen(regname[i]),i+5);
    textcolor(MAGENTA);
    vatcprintf("%s",regname[i]);
  }


  while(r != 'Q') {                  // main input loop
    if(drawvoice) {
      for(i = 0; i < 11; i++) {      // display instrument data
        gotoxy(51,i+5);
        bitprint(inst[instrument][i]);
      }
      for(i = 0; i < 9; i++) {
        FMSetVoice ( i,inst[instrument]) ; // initialize new voice
      }
      drawvoice = 0;
      textcolor(LIGHTGRAY);
      gotoxy(52,3);
      vatcprintf("Instrument #%2d ",instrument);
    }

    gotoxy(cx,cy);                   // put cursor in right spot

    while(!kbhit());

    r = toupper(getch());
    if(r >= '0' && r <= '9') {
      FMKeyOff (voice);
      FMSetVoice (voice,inst[instrument]);
      FMNote (voice, (r-'0'+3) * 8) ;
      FMVolume (voice,vol);
      FMKeyOn (voice);
    }
    else if(r == 'I') {              // i,j,k,l = cursor movement
      cy--;
      if (cy < 5)
        cy = 15;
    }
    else if(r == 'K') {
      cy++;
      if (cy > 15)
        cy = 5;
    }
    else if(r == 'J') {
      cx--;
      if (cx < 53)
        cx = 60;
    }
    else if(r == 'L') {
      cx++;
      if (cx>60)
        cx = 53;
    }
    else if(r == ' ') {              // space = toggle bit
      togbit(inst[instrument][cy-5],(7-(cx-53)));
      drawvoice = 1;
    }
    else if(r == 'N') {              // I = change instrument
      instrument++;
      if(instrument > 8) instrument = 0;
      drawvoice = 1;
    }
    else if(r == 'R') {              // r = toggle rhythm mode
      if (rhythm)
        FMRhythm (v_no_rhythm);
      else
        FMRhythm (v_hihat_rhythm);
      rhythm = !rhythm;
      gotoxy (1,2);                   // tell the user
      if (rhythm)
        vatcprintf ("Rhythm Mode ON  (voices 6,7,8 only) ");
      else
        vatcprintf ("Rhythm Mode OFF                     ");
    }
    else if(r == 'V') {              //  v = change voice
      FMKeyOff (voice);
      FMVolume (voice, 0);
      voice ++;
      if (voice > 8) voice = 0;
      gotoxy (1,3);
      vatcprintf ("Voice: %d ",voice);
    }

  }
  for(i = 0; i < 9; i++) {
    FMVolume (i, 0);
  }
  FMRhythm (v_no_rhythm);

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
    _outtext(p);
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
//  textcolor(MAGENTA);
//  tprintf("------------------------------------------------------------------------------\n\r");
//  tprintf("-----------------------###-------------####-------------################# ----\n\r");
//  tprintf("------####+ ----------##+++  --------####+  -----------##+++++++++++++++  ----\n\r");
//  tprintf("----####+++  ---------##+++ --------##+++++  ---------##+++++++++++++++  -----\n\r");
//  tprintf("----#+++++++  -------##++  ---------##++++++  -------##      ++++       ------\n\r");
//  tprintf("----##+++++++  -----##++  ---------##++++++++  --------------#++ -------------\n\r");
//  tprintf("-----###+++++++ ---##++  ---------##+  #+++++++  ------------#++ -------------\n\r");
//  tprintf("-------##+++++++ -##++  ---------##++-##++++++++  -----------#++  ------------\n\r");
//  tprintf("--------###++++++++++  ---------##+++++++++++++++  ----------#++  ------------\n\r");
//  tprintf("----------##++++++++  ---------##+++++++++++++++++  ---------#+++  -----------\n\r");
//  tprintf("-----------##++++++  ----------##++        #+++++++  --------#+++  -----------\n\r");
//  tprintf("-------------##+++  ----------##+++ --------#+++++++  -------#+++  -----------\n\r");
//  tprintf("--------------##+  ARMINT'S--##++  ----------#        UDIO---#++  OOLS--------\n\r");
//  tprintf("---------------#  ----------##++  ---------------------------#  --------------\n\r");
//  tprintf("------------------------------------------------------------------------------\n\r");
  if (!fopen("survey.txt","r")){
    textcolor(LIGHTGRAY);
    vatcprintf("\nThanks for trying out VAT!\r\n");
    vatcprintf("This demo has command line options. Run as 'VATDEMO -?' for details. \r\n\n");
    textcolor(YELLOW);

    vatcprintf("Please edit the file survey.txt and return it to:  groundup@groundup.com\r\n");
    printf("\n");
    printf("You will only see this message once.");
  }
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
  printf("\nPress any key to continue...\n");
  fflush(stdout);
                                           // Write the survey
  fprintf(diagoutput,"Survey for Varmint's Audio tools.\n");
  fprintf(diagoutput,"\n");
  fprintf(diagoutput,"Please email the completed survey to groundup@groundup.com\n");
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
  vatcprintf("VAT debug options\n\r");
  textcolor(LIGHTGRAY);
  vatcprintf("The only problem seen these days with VAT is static on a very few\r\n");
  vatcprintf("systems.  If you hear static in this demo, these tests will help to\r\n");
  vatcprintf("determine the source of the static.  You will need make sure a \r\n");
  vatcprintf("MOD is playing in the background while trying these tests.\r\n");

  textcolor(LIGHTGREEN);

  gotoxy(10,7);                             // show options
  vatcprintf("1) Reverse DMA flipflop (kills static on some systems)");
  gotoxy(5,7);
  vatcprintf("%s", debug_reverseflipflop?"ON ":"OFF");
  gotoxy(10,8);
  vatcprintf("2) Static Source test. (Tests for some causes of static)");


  gotoxy(5,22);
  vatcprintf("Press a number to toggle an option, or Q to quit.");

                                           // input loop
  textcolor(WHITE);
  while(tolower(r) != 'q') {
    r = toupper(getch());
    if(r == '1') {                         // change the flipflop
      debug_reverseflipflop ^= v_true;
      gotoxy(5,7);
      if(debug_reverseflipflop) vatcprintf("ON  ");
      else vatcprintf("OFF ");
    }                                      // key/screen test
    else if(r == '2') {
      gotoxy(1,10);
                                        // clear part of the screen
      for(i = 1; i < 81; i++){
        for(j = 10; j < 21; j++) {
          gotoxy(i,j);
          vatcprintf(" ");
        }
      }
                                        // print information
      gotoxy(1,10);
      textcolor(LIGHTGRAY);
      vatcprintf("STATIC SOURCE TEST.  This will help determine if the keyboard handler\r\n");
      vatcprintf("or video card are causing static.  This test will last about\r\n");
      vatcprintf("10 seconds.  Press <SPACE> to begin...\r\n");

      while(!kbhit());                  // wait for a keystroke
                                        // begin testing
      textcolor(LIGHTMAGENTA);
      vatcprintf("\nTEST1:  Updating the screen only.\r\n");
      for(i = 0; i < 600; i++) {
        gotoxy(36,14);
        vatcprintf("%c",random(80)+32);
        MilliDelay(5);
      }
      vatcprintf("\r\nTEST2:  Checking the keyboard only.\r\n");
      for(i = 0; i < 500; i++) {
        kbhit();
        MilliDelay(5);
      }
      vatcprintf("TEST3:  No activity.\r\n");
      for(i = 0; i < 600; i++) {
        MilliDelay(5);
      }
      textcolor(LIGHTGRAY);
      vatcprintf("\nTest completed.  Did these tests have any effect on static? Please\r\n");
      vatcprintf("fill out the survey.txt file and report these results to\r\n");
      vatcprintf("groundup@groundup.com.\r\n");
    }
  }
}



CHAR vatoutstring[255];

/**************************************************************************
  void vatcprintf(CHAR *string,...)

  DESCRIPTION:  Special printf function that disables interrupts.  There is
                some concern that interrupting a printf may cause some
                systems to crash.  This is an experimental precaution.

**************************************************************************/
void vatcprintf(CHAR *string,...)
{
  va_list ap;

  _disable();

  va_start(ap, string);                  // sort out variable argument list
  vsprintf(vatoutstring,string,ap);      // dump output to a string
  _outtext(vatoutstring);            // dump string to screen
  va_end(ap);                            // clean up
  _enable();
}

/*************************************************************************
WORD random(WORD num)

DESCRIPTION:  Special random function for compatibility with watcom
**************************************************************************/

WORD random(WORD num)
{
  return(WORD)(((WORD)rand()*num)/(RAND_MAX+1));
}

