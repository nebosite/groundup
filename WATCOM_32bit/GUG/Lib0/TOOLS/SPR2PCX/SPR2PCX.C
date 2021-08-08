#include <stdio.h>
#include <gug.h>
#include <math.h>

void main(int argc,char *argv[])
{
  char *spr[1024];
  int  i,s,x,y,maxy,st;

  if (argc < 3)
  {
    printf("\n\nSprite to PCX Converter - Version 0.1 - GUG Version %s\n",GUGVersion());
	printf("  Copyright 1995-1996 Ground Up Software\n");
    printf("  usage: spr2666 infile.spr outfile.pcx [start_sprite]\n\n\n");
	return;
  }     

  if ((s=GUGLoadSprite(argv[1],spr)) < 0)
  {
    printf("Failed to load %s\n",argv[1]);
	return;
  }

  GUGInitialize();

  GUGClearDisplay();

  x    = 0;
  y    = 0;
  maxy = 0;

  st = 0;
  if (argc > 3)
  {
    st = atoi(argv[3]);
  }

  for (i=st; i<s; ++i)
  {
    GUGPutBGSprite(x,y,spr[i]);
	x += GUGSpriteWidth(spr[i]);
    if (GUGSpriteHeight(spr[i]) > maxy)
    {
	  maxy = GUGSpriteHeight(spr[i]); 
    }
	if (GUGSpriteWidth(spr[i+1]) > (320-x))
	{
      x    = 0;
	  y   += maxy;
	  maxy = 0;
	}
  }

  GUGCopyToDisplay();

  do {} while (!kbhit());
  getch();

  GUGSavePCX(argv[2],VGA_POINTER,GUG_666_Palette);

  GUGEnd();
}

