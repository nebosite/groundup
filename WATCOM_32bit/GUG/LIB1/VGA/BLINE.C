/**************************************************************************
  GUGBLine(color, x1, y1, x2, y2)

  DESCRIPTION:  Draw a line from x1,y1 to x2,y2  (bresenham's alg.)

**************************************************************************/
void GUGSetPixel(int xpos, int ypos,int color);

#define mysgn(val)      (((val) >= 0) ? 1 : -1)

GUGBLine(int x1,int  y1,int x2,int y2,int color)
{
  int dx, dy, incrE, incrNE, d, x, y, incx,incy,check;

  dx = x2-x1;
  dy = y2-y1;
                                   // Handle slopes between 0 and 1
  if(abs(dx)>abs(dy)) {
    
    d = abs(dy+dy)-abs(dx);       // error threshhold
    incrE = 2*dy*mysgn(dy);       // Error increment (always positive)
    incrNE = 2*(abs(dy)-abs(dx)); // Error Correction (always negative)

    x = x1;                       // initialize loop variables
    y = y1;
    incy = mysgn(dy);
    incx = mysgn(dx);

    GUGSetPixel(x,y,color);
//  drwpoint(SET,color,x,y);      // draw first point

    while (x != x2) {             // Drawing loop
      if (d <= 0) {               // Still below error threshold?
        d += incrE;               // increment error
        x += incx;                // increment drawing varaible
      }
      else {                      // Error threshhold exceeded?
        d += incrNE;              // Correct Error
        x+= incx;                 // Increment drawing varaibles
        y+= incy;
      }
      GUGSetPixel(x,y,color);
//    drwpoint(SET,color,x,y);    // Draw the point
    }
  }
                                  // SLOPES > 1
   else {
    
    d = abs(dx+dx)-abs(dy);       // error threshhold
    incrE = 2*dx*mysgn(dx);       // Error increment (always positive)
    incrNE = 2*(abs(dx)-abs(dy)); // Error Correction (always negative)

    x = x1;                       // initialize loop variables
    y = y1;
    incy = mysgn(dy);
    incx = mysgn(dx);

    GUGSetPixel(x,y,color);
//  drwpoint(SET,color,x,y);      // draw first point

    while (y != y2) {             // Drawing loop
      if (d <= 0) {               // Still below error threshold?
        d += incrE;               // increment error
        y += incy;                // increment drawing varaible
      }
      else {                      // Error threshhold exceeded?
        d += incrNE;              // Correct Error
        x+= incx;                 // Increment drawing varaibles
        y+= incy;
      }
      GUGSetPixel(x,y,color);
//    drwpoint(SET,color,x,y);    // Draw the point
    }
  }
}


