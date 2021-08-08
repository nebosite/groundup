// Draw a Filled Rectangle
// Ground Up Software
// Neil B. Breeden II

// Draws a filled rectangle between the specified endpoints

void GUG_fix_point(int *p1, int *p2,char axis);
void GUGHLine(int xstart, int xstop, int y, int color);

void GUGFillRectangle(int xstart, int ystart,
                      int xstop,  int ystop,
                      int color)
{
  int y;

  GUG_fix_point(&xstart,&xstop,'X');
  GUG_fix_point(&ystart,&ystop,'Y');

  for (y=ystart; y<=ystop; y++)
  {
    GUGHLine(xstart,xstop,y,color);
  }
}

