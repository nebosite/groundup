// Line drawing routines to resemble svgacc
// Eric Jorgensen (August 1997)


#include <dos.h>
#include "vga.h"
#include "mode.h"
#include "..\gug.h"

enum enum_outcodes {LINE_LEFT=1,LINE_RIGHT=2,LINE_BOTTOM=4,LINE_TOP=8};


																				// --- internal funcs
void GUGDraw_h_line(PIXELMODE pmode,  int Colorchar,char **ScreenPtr, int XAdvance, int RunLength);
void GUGDraw_v_line(PIXELMODE pmode,  int Colorchar,char **ScreenPtr, int XAdvance, int RunLength);
void CirclePoints(PIXELMODE pmode, int color, int cx,int cy,int x, int y);

																				// --- external funcs
void GUG_fix_point(int *x, int *y, char axis);


int GUGClipMinx = 0,GUGClipMaxx = 319,GUGClipMiny = 0,GUGClipMaxy = 199;


/**************************************************************************
	void GUGDrawPoint(PIXELMODE pmode, int color, int x, int y)

	DESCRIPTION:

**************************************************************************/
void GUGDrawPoint(PIXELMODE pmode, int color, int x, int y)
{
	char *vga_mem = VGA_START + y * X_WRAP_SIZE + x;

	if( x< 0 || x >= MAX_X_SIZE || y < 0 || y >= MAX_Y_SIZE) return;

	switch(pmode) {
	case SET: *vga_mem =  color; break;
	case XOR: *vga_mem ^= color; break;
	case AND: *vga_mem &= color; break;
	case OR:  *vga_mem |= color; break;
	}
}

/**************************************************************************
	void GUGDrawFillCircle(PIXELMODE pmode, int color, int cx, int cy, int radius)

	DESCRIPTION:  Draw a filled circle with Midpoint Algorithm

**************************************************************************/
void GUGDrawFillCircle(PIXELMODE pmode, int color, int cx, int cy, int radius)
{
	int x=0,
			y=radius,
			d=1-radius,
			deltaE=3,
			deltaSE= -2 * radius + 5;
	int lasty = y,lastx = x;


	while(y > x) {
																		// Draw lines acrross the circle
		if(y != lasty) {
			GUGDrawHLine(pmode,color,cx-lastx,cx+lastx,cy-lasty);
			GUGDrawHLine(pmode,color,cx-lastx,cx+lastx,cy+lasty);
		}
		if(x != lastx){
			GUGDrawHLine				 (pmode,color,cx-lasty,cx+lasty,cy-lastx);
			if(lastx)GUGDrawHLine(pmode,color,cx-lasty,cx+lasty,cy+lastx);
		}
		lastx = x;
		lasty = y;
																		// execute midpoint algorithm
		if(d<0) {
			d += deltaE;
			deltaE += 2;
			deltaSE +=2;
			x++;
		}
		else {
			d += deltaSE;
			deltaE += 2;
			deltaSE += 4;
			x++;
			y--;
		}
	}
																		// Finish up
		if(y != lasty) {
			GUGDrawHLine(pmode,color,cx-lastx,cx+lastx,cy-lasty);
			GUGDrawHLine(pmode,color,cx-lastx,cx+lastx,cy+lasty);
		}
		if(x != lastx){
			GUGDrawHLine				 (pmode,color,cx-lasty,cx+lasty,cy-lastx);
			if(lastx)GUGDrawHLine(pmode,color,cx-lasty,cx+lasty,cy+lastx);
		}

	if(y == x){
			GUGDrawHLine(pmode,color,cx-x,cx+x,cy-y);
			GUGDrawHLine(pmode,color,cx-x,cx+x,cy+y);
	}
}

/**************************************************************************
	GUGDrawCricle(PIXELMODE pmode, int color, int x, int y, int r)

	DESCRIPTION:  Midpoint circle algorythm.

**************************************************************************/
void GUGDrawCircle(PIXELMODE pmode, int color, int cx, int cy, int radius)
{
	int x=0,
			y=radius,
			d=1-radius,
			deltaE=3,
			deltaSE= -2 * radius + 5;


	if(!radius) GUGDrawPoint(pmode,color,cx,cy);

	while(y > x) {
		CirclePoints(pmode,color,cx,cy,x,y);
		if(d<0) {
			d += deltaE;
			deltaE += 2;
			deltaSE +=2;
			x++;
		}
		else {
			d += deltaSE;
			deltaE += 2;
			deltaSE += 4;
			x++;
			y--;
		}

	}
	if(y == x)CirclePoints(pmode,color,cx,cy,x,y);

}

