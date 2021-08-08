/********************************************************************

	FLABBERGASTED!

	Eric Jorgensen 1997

	Sounds.c

	Sound access routines

*********************************************************************/
#include <stdio.h>
#include <malloc.h>
#include <math.h>
#include <conio.h>
#include "\watcom\vat\vat.h"
#include "flabber.h"
#include "util.h"

/*

Keyboard information


 0x1:   						// KEY: Esc      									s00	Wow
 0x2:   KEY: 1   Note                                 s01 (made on the fly)
 0x3:   KEY: 2   Note
 0x4:   KEY: 3   Note
 0x5:   KEY: 4   Note
 0x6:   KEY: 5   Note
 0x7:   KEY: 6   Note
 0x8:   KEY: 7   Note
 0x9:   KEY: 8   Note
 0xA:   KEY: 9   Note
 0xB:   KEY: 0   Note
 0xC:   KEY: -   Note
 0xD:   KEY: =   Note
 0xE:   KEY: Backspace  Stop everything               s02 Thud/spring
 0xF:   KEY: TAB  lock 'n drag                        s03 Two click
 0x10:  KEY: q  Do nothing                            s04 Metal Click
 0x11:  KEY: w  Checker ball                          s05 Low Bubble
 0x12:  KEY: e  Cone                                  s06 Hit pan
 0x13:  KEY: r  Starburst                             s07 Low Spin
 0x14:  KEY: t  Tree                                  s08 Sneeze
 0x15:  KEY: y  Argle                                 s09 Low squirt
 0x16:  KEY: u  Checkerboard Pattern                  s10 Comic Rattlesnale
 0x17:  KEY: i  Spiral Bar                            s11 wooeep
 0x18:   KEY: o  Circle brush shape                   s12 Hydraulic shzt
 0x19:   KEY: p  Draw/erase pallette                  s13 Twang
 0x1A:   KEY: [  Square brush shape                   s12 Hydraulic shzt
 0x1B:   KEY: ]        Horizontal line                s14 High Chime
 0x1C:   KEY: Enter    Vertical line                  s15 Low Chime
 0x1D:	 KEY: Left Ctrl  Do nothing                    		- Silent -
 0x1E:   KEY: a  Random regular circle                s16 "Bonk"
 0x1F:   KEY: s  Do nothing                           s17 Low Wooooooeeeeee
 0x20:   KEY: d  Nested circles                       s18 divboard
 0x21:   KEY: f  XOR whole screen with random color   s19 Screech
 0x22:   KEY: g  Coins                                s20 sonar vibration
 0x23:   KEY: h  Random XOR'ed rectangle              s21 Metal drum
 0x24:   KEY: j  Flabbergasted!                       s22 "Flabbergasted"
 0x25:   KEY: k  Palette box                          s23 Kachunksqueak
 0x26:   KEY: l  Reverse mouse coordinates            s24 Little man laugh
 0x27:   KEY: ;  Turn on/off mouse tiling             s25 March
 0x28:   KEY: '  Spray brush shape                    s12 Hydraulic shzt 2
 0x29:   KEY: `  Change note sound to last sound          - Last sound -
 0x2A:   KEY: Left Shift  Do nothing                      - Silent -
 0x2B:   KEY: \  Slant brush shape                    s12 Hydraulic shzt 3
 0x2C:   KEY: z  Circle                               s26 Tin bell
 0x2D:   KEY: x  Square                               s27 "Dwee"
 0x2E:   KEY: c  Nested boxes                         s28 Low Box & Spring
 0x2F:   KEY: v   Flood Fill                          s29 Hit Twang
 0x30:   KEY: b  Random XOR'd circle                  s30 Swing (miss)
 0x31:   KEY: n Play test Wave                        s01 (made on the fly)
 0x32:   KEY: m
 0x33:   KEY: ,  Smaller brush                        s31 sniff
 0x34:   KEY: .  Larger brush                         s31 sniff
 0x35:   KEY: /  slash brush shape                    s12 Hydraulic shzts
 0x36:   KEY: Right Shift Do nothing                      - Silence -
 0x37:   KEY: Keypad *  Fireworks                     s32 Phoomp
																											s33 Pow
 0x38:   KEY: Left Alt  Do Nothing                        - Silence -
 0x39:   KEY: Spacebar                                s34 Plip
 0x3A:   KEY: Caps lock Do nothing (lock color)       s35 Guncock (clicking)
 0x3B:   KEY: F1  Clear to black                      s36 Alarm Clock
 0x3C:   KEY: F2  Clear to random                     s37 Low Bell
 0x3D:   KEY: F3  scorched Earth Slump              C s38 rumble
 0x3E:   KEY: F4  Convert screen to B&W               s39 Cough
 0x3F:   KEY: F5  Game of life scren animation      C s25 Marching
 0x40:   KEY: F6  Plasma!                             s40 Big Cymbal (after!)
 0x41:   KEY: F7  Slide screen                      C s41 Small Whoop
 0x42:   KEY: F8 Snow!                                s42 High spin
 0x43:   KEY: F9 Alternate Lines                    C s43 Squeek
 0x44:   KEY: F10 Diffusion                         C s44 Hi Locomotive
 0x45:   KEY: Num Lock  Toggle White/black palette    s45 Clear Bell
 0x46:   KEY: Scroll lock  Memory Check               s46 Long Cymbal
 0x47:             KEY: KeyPad 7                      s47 Drum tune 1
 0x48:             KEY: KeyPad 8                      s48 Drum Tune 2
 0x49:             KEY: KeyPad 9                      s49 Drum Tune 3
 0x4A:   KEY: KeyPad -  giTempo slower                s50 Snare
 0x4B:   KEY: KeyPad 4 FFT Brush                      s51 Dweewee
 0x4C:   KEY: KeyPad 5 Polar Waveform Brush           s52 Engine Revv
 0x4D:   KEY: KeyPad 6 Reverse Sounds                 s22 "Flabbergasted"
 0x4E:   KEY: KeyPad +  giTempo faster                s50 Snare
 0x4F:   KEY: KeyPad 1  Crazy screen effect         C s53 Drumming
 0x50:   KEY: KeyPad 2  Hyper-Vortex Screen Effect  C s54 Low Wah Wah
 0x51:   KEY: KeyPad 3  Vortex Screen Effect        C s55 Gargle
 0x52:   KEY: KeyPad Insert  Moire brush              s56 Descending Drum
 0x53:   KEY: KeyPad Delete								s63 Delicate Crash
 0x57:   KEY: F11 Blur                                s57 Short Cow
 0x58:   KEY: F12 FFT animation                       s58 Whistle and bonks
 0x60:   KEY: Right alt  Do nothing                       - Silence -
 0x61:   KEY: Right Ctrl Do nothing                       - Silence -
 0x62:   KEY: Arrow Up Draw a Spiral                  s59 Big Boing
 0x63:   KEY: Arrow left  Bouncing Ball               s60 Dull Thud
 0x64:   KEY: Arrow Right  Colors up 1                s61 Single Laugh (high)
 0x65:   KEY: Arrow Down   Colors down 1              s62 Single laugh (low)
 0x66:   KEY: Insert Start music/next music file          - Silence -
 0x67:   KEY: Home  Toggle Music                          - Silence -
 0x68:   KEY: Page Up  Draw Line  (+ Stress Mode)     s64 Small Boing
																											s70 Yell (stress mode)
 0x69:   KEY: Delete  Prev song                           - Silence -
 0x6A:  					 KEY: End                       		s66 Tinkerbell
 0x6B:   KEY: Page Down Starburst (Stressmode)        s65 Hard Strike
																											s70 Yell (stress mode)
 0x6C:             KEY: Print Screen                  s67 Big Pipe
 0x6D:   KEY: Keypad /  Toggle sound                      >> Random sound when on <<
 0x6E:   KEY: Keypad enter    Text Typing             s68 Click


 OTHER SOUNDS
				 User not doing anything at start             s69 Yawn

*/



