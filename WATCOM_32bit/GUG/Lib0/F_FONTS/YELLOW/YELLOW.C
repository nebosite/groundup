void GUGPrintYellow6x8(int x,int y,char *txt)
{
  int  l;
  char c;

  for (l=0; l<strlen(txt); ++l)
  {
    c = txt[l];
	if ((c > 32) && (c < 127))
	{
          draw_y6x8(c-33,x,y);
	}
    x+=6;
  }
}

void GUGPrintYellow5x10(int x,int y,char *txt)
{
  int  l;
  char c;

  for (l=0; l<strlen(txt); ++l)
  {
    c = txt[l];
	if ((c > 32) && (c < 127))
	{
          draw_y5x10(c-33,x,y);
	}
    x+=5;
  }
}

void GUGPrintYellow4x6(int x,int y,char *txt)
{
  int  l;
  char c;

  for (l=0; l<strlen(txt); ++l)
  {
    c = txt[l];
	if ((c > 32) && (c < 127))
	{
          draw_y4x6(c-33,x,y);
	}
    x+=4;
  }
}

