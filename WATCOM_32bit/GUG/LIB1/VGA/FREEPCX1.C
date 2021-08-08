#include <conio.h>
#include <io.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys\stat.h>

#include "..\gug_pcx.h"

void GUGFreePCX(GUG_PCX *gug_pcx)
{
  // Release the IMAGE portion
  if (gug_pcx->image != NULL)
    free(gug_pcx->image);
  gug_pcx->image = NULL;

  // Release the structure
  if (gug_pcx != NULL)
    free(gug_pcx);
  gug_pcx = NULL;
}
