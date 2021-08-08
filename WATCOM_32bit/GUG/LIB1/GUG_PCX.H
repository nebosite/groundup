//**************************************************************************
// Ground Up Graphics PCX structures
//   Copyright 1995 Ground Up Software
//**************************************************************************

/* pcx file header structure */
typedef struct	{
	char  manufacturer;
	char  version;
	char  encoding;
	char  bits_per_pixel;
	short xmin, ymin;
	short xmax, ymax;
//        short hres;
//        short vres;
        unsigned short check_one;
        unsigned short check_two;
        char  sname[21];
        char  filler1[27];
//        char  palette[48];
        char  reserved;
	char  color_planes;
	short bytes_per_line;
	short palette_type;
        char  filler2[58];
} PCXHEAD;


// PCX functions for x_size by y_size by 256 PCX's
typedef struct {
  int x_size;         // Width of the PCX
  int y_size;	      // Height of the PCX
  char *image;	      // Points to the PCX's image data
  char palette[768];  // Points to the PCX's palette data
  PCXHEAD pcxheader;  // Header from the PCX
} GUG_PCX;
