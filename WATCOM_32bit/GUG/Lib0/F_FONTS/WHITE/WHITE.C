void GUGPrintWhite6x8(int x,int y,char *txt)
{
  int  l;
  char c;

  for (l=0; l<strlen(txt); ++l)
  {
    c = txt[l];
	if ((c > 32) && (c < 127))
	{
          draw_w6x8(c-33,x,y);
	}
    x+=6;
  }
}

void GUGPrintWhite5x10(int x,int y,char *txt)
{
  int  l;
  char c;

  for (l=0; l<strlen(txt); ++l)
  {
    c = txt[l];
	if ((c > 32) && (c < 127))
	{
          draw_w5x10(c-33,x,y);
	}
    x+=5;
  }
}

void GUGPrintWhite4x6(int x,int y,char *txt)
{
  int  l;
  char c;

  for (l=0; l<strlen(txt); ++l)
  {
    c = txt[l];
	if ((c > 32) && (c < 127))
	{
          draw_w4x6(c-33,x,y);
	}
    x+=4;
  }
}
