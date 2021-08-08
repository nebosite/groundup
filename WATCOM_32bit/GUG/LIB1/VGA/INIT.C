#include <i86.h>
#include <stdlib.h>
#include <malloc.h>
#include <dos.h>
#include "mode.H"

#define REGISTERED 1

// point to the beginning of the VGA memory in mode 13x
#define SCREEN_AREA           0xa000
#define SCREEN_LINEAR_ADDRESS ((SCREEN_AREA) << 4)

char *VGA_MEMORY;              // Always points to the 100K buffer
char *VGA_POINTER;             // Always points to the VGA memory
char *VGA_START;               // Points into VGA_MEMORY

// Used for the GLYPH font
int  GUG_Font_Height = 8;      // height of the font in pixels
int  GUG_Font_Width  = 7; // 8     // width of the font in pixels

// Use for loadable fonts
typedef struct
{
  int x_size;
  int y_size;
  char *chars[256];
} GUG_FONT;
GUG_FONT *gug_font = NULL;		// Default Loadable Font Pointer

char GUG_Old_Palette[768];      // holder for the OLD palette
char GUG_666_Palette[768];	    // the 666 palette

int  GUG_KBD_Installed = 0;    // 0 = Not Installed

int   GUG_Video_Mode    = GUG320X200;     // 320x200 is default

void  GUGGetPalette(char *palette);       // Set a Palette
void  GUGSetPalette(char *palette);       // Get a Palette
void  GUGMake666Palette(char *palette);	  // Create a 66 Palette
void  GUGCenterText(int y, int c, char *txt);  // Center Text
char *GUGVersion();  // Return a pointer to the version number string
void  GUGCopyToDisplay();
void  GUGCopyToBuffer(char *from);

char font[8*256];               // Store a copy of the glyph

// Used in the PIX rountines
int  pix_x = 0;
int  pix_y = 0;
int  pix_c = 0;

// Joystick Globals
int GUGJ1XMax = 1;
int GUGJ1XMin = 1;
int GUGJ1YMax = 1;
int GUGJ1YMin = 1;
int GUGJ2XMax = 1;
int GUGJ2XMin = 1;
int GUGJ2YMax = 1;
int GUGJ2YMin = 1;
int GUGX1Active = 0;
int GUGX2Active = 0;

// Draw Rectangle Stuff
int GUG_rect_index = 0;    // Index into GUG_rect
int GUG_rect[128][4];	   // GUG_rect array

// GUG Sprite Based Mouse Stuff
int  SHOW_SPRITE_MOUSE = 0;     // Sprite Mouse is hidden
char *GUG_Sprite_Mouse = NULL;	// Pointer to the Mouse Sprite to use

// Track the video mode GUG was started from
int curmode;

// Various colors - these default to in 666 palette index but
//   can be tuned for a custom palette.	These are used in GUG
//   functions such as the Widgets.
int GUG_PURPLE  = 191;
int GUG_ORANGE  =  17;
int GUG_YELLOW  =  35;
int GUG_TAN     =  94;
int GUG_BROWN   =  51;
int GUG_BLACK   = 216;
int GUG_GREY_1  =  43;
int GUG_GREY_2  =  86;
int GUG_GREY_3  = 129;
int GUG_GREY_4  = 172;
int GUG_WHITE   = 215;
int GUG_B_RED   =   5;
int GUG_RED     =   4;
int GUG_D_RED   =   3;
int GUG_B_GREEN =  30;
int GUG_GREEN   =  18;
int GUG_D_GREEN =  48;
int GUG_B_BLUE  = 212;
int GUG_L_BLUE  = 156;
int GUG_BLUE    = 181;
int GUG_D_BLUE  = 144;

