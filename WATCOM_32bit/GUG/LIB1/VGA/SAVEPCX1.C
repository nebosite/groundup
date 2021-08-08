/*
** save a pcx image file
*/

#include <conio.h>
#include <io.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys\stat.h>

typedef struct {
  int x_size;         // Width of the PCX
  int y_size;	      // Height of the PCX
  char *image;	      // Points to the PCX's image data
  char palette[768];  // Points to the PCX's palette data
} GUG_PCX;

/* pcx file header structure */
typedef struct	{
	char  manufacturer;
	char  version;
	char  encoding;
	char  bits_per_pixel;
	short xmin, ymin;
	short xmax, ymax;
	short hres;
	short vres;
	char  palette[48];
	char  reserved;
	char  color_planes;
	short bytes_per_line;
	short palette_type;
	char  filler[58];
} PCXHEAD;

int GUGWritePCX(char *file,
                int x_start, int y_start, 
                int x_size,  int y_size,
                unsigned char *palette)
{
	unsigned x,y,r,rc;
	FILE *out;
	PCXHEAD	pcxheader;

    x_size++;
	y_size++;

    pcxheader.manufacturer   =  10;
    pcxheader.version        =   5;
    pcxheader.encoding       =   1;
    pcxheader.bits_per_pixel =   8;
    pcxheader.xmin           =   0;
    pcxheader.ymin           =   0;
    pcxheader.xmax			 = x_size-1;
    pcxheader.ymax           = y_size-1;
    pcxheader.hres			 = 640;
    pcxheader.vres           = 480;
    pcxheader.reserved       =   0;
    pcxheader.color_planes   =   1;
    if ((x_size&1) == 0)
      pcxheader.bytes_per_line = x_size;
	else
      pcxheader.bytes_per_line = x_size+1;	
    pcxheader.palette_type   =   1;

    for (x=0; x<48; ++x)
      pcxheader.palette[x] = 0;
    for (x=0; x<58; ++x)
     pcxheader.filler[x]   = 0;

	/* were we able to open the file? */
	if((out = fopen(file, "wb")) == 0)
		return -1;

	/* write the header */
	fwrite(&pcxheader, sizeof(PCXHEAD), 1, out);

	/* write the file */
    rc = 0;
	for (y=0; y<y_size; ++y)
	{
	  for (x=0; x<pcxheader.bytes_per_line; ++x)
	  {
        if (pcxheader.bytes_per_line == x_size)
		{
	      if ((unsigned char)GUGGetPixel(x+x_start,y+y_start) < 0xc0)
		  {
		    fputc((unsigned char)GUGGetPixel(x+x_start,y+y_start),out);
		  }
		  else
		  {
	        fputc(0xC1,out);
		    fputc((unsigned char)GUGGetPixel(x+x_start,y+y_start),out);
		  }
		}
		else
		{
		  ++rc;
		  if (rc < pcxheader.bytes_per_line)
		  {
	        if ((unsigned char)GUGGetPixel(x+x_start,y+y_start) < 0xc0)
		    {
		      fputc((unsigned char)GUGGetPixel(x+x_start,y+y_start),out);
		    }
		    else
		    {
	          fputc(0xC1,out);
		      fputc((unsigned char)GUGGetPixel(x+x_start,y+y_start),out);
		    }
		  }
		  else
		  {
		    rc=0;
		    fputc((unsigned char)0,out);
		  }
		}
	  }
	}

	/* save the palette */
	fputc(0x0c,out);
    for (x=0; x<768; x+=3)
	{
	  fputc((unsigned char)palette[x]<<2  ,out);
	  fputc((unsigned char)palette[x+1]<<2,out);
	  fputc((unsigned char)palette[x+2]<<2,out);
  }

	fclose(out);
	return 0;
}
