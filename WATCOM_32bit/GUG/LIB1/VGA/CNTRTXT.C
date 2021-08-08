//*************************************************************************
// Center a line of text on the screen
//
// GUG2.0
//

#include <string.h>
#include "mode.h"

extern int  GUG_Font_Width;
extern int  GUGTextWidth(char *text);
extern void GUGPutText(int xpos,int ypos,int color,char *buf);
 
void GUGCenterText(int y, int c, char *txt)
{
  int x;
  x = (strlen(txt) * GUG_Font_Width);
  x = MAX_X_SIZE - x;   // Screen is 320 pixels
  x = x / 2;
  GUGPutText(x,y,c,txt);
}       
