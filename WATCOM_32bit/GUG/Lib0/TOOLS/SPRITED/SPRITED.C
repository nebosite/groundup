#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <gug.h>
#include <colors.h>

void get_line(char *s,FILE *in);

void main(int argc,char *argv[])
{
  int  npointer;
  char *pointer[5];	/* declare an array of pointers */
  char *sprites[120];
  int  max;
  int  i,j;
  int  t;
  int  x[10][120],y[10][120];
  int  flag;
  char s[80];
  char op[768];
  char np[768];
  char *c;
  char infile[120];
  char temp[120];
  char outfile[120];
  char headfile[120];
  FILE *out,*in;
  int  points;
  int  xm,ym;
  char buffer[120];
  char yn;
  int  status;
  unsigned int buttons,mx,my,mb;

  int  colors[9] =
  {
    B_RED,B_GREEN,B_BLUE,RED,GREEN,BLUE,D_RED,D_GREEN,L_BLUE
  };


  extern char *mouse[4];

  printf("\nSprite Designator Ver 1.00\n");
  printf(" Copyright 1996 Ground Up\n\n");

  if (argc < 3)
  {
	fprintf(stderr,"usage: sprited filename points colorflag\n");
	return;
  }

  points = atoi(argv[2]);

  if (points < 1)
  {
	 printf("Error - You must designate at least 1 point\n");
	 return;
  }
  if (points > 9)
  {
	 printf("Error - You may designate no more than 9 points\n");
	 return;
  }

  if ((c = strstr(argv[1],".")) != NULL)
  {
	*c = '\0';
  }
  for (i=0; i<strlen(argv[1]); ++i)
	argv[1][i] = tolower(argv[1][i]);
  sprintf(infile  ,"%s.spr",argv[1]);

  strcpy(temp,argv[1]);
  i = strlen(temp);
  if (i > 6) i = 6;
  temp[i]   = '_';
  temp[i+1] = 'd';
  temp[i+2] = '\0';
  sprintf(outfile ,"%s.c"  ,temp);
  sprintf(headfile,"%s.h"  ,temp);

  max = GUGLoadSprite(infile,sprites);

  if (max < 1)
  {
	 printf("Error loading the sprite file\n");
	 return;
  }

  if ((in = fopen(outfile,"r")) != NULL)
  {
    get_line(buffer,in);
    get_line(buffer,in);
    get_line(buffer,in);
    get_line(buffer,in);

    for (i=0; i<points; i++)
    {
		for (j=0;j<=max;++j)
		{
		  get_line(buffer,in);
		  if (buffer[2] == ' ')
			 x[i][j] = atoi(&buffer[3]);
		  else
			 x[i][j] = atoi(&buffer[2]);
//		  printf("%s %d %d %d\n",buffer,i,j,x[i][j]);
//		  getch();
		}
	 }
	 get_line(buffer,in);
	 get_line(buffer,in);

	 get_line(buffer,in);
	 get_line(buffer,in);
	 for (i=0; i<points; i++)
	 {
		for (j=0;j<=max;++j)
		{
		  get_line(buffer,in);
		  if (buffer[2] == ' ')
			 y[i][j] = atoi(&buffer[3]);
		  else
			 y[i][j] = atoi(&buffer[2]);
//		  printf("%s %d %d %d\n",buffer,i,j,y[i][j]);
//		  getch();
		}
	 }

	 fclose(in);
  }
  else
  {
	 for (i=0; i<points; i++)
	 {
		for (j=0;j<=max;++j)
		{
		  x[i][j] = -1;
		  y[i][j] = -1;
		}
	 }
  }

  GUGInitialize();
  GUGMouseReset(&status,&buttons);  

  /* change the mouse shape to the red pointer from the sprite file */
  //SetMouse(mouse[0]);
  GUGMouseShow();

  i = 0;

  for (flag=1;flag==1;)
  {
    GUGMouseHide();
    GUGClearDisplay();
	if (argc > 3)
	{
	  GUGPutFGSprite(100,100,sprites[i]);
	  for (j=0; j<points; ++j)
	  {
		 if ((x[i][j] > -1) && (y[i][j] > -1))
		 {
			GUGSetPixel(x[j][i]+100,y[j][i]+100,colors[j]);
			sprintf(s," Point %1d at %2d,%2d",j,x[j][i],y[j][i]);
//			SpriteColor = colors[j];
			GUGPutText(0,(j+1)*10,colors[j],s);
		 }
	  }

	  if (i>0)
	  {
		 GUGPutFGSprite(140,100,sprites[i-1]);
		 for (j=0; j<points; ++j)
		 {
			GUGSetPixel(x[j][i-1]+140,y[j][i-1]+100,colors[j]);
		 }
	  }
	}
	else
	{
	  GUGPutMNSprite(100,100,15,sprites[i]);
	  for (j=0; j<points; ++j)
	  {
		 if ((x[j][i] > -1) && (y[j][i] > -1))
		 {
			GUGSetPixel(x[j][i]+100,y[j][i]+100,colors[j]);
			sprintf(s," Point %1d at %2d,%2d",j,x[j][i],y[j][i]);
//			SpriteColor = colors[j];
			GUGPutText(0,(j+1)*10,colors[j],s);
		 }
	  }
	  if (i>0)
	  {
		 GUGPutMNSprite(160,100,15,sprites[i-1]);
		 for (j=0; j<points; ++j)
		 {
			GUGSetPixel(x[j][i-1]+160,y[j][i-1]+100,colors[j]);
		 }
	  }
	}

	GUGRectangle(50,185,80,199,215);
	GUGPutText(55,188,WHITE,"Prev");

	GUGRectangle(90,185,120,199,215);
	GUGPutText(95,188,215,"Next");

	GUGRectangle(130,185,160,199,215);
	GUGPutText(135,188,215,"Exit");

//	GUGSpriteColor = colors[8];
//	GUGPutText(0,0,215,s);

	GUGMouseShow();

    do
	{
	  GUGMousePosition(&mb,&mx,&my);
	}
	while (mb != 1);
	xm = mx;
	ym = my;

	if ((xm >  50) &&
		 (ym > 185) &&
		 (xm <  80) &&
		 (ym < 199))
	{
	  GUGMouseHide();
	  GUGPutText(55,188,6,"Prev");
	  GUGMouseShow();
	  if (i > 0)
	  {
		 i--;
	  }
      do
	  {
	    GUGMousePosition(&mb,&mx,&my);
	  }
	  while (mb == 1);
	}
	else if ((xm >  90) &&
		 (ym > 185) &&
		 (xm < 120) &&
		 (ym < 199))
	{
	  GUGMouseHide();
	  GUGPutText(95,188,6,"Next");
	  GUGMouseShow();
	  if (i < max)
	  {
		 i++;
	  }
      do
	  {
	    GUGMousePosition(&mb,&mx,&my);
	  }
	  while (mb == 1);
	}
	else if ((xm > 130) &&
		 (ym > 185) &&
		 (xm < 185) &&
		 (ym < 199))
	{
	  GUGMouseHide();
	  GUGPutText(135,188,6,"Exit");
	  GUGMouseShow();
	  flag = 0;
      do
	  {
	    GUGMousePosition(&mb,&mx,&my);
	  }
	  while (mb == 1);
	}
	else if ((xm >= 100) &&
		 (ym >= 100) &&
		 (xm <= 100+GUGSpriteWidth(sprites[i])) &&
		 (ym <= 100+GUGSpriteHeight(sprites[i])) )
	{
      do
	  {
	    GUGMousePosition(&mb,&mx,&my);
	  }
	  while (mb == 1);
	  GUGMouseHide();
	  GUGFillRectangle(100,100,
					   100+GUGSpriteWidth(sprites[i]),
					   100+GUGSpriteHeight(sprites[i]),0);
	  GUGFillRectangle(160,100,
					   160+GUGSpriteWidth(sprites[i]),
					   100+GUGSpriteHeight(sprites[i]),0);

	  GUGRectangle(50,185,80,199,6);
	  GUGPutText(55,188,6,"Prev");

	  GUGRectangle(90,185,120,199,6);
	  GUGPutText(95,188,6,"Next");

	  GUGRectangle(130,185,160,199,6);
	  GUGPutText(135,188,6,"Exit");

	  if (argc > 3)
	  {
		 GUGPutFGSprite(100,100,sprites[i]);
		 if (i>0)
		 {
			GUGPutFGSprite(140,100,sprites[i-1]);
			for (j=0; j<points; ++j)
			{
			  GUGSetPixel(x[j][i-1]+160,y[j][i-1]+100,colors[j]);
			}
		 }
	  }
	  else
	  {
		 GUGPutMNSprite(100,100,15,sprites[i]);
		 if (i>0)
		 {
			GUGPutMNSprite(160,100,15,sprites[i-1]);
			for (j=0; j<points; ++j)
			{
			  GUGSetPixel(x[j][i-1]+160,y[j][i-1]+100,colors[j]);
			}
		 }
	  }
	  GUGMouseShow();

	  for (j=0; j<points;)
	  {
         do
	     {
	       GUGMousePosition(&mb,&mx,&my);
	     }
	     while (mb == 1);
		 xm = mx;
		 ym = my;
		 if ((xm >= 100) &&
			 (ym >= 100) &&
			 (xm <= 100+GUGSpriteWidth(sprites[i])) &&
			 (ym <= 100+GUGSpriteHeight(sprites[i])) )
		 {
			x[j][i] = xm-100;
			y[j][i] = ym-100;
			sprintf(s," Point %1d at %2d,%2d",j,x[j][i],y[j][i]);
			GUGPutText(0,(j+1)*10,colors[j],s);
			GUGMouseHide();
			GUGSetPixel(x[j][i]+100,y[j][i]+100,colors[j]);
			GUGMouseShow();
			++j;
		 }
        do
	    {
	      GUGMousePosition(&mb,&mx,&my);
	    }
	    while (mb == 1);
	  }
	}
	else
	{
      do
	  {
	    GUGMousePosition(&mb,&mx,&my);
	  }
	  while (mb == 1);
	}
  }

  GUGEnd();


  yn = ' ';
  do
  {
	 printf("Save Changes [Y/N] ? ");
	 yn = toupper(getch());
  }
  while (!((yn == 'N') || (yn == 'Y')));


  if (yn == 'Y')
  {
    out = fopen(outfile,"w");
    fprintf(out,"// Sprite Designator Ver 1.00 \n\n");

    fprintf(out,"int %s_x[%1d][%1d] =\n",argv[1],points,max+1);
    fprintf(out,"{\n");
    for (i=0; i<points; i++)
    {
	  for (j=0;j<max;++j)
	  {
		fprintf(out,"  %2d,  // %s_x[%1d][%1d]\n",x[i][j],argv[1],i,j);
	  }
	  fprintf(out,"  %2d   // %s_x[%1d][%1d]\n",x[i][j],argv[1],i,j);
    }
    fprintf(out,"};\n\n");

    fprintf(out,"int %s_y[%1d][%1d] =\n",argv[1],points,max+1);
    fprintf(out,"{\n");
    for (i=0; i<points; i++)
    {
	  for (j=0;j<max;++j)
	  {
		fprintf(out,"  %2d,  // %s_y[%1d][%1d]\n",y[i][j],argv[1],i,j);
	  }
	  fprintf(out,"  %2d   // %s_y[%1d][%1d]\n",y[i][j],argv[1],i,j);
    }
    fprintf(out,"};\n");

    fclose(out);


    out = fopen(headfile,"w");
    fprintf(out,"// Sprite Designator Ver 1.00 \n\n");

    fprintf(out,"extern int %s_x[%d][%1d];\n",argv[1],points,max+1);
    fprintf(out,"extern int %s_y[%d][%1d];\n",argv[1],points,max+1);

    fclose(out);

    printf("\n\nChanges Saved\n\n");
  }
}

/**********************************************************************/

void get_line(char *s,FILE *in)
{
  int c,i;

  for (i=0; i<119 && (c=getc(in))!=EOF && c!='\n'; ++i)
	 s[i] = c;
  s[i] = '\0';
}

