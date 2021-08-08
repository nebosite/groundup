// Joystick calibration routines.  These are the ones that are supposed to
// display the box on the screen and ask the user to move the little box
// around the larger boxes.

#include "stdio.h"
#include "..\gug.h"
#include "..\keydefs.h"
#include "..\colors.h"

#include <conio.h>
#include <dos.h>
#include <i86.h>

int GUGJoystickCalibrate(void) {    // Here is the actual calibration.
  int  curx1, cury1;      // Current x and y location, use to make box.
  int  curx2, cury2;      // Current x and y location, use to make box.
  int  x,y;
  int  flag = 0;
  int  buttons;
  int  installed = 0;
  FILE *in,*out;
  int  mode = 0;
  char mes[80];

  if ((in = fopen("JOY.CAL","r")) != NULL)
  {
    fscanf(in,"%d\n",&GUGX1Active);
    fscanf(in,"%d\n",&GUGJ1XMin);
    fscanf(in,"%d\n",&GUGJ1YMin);
    fscanf(in,"%d\n",&GUGJ1XMax);
    fscanf(in,"%d\n",&GUGJ1YMax);
    fscanf(in,"%d\n",&GUGX2Active);
    fscanf(in,"%d\n",&GUGJ2XMin);
    fscanf(in,"%d\n",&GUGJ2YMin);
    fscanf(in,"%d\n",&GUGJ2XMax);
    fscanf(in,"%d\n",&GUGJ2YMax);
    GUGX1Active = GUGX1Detect();   // Make sure a joystick is installed!
    GUGX2Active = GUGX2Detect();
    installed = GUGX1Active + GUGX2Active;
    fclose(in);
	return(installed);
  }

  GUGX1Active = GUGX1Detect();
  GUGX2Active = GUGX2Detect();

  installed = GUGX1Active + GUGX2Active;

  if (installed == 0)           // then no joysticks attached
  {
    out = fopen("JOY.CAL","w");
	fprintf(out,"0\n0\n0\n0\n0\n0\n0\n0\n0\n0\n");
    fclose(out);
    return(0);
  }

  if (mode == 0)  // then in auto cal mode
  {
    if (GUGX1Active)
    {
      curx1 = GUGReadX1Axis();            // Get the current x and set limits.
//      if (curx1 <   0) curx1 =   0;
//      if (curx1 > 600) curx1 = 600;
      GUGJ1XMin = curx1;
      GUGJ1XMax = curx1;
      delay(50);
      cury1 = GUGReadY1Axis();            // Get the current y and set limits.
//      if (cury1 <   0) cury1 =   0;
//  	if (cury1 > 600) cury1 = 600;
      GUGJ1YMin = cury1;
      GUGJ1YMax = cury1;
      delay(50);
    }

    if (GUGX2Active)
    {
      curx2 = GUGReadX2Axis();            // Get the current x and set limits.
//      if (curx2 <   0) curx2 =   0;
//      if (curx2 > 600) curx2 = 600;
      GUGJ2XMin = curx2;
      GUGJ2XMax = curx2;
      delay(50);
      cury2 = GUGReadY2Axis();            // Get the current y and set limits.
//      if (cury2 <   0) cury2 =   0;
//      if (cury2 > 600) cury2 = 600;
      GUGJ2YMin = cury2;
      GUGJ2YMax = cury2;
      delay(50);
    }
  }

  while (GUG_key_table[ESC] == KEY_IS_UP) 
  {
      GUGClearDisplay();
      GUGCenterText(0,  BLUE,"GUG - Joystick Calibration");
      if (mode == 0)
	  {
        GUGCenterText(162,B_BLUE,"Swirl each joystick around several times");
	    GUGCenterText(171,B_BLUE,"then trim for center if necessary.");
        GUGCenterText(180,GREEN ,"<F1> to reset or <M> for manual Mode");
	    GUGCenterText(191,RED,"Press <ESC> when finished");
	  }
	  else if (mode < 9)
	  {
        GUGCenterText(162,B_BLUE,"Press <SPACE> while");
        switch(mode)
		{
		  case 1: GUGCenterText(171,B_BLUE,"holding Joystick 1 fully LEFT");
		          break;
		  case 2: GUGCenterText(171,B_BLUE,"holding Joystick 1 at full TOP");
		          break;
		  case 3: GUGCenterText(171,B_BLUE,"holding Joystick 1 fully RIGHT");
		          break;
		  case 4: GUGCenterText(171,B_BLUE,"holding Joystick 1 at full BOTTOM");
		          break;
		  case 5: GUGCenterText(171,B_BLUE,"holding Joystick 2 fully LEFT");
		          break;
		  case 6: GUGCenterText(171,B_BLUE,"holding Joystick 2 at full TOP");
		          break;
		  case 7: GUGCenterText(171,B_BLUE,"holding Joystick 2 fully RIGHT");
		          break;
		  case 8: GUGCenterText(171,B_BLUE,"holding Joystick 2 at full BOTTOM");
		          break;
		}
	  }
      else
	  {
	    GUGCenterText(171,B_BLUE,"Trim for center if necessary.");
        GUGCenterText(180,GREEN ,"<F1> to reset or <M> for manual Mode");
	    GUGCenterText(191,RED,"Press <ESC> when finished");
	  }

      if (GUG_key_table[KEY_M] == KEY_IS_DOWN)
	  {
        if ((mode == 0) || (mode == 9))
	      mode = 1;
		GUG_key_table[KEY_M] = KEY_IS_UP;
	  }

      if (GUG_key_table[F1] == KEY_IS_DOWN)
	  {
	    mode = 0;
        if (GUGX1Active)
        {
          curx1 = GUGReadX1Axis();            // Get the current x and set limits.
//          if (curx1 <   0) curx1 =   0;
//	      if (curx1 > 500) curx1 = 500;
          GUGJ1XMin = curx1;
          GUGJ1XMax = curx1;
          delay(50);
          cury1 = GUGReadY1Axis();            // Get the current y and set limits.
//          if (cury1 <   0) cury1 =   0;
//	      if (cury1 > 500) cury1 = 500;
          GUGJ1YMin = cury1;
          GUGJ1YMax = cury1;
          delay(50);
        }

        if (GUGX2Active)
        {
          curx2 = GUGReadX2Axis();            // Get the current x and set limits.
//          if (curx2 <   0) curx2 =   0;
//	      if (curx2 > 500) curx2 = 500;
          GUGJ2XMin = curx2;
          GUGJ2XMax = curx2;
          delay(50);
          cury2 = GUGReadY2Axis();            // Get the current y and set limits.
//          if (cury2 <   0) cury2 =   0;
//	      if (cury2 > 500) cury2 = 500;
          GUGJ2YMin = cury2;
          GUGJ2YMax = cury2;
          delay(50);
        }
	    GUG_key_table[F1] = KEY_IS_UP;
	  }

      if (GUGX1Active)
        GUGPutText( 57,30,GREEN,"Joystick #1");
      else
        GUGPutText( 51,30,RED  ,"Not Installed");

      if (GUGX2Active)
        GUGPutText(187,30,GREEN,"Joystick #2");
      else
        GUGPutText(181,30,RED  ,"Not Installed");

      if ((mode == 0) || (mode == 9))
	  {
        if (flag == 0)
  	    {
          curx1 = GUGScaleX1Axis();
   	    }
  	    else if (flag == 2)
  	    {
          curx2 = GUGScaleX2Axis();
   	    }
  	    else if (flag == 1)
  	    {
          cury1 = GUGScaleY1Axis();
        }
  	    else if (flag == 3)
  	    {
          cury2 = GUGScaleY2Axis();
  	    }
  	  }
      else
	  {
	    if (GUG_key_table[SPACE] == KEY_IS_DOWN)
		{
		  GUG_key_table[SPACE] = KEY_IS_UP;
	      switch(mode)
		  {
		    case 1: curx1 = GUGReadX1Axis();
//                    if (curx1 <   0) curx1 =   0;
//	                if (curx1 > 500) curx1 = 500;
                    GUGJ1XMin = curx1;
 			        break;
		    case 2: cury1 = GUGReadY1Axis();
//                    if (cury1 <   0) cury1 =   0;
//	                if (cury1 > 500) cury1 = 500;
                    GUGJ1YMin = cury1;
 			        break;
		    case 3: curx1 = GUGReadX1Axis();
//                    if (curx1 <   0) curx1 =   0;
//	                if (curx1 > 500) curx1 = 500;
                    GUGJ1XMax = curx1;
				    break;
		    case 4: cury1 = GUGReadY1Axis();
//                    if (cury1 <   0) cury1 =   0;
//	                if (cury1 > 500) cury1 = 500;
                    GUGJ1YMax = cury1;
 			        break;
		    case 5: curx2 = GUGReadX2Axis();
//                    if (curx2 <   0) curx2 =   0;
//	                if (curx2 > 500) curx2 = 500;
                    GUGJ2XMin = curx2;
 			        break;
		    case 6: cury2 = GUGReadY2Axis();
//                    if (cury2 <   0) cury2 =   0;
//	                if (cury2 > 500) cury2 = 500;
                    GUGJ2YMin = cury2;
 			        break;
		    case 7: curx2 = GUGReadX2Axis();
//                    if (curx2 <   0) curx2 =   0;
//	                if (curx2 > 500) curx2 = 500;
                    GUGJ2XMax = curx2;
 			        break;
		    case 8: cury2 = GUGReadY2Axis();
//                    if (cury2 <   0) cury2 =   0;
//	                if (cury2 > 500) cury2 = 500;
                    GUGJ2YMax = cury2;
 			        break;
    	  }
		  if ((GUGX2Active)	&& (mode < 9))
		    mode++;
		  if ((!GUGX2Active) && (mode == 5))
		    mode = 9;
		}
	  }

      buttons = GUGReadButtons();
      if (buttons & J1_B1)
	  {
	    GUGFillRectangle(50,140,80,150,GREEN);
	  }
	  else
	  {
	    GUGRectangle(50,140,80,150,RED);
	  }
      if (buttons & J1_B2)
	  {
	    GUGFillRectangle(108,140,138,150,GREEN);
	  }
	  else
	  {
	    GUGRectangle(108,140,138,150,RED);
	  }

      if (buttons & J2_B1)
	  {
	    GUGFillRectangle(180,140,210,150,GREEN);
	  }
	  else
	  {
	    GUGRectangle(180,140,210,150,RED);
	  }
      if (buttons & J2_B2)
	  {
	    GUGFillRectangle(238,140,268,150,GREEN);
	  }
	  else
	  {
	    GUGRectangle(238,140,268,150,RED);
	  }


      for (x=0; x<99; x+=11)
	  {
	    for (y=0; y<99; y+=11)
		{
		  if ((curx1 >= x) && (curx1 <= (x+11)) &&
		      (cury1 >= y) && (cury1 <= (y+11)))
		  {
		    GUGFillRectangle(x+45,y+40,x+56,y+51,GREEN);
		  }
		  else
		  {
		    GUGRectangle(x+45,y+40,x+56,y+51,RED);
		  }

		  if ((curx2 >= x) && (curx2 <= (x+11)) &&
		      (cury2 >= y) && (cury2 <= (y+11)))
		  {
		    GUGFillRectangle(x+175,y+40,x+186,y+51,GREEN);
		  }
		  else
		  {
		    GUGRectangle(x+175,y+40,x+186,y+51,RED);
		  }

		}
	  }
//	  GUGFastCopy(VGA_START);
      GUGCopyToDisplay();
      ++flag;
	  flag &= 3;

     if (!GUG_KBD_Installed)
	 {
	   if (kbhit())
	   {
         GUG_key_table[ESC] = KEY_IS_DOWN;
		 getch();
	   }
	 }
    if ((mode > 0) && (mode < 9))
	  GUG_key_table[ESC] = KEY_IS_UP;
  }
  GUG_key_table[ESC] = KEY_IS_UP;

  if ((out = fopen("JOY.CAL","w")) != NULL)
  {
    fprintf(out,"%d\n",GUGX1Active);
    fprintf(out,"%d\n",GUGJ1XMin);
    fprintf(out,"%d\n",GUGJ1YMin);
    fprintf(out,"%d\n",GUGJ1XMax);
    fprintf(out,"%d\n",GUGJ1YMax);
    fprintf(out,"%d\n",GUGX2Active);
    fprintf(out,"%d\n",GUGJ2XMin);
    fprintf(out,"%d\n",GUGJ2YMin);
    fprintf(out,"%d\n",GUGJ2XMax);
    fprintf(out,"%d\n",GUGJ2YMax);
    fclose(out);
  }

  return(installed);
}
////////////////////////////////////////////////////////////////////////////
int GUGScaleX1Axis()
{
  int curx1;

  if (GUGX1Active == 0)
    return(0);

  curx1 = GUGReadX1Axis();
//  if (curx1 <   0) curx1 =   0;
//  if (curx1 > 500) curx1 = 500;

  if (curx1 < GUGJ1XMin) { GUGJ1XMin = curx1; }
    else if (curx1 > GUGJ1XMax) { GUGJ1XMax = curx1; }
  if (GUGJ1XMax != GUGJ1XMin)
  {
     curx1 = ((curx1 - GUGJ1XMin) * 100) / (GUGJ1XMax-GUGJ1XMin);
     if (curx1 < 0)  curx1 =  0;
     if (curx1 > 99) curx1 = 99;
  }
  return(curx1);
}
////////////////////////////////////////////////////////////////////////////
int GUGScaleX2Axis()
{
  int curx2;

  if (GUGX2Active == 0)
    return(0);

  curx2 = GUGReadX2Axis();
//  if (curx2 <   0) curx2 =   0;
//  if (curx2 > 500) curx2 = 500;

  if (curx2 < GUGJ2XMin) { GUGJ2XMin = curx2; }
    else if (curx2 > GUGJ2XMax) { GUGJ2XMax = curx2; }
  if (GUGJ2XMax != GUGJ2XMin)
  {
    curx2 = ((curx2 - GUGJ2XMin) * 100) / (GUGJ2XMax-GUGJ2XMin);
    if (curx2 < 0)  curx2 =  0;
    if (curx2 > 99) curx2 = 99;
  }
  return(curx2);
}
////////////////////////////////////////////////////////////////////////////
int GUGScaleY1Axis()
{
  int cury1;

  if (GUGX1Active == 0)
    return(0);

  cury1 = GUGReadY1Axis();
//  if (cury1 <   0) cury1 =   0;
//  if (cury1 > 500) cury1 = 500;
 
  if (cury1 < GUGJ1YMin) { GUGJ1YMin = cury1; }
    else if (cury1 > GUGJ1YMax) { GUGJ1YMax = cury1; }
  if (GUGJ1YMax != GUGJ1YMin)
  {
    cury1 = ((cury1 - GUGJ1YMin) * 100) / (GUGJ1YMax-GUGJ1YMin);
    if (cury1 < 0)  cury1 =  0;
    if (cury1 > 99) cury1 = 99;
  }
  return(cury1);
}
////////////////////////////////////////////////////////////////////////////
int GUGScaleY2Axis()
{
  int cury2;

  if (GUGX2Active == 0)
    return(0);

  cury2 = GUGReadY2Axis();
//  if (cury2 <   0) cury2 =   0;
//  if (cury2 > 500) cury2 = 500;
 
  if (cury2 < GUGJ2YMin) { GUGJ2YMin = cury2; }
    else if (cury2 > GUGJ2YMax) { GUGJ2YMax = cury2; }
  if (GUGJ2YMax != GUGJ2YMin)
  {
    cury2 = ((cury2 - GUGJ2YMin) * 100) / (GUGJ2YMax-GUGJ2YMin);
    if (cury2 < 0)  cury2 =  0;
	if (cury2 > 99) cury2 = 99;
  }
  return(cury2);
}
