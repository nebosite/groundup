#include <string.h>
#include "vga.h"
#include "mode.h"
 
void GUG_display_character(int xpos,int ypos,int color,int c);

//**************************************************************************
// Write text on the screen
//
void GUGPutText(int xpos,int ypos,int color,char *buf) {
  int x,p;

  // clip to the screen
  if ((ypos < 0) || (ypos > (MAX_Y_SIZE-1))) return;

  for (x=xpos,p=0; p<strlen(buf); ++p,x+=GUG_Font_Width)	  // x+=8
  {
   if ((x > -1) && (x < MAX_X_SIZE)) {		  
       GUG_display_character(x,ypos,color,(int)buf[p]);
    }
  }
}

void GUG_display_character(int xpos,int ypos,int color,int chr) {
  char *glyph;
  char *screen;
  int x,y;
  int c;

//  xpos += MAX_X_SIZE;
//  ypos += MAX_Y_SIZE;

//  glyph  = (char *)0x000ffa6e + (chr * 8);
    glyph  = (char *)&font[0]   + (chr * 8);

  for (y=ypos; y<ypos+8; ++y,++glyph) {
    c = (int)*glyph;

    screen = (char *)VGA_START + xpos + (y * X_WRAP_SIZE);

    if (c & 128) *screen     = color;
    if (c &  64) *(screen+1) = color;    
    if (c &  32) *(screen+2) = color;    
    if (c &  16) *(screen+3) = color;
    if (c &   8) *(screen+4) = color;
    if (c &   4) *(screen+5) = color;
    if (c &   2) *(screen+6) = color;
    if (c &   1) *(screen+7) = color;
  }
}

