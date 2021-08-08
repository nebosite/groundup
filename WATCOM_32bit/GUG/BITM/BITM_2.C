#include "stdio.h"
#include "malloc.h"
#include "..\lib1\gug.h"
#include "..\lib1\keydefs.h"

void main()
{
  char *spr[5];
  int  xs,ys;
  int  x,y;
  int  flag = 0;
  char *mes;

  mes = malloc(120);

  GUGLoadSprite("sship.spr",spr);

  xs = GUGSpriteWidth(spr[0]);
  ys = GUGSpriteHeight(spr[0]);

  GUGInitialize();
  GUGStartKeyboard();
  GUGJoystickCalibrate();

  x = 10;
  y = 10;
  do
  {	
    GUGFastClear(VGA_START);
    GUGPutFGSprite(0,0,spr[0]);

    delay(1); 
    if (flag == 0)
	{
      x = GUGScaleX1Axis();
	  x += 1;
  	}
	else
	{
	  y = GUGScaleY1Axis();
	  y += 1;
	}

    sprintf(mes,"%3d %3d",x,y);
	GUGPutText(10,190,215,mes);

    GUGResizeRectangle(0,0,xs,ys,150,50,150+x,50+y);

    GUGFastCopy(VGA_START);
 
    ++flag;
	flag &= 1;

    if (GUG_key_table[ESC] == KEY_IS_DOWN) flag = -1;
  }
  while (flag >= 0);
  
  GUGStopKeyboard();
  GUGEnd();
}

