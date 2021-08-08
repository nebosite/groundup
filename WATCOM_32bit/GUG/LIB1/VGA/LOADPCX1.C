/*
** read a pcx image file into the GUG_PCX structure
*/

#include <conio.h>
#include <io.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys\stat.h>

#include "..\gug_pcx.h"

GUG_PCX *GUGReadPCX(char *file)
{
	unsigned depth,i,x,rc;
	int c;
	FILE *in;
    GUG_PCX *gug_pcx;
    char *image;

	/* does the file exist? */
	if (access(file, 0) || !(in = fopen(file, "rb")))
       return(NULL);

    // Create the GUG_PCX structure
	if ((gug_pcx = (GUG_PCX *)malloc(sizeof(GUG_PCX))) == NULL)
	{
	  fclose(in);
	  return(NULL);
    }

    // Init the GUG_PCX structure
    gug_pcx->image  = NULL;
	gug_pcx->x_size = 0;
	gug_pcx->y_size = 0;

	/* read in the header */
    fread(&gug_pcx->pcxheader, sizeof(PCXHEAD), 1, in);

	/* check to make sure it's a picture */
	if(gug_pcx->pcxheader.manufacturer != 0x0a ||
       gug_pcx->pcxheader.version != 5)
    {
	   fclose(in);
       free(gug_pcx);
       return(NULL);
	}

    // Set the X and Y size members
    gug_pcx->y_size  = gug_pcx->pcxheader.ymax - gug_pcx->pcxheader.ymin + 1;
    gug_pcx->x_size  = gug_pcx->pcxheader.xmax - gug_pcx->pcxheader.xmin + 1;
//  gug_pcx->x_size  = gug_pcx->pcxheader.bytes_per_line;

    // Is it a valid size?
    if ((!gug_pcx->y_size) || (!gug_pcx->x_size))
	{
	   fclose(in);
       free(gug_pcx);
       return(NULL);
	}

	/* find the palette marker */
	fseek(in, -769L, SEEK_END);

    // Are we at the palette marker
    if (fgetc(in) != 0x0c)
    {
	   fclose(in);
       free(gug_pcx);
       return(NULL);
	}

    // Load the pallette
	fread(gug_pcx->palette, 768, 1, in);

    // Convert the palette from 8-bit to 6-bit
    for (x=0; x<768; x++)
	{
	  gug_pcx->palette[x] = gug_pcx->palette[x] >> 2;
	}

	/* determine size of picture */
//  depth = (gug_pcx->pcxheader.ymax - gug_pcx->pcxheader.ymin + 1) *
//                                     gug_pcx->pcxheader.bytes_per_line;
    depth = gug_pcx->y_size * gug_pcx->x_size;

	// malloc() the image buffer
	if ((gug_pcx->image = (char *)malloc(depth)) == NULL)
	{
	  fclose(in);
	  free(gug_pcx);
	  return(NULL);
	}

    // Point to the image portion of the input file
    fseek(in, 128L, SEEK_SET);

 	/* unpack the file */
	rc = x = 0;
    image = gug_pcx->image;
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
            {
			   // gug_pcx->image[x++] = c;
               if (gug_pcx->x_size < gug_pcx->pcxheader.bytes_per_line)
			   {
			     ++rc;
				 if (rc < gug_pcx->pcxheader.bytes_per_line)
				 {
			       *image = c;
			       image++;
			       x++;
				 }
				 else
				 {
				   rc = 0;
				 }
			   }
			   else
			   {
			     *image = c;
			     image++;
			     x++;
			   }
			}
		}
		else
		{
		  // gug_pcx->image[x++] = c;			/* else just store it */
          if (gug_pcx->x_size < gug_pcx->pcxheader.bytes_per_line)
		  {
		    ++rc;
		    if (rc < gug_pcx->pcxheader.bytes_per_line)
			{
			  *image = c;
			  image++;
			  x++;
			}
			else
			{
			  rc = 0;
			}
		  }
		  else
		  {
		    *image = c;
		    image++;
		    x++;
		  }
	    }
	}
	while(x < depth);

	fclose(in);
	return(gug_pcx);
}