// SOUND EFFECT WAVES
/*
#include "waves\snd00.h"
#include "waves\snd01.h"
#include "waves\snd02.h"
#include "waves\snd03.h"
#include "waves\snd04.h"
#include "waves\snd05.h"
#include "waves\snd06.h"
#include "waves\snd07.h"
#include "waves\snd08.h"
#include "waves\snd09.h"
#include "waves\snd10.h"
#include "waves\snd11.h"
#include "waves\snd12.h"
#include "waves\snd13.h"
#include "waves\snd14.h"
#include "waves\snd15.h"
#include "waves\snd16.h"
#include "waves\snd17.h"
#include "waves\snd18.h"
#include "waves\snd19.h"
#include "waves\snd20.h"
#include "waves\snd21.h"
#include "waves\snd22.h"
#include "waves\snd23.h"
#include "waves\snd24.h"
#include "waves\snd25.h"
#include "waves\snd26.h"
#include "waves\snd27.h"
#include "waves\snd28.h"
#include "waves\snd29.h"
#include "waves\snd30.h"
#include "waves\snd31.h"
#include "waves\snd32.h"
#include "waves\snd33.h"
#include "waves\snd34.h"
#include "waves\snd35.h"
#include "waves\snd36.h"
#include "waves\snd37.h"
#include "waves\snd38.h"
#include "waves\snd39.h"
#include "waves\snd40.h"
#include "waves\snd41.h"
#include "waves\snd42.h"
#include "waves\snd43.h"
#include "waves\snd44.h"
#include "waves\snd45.h"
#include "waves\snd46.h"
#include "waves\snd47.h"
#include "waves\snd48.h"
#include "waves\snd49.h"
#include "waves\snd50.h"
#include "waves\snd51.h"
#include "waves\snd52.h"
#include "waves\snd53.h"
#include "waves\snd54.h"
#include "waves\snd55.h"
#include "waves\snd56.h"
#include "waves\snd57.h"
#include "waves\snd58.h"
#include "waves\snd59.h"
#include "waves\snd60.h"
#include "waves\snd61.h"
#include "waves\snd62.h"
#include "waves\snd63.h"
#include "waves\snd64.h"
#include "waves\snd65.h"
#include "waves\snd66.h"
#include "waves\snd67.h"
#include "waves\snd68.h"
#include "waves\snd69.h"
#include "waves\snd70.h"
*/




