#include <stdio.h>
#include <string.h>
#include <malloc.h>

#include "..\gug_pcx.h"

// PCX Rotation

void GUGRotatePCX90(GUG_PCX *gug_pcx) {
  int  sz,sx,sy;
  int  x,y,y1,t;
  char *pcx_save;

  if (gug_pcx == NULL) return;

  // create the storage buffer and size the PCX
  sx = gug_pcx->x_size;
  sy = gug_pcx->y_size;
  sz = sx * sy;
  if ((pcx_save = malloc(sz)) == NULL)
    return;

  // get a copy of the PCX
  memcpy((char *)pcx_save,(char *)gug_pcx->image,sz);

  // Rotate the PCX
  for (x=0; x<sx; ++x) {
    for (y=0,y1=sy-1; y<sy; ++y,--y1) {
  	  gug_pcx->image[(x*sy)+y1] = pcx_save[(y*sx)+x];
    }
  }

  // Swap the X/Y size in the GUG_PCX structure
  t = gug_pcx->x_size;
  gug_pcx->x_size = gug_pcx->y_size;
  gug_pcx->y_size = t;

  // Swap the X/Y size in the PCXHEAD structure
  t = gug_pcx->pcxheader.xmin;
  gug_pcx->pcxheader.xmin = gug_pcx->pcxheader.ymin;
  gug_pcx->pcxheader.ymin = t;
  t = gug_pcx->pcxheader.xmax;
  gug_pcx->pcxheader.xmax = gug_pcx->pcxheader.ymax;
  gug_pcx->pcxheader.ymax = t;
  gug_pcx->pcxheader.bytes_per_line =	
    gug_pcx->pcxheader.xmax - gug_pcx->pcxheader.xmin + 1;

  free(pcx_save);
}

