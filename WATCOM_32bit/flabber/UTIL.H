// Utilities for Flabbergasted (include file)
// Eric Jorgensen (1997)

#include "\watcom\gug\lib1\gug.h"

//#define getcos(X) fpFastCos[X%360]
//#define getsin(X) fpFastSin[X%360]

#define fontwidth()  *(gpFont)
#define fontheight() *(gpFont+1)

extern int giPrintTransparent;
extern int giItalicsOn;
extern int giBoldOn;
extern int giUnderlineOn;
extern int giShadowOn;
extern char *gpFont;
extern char *gpFontData[20];
extern int giPrintX;
extern int giPrintY;
extern int giTabStop;

extern double fpFastSin[360];
extern double fpFastCos[360];


int random(int rmax);
long memleft(void);
int getarccos(int value);
void initutils(void);
void drwchar(PIXELMODE pmode, int fgcolor, int bgcolor, int x, int y, char c);
void print(PIXELMODE pmode, int fgcolor,int bgcolor, int x, int y, char *s, ...);

inline double getcos(int x) { return fpFastCos[x%360];}
inline double getsin(int x) { return fpFastSin[x%360];}
