typedef struct  {
  int x;
  int y;
}GUGVertex;

extern void  GUGLine(int XStart, int YStart, int XEnd, int YEnd, 
                     int Color);

/**************************************************************************/
void GUGPoly(int color, int points, GUGVertex poly[])
{
  int x;
  for (x=0; x<(points-1); ++x)
  {
    GUGLine(poly[x].x,poly[x].y,
	        poly[x+1].x,poly[x+1].y,
			color);
  }
  GUGLine(poly[points-1].x,poly[points-1].y,
          poly[0].x,poly[0].y,
	      color);
}
