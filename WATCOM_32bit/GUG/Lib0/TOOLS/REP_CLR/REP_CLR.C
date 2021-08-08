#include <stdio.h>
#include <i86.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <string.h>
#include <gug.h>

#define MAX                 1024

void main(int argc,char *argv[]) {
  char  *spr[MAX];
  int   from,too;
  int   count,x,y,i;
  int   x_size,y_size;
  char  txt[80];
  int   rep = 0;

  if (argc < 3) {
    printf("\n\nColor Replace Utility - Version 0.3 - GUG Version %s\n",GUGVersion());
	printf("  Copyright 1995-1996 Ground Up Software\n");
    printf("  usage: rep_color file.spr from_color_index too_color_index\n\n\n");
	return;
  }

  for (i=0; i<MAX; ++i) {
    spr[i] = NULL;
  }

  if ((count = GUGLoadSprite(argv[1],(char **)spr)) < 1) {
    printf("Error - Sprite file not found\n");
    return;
  }

  if (GUGSaveSprite("backout.bak",(char **)spr,count-1) != 1) {
    printf("Error creating backout file 'backout.bak'");
    return;
  }

  from = atoi(argv[2]);
  too  = atoi(argv[3]);

  GUGInitialize();

  for (i=0; i<MAX && (spr[i] > NULL); ++i)
  {
    GUGClearDisplay();
    GUGPutFGSprite(0,80,spr[i]);
    x_size  = spr[i][0];
    x_size += (spr[i][1] * 256);
    y_size  = spr[i][2];
	y_size += (spr[i][3] * 256);

    sprintf((char *)txt,"Sprite %3d  -  x:%2d by y:%2d",i,x_size,y_size);
    GUGPutText(20,190,20,(char *)txt);

    for (y=0; y<y_size; y++) {
	  for (x=0; x<x_size; ++x) {
        if (spr[i][(y*x_size)+x+4] == from) {
		  spr[i][(y*x_size)+x+4] = too;
          rep++;
		}
      }
	}
    GUGCopyToDisplay();
  }

  GUGEnd();

  if (GUGSaveSprite(argv[1],(char **)spr,count-1) != 1) {
    printf("Error saving changes.'");
    return;
  }

  printf("Processed file : %s\n",argv[1]);
  printf("Created files  : backout.bak (original sprite file)\n");
  printf("Replaced index %1d with index %1d\n",from,too);
  printf("%1d pixels were replaced\n",rep);
  printf("Program Terminated Normally\n");
}