//***************************************************************************
// Set the VGA card to mode 13 (320x200 256 color)
// Set up working memory buffers
//
int GUGInitialize(void) {
  union REGS regs;           // Used in the int386 function call
  char black_palette[768];
  int  x,i,s,xs,ys;
  extern char gug_0[];
  char *from;
  char mes[80];
#define MAX_FRAMES 10
  char *introframes[MAX_FRAMES];

  for (x=0; x<MAX_FRAMES; ++x)
    introframes[x] = NULL;

  // Make a copy of the GLYPH in RAM as RAM is faster to access than ROM
  from = (char *)0x000FFa6e;
  for (x=0; x<(8*256); ++x)
  {
    font[x] = *from;
	from++;
  }

  // create an all black palette
  for (x=0; x<768; ++x)
    black_palette[x] = 0;

  // initialize the pointers
  VGA_POINTER =	(char *)SCREEN_LINEAR_ADDRESS;

  // malloc a workspace
//  if ((VGA_MEMORY = (char *)malloc(((X_WRAP_SIZE*Y_WRAP_SIZE)*4)+8)) == NULL)
  if ((VGA_MEMORY = (char *)malloc((X_WRAP_SIZE*Y_WRAP_SIZE)+8)) == NULL)
     return(0);

  // Point to buffers
  VGA_START = (VGA_MEMORY + (X_WRAP_SIZE  * MAX_SPRITE_Y) +
               MAX_SPRITE_X + 1);
//  VGA_START = (VGA_MEMORY + ((MAX_X_SIZE*MAX_Y_SIZE)*3)*2)+32000;
//  VGA_START = VGA_MEMORY + ((MAX_X_SIZE+MAX_SPRITE_X)*MAX_SPRITE_Y)+MAX_SPRITE_X+32000;
  x = (int)VGA_START;
  // make sure we are on a 4 byte boundry for speed
  if (x & 0x00000001) VGA_START -= 1;
  if (x & 0x00000002) VGA_START -= 2;

  regs.h.ah = 0x0f;          // Int 0x10 option 0x0f to get the VGA mode
  regs.h.al = 0x00;
  int386(0x10,(union REGS *)&regs,
              (union REGS *)&regs);  // And get the mode

  curmode = regs.h.al;  // save the old mode

//  printf("Old mode = %d\n",curmode);
//  while (!kbhit()) ;
//  getch();

  regs.h.ah = 0x00;          // Int 0x10 option 0x00 set VGA mode
  regs.h.al = 0x13;          // Use mode 0x13 - 320x200 256 color
  int386(0x10,(union REGS *)&regs,
              (union REGS *)&regs);  // And set the mode

  GUGGetPalette(GUG_Old_Palette);      // Get the old palette
  GUGMake666Palette(GUG_666_Palette);  // Generate a 666 palette

  GUGSetPalette((char *)black_palette);        // Screen is black
  GUGClearDisplay();
  GUGCopyToDisplay();
  GUGSetPalette((char *)GUG_666_Palette);

#ifndef REGISTERED

  xs = GUGSpriteWidth(gug_0);
  ys = GUGSpriteHeight(gug_0);

  introframes[0] = (char *)GUGResizeSpriteToSprite(gug_0, 10, 20);
  introframes[1] = (char *)GUGResizeSpriteToSprite(gug_0, 40, 40);
  introframes[2] = (char *)GUGResizeSpriteToSprite(gug_0, 80, 60);
  introframes[3] = (char *)GUGResizeSpriteToSprite(gug_0,120, 80);
  introframes[4] = (char *)GUGResizeSpriteToSprite(gug_0,160,100);
  introframes[5] = (char *)GUGResizeSpriteToSprite(gug_0,200,120);
  introframes[6] = (char *)GUGResizeSpriteToSprite(gug_0,240,140);

  GUGPutBGSprite(160-5,100-10,introframes[0]);
  GUGCopyToDisplay();
  delay(20);
  GUGPutBGSprite(160-20,100-20,introframes[1]);
  GUGCopyToDisplay();
  delay(20);
  GUGPutBGSprite(160-40,100-30,introframes[2]);
  GUGCopyToDisplay();
  delay(20);
  GUGPutBGSprite(160-60,100-40,introframes[3]);
  GUGCopyToDisplay();
  delay(20);
  GUGPutBGSprite(160-80,100-50,introframes[4]);
  GUGCopyToDisplay();
  delay(20);
  GUGPutBGSprite(160-100,100-60,introframes[5]);
  GUGCopyToDisplay();
  delay(20);
  GUGPutBGSprite(160-120,100-70,introframes[6]);
  GUGCopyToDisplay();
  delay(20);

  GUGPutBGSprite(23,18,gug_0);
  sprintf(mes,"Version %s",GUGVersion());
  GUGCenterText(190,205,mes);
  GUGCopyToDisplay();

//  GUGFadeToPalette(GUG_666_Palette,25);
  x = 0;
  while (x < 150)
  {
    delay(10);  // 10mS delay
    x++;
	if (kbhit())
	{
	  getch();
	  x = 300;
	}
  }
  GUGFadeToColor(0,25);

  GUGClearDisplay();
  GUGCopyToDisplay();

  GUGSetPalette(GUG_666_Palette);      // and install the 666 palette

#endif

  for (x=0; x<MAX_FRAMES; ++x)
  {
    if (introframes[x] > NULL)
      free(introframes[x]);
  }

  return(1);  // Success
}
