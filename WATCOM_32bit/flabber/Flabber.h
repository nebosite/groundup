/********************************************************************

	FLABBERGASTED!

	Eric Jorgensen 1997

	flabber.h

	General header file

*********************************************************************/

#include <string.h>
#include <stdio.h>
#include "\watcom\vat\vat.h"
#include "\watcom\gug\lib1\gug.h"
#include "Routine.h"

// ------------------- *** DEFINES *** -----------------------

#ifndef NULL
#define NULL 0
#endif

#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif

#ifndef FLABBER_H
#define FLABBER_H

#define MAXSOUNDS 71
#define MAXSPRITES 50
#define VERSION "1.10a"
#define BIGBUFFERSIZE 30000
//#define MEMTESTSIZE 500000
#define MEMTESTSIZE 500

#define TRUE 1

#define ANIMCOLOR0 64
#define ANIMCOLOR1 80
#define ANIMCOLOR2 96
#define ANIMCOLOR3 112
#define ANIMCOLOR4 128
#define ANIMCOLOR5 144
#define ANIMCOLOR6 160
#define ANIMCOLOR7 176
#define ANIMCOLOR8 192
#define ANIMCOLOR9 208
#define ANIMCOLOR10 224
#define ANIMCOLOR11 240

#define SCANCODE_LCTRL 	0x1D
#define SCANCODE_RCTRL 	0x61
#define SCANCODE_LALT 	0x38
#define SCANCODE_RALT 	0x60
#define SCANCODE_LSHIFT 0x2A
#define SCANCODE_RSHIFT 0x36
#define SCANCODE_CAPS 	0x3A

#define CHROMATIC_RATIO 1.059463094

#define DEMOMEMORYSIZE 6000000



// -------------------- MACROS ------------------------


// ------------------- *** ENUMS *** -----------------------

typedef enum {cursor_square = 1,
							cursor_circle,
							cursor_slant,
							cursor_slash,
							cursor_spray,
							cursor_x,
							cursor_plus,
							cursor_fill} MOUSECURSORS;

typedef enum {brush_square = 1,
							brush_circle,
							brush_slant,
							brush_slash,
							brush_spray} BRUSHSHAPES;

typedef enum {signal_start,
							signal_continue} SIGNALS;

enum {stressmode_off = 0,
			stressmode_sporatic,
			stressmode_deliberate};

// ------------------- *** CLASSES *** -----------------------

#ifndef MUSICNAMEFOO
#define MUSICNAMEFOO

class MUSICNAME {
public:

	signed char path[200];
	MUSICNAME *next,*prev;
	VATMUSICTYPE type;
	int	iszot;

	MUSICNAME(char *name)
		{
			strcpy((char *)path,name);
			next = prev =NULL;
			iszot = 0;
		}
};

#endif



// ------------------- *** INTERNAL GLOBALS *** -----------------------
extern int (*animfunc)(int signal);
extern int (*brushfunc)(int signal);
extern int (*gamefunc)(int signal);

extern int giSaveScreen;

extern WAVE *flabbersound[MAXSOUNDS];
extern RasterBlock *flabbersprite[MAXSPRITES];
extern Palette palette[];
extern RasterBlock *grbWorkSpace;
extern RasterBlock *grbTemp[3];
extern RasterBlock *grbPaletteBlock;
extern double   giScale[88];

extern char gcEvData[];
extern char *gcRegUser;
extern char *gcRegDate;
extern char gcUserName[];
extern int giDemoDays;


extern int		giMusicOn;
extern int		giFXOn;
extern int 	giVerbose;
extern int 	giHardQuit;
extern int		giStartWithMusic;
extern int 	giScreenSaverMode;
extern int 	giNiceMouse;
extern int		giEggMe;
extern int		giMouseX1;
extern int		giMouseY1;
extern int		giMouseW;
extern int		giMouseH;
extern int		giUseMouseCoords;
extern int  giMouseIsThere;
extern int  giMouseCursor;
extern int  giBrushShape;
extern int  giBrushSize;
extern int 	giWorkingColor;
extern BYTE gColorStack[10];
extern int  giPalPut;
extern int 	giFloodFill;
extern int  giDrawFrameCount;
extern int  giWhitePalette;
extern int  giMakeNoise;
extern int  giSoundOn;
extern int  giBackgroundSound;
extern double gfprealmousex,gfprealmousey;
extern int gilastmusiccounter;


extern int maxx;
extern int maxy;

extern CRoutine *gRoutineList;

extern int giLastSound;

extern MUSICNAME *gpMusicList,*gpMusicPointer,*gpMusicTail;
extern MOD *gpMyMod;
extern S3M *gpMyS3M;
extern MIDI *gpMyMidi;

extern int giMouseReverse;
extern int giMouseTile;
extern int giStatusMode;
extern int giTempo;

extern FILE *gpKeyFile;
extern FILE *gpLogFile;
extern FILE *gpAutoFile;

extern BYTE bigbuffer[];

extern int giTextType;
extern int giStressMode;
extern int giStressFrame;
extern int giStressRepeat;
extern char giStressKey;

extern char *memorytest_preallochunk;
extern char *memorytest_postallochunk;
extern char memorytest_prehunk[MEMTESTSIZE];
extern char memorytest_posthunk[MEMTESTSIZE];


// ------------------ *** FUNCTIONS *** ----------------------

void *flabmalloc(int size);
void verbosef(char *string,...);
void Log(char *s, ...);
void loadsprites(void);
void loadsounds(void);
void freesounds(void);
void flabber(void);
void dopalette(int t);
void setuppalette();
void palbox(int x,int y);
void domouse(int x, int y, int b);
void dokey(char r);
void dosound(int sn,int vol=50, double fratio = 1.0,int pan = 30);
void dosound2(int sn,int vol=50, double fratio = 1.0,int pan = 30);
void dobackgroundsound(int sn,int vol=50, double fratio = 1.0,int pan = 30);
void doplasma(int x1, int y1, int w, int h, int colorbase);
void bnwrect(int x1,int y1, int x2, int y2);
void playmusic(int direction);
int  getangleindex(int x1, int y1, int x2, int y2,int divisions);
void typer(char c);
void drawwatermark(void);
void erasewatermark(void);
void doscreen(int);
VATMUSICTYPE ZotType(char *filename);
void *LoadZot(char *filename,char *errstring);
int QuickSqrt(int seed);


int animation1(int signal);
int animation2(int signal);
int animation3(int signal);
int animation4(int signal);
int animation5(int signal);
int animation6(int signal);
int animation7(int signal);
int animation8(int signal);
int animation9(int signal);
int animation10(int signal);
int animation11(int signal);
//int animation12(int signal);
//int animation13(int signal);

int autobrush1(int signal);
int autobrush2(int signal);
int autobrush3(int signal);

void fftgame(int signal);
void colordown(void);
void colorup(void);


#endif
