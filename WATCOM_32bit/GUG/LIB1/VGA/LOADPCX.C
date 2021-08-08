/*
** load a pcx image file
*/

//#define DEBUG 1

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

int GUGLoadPCX(char *file, char *buffer, unsigned char *palette)
{
	unsigned depth,i,x;
	int c;
	FILE *in;
	PCXHEAD	pcxheader;
#ifdef DEBUG
    FILE *out;
    int  xx;
#endif

	/* does the file exist? */
	if(access(file, 0))
		return(0);

	/* were we able to open the file? */
	if((in = fopen(file, "rb")) == 0)
		return(0);

	/* read in the header */
	fread(&pcxheader, sizeof(PCXHEAD), 1, in);

#ifdef DEBUG
    out = fopen("header.txt","w");
	fprintf(out,"pcxheader.manufacturer   %c %d\n",pcxheader.manufacturer,pcxheader.manufacturer);
	fprintf(out,"pcxheader.version        %c %d\n",pcxheader.version,pcxheader.version);
	fprintf(out,"pcxheader.encoding       %c %d\n",pcxheader.encoding,pcxheader.encoding);
	fprintf(out,"pcxheader.bits_per_pixel %c %d\n",pcxheader.bits_per_pixel,pcxheader.bits_per_pixel);

	fprintf(out,"pcxheader.xmin,pcxheader.ymin      %d,%d\n",pcxheader.xmin,pcxheader.ymin);
	fprintf(out,"pcxheader.xmax,pcxheader.ymax      %d,%d\n",pcxheader.xmax,pcxheader.ymax);
	fprintf(out,"pcxheader.hres,pcxheader.vres      %d,%d\n",pcxheader.hres,pcxheader.vres);

    fprintf(out,"pcxheader.palette[] ");
    for (xx=0; xx<48; ++xx)
	{
	  fprintf(out,"%1d,",pcxheader.palette[xx]);
	}
    fprintf(out,"\n");

	fprintf(out,"pcxheader.reserved       %c %d\n",pcxheader.reserved,pcxheader.reserved);
	fprintf(out,"pcxheader.color_planes   %c %d\n",pcxheader.color_planes,pcxheader.color_planes);

	fprintf(out,"pcxheader.bytes_per_line %d\n",pcxheader.bytes_per_line);
	fprintf(out,"pcxheader.palette_type   %d\n",pcxheader.palette_type);

    fprintf(out,"pcxheader.filler[] ");
    for (xx=0; xx<50; ++xx)
	{
	  fprintf(out,"%1d,",pcxheader.filler[xx]);
	}
    fprintf(out,"\n");

    fclose(out);
#endif

	/* check to make sure it's a picture */
	if(pcxheader.manufacturer != 0x0a || pcxheader.version != 5)
		return(0);

	/* find the palette */
	fseek(in, -769L, SEEK_END);

	if(fgetc(in) != 0x0c)
		return(0);

	fread(palette, 768, 1, in);
	fseek(in, 128L, SEEK_SET);
    for (x=0; x<768; x++)
	{
	  palette[x] = palette[x] >> 2;
	}
  
	/* determine size of picture */
	depth = (pcxheader.ymax - pcxheader.ymin + 1) *
					pcxheader.bytes_per_line;

	/* unpack the file */
	x = 0;
	do
	{
		/* get a key byte */
		c = fgetc(in) & 0xff;

		/* if it's a run of bytes field */
		if((c & 0xc0) == 0xc0)
		{
			i = c & 0x3f;			/* AND off the high bits */
			c = fgetc(in);		/* get the run byte */
			while(i--)				/* run the byte */
				buffer[x++] = c;
		}
		else
			buffer[x++] = c;			/* else just store it */
	}
	while(x < depth);

	fclose(in);
	return(1);
}
