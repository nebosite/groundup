#include <stdio.h>
#include <gug.h>
#include <malloc.h>

void main(int argc,char *argv[])
{
  int  c,i,s,x,y;
  int  xlate[256];
  GUG_PCX *gug_pcx;

  if (argc < 2)
  {
    printf("\n\nPCX 666 Palette Converter - Version 0.3 - GUG Version %s\n",GUGVersion());
	printf("  Copyright 1995-1996 Ground Up Software\n");
    printf("  usage: pcx2666 infile.pcx outfile.pcx\n\n\n");
	return;
  }     

  if ((gug_pcx = GUGReadPCX(argv[1])) == NULL)
  {
    printf("Failed to load %s\n",argv[1]);
	return;
  }

  GUGInitialize();

  GUGClearDisplay();
  GUGSetPalette(gug_pcx->palette);
  GUGShowPCX(0,0,gug_pcx);
  GUGCopyToDisplay();

  do {} while (!kbhit());
  getch();

  GUGSetPalette(GUG_666_Palette);

  do {} while (!kbhit());
  getch();

  GUGRemapPalette(xlate,gug_pcx->palette,GUG_666_Palette);

  for (x=0; x<320; ++x)
  {
    for (y=0; y<200; ++y)
	{
	  GUGSetPixel(x,y,xlate[GUGGetPixel(x,y)]);
    }
  }

  GUGCopyToDisplay();
 
  GUGWritePCX(argv[2],
              0,0,
			  gug_pcx->x_size,gug_pcx->y_size,
			  GUG_666_Palette);

  do {} while (!kbhit());
  getch();

  GUGEnd();
}