/**************************************************************************
	void CirclePoints(PIXELMODE pmode, int color, int cx,int cy,int x, int y)

	DESCRIPTION:

**************************************************************************/
void CirclePoints(PIXELMODE pmode, int color, int cx,int cy,int x, int y)
{
	int x1=cx-x,
			x2=cx-y,
			x3=cx+y,
			x4=cx+x,

			y1=cy-x,
			y2=cy-y,
			y3=cy+y,
			y4=cy+x;

	if(x && y) {
		GUGDrawPoint(pmode,color,x3,y4);
		GUGDrawPoint(pmode,color,x2,y1);
		GUGDrawPoint(pmode,color,x1,y3);
		GUGDrawPoint(pmode,color,x4,y2);
	}

	if(x == y) return;
	GUGDrawPoint(pmode,color,x4,y3);
	GUGDrawPoint(pmode,color,x2,y4);
	GUGDrawPoint(pmode,color,x1,y2);
	GUGDrawPoint(pmode,color,x3,y1);


}

/**************************************************************************
	void GUGDrawFillRectangle(PIXELMODE pmode,int color,int xstart, int ystart,int xstop,  int ystop)

	DESCRIPTION:

**************************************************************************/
void GUGDrawFillRectangle(PIXELMODE pmode,int color,int xstart, int ystart,int xstop,  int ystop)
{
	int y;

	GUG_fix_point(&xstart,&xstop,'X');
	GUG_fix_point(&ystart,&ystop,'Y');

	for (y=ystart; y<=ystop; y++)
	{
		GUGDrawHLine(pmode,color,xstart,xstop,y);
	}
}

/**************************************************************************
	void GUGDrawRectangle(PIXELMODE pmode,int color, int xstart, int ystart,int xstop,  int ystop)

	DESCRIPTION:

**************************************************************************/
void GUGDrawRectangle(PIXELMODE pmode,int color, int xstart, int ystart,int xstop,  int ystop)
{
	GUGDrawHLine(pmode,color,xstart,xstop ,ystart);
	GUGDrawHLine(pmode,color,xstart,xstop ,ystop );
	GUGDrawVLine(pmode,color,ystart,ystop ,xstart);
	GUGDrawVLine(pmode,color,ystart,ystop ,xstop );
}

/**************************************************************************
	void GUGDrawHLine(PIXELMODE pmode, int color, int xstart, int xstop, int y)

	DESCRIPTION: Draws a horizontal line

**************************************************************************/
void GUGDrawHLine(PIXELMODE pmode, int color, int xstart, int xstop, int y)
{
	 char *vga_mem;
	 int temp;

	 if (y <   0) return;
	 if (y >=  MAX_Y_SIZE) return;

	if(xstop < xstart) {
		temp = xstop;
		xstop = xstart;
		xstart = temp;
	}

	if (xstart <              0) xstart =   0;
	if (xstart > (MAX_X_SIZE-1)) return;
	if (xstop <              0) return ;
	if (xstop > (MAX_X_SIZE-1)) xstop = (MAX_X_SIZE-1);

	 vga_mem = VGA_START + xstart + (y * X_WRAP_SIZE);

	 while (xstart <= xstop) {
		 switch(pmode) {
		 case SET:
			*vga_mem = color;
				break;
		 case XOR:
			*vga_mem ^= color;
				break;
		 case AND:
			*vga_mem &= color;
				break;
		 case OR:
			*vga_mem |= color;
				break;
		 }
		 ++vga_mem;
		 ++xstart;
	 }
}


/**************************************************************************
	void GUGDrawVLine(PIXELMODE pmode, int color,int ystart, int ystop, int x)

	DESCRIPTION:

**************************************************************************/
void GUGDrawVLine(PIXELMODE pmode, int color,int ystart, int ystop, int x)
{
	 char *vga_mem;
	 int temp;

	 if (x <   0) return;
	 if (x > (MAX_X_SIZE-1)) return;

	if(ystop < ystart) {
		temp = ystop;
		ystop = ystart;
		ystart = temp;
	}

	if (ystart <              0) ystart =   0;
	if (ystart > (MAX_Y_SIZE-1)) return;
	if (ystop <              0) return ;
	if (ystop > (MAX_Y_SIZE-1)) ystop = (MAX_Y_SIZE-1);


	 vga_mem = VGA_START + x + (ystart * X_WRAP_SIZE);
   
   while (ystart <= ystop) {
		 switch(pmode) {
		 case SET:
			*vga_mem = color;
				break;
		 case XOR:
			*vga_mem ^= color;
				break;
		 case AND:
			*vga_mem &= color;
				break;
		 case OR:
			*vga_mem |= color;
				break;
		 }
		 vga_mem += X_WRAP_SIZE;
     ystart++;
   }
}




