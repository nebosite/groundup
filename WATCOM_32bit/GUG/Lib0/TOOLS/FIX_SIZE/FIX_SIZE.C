#include <stdio.h>
#include <gug.h>
#include <math.h>

void main(int argc,char *argv[])
{
  char *inspr[1024];
  char *outspr[1024];
  int  i,x,y,s;

  if (argc < 4)
  {
    printf("\n\nSprite Size Fixer - Version 0.1 - GUG Version %s\n",GUGVersion());
	printf("  Copyright 1995-1996 Ground Up Software\n");
    printf("  usage: fix_size infile.spr x_size y-size\n\n\n");
	return;
  }     

  if ((s=GUGLoadSprite(argv[1],inspr)) < 0)
  {
    printf("Failed to load %s\n",argv[1]);
	return;
  }

  x = atoi(argv[2]);
  y = atoi(argv[3]);

  if ((x > 320) || (x < 1))
  {
    printf("Illegal X size specified:%d\n",argv[2]);
	return;
  }

  if ((y > 200) || (y < 1))
  {
    printf("Illegal Y size specified:%d\n",argv[3]);
	return;
  }

  if (s > 1024)
  {
    printf("More that 1024 sprites in the SPR file, aborting!\n");
	return;
  }

  GUGInitialize();

  for (i=0; i<s; ++i)
  {
    GUGClearDisplay();
    GUGPutBGSprite(0,0,inspr[i]);
    GUGCopyToDisplay();
	outspr[i] = GUGClipSprite(0,0,x-1,y-1);
  }

  GUGSaveSprite(argv[1],outspr,s-1);

  GUGEnd();
}

