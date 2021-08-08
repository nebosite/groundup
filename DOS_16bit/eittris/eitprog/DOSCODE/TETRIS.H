#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "svgacc.h"
#include <alloc.h>
#include "svgaplus.h"
#include "kbd.h"
#include <string.h>
#include <time.h>
#include <ctype.h>
//#include "led.h"
#include "vatfree.h"
#include "player.h"


#define VERSION "1.30b"

//#define BYTE unsigned char
//#define WORD unsigned int
//#define DWORD unsigned long int
#define TRUE 1
#define FALSE 0
#define YELLOW666 35
#define RED666 5
#define GREEN666 30
#define BLUE666 180
#define MAGENTA666 185
#define CYAN666 210
#define GRAY0 216
#define TRANSCOLOR 255
#define REDUNIT 1
#define GREENUNIT 6
#define BLUEUNIT 36

#define NOSOUND 0
#define SBSOUND 1
#define PCSOUND 2

#define MAXPLAYERS 4

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77

	// pointers to shapes

#define SH_DIZZOLVE 0
#define NORMALBASE 0
#define SPECIALBASE 40
#define BGBASE 80
#define ANIMBASE 200


	// ID's for affliction items

#define	FREEZEDRIED 						0
#define	TRANSPARENTGRIDBLOCKS  	1
#define	INVISIBLEPIECES  				2
#define	FUTUREPIECEHIDING  			3
#define CRAZYIVAN								4
#define ZEEVIRUS								5
#define PSYCHO									6

  // misc

#define NUMBEROFSPECIALS 22

#define PKEYLEFT      0
#define PKEYRIGHT     1
#define PKEYDOWN      2
#define PKEYDROP      3
#define PKEYRLEFT     4
#define PKEYRRIGHT    5
#define PKEYVICTIM    6
#define PKEYANTEDOTE  7



//------------------------------ MACROS

#define ERASE(X) erasepiece(X,person[i]->gridx + person[i]->px * person[i]->bw,person[i]->gridy + person[i]->py * person[i]->bh,person[i]->px,person[i]->py,person[i]->bw,person[i]->bh,person[i]->gridy,(-person[i]->background)-1)
#define DRAW(X) drawpiece(X,person[i]->gridx + person[i]->px * person[i]->bw,person[i]->gridy + person[i]->py * person[i]->bh,person[i]->bw,person[i]->bh,person[i]->gridy)

#define HOSEDWITH(x,y) (x->afflicted & (1L << y))
#define HOSE(x,y) x->afflicted |= (1L << y)

//#define DOSOUND(X) PlaySound(soundbite[X],v_plain);
//#define DOFSOUND(X) PlaySound(soundbite[X],v_fancy);

#define FINISHANIM(X) while(X->gridanimation) X->gridanimation(X);


//------------------------------ DATA STRUCTURES

typedef struct bground {
  RasterBlock far *b[2][2];
} BGROUND;

typedef struct music {
	char *name;
  char type;
  BYTE fmmap[32];
} MUSIC;



//------------------------------ FUNCTIONS

												// overlaid modules
void setup(void);
void writesounds(void);
void readconfig(void);
void readplayerconfig(void);
void mainmenu(void);
void defineplayer(int num);
void playgame(void);
void endround(void);

                        // gameseg.c
int gamesegment(void);
int gridhaspieces(PLAYER *p);
int condensegrid(PLAYER *p);
void activatespecial(int special,PLAYER *p);


												// main.c
//void configuregame(void);
void setsounds(void);


												// utility.c
void setscore(PLAYER *p,long int score);
long int getscore(PLAYER *p);
void addtoscore(PLAYER *p,long int change);
void setanddrawpiece(PIECE *pc,PLAYER *p);
int pickspecial(WORD sgrid[]);
void drawblock(int x, int y, PLAYER *p);
void eraseblock(int x, int y, PLAYER *p);
void playerinit(PLAYER *p);
PLAYER far *newplayer(int num);
int collisioncheck(int px, int py,PIECE *p,BYTE spot[]);
void generatepiece(PIECE *p, BYTE pnum);
void drawpiece(PIECE *p,int x, int y, int w, int h,int top);
void copypiece(PIECE *p1, PIECE *p2);
void erasepiece(PIECE *p,int x, int y, int w,int gx, int gy, int h,int top,int background);
void rotatepieceleft(PIECE *p);
void rotatepieceright(PIECE *p);
void prepgrids(void);
void drawgrid(PLAYER *p);
void drawbox(int x1,int y1,int x2,int y2,int bw,int hc, int sc, int bc);
void drawpit(int x1,int y1,int x2,int y2,int bw,int hc, int sc, int bc);
int pickpiece(int p);
void setpiece(int px, int py,PIECE *p,BYTE spot[]);
void dostats(PLAYER *p);
int countbits(DWORD num);

                        // specials.c

void jumblegridanimation(PLAYER *p);
void randomizegridanimation(PLAYER *p);
void clearscreengridanimation(PLAYER *p);
void bridgegridanimation(PLAYER *p);
void wallgridanimation(PLAYER *p);
void staircasegridanimation(PLAYER *p);
void antedotegridanimation(PLAYER *p);
void standardgridanimation(PLAYER *p);
void fadegridanimation(PLAYER *p);
void freezedrygridanimation(PLAYER *p);
void eitomaticgridanimation(PLAYER *p);
void shacklegridanimation(PLAYER *p);
void towergridanimation(PLAYER *p);

												// computer.c
void pickmove(PLAYER *p);
void copygrid(BYTE g1[],BYTE g2[]);

												// sfx.c
void sticksound(int p);
void dosound(int sn,int vol, int freq);
void menuclicksound(int f);
void pcsound(int s);

//------------------------------ GLOBAL VARIABLES


extern int tinytim;
extern int grid_width,grid_height;
extern PLAYER far *person[MAXPLAYERS];
extern BYTE charbuffer[256];
extern int stressmode;
extern int hires;
extern int highscoreson;

extern int snapshotmode;

//extern BYTE piece_rotateleft[25] ;
//extern BYTE piece_rotateright[25] ;
//extern BYTE piece_bitmap[8][5];
extern int piecedata[8][4][8];
extern RasterBlock far *shape[],*dummy[];
extern BYTE fade[256],bwfade[256];
extern int number_of_specials;
extern int frames_per_speedup;
extern double speedup;
extern int txtht;
extern RGB palette[256];
extern RGB fogpal[256];
extern int pprob[8];
extern int repeatprob[8];
extern int block_width,block_height;
extern char *names[];
extern WORD specialgrid[];
extern int currentround,totalrounds;
extern int tetrisspecial;
extern int special_lifetime;
extern int maxtime_to_special;
extern int antedote_probability;
extern int numbackgrounds;
extern int soundtype;
extern char *playerfile;
extern char *specialname[];
extern BGROUND far *bgrnd[];
extern int startspeed;
extern int gamespeed;
extern int arrowseq[];
extern unsigned int frame;
extern long unsigned int current_frame;
extern char configfilename[];
extern WORD tetrissamplerate;


  // sound stuff

extern MUSIC tune[];
extern int numtunes;
extern WAVE VFAR *soundbite[];
extern DWORD soundlength[];
extern char musictype;
extern int currenttune;
extern int musicvolume;
extern int soundon,musicon;
extern int sbactive;

// eittimer stuff

extern DWORD eitclock;
extern int integritytest;


// scoring items

extern long int scoretable[7];
extern int slowcomputer;
extern WORD localkey;