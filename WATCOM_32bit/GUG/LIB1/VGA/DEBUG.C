#include <i86.h>
#include <stdlib.h>
#include <malloc.h>
#include <dos.h>
#include <string.h>
#include "mode.H"

// point to the beginning of the MONO memory in mode
#define MONO_AREA           0xb000
#define MONO_LINEAR_ADDRESS ((MONO_AREA) << 4)

void GUGDebugString(char *str) {
  int i;
  char *MONO_MEMORY;

  MONO_MEMORY =	(char *)MONO_LINEAR_ADDRESS;
  
  for (i=0; i<240; ++i)
  {
    *MONO_MEMORY = ' ';
    ++MONO_MEMORY;
    ++MONO_MEMORY;
  } 
	
  MONO_MEMORY =	(char *)MONO_LINEAR_ADDRESS;

  for (i=0; i<strlen(str);++i) {
    *MONO_MEMORY = str[i];
    ++MONO_MEMORY;
    ++MONO_MEMORY;
  }
}

void GUGDebugClear() {
  int i;
  char *MONO_MEMORY;

  MONO_MEMORY =	(char *)MONO_LINEAR_ADDRESS;
  
  for (i=0; i<((80*25)*2); ++i)
  {
    *MONO_MEMORY = ' ';
    ++MONO_MEMORY;
  } 
}


void GUGDebugStringAtLine(char *str,int line) {
  int i;
  char *MONO_MEMORY;

  if ((line < 1) || (line > 25)) return;

  MONO_MEMORY =	(char *)MONO_LINEAR_ADDRESS;
  MONO_MEMORY += ((line-1) * 160);

  for (i=0; i<80; ++i)
  {
    *MONO_MEMORY = ' ';
    ++MONO_MEMORY;
    ++MONO_MEMORY;
  } 
	
  MONO_MEMORY =	(char *)MONO_LINEAR_ADDRESS;
  MONO_MEMORY += ((line-1) * 160);

  for (i=0; (i<strlen(str) && (i < 80));++i) {
    *MONO_MEMORY = str[i];
    ++MONO_MEMORY;
    ++MONO_MEMORY;
  }
}

void GUGDebugStringAtXY(char *str,int col,int line) {
  int i;
  char *MONO_MEMORY;

  if ((line < 1) || (line > 25)) return;
  if ((col  < 1) || (col  > 80)) return;

  MONO_MEMORY =	(char *)MONO_LINEAR_ADDRESS;
  MONO_MEMORY += ((line-1) * 160) + ((col-1) * 2);

  for (i=0; (i<strlen(str) && (i < (80-strlen(str))));++i) {
    *MONO_MEMORY = str[i];
    ++MONO_MEMORY;
    ++MONO_MEMORY;
  }
}

