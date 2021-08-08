void GUGPrintRed6x8(int x,int y,char *txt)
{
  int  l;
  char c;

  for (l=0; l<strlen(txt); ++l)
  {
    c = txt[l];
	if ((c > 32) && (c < 127))
	{
          draw_r6x8(c-33,x,y);
	}
    x+=6;
  }
}

void GUGPrintRed5x10(int x,int y,char *txt)
{
  int  l;
  char c;

  for (l=0; l<strlen(txt); ++l)
  {
    c = txt[l];
	if ((c > 32) && (c < 127))
	{
          draw_r5x10(c-33,x,y);
	}
    x+=5;
  }
}

void GUGPrintRed4x6(int x,int y,char *txt)
{
  int  l;
  char c;

  for (l=0; l<strlen(txt); ++l)
  {
    c = txt[l];
	if ((c > 32) && (c < 127))
	{
          draw_r4x6(c-33,x,y);
	}
    x+=4;
  }
}

