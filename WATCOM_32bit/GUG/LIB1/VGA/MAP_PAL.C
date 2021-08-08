//////////////////////////////////////////////////////////////////////////
void GUGRemapPalette(int *xlate,char *from, char *too)
{
  int x,i;
  int d1,d2,d3,dt;
  int t1,t2,t3,tt;

  for (x=0; x<256; ++x)
  {
    xlate[x] = -1;
  }

  for (i=0; i<768; i+=3)
  {
    t1 = t2 = t3 = tt = 9999;
    for (x=765; x>=0; x-=3)
	{
	  d1 = abs(from[i]   - too[x]);
	  d2 = abs(from[i+1] - too[x+1]);
	  d3 = abs(from[i+2] - too[x+2]);
	  dt = d1 + d2 + d3;
	  if ( (d1 <= t1) &&
	       (d2 <= t2) &&
		   (d3 <= t3) )
	  {
	    t1 = d1;
	    t2 = d2;
	    t3 = d3;
        tt = dt;
		xlate[i/3] = x/3;
	  }
	}
  }
}

