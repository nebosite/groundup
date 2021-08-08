//*************************************************************************
// Return the width of a text string in the current font
//

#include <string.h>

extern int GUG_Font_Width;

int GUGTextWidth(char *text)
{
  return(strlen(text) * GUG_Font_Width);
}       
