//*************************************************************************
// Put a PCX on the screen as if it was a sprite
//
#include "vga.h"
#include "mode.h"

/* pcx file header structure */
typedef struct	{
	char  manufacturer;
	char  version;
	char  encoding;
	char  bits_per_pixel;
	short xmin, ymin;
	short xmax, ymax;
//        short hres;
//        short vres;
        unsigned short check_one;
        unsigned short check_two;
        char  sname[21];
        char  filler1[27];
//        char  palette[48];
        char  reserved;
	char  color_planes;
	short bytes_per_line;
	short palette_type;
        char  filler2[58];
} PCXHEAD;

// PCX functions for x_size by y_size by 256 PCX's
typedef struct {
  int x_size;         // Width of the PCX
  int y_size;	      // Height of the PCX
  char *image;	      // Points to the PCX's image data
  char palette[768];  // Points to the PCX's palette data
  PCXHEAD pcxheader;  // Header from the PCX
} GUG_PCX;

void GUGPutBGPCX(int xb,int yb,GUG_PCX *pcx)
{
  int   x,xs,y,ys;
  char  *write;
  char  *spr, *spr_end, *spr_sub_end;
  int   write_inc;

  // Get the X/Y sizes
  xs = pcx->x_size;
  ys = pcx->y_size;
  spr = pcx->image;

//  xs =  *spr++; 
//  xs += (*spr++ * 256);
//  ys =  *spr++; 
//  ys += (*spr++ * 256);

  // Clip it to the screen
  if (xb <= (0-xs)         || 
      xb >  (MAX_X_SIZE-1) || 
      yb <= (0-ys)         || 
      yb >  (MAX_Y_SIZE-1)) 
     return;

//  xb += MAX_X_SIZE;		// offset for clipping area
//  yb += MAX_Y_SIZE;
  // compute start address in vga page.
  write = ((char *)VGA_START + (yb * X_WRAP_SIZE)) + xb;

  // compute difference between length of VGA line + clip area and width of
  // sprite.
  write_inc = X_WRAP_SIZE - xs;

  // nice tight loop.

  spr_end = spr + xs * ys;
  do {
	spr_sub_end = spr + xs;
	switch (xs & 0x7) {
	case 7:
	  *write=*spr;
	  spr++;
	  write++;
	case 6:
	  *write=*spr;
	  spr++;
	  write++;
	case 5:
	  *write=*spr;
	  spr++;
	  write++;
	case 4:
	  *write=*spr;
	  spr++;
	  write++;
	case 3:
	  *write=*spr;
	  spr++;
	  write++;
	case 2:
	  *write=*spr;
	  spr++;
	  write++;
	case 1:
	  *write=*spr;
	  spr++;
	  write++;
	}
	if (spr < spr_sub_end)
      do {
	    *write=*spr;
	    spr++;
	    write++;
	    *write=*spr;
	    spr++;
	    write++;
	    *write=*spr;
	    spr++;
	    write++;
	    *write=*spr;
	    spr++;
	    write++;
	    *write=*spr;
	    spr++;
	    write++;
	    *write=*spr;
	    spr++;
	    write++;
	    *write=*spr;
	    spr++;
	    write++;
	    *write=*spr;
	    spr++;
	    write++;
	  } while (spr < spr_sub_end);
    write += write_inc;
  }	while (spr < spr_end);

/*
  // nice tight loop.
  for (y=0; y<ys; ++y) {
    for (x=0; x<xs; x++) {
	  *write=*spr;
	  spr++;
	  write++;
	}
    write += write_inc;
  }
*/
}	