/**************************************************************************
	int outcode(int x,int y,int minx, int maxx, int miny, int maxy)

	DESCRIPTION: returns the outcode for the specified point

**************************************************************************/
int outcode(int x,int y,int minx, int maxx, int miny, int maxy)
{
	int code =0;
	if(y > maxy) code += LINE_TOP;
	if(y < miny) code += LINE_BOTTOM;
	if(x > maxx) code += LINE_RIGHT;
	if(x < minx) code += LINE_LEFT;

	return code;
}

/**************************************************************************
	int clipline(int *x1, int *y1, int *x2, int *y2,int minx, int maxx, int miny, int maxy)

	DESCRIPTION: Clips the line to the screen.  Returns 0 if line is off screen

**************************************************************************/
int clipline(int *x0, int *y0, int *x1, int *y1,int minx, int maxx, int miny, int maxy)
{
	int accept=0,done=0,outcode0=0,outcode1=0,outcodeout=0;
	int code = 0,x,y;
															 // Check initial end points
	outcode0 = outcode(*x0,*y0,minx,maxx,miny,maxy);
	outcode1 = outcode(*x1,*y1,minx,maxx,miny,maxy);


	while(!done) {
															 // Trivial Accept (line totally inside)
		if(!outcode0 && !outcode1) {
			done = accept = 1;
			continue;
		}
															 // Trivial reject (line totally outside)
		if(outcode0 & outcode1) {
			done = 1;
			continue;
		}

															 // At this point, we need to break up the
															 // line and reject parts.
		if(outcode0) outcodeout = outcode0;
		else outcodeout = outcode1;
															 // Find intersection point
		if(LINE_TOP & outcodeout) {
			x = *x0 + (*x1-*x0) * (maxy-*y0) / (*y1-*y0);
			y = maxy;
		}
		else if(LINE_BOTTOM & outcodeout) {
			x = *x0 + (*x1-*x0) * (miny-*y0) / (*y1-*y0);
			y = miny;
		}
		else if(LINE_RIGHT & outcodeout) {
			y = *y0 + (*y1-*y0) * (maxx-*x0) / (*x1-*x0);
			x = maxx;
		}
		else if(LINE_LEFT & outcodeout) {
			y = *y0 + (*y1-*y0) * (minx-*x0) / (*x1-*x0);
			x = minx;
		}
															// Move outside point to the intersect and
															// repeat pass.
		if(outcodeout == outcode0) {
			*x0 = x;
			*y0 = y;
			outcode0 = outcode(*x0,*y0,minx,maxx,miny,maxy);
		}
		else {
			*x1 = x;
			*y1 = y;
			outcode1 = outcode(*x1,*y1,minx,maxx,miny,maxy);
		}

	}
	return accept;
}

