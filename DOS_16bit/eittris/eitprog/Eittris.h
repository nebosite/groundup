// Varmint's EITTRIS
// Copyright (C) 1996-2000, Purple Planet Software

#include <DVinput.h>
#include <DVsound.h>
#include <DVdraw.h>
#include <math.h>
#include <time.h>
#include <ctype.h>
#include "player.h"


	// Random data

#define VERSION "1.51 "

#define MAXPLAYERS 4

	// pointers to shapes

#define SH_DIZZOLVE 0
#define NORMALBASE 0
#define SPECIALBASE 40
#define BGBASE 80
#define ANIMBASE 200


	// ID's for affliction items

#define	FREEZEDRIED 				0
#define	TRANSPARENTGRIDBLOCKS  		1
#define	INVISIBLEPIECES  			2
#define	FUTUREPIECEHIDING  			3
#define CRAZYIVAN					4
#define ZEEVIRUS					5
#define PSYCHO						6

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

#define EIT_TIMER_ID 22



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
  DVSPRITE *b[2][2];
} BGROUND;
//
typedef struct music {
	char *name;
	char type;
	BYTE fmmap[32];
} MUSIC;



//------------------------------ FUNCTIONS

												// overlaid modules
int eitsetup(void);
void eitcleanup(void);
//void writesounds(void);
void readconfig(void);
void readplayerconfig(void);
void mainmenu(void);
void defineplayer(int num);
void playgame(void);
void endround(void);

                        // gameseg.c
int gamesegment(void);
int gridhaspieces(PLAYER *p);
//int condensegrid(PLAYER *p);
//void activatespecial(int special,PLAYER *p);


												// main.c
//void configuregame(void);
//void setsounds(void);


												// utility.c
void setscore(PLAYER *p,int score);
int getscore(PLAYER *p);
void addtoscore(PLAYER *p,int change);
void setanddrawpiece(PIECE *pc,PLAYER *p);
int pickspecial(WORD sgrid[]);
void drawblock(int x, int y, PLAYER *p);
void eraseblock(int x, int y, PLAYER *p);
//void playerinit(PLAYER *p);
PLAYER *newplayer(int num);
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
//void drawpit(int x1,int y1,int x2,int y2,int bw,int hc, int sc, int bc);
int pickpiece(int p);
//void setpiece(int px, int py,PIECE *p,BYTE spot[]);
void dostats(PLAYER *p);
//int countbits(DWORD num);
int random(int max);
void getinput(int x,int y,int fc,int bc,char *prompt,char *string,int maxlength);
void debugf(char *szForamt,...);
bool eitkbhit();
int egetch();
int getscancode();
bool scankeyhit();
void dopsycho(DWORD color,int x1,int y1,int x2,int y2);


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
//void pickmove(PLAYER *p);
void copygrid(BYTE g1[],BYTE g2[]);

												// sfx.c
void sticksound(int p);
void dosound(int sn,int vol, int freq);
void menuclicksound(int f);
//void pcsound(int s);

//------------------------------ GLOBAL VARIABLES

extern FILE *eitdebugfile;

//extern int tinytim;
extern int grid_width,grid_height;
extern PLAYER *person[MAXPLAYERS];
extern int charbuffer[256];
extern int stressmode;
extern int highscoreson;
extern int snapshotmode;

//extern BYTE piece_rotateleft[25] ;
//extern BYTE piece_rotateright[25] ;
//extern BYTE piece_bitmap[8][5];
extern int piecedata[8][4][8];
extern DVSPRITE *shape[],*dummy[];
//extern BYTE fade[256],bwfade[256];
extern int number_of_specials;
extern int frames_per_speedup;
extern double speedup;
//extern int txtht;
//extern RGB palette[256];
//extern RGB fogpal[256];
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
extern char *playerfile;
extern char *specialname[];
extern BGROUND *bgrnd[];
extern int startspeed;
extern int gamespeed;
extern int arrowseq[];
extern unsigned int frame;
//extern long unsigned int current_frame;
extern char configfilename[];
extern WORD tetrissamplerate;


  // sound stuff

extern MUSIC tune[];
extern int numtunes;
extern DVWAVE *soundbite[];
//extern DWORD soundlength[];
extern char musictype;
extern int currenttune;
extern int musicvolume;
extern int soundon,musicon;
extern DVMOD *g_lpmod;
extern DVS3M *g_lps3m;	
extern DWORD fadetable[66000];
			     

//extern int sbactive;

// eittimer stuff

//extern DWORD eitclock;
//extern int integritytest;


// scoring items

//extern int scoretable[7];
//extern int slowcomputer;
extern DWORD localkey;

// Direct X stuff
extern int maxx,maxy;
extern CDVDraw *g_lpdvdrawobject;
extern CDVInput *g_lpdvinputobject;
extern CDVSound *g_lpdvsoundobject;

extern DWORD col_White;
extern DWORD col_Black;
extern DWORD col_Blue;
extern DWORD col_Green;
extern DWORD col_Red;
extern DWORD col_Magenta;
extern DWORD col_Yellow;
extern DWORD col_Orange;
extern DWORD col_Cyan;
extern DWORD col_SkyBlue;
extern DWORD col_Gray[16];

void SetDrawHandle(CDVDraw *drawobject);
void SetInputHandle(CDVInput *inputobject);
void SetSoundHandle(CDVSound *soundtobject);
DWORD col(int r, int g, int b);

