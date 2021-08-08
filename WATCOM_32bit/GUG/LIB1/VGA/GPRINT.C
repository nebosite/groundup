#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "svgacc.h"
#include <math.h>
#include <stdarg.h>
                                    // prototypes
void print(PixelMode pmode, int color, int x, int y, char *s, ...);
void drwnormalchar(PixelMode pmode, int color, int *x, int *y, char c);
void drwtalldiagchar(PixelMode pmode, int color, int *x, int *y, char c);
void drwtechchar(PixelMode pmode, int color, int *x, int *y, char c);
void drwwavybowchar(PixelMode pmode, int color, int *x, int *y, char c);

                                    // Globals
void (*charfunction)(PixelMode pmode, int color, int *x, int *y, char c);
int textx,texty,leftmargin=0,rightmargin=0,tabs=50,charsprinted;

/**************************************************************************
  main()

  DESCRIPTION:  Demonstrate user defined character functions

**************************************************************************/
main()
{
  int mouse,videocard,vmode;
  int i=32;
  float f = 22.6546;
  RGB palette[256];

  videocard = whichvga();           // Initialize graphics
  res800();                         // Select 800x600x256 resolution.
  mouse = whichmouse();             // initialize mouse

  leftmargin = 20;

  charfunction = drwnormalchar;

  print(SET,15,20,20,"Text with variables (just like printf!) %d %f",i,f);
  print(SET,14,20,40,"This\tis\ttext\twith\ttabs\tin\tit.");
  print(SET,14,20,60,"This is text with\nnewline characters\nin it.");

  charfunction = drwwavybowchar;

  print(SET,9,20,120,"Check out this wavy rainbow printing.................");

  charfunction = drwtalldiagchar;
  print(SET,13,20,160,"This is printed with talldiagchar.");
  print(SET,13,20,220,"This is printed with talldiagchar\nwith newlines\n");
  print(SET,13,textx,texty,"in it too!\nIt is also done in two statements.");

  charfunction = drwtechchar;
  print(SET,12,20,500,"You can do anything with user defined character");
  print(SET,12,textx,texty,"functions; even slow noisy text!");
  getch();


  restext();
}


/***************************************************************************
  print(pmode,color,x,y,*s,...)

  DESCRIPTION: This draws a string using a user defined char function.

    Note:  The char functions should have a prototype like this:

      foocharfunc(PixelMode pmode, int color, int *x, int *y, char c)

      This char function should also update the x and y coordinates passed
      to it.  Other than that, this function can pretty much to anything
      it likes.

    Note:  print modifies the globals textx, texty, and charsprinted

  INPUTS:
    pmode      Drawing mode
    color      Drawing color
    x,y        Upper left of text
    *s        Format string
    ...        Optional arguments (Just like printf)


****************************************************************************/
void print(PixelMode pmode, int color, int x, int y, char *s, ...)
{
  int i;
  va_list ap;
  static char string[1024];             // Note that largest printable string
                                        // is only 1  kb!

  va_start(ap, s);                      // sort out variable argument list
  vsprintf(string,s,ap);                // dump output to a string

  textx = x;                            // initialize globals
  texty = y;
  charsprinted=0;
                                        // check for NULL string pointer
  if(!string) {
    va_end(ap);                         // clean up
    return;
  }


  for(i=0; i < strlen(string); i++) {   // loop through the string
    charfunction(pmode,color,&textx,&texty,string[i]);  //  draw the char
    charsprinted++;
  }
  va_end(ap);                            // clean up

}


/**************************************************************************
  void drwnormalchar(PixelMode pmode, int color, int *x, int *y, char c)

  DESCRIPTION:  Regular character drawing

**************************************************************************/
void drwnormalchar(PixelMode pmode, int color, int *x, int *y, char c)
{
  char cbuf[2] = {"a"};

                                      // tab? 50 pixels
  if(c == '\t') {
    *x = ((int)(*x/tabs)+1)*tabs;
    return;
  }
  else if (c == '\n') {       // return?  newline
    *x = leftmargin;
    *y += 14;
    return;
  }

  cbuf[0] = c;                         // Build a pseudo string

  drwstring(pmode,color,0,cbuf,*x,*y); // Draw the character

  *x += 8;                             // Up date coordinates
}
/**************************************************************************
  void drwwavybowchar(PixelMode pmode, int color, int *x, int *y, char c)

  DESCRIPTION:  Wavy rainbow character drawing.

**************************************************************************/
void drwwavybowchar(PixelMode pmode, int color, int *x, int *y, char c)
{
  char cbuf[2] = {"a"};
  static int sy,scolor;


  if(!charsprinted) {                  // initialize inter variables at start
    scolor = color;
    sy = *y;
  }


                                      // tab? 50 pixels
  if(c == '\t') {
    *x = ((int)(*x/tabs)+1)*tabs;
    return;
  }
  else if (c == '\n') {       // return?  newline
    *x = leftmargin;
    *y += 14;
    return;
  }

  cbuf[0] = c;                         // Build a pseudo string

  drwstring(pmode,scolor,0,cbuf,*x,*y); // Draw the character

  *x += 8;                             // Up date coordinates
  *y = sy + 20 * sin(charsprinted/4.0);
  scolor++;
  if(scolor > 15) scolor = 9;
}
/**************************************************************************
  void drwtechchar(PixelMode pmode, int color, int *x, int *y, char c)

  DESCRIPTION:  Slow Regular character drawing with sound!

**************************************************************************/
void drwtechchar(PixelMode pmode, int color, int *x, int *y, char c)
{
  char cbuf[2] = {"a"};

  sound(1000);
  delay(1);
  nosound();
  delay(30);
                                      // tab? 50 pixels
  if(c == '\t') {
    *x = ((int)(*x/tabs)+1)*tabs;
    return;
  }
  else if (c == '\n') {       // return?  newline
    *x = leftmargin;
    *y += 14;
    return;
  }

  cbuf[0] = c;                         // Build a pseudo string

  drwstring(pmode,color,0,cbuf,*x,*y); // Draw the character

  *x += 8;                             // Up date coordinates
}

/**************************************************************************
  void drwtalldiagchar(PixelMode pmode, int color, int *x, int *y, char c)

  DESCRIPTION:  Big characters draw in a diagnanol fashion

**************************************************************************/
void drwtalldiagchar(PixelMode pmode, int color, int *x, int *y, char c)
{
  char cbuf[2] = {"a"};
  int i,j;

                                        // tab? 50 pixels
  if(c == '\t') {
    *x = ((int)(*x/tabs)+1)*tabs;
    return;
  }
  else if (c == '\n') {       // return?  newline
    *x = leftmargin;
    *y += 14;
    return;
  }

  cbuf[0] = c;                         // Build a pseudo string

  drwstring(pmode,color,0,cbuf,*x,*y); // Draw the character

  for(i = 7; i >= 0; i--) {           // Expand the character
    for(j = 13; j >= 0; j-- ) {
      drwfillbox(pmode,getpoint(i+*x,j+*y),i*2+*x,j*2+*y,i*2+*x+1,j*2+*y+1);
    }
  }

  *x += 16;                             // Up date coordinates
  *y += 2;
}