/**************************************************************************
	void GUGDrawLine(PIXELMODE pmode, int Color,int XStart, int YStart, int XEnd, int YEnd)

	DESCRIPTION:  Draws a line between the specified endpoints in color Color.

**************************************************************************/
void GUGDrawLine(PIXELMODE pmode, int Color,int XStart, int YStart, int XEnd, int YEnd)
{
	 int Temp, AdjUp, AdjDown, ErrorTerm, XAdvance, XDelta, YDelta;
	 int WholeStep, InitialPixelCount, FinalPixelCount, i, RunLength;
	 char *ScreenPtr;


	 if(!clipline(&XStart,&YStart,&XEnd,&YEnd,GUGClipMinx,GUGClipMaxx,GUGClipMiny,GUGClipMaxy))
		return;
//  XStart += MAX_X_SIZE;
//  YStart += MAX_Y_SIZE;
//  XEnd   += MAX_Y_SIZE;
//  YEnd   += MAX_Y_SIZE;		 

// We'll always draw top to bottom, to reduce the number of cases we have to
// handle, and to make lines between the same endpoints draw the same pixels
   if (YStart > YEnd) {
      Temp = YStart;
      YStart = YEnd;
      YEnd = Temp;
      Temp = XStart;
      XStart = XEnd;
      XEnd = Temp;
   }
// Point to the bitmap address first pixel to draw
	 ScreenPtr = (char *)(VGA_START + (YStart * X_WRAP_SIZE) + XStart);

// Figure out whether we're going left or right, and how far we're
//  going horizontally
   if ((XDelta = XEnd - XStart) < 0)
   {
      XAdvance = -1;
      XDelta = -XDelta;
   }
   else
   {
      XAdvance = 1;
   }
// Figure out how far we're going vertically
   YDelta = YEnd - YStart;

// Special-case horizontal, vertical, and diagonal lines, for speed
//   and to avoid nasty boundary conditions and division by 0
   if (XDelta == 0)
   {
      // Vertical line
      for (i=0; i<=YDelta; i++)
      {
				 switch(pmode) {
				 case SET:
					*ScreenPtr = Color;
						break;
				 case XOR:
					*ScreenPtr ^= Color;
						break;
				 case AND:
					*ScreenPtr &= Color;
						break;
				 case OR:
					*ScreenPtr |= Color;
						break;
				 }
				 ScreenPtr += X_WRAP_SIZE;
      }
      return;
   }
   if (YDelta == 0)
   {
      // Horizontal line
      for (i=0; i<=XDelta; i++)
      {
				 switch(pmode) {
				 case SET:
					*ScreenPtr = Color;
						break;
				 case XOR:
					*ScreenPtr ^= Color;
						break;
				 case AND:
					*ScreenPtr &= Color;
						break;
				 case OR:
					*ScreenPtr |= Color;
						break;
				 }
				 ScreenPtr += XAdvance;
			}
			return;
	 }
   if (XDelta == YDelta)
   {
      // Diagonal line
      for (i=0; i<=XDelta; i++)
      {
				 switch(pmode) {
				 case SET:
					*ScreenPtr = Color;
						break;
				 case XOR:
					*ScreenPtr ^= Color;
						break;
				 case AND:
					*ScreenPtr &= Color;
						break;
				 case OR:
					*ScreenPtr |= Color;
						break;
				 }
				 ScreenPtr += XAdvance + X_WRAP_SIZE;
      }
      return;
   }

// Determine whether the line is X or Y major, and handle accordingly
   if (XDelta >= YDelta)
   {
      // X major line
      // Minimum # of pixels in a run in this line
			WholeStep = XDelta / YDelta;

      // Error term adjust each time Y steps by 1; used to tell when one
      // extra pixel should be drawn as part of a run, to account for
      // fractional steps along the X axis per 1-pixel steps along Y
      AdjUp = (XDelta % YDelta) * 2;

      // Error term adjust when the error term turns over, used to factor
      // out the X step made at that time 
      AdjDown = YDelta * 2;

			// Initial error term; reflects an initial step of 0.5 along the Y
      // axis
      ErrorTerm = (XDelta % YDelta) - (YDelta * 2);

      // The initial and last runs are partial, because Y advances only 0.5
      // for these runs, rather than 1. Divide one full run, plus the
      // initial pixel, between the initial and last runs
      InitialPixelCount = (WholeStep / 2) + 1;
      FinalPixelCount = InitialPixelCount;

      // If the basic run length is even and there's no fractional
			// advance, we have one pixel that could go to either the initial
      // or last partial run, which we'll arbitrarily allocate to the
      // last run 
      if ((AdjUp == 0) && ((WholeStep & 0x01) == 0))
      {
         InitialPixelCount--;
      }
      // If there're an odd number of pixels per run, we have 1 pixel that can't
      // be allocated to either the initial or last partial run, so we'll add 0.5
			// to error term so this pixel will be handled by the normal full-run loop */
			if ((WholeStep & 0x01) != 0)
      {
         ErrorTerm += YDelta;
      }
      // Draw the first, partial run of pixels
			GUGDraw_h_line(pmode,Color,&ScreenPtr, XAdvance, InitialPixelCount);
      // Draw all full runs 
      for (i=0; i<(YDelta-1); i++)
      {
         RunLength = WholeStep;  // run is at least this long
         // Advance the error term and add an extra pixel if the error
         // term so indicates 
         if ((ErrorTerm += AdjUp) > 0)
         {
						RunLength++;
            ErrorTerm -= AdjDown;   // reset the error term
         }
         // Draw this scan line's run 
				 GUGDraw_h_line(pmode,Color,&ScreenPtr, XAdvance, RunLength);
			}
      // Draw the final run of pixels
			GUGDraw_h_line(pmode,Color,&ScreenPtr, XAdvance, FinalPixelCount);
      return;
   }
   else
   {
      // Y major line
      // Minimum # of pixels in a run in this line
      WholeStep = YDelta / XDelta;

			// Error term adjust each time X steps by 1; used to tell when 1 extra
      // pixel should be drawn as part of a run, to account for
      // fractional steps along the Y axis per 1-pixel steps along X
			AdjUp = (YDelta % XDelta) * 2;

      // Error term adjust when the error term turns over, used to factor
      // out the Y step made at that time
      AdjDown = XDelta * 2;

      // Initial error term; reflects initial step of 0.5 along the X axis
      ErrorTerm = (YDelta % XDelta) - (XDelta * 2);

      // The initial and last runs are partial, because X advances only 0.5
      // for these runs, rather than 1. Divide one full run, plus the
      // initial pixel, between the initial and last runs
      InitialPixelCount = (WholeStep / 2) + 1;
      FinalPixelCount = InitialPixelCount;

      // If the basic run length is even and there's no fractional advance, we
			// have 1 pixel that could go to either the initial or last partial run,
      // which we'll arbitrarily allocate to the last run
      if ((AdjUp == 0) && ((WholeStep & 0x01) == 0))
			{
         InitialPixelCount--;
      }
      // If there are an odd number of pixels per run, we have one pixel
      // that can't be allocated to either the initial or last partial
      // run, so we'll add 0.5 to the error term so this pixel will be
      // handled by the normal full-run loop 
			if ((WholeStep & 0x01) != 0)
      {
				 ErrorTerm += XDelta;
      }
      // Draw the first, partial run of pixels
			GUGDraw_v_line(pmode,Color,&ScreenPtr, XAdvance, InitialPixelCount);

      // Draw all full runs
      for (i=0; i<(XDelta-1); i++)
      {
         RunLength = WholeStep;  // run is at least this long
         // Advance the error term and add an extra pixel if the error
         // term so indicates
         if ((ErrorTerm += AdjUp) > 0)
         {
            RunLength++;
            ErrorTerm -= AdjDown;   // reset the error term
         }
         // Draw this scan line's run
				 GUGDraw_v_line(pmode,Color,&ScreenPtr, XAdvance, RunLength);
      }
      // Draw the final run of pixels
			GUGDraw_v_line(pmode,Color,&ScreenPtr, XAdvance, FinalPixelCount);
      return;
	 }
}

