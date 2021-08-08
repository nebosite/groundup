#include <stdio.h>
#include <math.h>
#include "..\lib1\gug.h"
#include "..\lib1\colors.h"
#include "..\lib1\pi.h"
#include "..\lib1\widgets.h"

int hcf(i,j)
{
  int remain;
  do 
  { 
    remain=i % j;
	i = j;
	j = remain;
  }
  while (remain != 0);
  return(i);
}

void circle(float r,int l, int ox, int oy)
{
  float theta=0;
  float thinc;
  int   i;
  int   x,y;

  thinc=2*M_PI/l;
 
  if (r == 0) return;
  GUGPIXMove((int)r+ox,0+oy);
  for (i=0; i<l; ++i)
  {
    theta = theta + thinc;
    x = r * cos(theta);
	y = r * sin(theta);
	GUGPIXLine(x+ox,y+oy);
  }
}




void spirograph(int a, int b, int d)
{
  int i,n,ptnumber;
  float phi;
  float theta=0;
  float thinc=M_PI * 0.02;
  int   x,y;

  if (a == 0) return;
  if (b == 0) return;
  if (d == 0) return;

  n = b / hcf(a,b);
  ptnumber = n * 100;
  pix_x = a-b+d;
  pix_y = 0;

  GUGPIXMove(pix_x+146,pix_y+100);

  for (i=0; i<ptnumber; i++)
  {
    theta += thinc;
	phi = theta * (a-b) / b;
	x = (a-b)*cos(theta)+d*cos(phi);
	y = (a-b)*sin(theta)+d*sin(phi);
    if ((x+146) < 298)
	  GUGPIXLine(x+146,y+100);
  }
}

#define MAX 20

#define A_UP    1
#define A_DOWN  2
#define B_UP    3
#define B_DOWN  4
#define D_UP    5
#define D_DOWN  6
#define C_UP    7
#define C_DOWN  8
#define EXIT   10 
#define SEE    20

///////////////////
main(int argc,char *argv[])
{
    int a,b,d;
	int c;
    int x;
    int loop = 1;
    unsigned int mx,my,mb;
    struct GUG_cntrl *controls[MAX];
	char mes[80];
    char *spr[10];
    int  spiro;

    if (GUGLoadSprite("spiro.spr",spr) < 0)
    {
      printf("Sprite File not found\n");
	  return;
    }

    GUGInitControl(controls,MAX);

    GUGRegSpinSprite(298, 10,A_UP  ,spr[0],450,50,controls);    
    GUGRegSpinSprite(298, 31,A_DOWN,spr[1],450,50,controls);    

    GUGRegSpinSprite(298, 52,B_UP  ,spr[0],450,50,controls);    
    GUGRegSpinSprite(298, 73,B_DOWN,spr[1],450,50,controls);    

    GUGRegSpinSprite(298, 94,D_UP  ,spr[0],450,50,controls);    
    GUGRegSpinSprite(298,115,D_DOWN,spr[1],450,50,controls);    

    GUGRegSpinSprite(298,138,C_UP  ,spr[0],450,50,controls);    
    GUGRegSpinSprite(298,159,C_DOWN,spr[1],450,50,controls);    

    GUGRegControlText(281,185,EXIT  ,"Exit",WHITE,controls);    

    spiro = GUGRegRadioText(    0,179,SEE   ,"On ",GREEN,1,GUG_UNSELECTED,controls);
            GUGRegRadioText(    0,189,SEE   ,"Off",GREEN,1,GUG_SELECTED  ,controls);


    GUGInitialize();                      // Fire up GUG

	c = 112;

    a = 60;
	b = 18;
	d = 30;

    GUGClearDisplay();

    if (GUGGetRadioStatus(spiro,controls))
	{
   	  GUGPIXSetColor(WHITE);
      circle(a,30,146,100);
      circle(b,30,146+a-b,100);
      GUGLine(146+a-b-2+d,100,146+a-b+2+d,100,WHITE);
      GUGLine(146+a-b+d  , 98,146+a-b+d  ,102,WHITE);
	}

    GUGPIXSetColor(c);
    spirograph(a,b,d);
    sprintf(mes,"A:%3d B:%3d D:%3d  Clr:%3d",a,b,d,c);
    GUGCenterText(0,WHITE,mes);  
    GUGCopyToDisplay();
 
    do
    {
      GUGMouseShow();
	  x = GUGProcessControls(controls,&mx,&my,&mb);
	  GUGMouseHide();
      switch(x)
	  {
	    case C_UP:    if (x < 255) c++;
		              break;
		case C_DOWN:  if (x > 0) c--;
		              break;
		case A_UP:    a++;
		              break;
		case A_DOWN:  if (a > 1) a--;
		              break;
		case B_UP:    b++;
		              break;
		case B_DOWN:  if (b > 1) b--;
		              break;
		case D_UP:    d++;
		              break;
		case D_DOWN:  d--;
		              break;
		case EXIT:    loop = 0;
	                  break;
	  }

      GUGFillRectangle(  0,  0,297,184,0);
	  GUGFillRectangle(  0,185,280,199,0);

      if (GUGGetRadioStatus(spiro,controls))
	  {
 	    GUGPIXSetColor(WHITE);
        circle(a,30,146,100);
        circle(b,30,146+a-b,100);
        GUGLine(146+a-b-2+d,100,146+a-b+2+d,100,WHITE);
        GUGLine(146+a-b+d  , 98,146+a-b+d  ,102,WHITE);
	  }

      GUGPIXSetColor(c);
      spirograph(a,b,d);
      sprintf(mes,"A:%3d B:%3d D:%3d  Clr:%3d",a,b,d,c);
      GUGCenterText(0,WHITE,mes);  
      GUGCopyToDisplay();
    }
	while (loop);

    GUGEnd();						      // shutdown GUG
}       // end main 

