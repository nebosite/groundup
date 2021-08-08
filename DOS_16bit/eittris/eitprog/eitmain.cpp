// Varmint's EITTRIS
// Copyright (C) 1996-2000, Purple Planet Software

#include "stdafx.h"
#include "eittris.h"


//------------------------------ VARIABLES


int tinytim=TRUE;                       // Easter egg!
char configfilename[20]={"eittris.cfg"};
MUSIC tune[100];
DVWAVE *soundbite[50];
int numtunes = 0;
char musictype;
int musicvolume = 50;
int currenttune;
unsigned int frame=0;

char *playerfile={"players.cfg"};

int soundon = TRUE;
int musicon = TRUE;
int hires = FALSE;
int highscoreson = TRUE;

int stressmode = FALSE;
int snapshotmode = FALSE;
int grid_width = 10,grid_height = 22;
int frames_per_speedup = 700;
int special_lifetime = 1200;
int maxtime_to_special = 200;
int antedote_probability = 25;
char *specialname[NUMBEROFSPECIALS] = {
	"Speed Up",            // 0
	"Slow Down",           // 1
	"Escalator",           // 2
	"The Wall",            // 3
	"Jumble",              // 4
	"Crazy Ivan",          // 5
	"Switch Screens",      // 6
	"EIT-O-Matic",         // 7
	"Flip",          		   // 8
	"Freeze Dried",        // 9
	"Blindness",    			 // 10
	"No More Hints",       // 11
	"New background",      // 12
	"Antidote",            // 13
	"Bridge",              // 14
	"Transparency",        // 15
	"Clear Screen",        // 16
	"Junk Yard",           // 17
	"Zee Virus",           // 18
	"Psycho",              // 19
	"Shackle",             // 20
	"Tower of EIT" };      // 21

double speedup = 0.95;
PLAYER *person[MAXPLAYERS];
char *names[] = {"Fred","Wilma","Betty","Barney","Pebbles","BamBam","Dino",
				"Mr Slate","George","Jane","Elroy","Judy",
				"Homer","Marge","Bart","Lisa","Maggie",
				"Max"};
int charbuffer[256];

int piecedata[8][4][8] = {
 {{-1,-1,-1,-1,-1,-1,-1,-1},{-1,-1,-1,-1,-1,-1,-1,-1},       // Piece 0
	{-1,-1,-1,-1,-1,-1,-1,-1},{-1,-1,-1,-1,-1,-1,-1,-1}},

 {{2,1,2,2,2,3,2,4},{0,2,1,2,2,2,3,2},       // Piece 1  (long)
	{2,0,2,1,2,2,2,3},{1,2,2,2,3,2,4,2}},

 {{1,1,1,2,2,2,2,3},{2,1,3,1,1,2,2,2},       // Piece 2  (Z left)
	{2,1,2,2,3,2,3,3},{2,2,3,2,1,3,2,3}},

 {{3,1,2,2,3,2,2,3},{1,2,2,2,2,3,3,3},       // Piece 3  (Z right)
	{2,1,1,2,2,2,1,3},{1,1,2,1,2,2,3,2}},

 {{2,1,2,2,1,3,2,3},{1,1,1,2,2,2,3,2},       // Piece 4  (L left)
	{2,1,3,1,2,2,2,3},{1,2,2,2,3,2,3,3}},

 {{2,1,2,2,2,3,3,3},{1,2,2,2,3,2,1,3},       // Piece 5  (L right)
	{1,1,2,1,2,2,2,3},{3,1,1,2,2,2,3,2}},

 {{1,2,2,2,3,2,2,3},{2,1,1,2,2,2,2,3},       // Piece 6  (T)
	{2,1,1,2,2,2,3,2},{2,1,2,2,3,2,2,3}},

 {{1,1,2,1,1,2,2,2},{1,1,2,1,1,2,2,2},       // Piece 7  (Box)
	{1,1,2,1,1,2,2,2},{1,1,2,1,1,2,2,2}}

};

																		// Shape allocations:
																		// 0   Null piece
																		// 1-7 standard blocks
																		// 40 special blocks
																		// 80 background tiles
																		// 200 dizzolve blocks
DVSPRITE *shape[256],*dummy[2];
BGROUND *bgrnd[50];


/* WORD specialgrid[60] = {            // This grid is for testing
	0,0xff,0,0,0,0,0 ,0,0,0,
	0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0};*/
WORD specialgrid[60] = {
	0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,
	0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,
	0xffff,0xffff,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0}; 
int block_width=19,block_height=19;
int txtht=15;
DWORD fadetable[66000];
//BYTE fade[256],bwfade[256];
//RGB palette[256],fogpal[256];
int totalrounds=5,currentround=0;
int tetrisspecial = 14;
int numbackgrounds =30;
																		// piece probabilities (cumulative)
int pprob[8] = {0,15,10,10,15,15,10,10};
//int pprob[8] = {0,1,10,10,15,15,10,10};     // test probabliliteis
																		// repeat probabilities (percentile)
int repeatprob[8] = {0,45,5,5,15,15,10,10};
int startspeed = 70;
int gamespeed = 10;
int arrowseq[18] = {0,1,2,3,4,5,6,7,8,9,8,7,6,5,4,3,2,1};

int sbactive=FALSE;

FILE *eitdebugfile = NULL;

DWORD localkey = 0;
