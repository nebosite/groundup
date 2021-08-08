//**************************************************************************
// Ground Up Graphics
//   Copyright 1995 Ground Up Software
//**************************************************************************

#ifndef _GUG_H
#define _GUG_H

typedef enum {SET,XOR,AND,OR} PIXELMODE;

typedef struct {
  unsigned short int width;
  unsigned short int height;
  char data[1];
} RasterBlock;

typedef struct {
	char r;
	char g;
	char b;
} Palette;

#ifdef __cplusplus
extern "C" {
#endif

#define GUG_FALSE 0
#define GUG_TRUE  1
#define GUG_NONE -1

// Various colors - these default to in 666 palette index but
//   can be tuned for a custom palette.	These are used in GUG
//   functions such as the Widgets.
extern int GUG_PURPLE;
extern int GUG_ORANGE;
extern int GUG_YELLOW;
extern int GUG_TAN;
extern int GUG_BROWN;
extern int GUG_BLACK;
extern int GUG_GREY_1;
extern int GUG_GREY_2;
extern int GUG_GREY_3;
extern int GUG_GREY_4;
extern int GUG_WHITE;
extern int GUG_B_RED;
extern int GUG_RED;
extern int GUG_D_RED;
extern int GUG_B_GREEN;
extern int GUG_GREEN;
extern int GUG_D_GREEN;
extern int GUG_B_BLUE;
extern int GUG_L_BLUE;
extern int GUG_BLUE;
extern int GUG_D_BLUE;

extern int GUGClipMinx ,GUGClipMaxx,GUGClipMiny,GUGClipMaxy;


int   GUGInitialize(void);
void  GUGEnd(void);
char *GUGVersion();  // Return a pointer to the version number string

void  GUGClearDisplay(void);
void  GUGSetDisplay(int color);

void  GUGCopyToDisplay();
void  GUGCopyToBuffer(char *from);
void  GUGCopyRectToRect(int xs1,int ys1,int xs2,int ys2);

void  GUGFadeToDisplay(int type);
#define GUG_NO_FADE      0
#define GUG_RECT_FADE    1
#define GUG_PIXEL_FADE   2
#define GUG_SWIRL_FADE   3
#define GUG_SLIDEX_FADE  4
#define GUG_SLIDEY_FADE  5
#define GUG_RANDOM_FADE -1

void GUGDrawLine(PIXELMODE pmode, int Color,int XStart, int YStart, int XEnd, int YEnd);
void GUGDrawVLine(PIXELMODE pmode, int color,int ystart, int ystop, int x);
void GUGDrawHLine(PIXELMODE pmode, int color, int xstart, int xstop, int y);
void GUGDrawRectangle(PIXELMODE pmode,int color, int xstart, int ystart,int xstop,  int ystop);
void GUGDrawFillRectangle(PIXELMODE pmode,int color,int xstart, int ystart,int xstop,  int ystop);
void GUGDrawCircle(PIXELMODE pmode, int color, int cx, int cy, int radius);
void GUGDrawFillCircle(PIXELMODE pmode, int color, int cx, int cy, int radius);
void GUGDrawPoint(PIXELMODE pmode, int color, int x, int y);


void  GUGHLine(int xstart, int xstop, int y, int color);
void  GUGVLine(int ystart, int ystop, int x, int color);
void  GUGLine(int XStart, int YStart, int XEnd, int YEnd,
							int Color);

void  GUGCircle(float radius, int segments, int color, int x, int y);
void  GUGFillCircle(float radius, int segments, int color, int x, int y);

void  GUGFloodFill(int point_x, int point_y, int border, int color);
void 	GUGFloodFillColor(int point_x, int point_y, int color);

int   GUGSpriteWidth(char *spr);
int   GUGSpriteHeight(char *spr);
int   GUGSpriteSize(char *spr);
int   GUGCalcSize(int xsize,int ysize);

void  GUGSetPixel(int x, int y, int c);
int   GUGGetPixel(int x, int y);
int   GUGTestPixel(int x, int y, int c);

void GUGFastSetPixel(int xpos, int ypos,int color);

void  GUGPutXORFGSprite(int x, int y, char *sprite);
void  GUGPutFGSprite(int x, int y, char *sprite);
void  GUGPutBGSprite(int x, int y, char *sprite);
void  GUGPutMNSprite(int x, int y, int c, char *sprite);
int   GUGLoadSprite(char *fname,char *sprites[]);
int   GUGSaveSprite(char *fname,char *sprites[],int count);
char *GUGClipSprite(int xstart, int ystart, int xstop, int ystop);

void  GUGFlipYFGSprite(int xb,int yb,char spr[]);
void  GUGFlipYBGSprite(int xb,int yb,char spr[]);
void  GUGFlipYMNSprite(int xb,int yb,int color,char spr[]);
void  GUGFlipXFGSprite(int xb,int yb,char spr[]);
void  GUGFlipXBGSprite(int xb,int yb,char spr[]);
void  GUGFlipXMNSprite(int xb,int yb,int color,char spr[]);

char *GUGBlockGet(int xstart, int ystart, int xstop, int ystop, RasterBlock *rblk);

void GUGClipFGSprite(int xb,int yb,   // Upper left hand corner of the Sprite
                     int cwx1,
                     int cwy1,        // Upper left hand corner of the clip window
                     int cwx2,
                     int cwy2,        // Lower right hand corner of the clip window
                     char spr[]);
void GUGClipBGSprite(int xb,int yb,   // Upper left hand corner of the Sprite
                     int cwx1,
                     int cwy1,        // Upper left hand corner of the clip window
                     int cwx2,
                     int cwy2,        // Lower right hand corner of the clip window
                     char spr[]);
void GUGClipNMSprite(int xb,int yb,   // Upper left hand corner of the Sprite
                     int cwx1,
                     int cwy1,        // Upper left hand corner of the clip window
                     int cwx2,
                     int cwy2,        // Lower right hand corner of the clip window
                     char color,     
                     char spr[]);

int   GUGVSync(void);

void  GUGGetPalette(char *palette);
void  GUGSetPalette(char *palette);
void  GUGMake666Palette(char *palette);
void  GUGCyclePalette(char *pal, int start, int stop);
void  GUGFadeToColor(int color, int speed);
void  GUGFadeToPalette(char *nwp, int speed);
int   GUGLoadPalette(char *fname,char *pal);
int   GUGSavePalette(char *fname,char *pal);
void  GUGRemapPalette(int *xlate,char *from, char *too);
void  GUGSetPaletteEntry(int index,int red, int green, int blue);

// Text Functions
void  GUGCenterText(int y, int c, char *txt);
void  GUGCenterFrameText(int y, int text_c, char *txt, int bg_color);
void  GUGPutText(int x, int y, int c, char *text);
int   GUGTextWidth(char *text);

// Compiled Text Functions
void GUGPrintGreen6x8(int x,int y,char *txt);
void GUGPrintGreen5x10(int x,int y,char *txt);
void GUGPrintGreen4x6(int x,int y,char *txt);
void GUGPrintRed6x8(int x,int y,char *txt);
void GUGPrintRed5x10(int x,int y,char *txt);
void GUGPrintRed4x6(int x,int y,char *txt);
void GUGPrintBlue6x8(int x,int y,char *txt);
void GUGPrintBlue5x10(int x,int y,char *txt);
void GUGPrintBlue4x6(int x,int y,char *txt);
void GUGPrintYellow6x8(int x,int y,char *txt);
void GUGPrintYellow5x10(int x,int y,char *txt);
void GUGPrintYellow4x6(int x,int y,char *txt);
void GUGPrintOrange6x8(int x,int y,char *txt);
void GUGPrintOrange5x10(int x,int y,char *txt);
void GUGPrintOrange4x6(int x,int y,char *txt);
void GUGPrintWhite6x8(int x,int y,char *txt);
void GUGPrintWhite5x10(int x,int y,char *txt);
void GUGPrintWhite4x6(int x,int y,char *txt);

// GUG Loadable Fonts
#define GUG_FONT_FAIL  0
#define GUG_FONT_OK    1
typedef struct
{
  int x_size;
  int y_size;
  char *chars[256];
} GUG_FONT;
int     GUGLoadFont(char *fontname,GUG_FONT *font);
void    GUGPrintFont(int x,int y,int clr,int bgd,char *txt);
void    GUGCenterFont(int y,int clr,int bgd,char *txt);
extern  GUG_FONT *gug_font;
#define GUGSetFont(x) (GUG_set_font(&x))

// Rectangles
void  GUGRectangle(int xstart, int ystart,
                   int xstop,  int ystop,
                   int color);
void  GUGFillRectangle(int xstart, int ystart,
                       int xstop,  int ystop,
                       int color);

// Save/Restore the screen
void GUGSaveDisplay(char *too);
void GUGRestoreDisplay(char *from);

// PCX Functions for 320x200x256 PCX's only
int  GUGLoadPCX(char *file, char *buffer, char *palette);
int  GUGSavePCX(char *file, char *buffer, char *palette);

/* pcx file header structure */
typedef struct	{
	char  manufacturer;
	char  version;
	char  encoding;
	char  bits_per_pixel;
	short xmin, ymin;
	short xmax, ymax;
//        short hres;
//        short vres;
        unsigned short check_one;
        unsigned short check_two;
        char  sname[21];
        char  filler1[27];
//        char  palette[48];
        char  reserved;
	char  color_planes;
	short bytes_per_line;
	short palette_type;
        char  filler2[58];
} PCXHEAD;

// PCX functions for x_size by y_size by 256 PCX's
typedef struct {
  int x_size;         // Width of the PCX
  int y_size;	      // Height of the PCX
  char *image;	      // Points to the PCX's image data
  char palette[768];  // Points to the PCX's palette data
  PCXHEAD pcxheader;  // Header from the PCX
} GUG_PCX;


GUG_PCX *GUGReadPCX(char *file);
void GUGFreePCX(GUG_PCX *gug_pcx);
void GUGShowPCX(int x,int y,GUG_PCX *gug_pcx);
int  GUGWritePCX(char *file,
                 int x_start, int y_start,
                 int x_size,  int y_size,
                 unsigned char *palette);
PCXHEAD *GUGGetPCXHeader(char *file);
void GUGRotatePCX90(GUG_PCX *gug_pcx);

// Functions to treat PCX images like sprites
void GUGPutFGPCX(int xb,int yb,GUG_PCX *pcx);
void GUGPutBGPCX(int xb,int yb,GUG_PCX *pcx);
void GUGPutMNPCX(int xb,int yb,int c,GUG_PCX *pcx);

// Sprite Shifting Functions
void GUGShiftSpriteRight(char *sprite);
void GUGShiftSpriteLeft(char *sprite);
void GUGShiftSpriteUp(char *sprite);
void GUGShiftSpriteDown(char *sprite);

// Sprite Rotation/Flipping
void GUGSpriteRotate90(char *sprite);
void GUGSpriteVFlip(char *sprite);
void GUGSpriteHFlip(char *sprite);

// Sprite Get/Set Pixel Functions
int  GUGGetSpritePixel(int xpos, int ypos, char *spr);
void GUGSetSpritePixel(int xpos, int ypos, int color, char *spr);

// Image Warping Functions
// Resizes from a rectangle in the buffer to a rectangle in the buffer
void GUGResizeRectangle(int xs1,int ys1,int xs2,int ys2,int xd1,int yd1,int xd2,int yd2);
// Resizes from a sprite to a rectangle in the buffer
void GUGResizeSpriteToRectangle(char *spr,int xd1,int yd1,int xd2,int yd2);
// Resizes from a sprite to a sprite
char *GUGResizeSpriteToSprite(char *fspr,int xsize,int ysize);

// PIX Routines
void GUGPIXSetColor(int c);
void GUGPIXErase();
void GUGPIXSet(int x,int y);
void GUGPIXMove(int x,int y);
void GUGPIXLine(int x,int y);
void GUGPIXRGBLog(int i, float r, float g, float b);
//void GUGPIXPoly(int n,PolyList list);

// Timer Functions
void GUGStartTimer(void);
int  GUGStopTimer(void);
void GUGInitTimer(void);

// Experimental ASM functions
void GUGFastClear(char *c);
void GUGFastCopy(char *c);

// These are in init.c
extern char *VGA_MEMORY;    // Points to the 100K memory buffer
extern char *VGA_START;     // Points to the displayed part of VGA_MEMORY
extern char *VGA_POINTER;	// Points to the VGA Cards memory

extern int GUG_Font_Height;     // height of the font in pixels
extern int GUG_Font_Width;      // width of the font in pixels

extern char GUG_Old_Palette[];  // Holds the original palette
extern char GUG_666_Palette[];	// Holds the 666 palette

// Polygon Routines
typedef struct  {
  int x;
  int y;
}GUGVertex;
int  GUGFillPoly(int color, int points, GUGVertex poly[]);
extern int GUG_Poly_No_Cross;
void GUGPoly(int color, int points, GUGVertex poly[]);

// Joystick Globals
extern int GUGJ1XMax,GUGJ1XMin,GUGJ1YMax,GUGJ1YMin;
extern int GUGJ2XMax,GUGJ2XMin,GUGJ2YMax,GUGJ2YMin;
extern int GUGX1Active;
extern int GUGX2Active;

// PIX Globals
extern int pix_x;   // X Pixel Location
extern int pix_y;	// Y Lixel Location
extern int pix_c;	// Draw Color
#define PIX_MAXPOLY 32
#define PIX_TABNUM 256
#define PIX_NXPIX  320
#define PIX_NYPIX  200

// Draw Rectangle Stuff
extern int GUG_rect_index;        // Index into GUG_rect
extern int GUG_rect[128][4];	  // GUG_rect array

// Joystick detection functions
int GUGDetectX1();
int GUGDetectX2();

// Joystick 1 Raw Values
int GUGReadX1Axis();
int GUGReadY1Axis();
// Joystick 2 Raw Values
int GUGReadX2Axis();
int GUGReadY2Axis();

// Joystick 1 Scaled Values
int GUGScaleX1Axis();
int GUGScaleY1Axis();
// Joystick 2 Scaled Values
int GUGScaleX2Axis();
int GUGScaleY2Axis();

// Read the joystick buttons
int GUGReadButtons();

// Calabrate the Joysticks
int GUGJoystickCalibrate(void);

// Defines to test individual buttons
#define J1_B1 0x01
#define J1_B2 0x02
#define J2_B1 0x04
#define J2_B2 0x08

//**************************************************************************
// Ground Up's Keyboard Handler
//**************************************************************************
// functions
int						GUGScanKeyHit(void);
char					GUGGetScanCode(void);
int           GUGKeyHit(void);
char          GUGGetKey(void);
int           GUGKeyDown(void);
void          GUGStartKeyboard(void);
void          GUGStopKeyboard(void);
void          GUGFlushKey(void);
void          GUGWaitForKey();	// wait for a key press

// globals
extern char          GUG_key_lower_array[127];
extern unsigned char GUG_key_table[128];        // key state table for arrow keys
extern int           GUG_KBD_Installed;

//**************************************************************************
// GUG Sprite Mouse Stuff
//**************************************************************************
extern int  SHOW_SPRITE_MOUSE;  // Sprite Mouse is hidden
extern char *GUG_Sprite_Mouse;	// Pointer to the Mouse Sprite to use
void GUGSMShow();  // Show the sprite mouse
void GUGSMHide();  // Hide the sprite mouse
void GUGSMCopyToDisplay(int mouse_x, int mouse_y); // Copy page
void GUGSMBufferPut(int x, int y);  // Same As Copy Page
void GUGSMVGAPut(int x, int y);     // Put mouse to VGA
void GUGSMDraw(int xb,int yb);      // Put mouse in buffer, remember background
void GUGSMUnDraw(void);             // put background back.


//**************************************************************************
// Include file for Ground Up's Mouse handler
//**************************************************************************

extern union  REGS inregs, outregs;
extern struct SREGS segreg;

#define MOUSE_LOADED -1
#define MOUSE_FAILED  0

#define MOUSE_NO_BUTTON     0
#define MOUSE_BUTTON_LEFT   1
#define MOUSE_BUTTON_RIGHT  2

void GUGMouseReset(int *mstatus, unsigned int *nbutton);
void GUGMouseShow(void);
void GUGMouseHide(void);
void GUGMousePosition(unsigned int *mpressed, unsigned int *mx,
                      unsigned int *my);
void GUGMouseButtonPress(unsigned int mbutton, unsigned int *mbstate,
	                     unsigned int *numpress, unsigned int *mx,
	                     unsigned int *my);
void GUGMouseButtonRelease(unsigned int mbutton, unsigned int *mbstatus,
	                       unsigned int *numrelease, unsigned int *mx,
	                       unsigned int *my);
void GUGMouseHorizontalLimit(unsigned int min, unsigned int max);
void GUGMouseVerticalLimit(unsigned int min, unsigned int max);
void GUGMousePut(unsigned int mx, unsigned int my);
void GUGMouseGraphicsCursor(int *cursor, unsigned int hotx, unsigned int hoty);
void GUGMouseTextCursor(unsigned int type, unsigned int screen,
                        unsigned int cursor);
void GUGMouseReadMotion(unsigned int *hcount, unsigned int *vcount);
void GUGMouseDefineInterupt(void far *routine, unsigned int mask);
void GUGMouseLightPenOn(void);
void GUGMouseLightPenOff(void);
void GUGMouseMickeyToPixel(unsigned int mickeyx, unsigned int mickeyy);
void GUGMouseDefineUpdate(unsigned int tlx, unsigned int tly, unsigned int brx,
	                  unsigned int bry);
void GUGMouseDefineThreshold(unsigned int speed);
void far *GUGMouseExchangeInterupt(void far *subroutine, unsigned int mask);
void GUGMouseDriverSpace(void far *buffer);
void GUGMouseSaveDriver(void far *buffer);
void GUGMouseRestoreDriver(void far *buffer);
int  GUGMouseAlternteInterupt(void far *routine, unsigned int mask);
void GUGMouseSensitivity(unsigned int hnum, unsigned int vnum,
                         unsigned int dst);
void GugMouseReadSensitivity(unsigned int *hnum, unsigned int *vnum,
                             unsigned int *dst);
void GUGMouseSetInteruptRate(unsigned int rate);
void GUGMouseDefinePage(unsigned int page);
unsigned int GUGMouseReturnPage(void);
void far *GUGMouseDisableDriver(void);
int  GUGMouseReenableDriver(void);
int  GUGMouseSoftwareReset(void);
void GUGMouseSetLanguage(unsigned int number);
unsigned int GUGMouseGetLanguage(void);
void GUGMouseReadInfo(unsigned int *major, unsigned int *minor,
                      unsigned int *type,  unsigned int *irq);
void GUGMouseReadDriverInfo(unsigned int *info, unsigned int *fCursorLock,
	                    unsigned int *fInMouseCode,
                            unsigned int *fMouseBusy);
void GUGMouseReadMAXVDC(unsigned int *enable, unsigned int *xmax,
                        unsigned int *ymax);
void GUGMouseReadCursor(unsigned int *screen, unsigned int *cursor,
                        unsigned int *hcount, unsigned int *vcount);
unsigned int GUGMouseSetVideoMode(unsigned int mode, unsigned int font);
void far *GUGMouseListVideoModes(void);
void GUGMouseReadHotSpot(unsigned int *fCursor, unsigned int *hhot,
                         unsigned int *vhot,	unsigned int *type);
unsigned int GUGMouseLoadCurves(unsigned int number, void far *curves);
void far *GUGMouseSaveCurves(unsigned int *curve, unsigned int *success);
char far *GUGMouseActiveCurves(int number, unsigned int *success,
                               unsigned int *curve);
int  GUGMouseHardReset(void);
void GUGMouseBallPoint(unsigned int command, int rotation, int *status,
                       unsigned int *angle, unsigned int *masks);
void GUGMouseGetVSC(unsigned int *xmin, unsigned int *ymin,unsigned int *xmax,
                    unsigned int *ymax);
unsigned int GUGMouseGetAdvanced(void);
int *GUGMouseSwitch(unsigned int *size);
char far *GUGMouseLocateINI(void);

// Mono card debug routines
void GUGDebugString(char *str);
void GUGDebugStringAtLine(char *str,int line);
void GUGDebugStringAtXY(char *str,int col,int line);
void GUGDebugClear();

#ifdef __cplusplus
};
#endif

#endif  // of _GUG_H