WAVE *flabbersound[MAXSOUNDS];
WAVE *baselist[MAXSOUNDS];          // In case sounds get mixed up
WAVE localwave1;
char testwave[22000];
void *wavememory = NULL;

int giLastSound = 0;
int giBackgroundSound = 0;
LONG wave_id=-1;
/**************************************************************************
	void loadwaves(char *filename)

	DESCRIPTION:  Loads a bnch of patches from a music Goop file

**************************************************************************/
void loadwaves(char *filename)
{
	char errstring[256],string[1000];
	int i,j,ptotal,totalmem,usedmem;
	FILE *input;
	BYTE *mempointer;
	int readmem = 0;

	for(i = 0; i < 256; i++) flabbersound[i] = NULL;

	input = fopen(filename,"rb");
	if(!input) {
		verbosef("Error opening patch input file: %s\n",filename);
		return;
	}

	verbosef("Reading waves...\n");

	if(fread(string,1,40,input) < 40) {
		fclose(input);
		verbosef("File Read error!\n");
		return;
	}
	if(!strstr(string,"FLABBERGASTED Wave Goop")) {
		fclose(input);
		verbosef("Not a Wave Goop file!\n");
		return;
	}

	if(fread(&usedmem,1,sizeof(int),input) < sizeof(int)) {
		fclose(input);
		verbosef("File Read error!\n");
		return;
	}

	wavememory = flabmalloc(usedmem);
	if(!wavememory) {
		fclose(input);
		verbosef("Out of memory!\n");
		return;
	}

	mempointer = (BYTE *)wavememory;
	while(readmem < usedmem) {
		verbosef(".");
		if(fread(mempointer+readmem,1,50000,input) < 50000) break;
		readmem += 50000;
	}


	verbosef("  Waves loaded into raw memory.  Processing...\n");

	for(i = 0; i <= 70; i++) {
																		// Set up pointers for this patch
		flabbersound[i] = (WAVE *)mempointer;
		baselist[i] = (WAVE *)mempointer;
		flabbersound[i]->id = wave_id--;
		flabbersound[i]->head = flabbersound[i];
		mempointer += sizeof(WAVE);
		flabbersound[i]->data = (SAMPLE *)mempointer;
		mempointer += flabbersound[i]->chunk_size;
	}

	fclose(input);


}


/**************************************************************************
	void makewave(WAVE *nw,SAMPLE *data, LONG l)

	DESCRIPTION:

**************************************************************************/
void makewave(WAVE *nw,SAMPLE *data, LONG l)
{
	static myid = -10000;
	if(!nw) return;

																				// Put in intial values.
	nw->chunk_size = l;             			// size of this chunk in bytes
	nw->data = data;                      // pointer to raw data
	nw->next = NULL;                      // terminate tail.

																				// If w is NULL, that means we
																				// start fresh.
	nw->stereo = v_false;
	nw->loaded = 0;
	nw->id = myid;                // Give it a handle
	myid--;
	nw->head = nw;                			// points to top link.
	nw->sample_size = l;          			// size of entire linked sample
}


