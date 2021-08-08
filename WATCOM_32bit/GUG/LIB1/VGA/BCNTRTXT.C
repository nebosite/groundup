//*************************************************************************
// Center a line of text on the screen
#include <string.h>
#include "mode.h"

extern int  GUG_Font_Width;
extern int  GUGTextWidth(char *text);
extern void GUGPutText(int xpos,int ypos,int color,char *buf);
void  GUGFillRectangle(int xstart, int ystart,
                       int xstop,  int ystop,
                       int color);

 
void GUGCenterFrameText(int y, int text_c, char *txt, int bg_color)
{
  int x,l;
  x = (strlen(txt) * GUG_Font_Width);
  l = x;
  x = MAX_X_SIZE - x;   // Screen is 320 pixels
  x = x / 2;
  GUGFillRectangle(x-1,y-1,x+l,y+7,bg_color);
  GUGPutText(x,y,text_c,txt);
}       
