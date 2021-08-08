#include <stdio.h>
#include <gug.h>
#include <colors.h>
#include <keydefs.h>
#include <math.h>

void main(int argc,char *argv[])
{
  int i,x,y;
  int p=1;
  GUG_FONT font1,font2,font3;
  char mes[80];

  if (GUGLoadFont("gf4x6.spr",&font1) == GUG_FONT_FAIL)
  {
    printf("Failed to load font gf4x6.spr\n");
	return;
  }

  if (GUGLoadFont("gf6x8.spr",&font2) == GUG_FONT_FAIL)
  {
    printf("Failed to load font gf6x8.spr\n");
	return;
  }

  if (GUGLoadFont("gf5x10.spr",&font3) == GUG_FONT_FAIL)
  {
    printf("Failed to load font gf5x10.spr\n");
	return;
  }

  GUGInitialize();

  p = 0;

  do {

  GUGClearDisplay();

  x = y = 0;

  if (gug_font > NULL)
  {
  for (i=0; i<94; ++i)
  {
    GUGPutBGSprite(x,y,gug_font->chars[i]);
    x += gug_font->x_size;
	if ((x + gug_font->x_size) > 320)
	{
	  x = 0;
	  y += gug_font->y_size;
	}
  }

  sprintf(mes,"Loaded font is %1dx%1d pixels - %d",
          gug_font->x_size,gug_font->y_size,p);
  GUGCenterFont(70,YELLOW,GUG_NONE,mes);
  }
  else
  {
  GUGCenterFont(0,RED,GUG_NONE,"Defaulting to the GLYPH font!");
  }

  GUGPrintFont( 0, 90,WHITE ,GUG_NONE,"White Text");
  GUGPrintFont(10,110,RED   ,WHITE   ,"Red Text on White background");
  GUGPrintFont(20,130,BLUE  ,GUG_NONE,"Blue Text");
  GUGPrintFont(30,150,ORANGE,GREEN   ,"Orange Text on Green background");
 
  GUGCenterFont(170,GREEN,WHITE,"A line of centered text!");
  GUGCenterFont(190,GUG_NONE,GUG_NONE,"Native Font Color!");

  GUGCopyToDisplay();

  if (!(p % 500))
  {
    if (gug_font == &font1)
     GUGSetFont(font2);
    else if (gug_font == &font2)
     GUGSetFont(font3);
    else if (gug_font == &font3)
     gug_font = NULL;
    else if (gug_font == NULL)
     GUGSetFont(font1);
  }

  p++;
  }
  while (!kbhit());

  GUGEnd();
}

