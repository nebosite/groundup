// Draw a Rectangle
// Ground Up Software
// Neil B. Breeden II
// 13-Jun-1995

// Draws a rectangle between the specified endpoints

//void GUG_fix_point(int *p1, int *p2, char c);
void GUGHLine(int xstart,int xstop, int y, int color);
void GUGVLine(int ystart,int ystop, int x, int color);

void GUGRectangle(int xstart, int ystart,
                  int xstop,  int ystop,
                  int color)
{
  GUGHLine(xstart,xstop ,ystart,color);
  GUGHLine(xstart,xstop ,ystop ,color);
  GUGVLine(ystart,ystop ,xstart,color);
  GUGVLine(ystart,ystop ,xstop ,color);
}
