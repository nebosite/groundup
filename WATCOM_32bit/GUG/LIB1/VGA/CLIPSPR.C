#include <stdio.h>
#include "vga.h"
#include "mode.h"
#include "..\gug.h"
#include <malloc.h>

int GUGCalcSize(int x,int y);

char *GUGClipSprite(int xstart, int ystart, int xstop, int ystop)
{
   char *vga_mem;
   char *buffer;
   int size,xsize,ysize,n,x,y;
   
   xsize = xstop - xstart + 1;
   ysize = ystop - ystart + 1;
   size  = GUGCalcSize(xsize,ysize);

   if ((buffer = (char *)malloc(size)) == NULL) {
     return(NULL);
   }
   
   buffer[0] = (char)(xsize & 0xFF);
   buffer[1] = (char)((xsize & 0xFF00) >> 8);
   buffer[2] = (char)(ysize & 0xFF);
   buffer[3] = (char)((ysize & 0xFF00) >> 8);
//   buffer[1] = '\0';
//   buffer[3] = '\0';
   n = 4;

   for (y=ystart; y<=ystop; ++y) {
     for (x=xstart; x<=xstop; ++x) {
       vga_mem = (char *)VGA_POINTER + x + (y * 320); 
       buffer[n] = *vga_mem;
       n++;
	 }
   }
   return(buffer);
}


/**************************************************************************
	char *GUGBlockGet(int xstart, int ystart, int xstop, int ystop)

	DESCRIPTION:  Grabs a block from the work area and stuffs it into an
								allocated chunk of memory.

**************************************************************************/
char *GUGBlockGet(int xstart, int ystart, int xstop, int ystop, RasterBlock *rblk)
{
	 char *vga_mem;
	 char *buffer;
	 int xsize,ysize,y;

	 xsize = xstop - xstart + 1;
	 ysize = ystop - ystart + 1;

	 rblk->width = xsize;
	 rblk->height = ysize;

	 buffer = rblk->data;
	 vga_mem = (char *)VGA_START + xstart + (ystart * X_WRAP_SIZE);

	 for (y=ystart; y<=ystop; ++y) {
		 memcpy(buffer,vga_mem,xsize);
		 buffer += xsize;
		 vga_mem += X_WRAP_SIZE;
	 }
   return(buffer);
}
