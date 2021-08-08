// PIX routines

extern int pix_x;   // X Pixel Location
extern int pix_y;	// Y Lixel Location
extern int pix_c;	// Draw Color

void GUGPIXSetColor(int c)
{
  pix_c = c;
}

void GUGPIXErase()
{
  GUGSetDisplay(pix_c);
}

void GUGPIXSet(int x,int y)
{
  GUGSetPixel(x,y,pix_c);
}

void GUGPIXMove(int x,int y)
{
  pix_x = x;
  pix_y = y;
}

void GUGPIXLine(int x,int y)
{
  GUGLine(pix_x,pix_y,x,y,pix_c);
  pix_x = x;
  pix_y = y;
}

void GUGPIXRGBLog(int i, float r, float g, float b)
{
  char pal[768];
  if (i <   0) return;
  if (i > 255) return;  // 255 = gug.h GUGTABNUM 

  GUGGetPalette(pal);
  pal[i*3]     = 255 * r;
  pal[(i*3)+1] = 255 * g;
  pal[(i*3)+2] = 255 * b;
  GUGSetPalette(pal);
}
//void GUGPIXPoly(int n,PolyList list);


