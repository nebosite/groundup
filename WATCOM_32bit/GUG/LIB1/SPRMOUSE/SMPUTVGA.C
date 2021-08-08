//**************************************************************************
// This function Draws the mouse cursor to VGA only
//

#include "..\vga\vga.h"
#include "..\vga\mode.h"


/**************************************************************************
	void putvgaspr(int xb,int yb,char spr[])

	DESCRIPTION: internal sprite put routine that writes directly to VGA

**************************************************************************/
void putvgaspr(int xb,int yb,char spr[])
{
	int width,height,adjusted_width;
	int xstart,xend;
	int ystart,yend;
	int x,y,i;
	char *data,*writespot;

																	// Get dimensions on the sprite
	width = *((short int *)spr);
	height = *((short int *)(spr+2));

	xstart = ystart = 0;
	xend = width;
	yend = height;

	//width=16;
	//height = 16;

																	// Clip it to the screen
	if(xb < 0) xstart = -xb;
	if(xb+width >= MAX_X_SIZE) xend =  - (xb - MAX_X_SIZE);
	adjusted_width = xend-xstart;

	if(yb < 0) ystart = -yb;
	if(yb+width >= MAX_Y_SIZE) yend =  - (yb - MAX_Y_SIZE);

																	// draw it
	for(y = ystart; y < yend; y++) {
																				// Set pointers
		data = spr+4 + y*width + xstart;
		writespot = VGA_POINTER + (y+yb) * MAX_X_SIZE + xb + xstart;

																				// GO through a line of pixels
		for(i = 0; i < adjusted_width; i++) {
			if(*data) *writespot = *data;
			data++;
			writespot++;
		}
	}




/*


  int   x,xs,y,ys;
  char  *write,*spr_end,*spr_sub_end;
  int   write_inc;

  // Get the X/Y sizes
  xs =  *spr++; 
  xs += (*spr++ * 256);
  ys =  *spr++; 
  ys += (*spr++ * 256);

  // Clip it to the screen
  if (xb <= (0-xs)         || 
      xb >  (MAX_X_SIZE-1) || 
      yb <= (0-ys)         || 
      yb >  (MAX_Y_SIZE-1)) 
     return;

//  xb += MAX_X_SIZE;		// offset for clipping area
//  yb += MAX_Y_SIZE;
  // compute start address in vga page.
	write = ((char *)VGA_POINTER + (yb * MAX_X_SIZE)) + xb;

  // compute difference between length of VGA line + clip area and width of
  // sprite.
	write_inc = MAX_X_SIZE - xs;

  spr_end = spr + xs * ys;
  do {
	spr_sub_end = spr + xs;
	switch (xs & 0x7) {
	case 7:
	  if (*spr) *write=*spr;
	  spr++;
		write++;
	case 6:
		if (*spr) *write=*spr;
	  spr++;
	  write++;
	case 5:
	  if (*spr) *write=*spr;
	  spr++;
	  write++;
	case 4:
		if (*spr) *write=*spr;
	  spr++;
	  write++;
	case 3:
	  if (*spr) *write=*spr;
	  spr++;
	  write++;
	case 2:
	  if (*spr) *write=*spr;
	  spr++;
	  write++;
	case 1:
	  if (*spr) *write=*spr;
	  spr++;
	  write++;
	}
	if (spr < spr_sub_end)
      do {
	    if (*spr) *write=*spr;
	    spr++;
	    write++;
	    if (*spr) *write=*spr;
	    spr++;
	    write++;
	    if (*spr) *write=*spr;
	    spr++;
	    write++;
	    if (*spr) *write=*spr;
	    spr++;
	    write++;
	    if (*spr) *write=*spr;
	    spr++;
	    write++;
			if (*spr) *write=*spr;
			spr++;
			write++;
			if (*spr) *write=*spr;
			spr++;
			write++;
			if (*spr) *write=*spr;
			spr++;
			write++;
		} while (spr < spr_sub_end);
		write += write_inc;
	}	while (spr < spr_end);

*/
}



/**************************************************************************
	void GUGSMVGAPut(int x, int y) {

	DESCRIPTION:  Puts a sprite directly on the VGA page

**************************************************************************/
void GUGSMVGAPut(int x, int y) {
	extern int  SHOW_SPRITE_MOUSE;
  extern char *GUG_Sprite_Mouse;

  if ((GUG_Sprite_Mouse) && (SHOW_SPRITE_MOUSE))
		putvgaspr(x,y,GUG_Sprite_Mouse);

}

