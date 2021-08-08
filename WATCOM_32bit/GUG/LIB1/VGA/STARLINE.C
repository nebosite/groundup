// Run-length slice line drawing implementation for mode 0x13
// Ground Up Software
// Neil B. Breeden II
// 9-Jun-1995

#include <dos.h>
#include "vga.h"
#include "mode.h"

void GUG_Star_h_line(char **ScreenPtr, int XAdvance, int RunLength,
                     int Color);
void GUG_Star_v_line(char **ScreenPtr, int XAdvance, int RunLength,
                     int Color);

// Draws a line between the specified endpoints in color Color.
void GUGStarLine(int XStart, int YStart, int XEnd, int YEnd, int Color)
{
   int Temp, AdjUp, AdjDown, ErrorTerm, XAdvance, XDelta, YDelta;
   int WholeStep, InitialPixelCount, FinalPixelCount, i, RunLength;
   char *ScreenPtr;

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
         *ScreenPtr = Color;
         Color--;
		 if (Color < 216) return;
         ScreenPtr += X_WRAP_SIZE;
      }
      return;
   }
   if (YDelta == 0)
   {
      // Horizontal line
      for (i=0; i<=XDelta; i++)
      {
         *ScreenPtr = Color;
		 Color--;
		 if (Color < 216) return;
         ScreenPtr += XAdvance;
      }
      return;
   }
   if (XDelta == YDelta)
   {
      // Diagonal line
      for (i=0; i<=XDelta; i++)
      {
         *ScreenPtr = Color;
		 Color--;
		 if (Color < 216) return;
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
      GUG_Star_h_line(&ScreenPtr, XAdvance, InitialPixelCount, Color);
      Color--;
	  if (Color < 216) return;
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
         GUG_Star_h_line(&ScreenPtr, XAdvance, RunLength, Color);
		 Color--;
		 if (Color < 216) return;
      }
      // Draw the final run of pixels
      GUG_Star_h_line(&ScreenPtr, XAdvance, FinalPixelCount, Color);
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
      GUG_Star_v_line(&ScreenPtr, XAdvance, InitialPixelCount, Color);
	  Color--;
	  if (Color < 216) return;
  
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
         GUG_Star_v_line(&ScreenPtr, XAdvance, RunLength, Color);
		 Color--;
		 if (Color < 216) return;
        }
      // Draw the final run of pixels
      GUG_Star_v_line(&ScreenPtr, XAdvance, FinalPixelCount, Color);
      return;
   }
}

// Draws a horizontal run of pixels, then advances the bitmap pointer to
// the first pixel of the next run.
void GUG_Star_h_line(char **ScreenPtr, int XAdvance,
                     int RunLength, int Color)
{
   int i;
   char *WorkingScreenPtr = *ScreenPtr;

   for (i=0; i<RunLength; i++)
   {
     *WorkingScreenPtr = Color;
     WorkingScreenPtr += XAdvance;
   }
   // Advance to the next scan line
   WorkingScreenPtr += X_WRAP_SIZE;
   *ScreenPtr = WorkingScreenPtr;
}

// Draws a vertical run of pixels, then advances the bitmap pointer to
// the first pixel of the next run.
void GUG_Star_v_line(char **ScreenPtr, int XAdvance,
                     int RunLength, int Color)
{
   int i;
   char *WorkingScreenPtr = *ScreenPtr;

   for (i=0; i<RunLength; i++)
   {
      *WorkingScreenPtr = Color;
      WorkingScreenPtr += X_WRAP_SIZE;
   }
   // Advance to the next column
   WorkingScreenPtr += XAdvance;
   *ScreenPtr = WorkingScreenPtr;
}