/**************************************************************************
	void loadsounds(void)

	DESCRIPTION: Loads all sounds needed for flabbergasted

**************************************************************************/
void loadsounds(void)
{
	static int wavesloaded = FALSE;

	if(!wavesloaded) {
		verbosef("Loading sounds\n");

		loadwaves("wavglob.wvs");

		flabbersound[1]->sample_rate = 22000;
		flabbersound[1]->byte_rate = 22000;
		flabbersound[1]->chunk_size = flabbersound[1]->sample_size  = 11000;
		flabbersound[1]->stereo = v_false;
		flabbersound[1]->loaded = 0;
		flabbersound[1]->head = flabbersound[1];           // points to top link.
		flabbersound[1]->data = (SAMPLE *)testwave;        // pointer to raw data
		flabbersound[1]->next = NULL;                      // terminate tail.

		for(int i = 0; i < 11000; i++) {
			testwave[i] = ((11000-i)/110.0)*sin(i/4.1);
			if(i < 200) testwave[i] = ( (signed char)testwave[i] * i/200.0);
			if(i < 5) testwave[i] = 0;
		}
		wavesloaded = TRUE;
	}
	else {
		for(int i = 0; i <70; i++) flabbersound[i] = baselist[i];
	}

}


/**************************************************************************
	void freesounds(void)

	DESCRIPTION: Frees up all memory allocated for sounds

**************************************************************************/
void freesounds(void)
{
	int i;

	for(i = 0; i < MAXSOUNDS; i++) {
		if(flabbersound[i]) FreeWave(flabbersound[i]);
	}

}
/**************************************************************************
	void dosound(int sn,int vol, int fratio ,int pan)

	DESCRIPTION:  General sound handler for tetris.  This takes sample rate
								into effect so that the sounds are the same no matter
								what it is.

	INPUTS:
		sn				Sound number
		vol				Sound Volume (0-100)
		fratio 		Frequency ratio from original sampling (Hrz)
		pan   		panning value (0-59)

**************************************************************************/
void dosound(int sn,int vol, double fratio ,int pan)
{
	LONG id;

	if(!giSoundOn || !giFXOn) return;

	giLastSound = sn;
	if(!giMakeNoise) return;

	id = 	PlayWave(flabbersound[sn],v_false,v_pan);

	if(fratio > 0.001) WaveSetting(id,v_rate,fratio * flabbersound[sn]->sample_rate);
//	if(vol)  WaveSetting(id,v_volume,(vol * 64)/100);
	if(vol)  WaveSetting(id,v_volume,(vol * 64)/75);
	if(pan)  WaveSetting(id,v_panpos,pan);
}

/**************************************************************************
	void dosound2(int sn,int vol, int fratio ,int pan)

	DESCRIPTION:  Same as dosound, except it does not remember last sound

**************************************************************************/
void dosound2(int sn,int vol, double fratio ,int pan)
{
	LONG id;

	if(!giSoundOn || !giFXOn) return;

	if(!giMakeNoise) return;

	id = 	PlayWave(flabbersound[sn],v_false,v_pan);

	if(fratio > 0.001) WaveSetting(id,v_rate,fratio * flabbersound[sn]->sample_rate);
//	if(vol)  WaveSetting(id,v_volume,(vol * 64)/100);
	if(vol)  WaveSetting(id,v_volume,(vol * 64)/75);
	if(pan)  WaveSetting(id,v_panpos,pan);
}

/**************************************************************************
	void dobackgroundsound(int sn,int vol, int fratio ,int pan)

	DESCRIPTION:  General sound handler for tetris.  This takes sample rate
								into effect so that the sounds are the same no matter
								what it is.

	INPUTS:
		sn				Sound number
		vol				Sound Volume (0-100)
		fratio 		Frequency ratio from original sampling (Hrz)
		pan   		panning value (0-59)

**************************************************************************/
void dobackgroundsound(int sn,int vol, double fratio ,int pan)
{
	if(!giSoundOn || !giFXOn) return;

	giLastSound = sn;
	if(!giMakeNoise) return;
																		// Stop the wave if it is playing
	if(giBackgroundSound) {
		WaveCommand(giBackgroundSound,v_stop);
	}
																		// Play wave and change settings
	giBackgroundSound = 	PlayWave(flabbersound[sn],v_false,v_fancy);
	WaveSetting(giBackgroundSound,v_repeat,-1);

	if(fratio > 0.001) WaveSetting(giBackgroundSound,v_rate,fratio * flabbersound[sn]->sample_rate);
	if(vol)  WaveSetting(giBackgroundSound,v_volume,(vol * 32)/100);
	if(pan)  WaveSetting(giBackgroundSound,v_panpos,pan);
}


