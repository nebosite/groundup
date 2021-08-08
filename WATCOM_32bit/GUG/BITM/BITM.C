#include "stdio.h"
#include "malloc.h"
#include "..\lib1\gug.h"
#include "..\lib1\keydefs.h"
#include "..\lib1\colors.h"

void main()
{
  char  *spr[5];
  char  *bgd[5];
  char  *gug[5];
  char  *nspr;
  int   xs,ys;
  int   x,y;
  int   flag = 0;
  char  *mes;
  float rt;

  mes = malloc(120);

  GUGLoadSprite("sship.spr",bgd);
  GUGLoadSprite("32x32.spr",spr);
  GUGLoadSprite("gug.spr",gug);

  GUGInitialize();
  if (!GUGJoystickCalibrate())
  {
    GUGEnd();
    printf("Error - No joysticks were detected!\n");
	return;
  }

  GUGStartKeyboard();
  GUGInitTimer();

  xs = GUGSpriteWidth(spr[0]);
  ys = GUGSpriteHeight(spr[0]);

  x = 10;
  y = 10;
  do
  {	
    delay(1); 
    if (flag == 0)
	{
      x = GUGScaleX1Axis();
      if (x <   1) x =   1;
	  if (x > 100) x = 100;
  	}
	else
	{
	  y = GUGScaleY1Axis();
      if (y <   1) y =   1;
	  if (y > 100) y = 100;
 	}

    GUGFastClear(VGA_START);

//    GUGPutFGSprite(0,  0,spr[0]);
    GUGStartTimer();
    GUGResizeSpriteToRectangle(spr[0],0,0,x,y);
	rt = GUGStopTimer();
	rt = rt / 1193.0;

    nspr = GUGResizeSpriteToSprite(spr[0],x,y);
//    GUGPutFGSprite(160,  0,spr[0]);
    if (nspr != NULL)
      GUGPutFGSprite(160,0,nspr);
    free(nspr);

    sprintf(mes,"Move the joystick: X:%3d Y:%3d",x,y);
	GUGPutText(0,180,215,mes);

    sprintf(mes,"RT:%5.2fmS",rt);
	GUGPutText(50,190,215,mes);


//    GUGPutFGSprite(0,100,bgd[0]);
    GUGStartTimer();
    GUGResizeSpriteToRectangle(bgd[0],0,100,x,y+100);
	rt = GUGStopTimer();
	rt = rt / 1193.0;

    nspr = GUGResizeSpriteToSprite(bgd[0],x,y);
//    GUGPutFGSprite(160,100,bgd[0]);
    if (nspr != NULL)
      GUGPutFGSprite(160,100,nspr);
    free(nspr);

    sprintf(mes,"RT:%5.2fmS",rt);
	GUGPutText(230,190,215,mes);


//    GUGFastCopy(VGA_START);
    GUGCopyToDisplay();

    ++flag;
	flag &= 1;

    if (GUG_key_table[ESC] == KEY_IS_DOWN) flag = -1;
  }
  while (flag >= 0);
  
  GUGStopKeyboard();
  GUGEnd();
}

