/********************************************************************
                VARMINT'S AUDIO TOOLS 0.72

  COMPAT.H

  Written by: Bryan Wilkins (Feb. 1996)
              bwilkins@rt66.com

  Description: Compatability file for watcom so we don't have to
               change a million lines in order to get VATDEMO to
               work.
********************************************************************/

#define gotoxy(x,y) _settextposition(y,x)
#define clrscr() _clearscreen(0)
#define textcolor(x) _settextcolor(x)
#define _setcursortype(x) _settextcursor(x)
#define textbackground(x) _setbkcolor(x)
#define _SOLIDCURSOR  0x0007
#define _NORMALCURSOR 0x0607
#define _NOCURSOR     0x2000
#define BLACK         0
#define BLUE          1
#define GREEN         2
#define CYAN          3
#define RED           4
#define MAGENTA       5
#define BROWN         6
#define WHITE         15
#define DARKGRAY      8
#define LIGHTGRAY     8
#define LIGHTBLUE     9
#define LIGHTGREEN    10
#define LIGHTRED      12
#define LIGHTMAGENTA  13
#define YELLOW        14
