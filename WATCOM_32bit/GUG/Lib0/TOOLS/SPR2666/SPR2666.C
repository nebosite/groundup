#include <stdio.h>
#include <gug.h>
#include <math.h>

void map_palette(int *xlate,char *from, char *too);

void main(int argc,char *argv[])
{
  char from_pal[768];
  char *spr[1024];
  int  c,i,s,x,y;
  int  xlate[256];

  if (argc < 4)
  {
    printf("\n\nSprite 666 Palette Converter - Version 0.1 - GUG Version %s\n",GUGVersion());
	printf("  Copyright 1995-1996 Ground Up Software\n");
    printf("  usage: spr2666 infile.spr outfile.spr from.pal\n\n\n");
	return;
  }     

  if ((s=GUGLoadSprite(argv[1],spr)) < 0)
  {
    printf("Failed to load %s\n",argv[1]);
	return;
  }

  if (GUGLoadPalette(argv[3],from_pal) != 1)
  {
    printf("Failed to load %s\n",argv[3]);
	return;
  }


  GUGInitialize();

  GUGClearDisplay();
  GUGSetPalette(from_pal);

  c = 0;
  for (y=0; y<16; ++y)
  {
    for (x=0; x<16; ++x)
    {
	  GUGFillRectangle((x*16),(y*12),(x*16)+16,(y*12)+12,c);
      c++;
	}
  }
  
  for (i=0; i<s; ++i)
  {
    GUGPutBGSprite(280,0+(i*32),spr[i]);
  }

  GUGCopyToDisplay();

  do {} while (!kbhit());
  getch();

  GUGSetPalette(GUG_666_Palette);
  GUGCopyToDisplay();

  do {} while (!kbhit());
  getch();

  map_palette(xlate,from_pal,GUG_666_Palette);

  for (i=0; i<s; ++i)
  {
    for (x=0; x<GUGSpriteWidth(spr[i]); ++x)
	{
	  for (y=0; y<GUGSpriteHeight(spr[i]); ++y)
	  {
	    c = GUGGetSpritePixel(x,y,spr[i]);
	    GUGSetSpritePixel(x,y,xlate[c],spr[i]);
      }
      GUGPutBGSprite(280,0+(i*32),spr[i]);
      GUGCopyToDisplay();
	}
  }

  GUGSaveSprite(argv[2],spr,s-1);

  GUGEnd();
}

//////////////////////////////////////////////////////////////////////////
void map_palette(int *xlate,char *from, char *too)
{
  int x,i;
  int d1,d2,d3;
  int t1,t2,t3;

  for (x=0; x<256; ++x)
  {
    xlate[x] = -1;
  }

  for (i=0; i<768; i+=3)
  {
    t1 = t2 = t3 = 9999;
    for (x=765; x>=0; x-=3)
	{
	  d1 = abs(from[i]   - too[x]);
	  d2 = abs(from[i+1] - too[x+1]);
	  d3 = abs(from[i+2] - too[x+2]);
	  if ( (d1 <= t1) &&
	       (d2 <= t2) &&
		   (d3 <= t3) )
	  {
	    t1 = d1;
	    t2 = d2;
	    t3 = d3;
		xlate[i/3] = x/3;
	  }
	}
  }
}