//

/**************************************************************************
	void GUGDraw_h_line(PIXELMODE pmode,  int Colorchar, **ScreenPtr, int XAdvance,int RunLength)

	DESCRIPTION: Draws a horizontal run of pixels, then advances
							 the bitmap pointer to the first pixel of the next run.

**************************************************************************/
void GUGDraw_h_line(PIXELMODE pmode,  int Color,char **ScreenPtr, int XAdvance,int RunLength)
{
   int i;
   char *WorkingScreenPtr = *ScreenPtr;

   for (i=0; i<RunLength; i++)
   {
			switch(pmode) {
			case SET:
			 *WorkingScreenPtr = Color;
				 break;
			case XOR:
			 *WorkingScreenPtr ^= Color;
				 break;
			case AND:
			 *WorkingScreenPtr &= Color;
				 break;
			case OR:
			 *WorkingScreenPtr |= Color;
				 break;
			}
			WorkingScreenPtr += XAdvance;
	 }
   // Advance to the next scan line
   WorkingScreenPtr += X_WRAP_SIZE;
   *ScreenPtr = WorkingScreenPtr;
}


/**************************************************************************
	void GUGDraw_v_line(PIXELMODE pmode,  int Colorchar, char **ScreenPtr, int XAdvance,int RunLength)

	DESCRIPTION:  Draws a vertical run of pixels, then advances the
								bitmap pointer to the first pixel of the next run.

**************************************************************************/
void GUGDraw_v_line(PIXELMODE pmode,  int Color, char **ScreenPtr, int XAdvance,int RunLength)
{
	 int i;
	 char *WorkingScreenPtr = *ScreenPtr;

	 for (i=0; i<RunLength; i++)
	 {
			switch(pmode) {
			case SET:
			 *WorkingScreenPtr = Color;
				 break;
			case XOR:
			 *WorkingScreenPtr ^= Color;
				 break;
			case AND:
			 *WorkingScreenPtr &= Color;
				 break;
			case OR:
			 *WorkingScreenPtr |= Color;
				 break;
			}
			WorkingScreenPtr += X_WRAP_SIZE;
	 }
	 // Advance to the next column
	 WorkingScreenPtr += XAdvance;
	 *ScreenPtr = WorkingScreenPtr;
}
