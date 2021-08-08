//
// Add loadable fonts to GUG
//

#include <stdio.h>
#include <malloc.h>
#include "..\..\gug.h"

//typedef struct
//{
//  int x_size;
//  int y_size;
//  char *chars[94];
//} GUG_FONT;


int GUGLoadFont(char *fontname,GUG_FONT *font)
{

  if (GUGLoadSprite(fontname,font->chars) < 1)
  {
    return(GUG_FONT_FAIL);
  }

  font->x_size = GUGSpriteWidth(font->chars[0]);
  font->y_size = GUGSpriteHeight(font->chars[0]);

  gug_font = font;

  return(GUG_FONT_OK);
}

void GUGPrintFont(int x,int y,int clr,int bkg,char *txt)
{
  int  l,len;
  char c;

  len = strlen(txt);

  if (gug_font == NULL)
  {
    if (bkg > GUG_NONE)
    {
      GUGFillRectangle(x-1,y-1,
                       x+(len*GUG_Font_Width),
					   y+GUG_Font_Height,bkg);
    }
    GUGPutText(x,y,clr,txt);
	return;
  }

  if (bkg > GUG_NONE)
  {
    GUGFillRectangle(x-1,y-1,
                     x+(len*gug_font->x_size),
					 y+gug_font->y_size,bkg);
  }

  for (l=0; l<len; ++l)
  {
    c = txt[l];
	if ((c > 32) && (c < 127))
	{
	  if (clr > -1)
          GUGPutMNSprite(x,y,clr,gug_font->chars[c-33]);
      else
          GUGPutFGSprite(x,y,gug_font->chars[c-33]);
	}
    x += gug_font->x_size;;
  }
}

void GUGCenterFont(int y,int clr,int bkg,char *txt)
{
  int  l,len;
  char c;
  int  x;

  len = strlen(txt);

  if (gug_font == NULL)
  {
    if (bkg > GUG_NONE)
    {
      x = len * GUG_Font_Width;
      x = x / 2;
      x = 160 - x;
      GUGFillRectangle(x-1,y-1,
                       x+(len*GUG_Font_Width),
					   y+GUG_Font_Height,bkg);
    }
     GUGCenterText(y,clr,txt);
	return;
  }

  x = len * gug_font->x_size;
  x = x / 2;
  x = 160 - x;

  if (bkg > GUG_NONE)
  {
    GUGFillRectangle(x-1,y-1,
                     x+(len*gug_font->x_size),
  				     y+gug_font->y_size,bkg);
  }

  for (l=0; l<len; ++l)
  {
    c = txt[l];
	if ((c > 32) && (c < 127))
	{
	  if (clr > -1)
          GUGPutMNSprite(x,y,clr,gug_font->chars[c-33]);
      else
          GUGPutFGSprite(x,y,gug_font->chars[c-33]);
	}
    x += gug_font->x_size;;
  }
}

void GUG_set_font(GUG_FONT *font)
{
  if (font > NULL)
    gug_font = font;
}
