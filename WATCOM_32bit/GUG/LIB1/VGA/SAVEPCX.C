/*
** write a pcx image file
*/

#include <conio.h>
#include <io.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys\stat.h>

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

int GUGSavePCX(char *file, char *buffer, unsigned char *palette)
{
	unsigned x,r;
	FILE *out;
	PCXHEAD	pcxheader;

    pcxheader.manufacturer   =  10;
    pcxheader.version        =   5;
    pcxheader.encoding       =   1;
    pcxheader.bits_per_pixel =   8;
    pcxheader.xmin           =   0;
    pcxheader.ymin           =   0;
    pcxheader.xmax			 = 319;
    pcxheader.ymax           = 199;
    pcxheader.hres			 = 640;
    pcxheader.vres           = 480;
    pcxheader.reserved       =   0;
    pcxheader.color_planes   =   1;
    pcxheader.bytes_per_line = 320;
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
	x = 0;
	do
	{
//      if (buffer[x] < 0xc0)
//	  {
//        r = 0;
//	    do
//	    {
//          r++;
//	    }
//	    while ((x % 320) && (r < 64) && ((x+r) < 64000) && (buffer[x] == buffer[x+r])); 
//        if (r > 1)
//		{
//          fputc((0xC0+r),out);
//          fputc((unsigned char)buffer[x],out);
//	      x += r;
//		}
//		else
//		{
//		  fputc((unsigned char)buffer[x],out);
//          x++;
//		}
//	  }
//	  else
//	  {
	    fputc(0xC1,out);
		fputc((unsigned char)buffer[x],out);
		x++;
//	  }
	}
	while(x < 64000);

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
