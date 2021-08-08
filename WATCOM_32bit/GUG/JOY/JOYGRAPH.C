#include "stdio.h"
#include "malloc.h"
#include "..\lib1\gug.h"
#include "..\lib1\keydefs.h"
#include "..\lib1\colors.h"

void main(void)
{
  int    x,y,ox,oy;
  int    i,f;
  float  rt1,rt2;
  char   *mes;

  
  mes = malloc(120);

  GUGInitialize();
  GUGStartKeyboard();
  GUGInitTimer();

  i = GUGJoystickCalibrate();

  GUGClearDisplay();

  x = ox = GUGScaleX1Axis();
  delay(10);
  y = oy = GUGScaleY1Axis();
  delay(10);

  rt1 = rt2 = 0.0;

  while (GUG_key_table[ESC] == KEY_IS_UP)
  {
    if (GUGReadButtons() & J1_B1)
	{
	  GUGClearDisplay();
	}

    if (f == 0)
	{
	  GUGStartTimer();
      x = GUGScaleX1Axis();	 // On even frames (f = 0)
      rt1 = GUGStopTimer();
	  rt1 = rt1 / 1193.0;
    }
    else
	{
      GUGStartTimer();
      y = GUGScaleY1Axis();	 // On odd frames (f = 1)
      rt2 = GUGStopTimer();
      rt2 = rt2 / 1193.0;
 	}

    sprintf(mes,"Run Time X:%5.2fmS Y:%5.2fms",rt1,rt2);
    GUGFillRectangle(50,180,270,189,BLACK);
	GUGCenterText(180,WHITE,mes);

	++f;	  // Increment f
	f &= 1;	  // F will always = 0 or one only

 	GUGLine(ox*3.2,oy*2.0,x*3.2,y*2.0,120);
	ox = x;
	oy = y;

    GUGCenterText(190,RED,"Button 1 to clear - <ESC> to exit");
    GUGFastCopy(VGA_START);
//    GUGCopyToDisplay();
  }

  GUGStopKeyboard();
  GUGEnd();

  printf("Joysticks Detected:%d\n",i);

}

