#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <io.h>
#include <ctype.h>
#include <gug.h>

void main(int argc, char *argv[])
{
  char infile[132];
  char outfile[132];
  char headfile[132];
  char *c;
  int  len;
  long x,y,z;
  unsigned char *buffer;
  char palette[768];
  unsigned short value;

  FILE *out;
  FILE *head;


  printf("\nPCX to C converter Ver 1.00 - GUG Version %s\n",GUGVersion());
  printf(" For 320x200x256 PCX's only!\n");
  printf(" Copyright 1995-1996 Ground Up Software\n\n");

  if (argc < 2)
  {
	fprintf(stderr,"usage: pcx2c filename\n");
	return;
  }

  if ((c = strstr(argv[1],".")) != NULL)
  {
	*c = '\0';
  }
  for (x=0; x<strlen(argv[1]); ++x)
	argv[1][x] = tolower(argv[1][x]);
  sprintf(infile  ,"%s.pcx",argv[1]);
  sprintf(outfile ,"%s.c"  ,argv[1]);
  sprintf(headfile,"%s.h"  ,argv[1]);

  buffer = (unsigned char *)malloc(128000L);

  if (GUGLoadPCX(infile,buffer,palette) == -1)
  {
	fprintf(stderr,"Unable to open or read PCX file\n");
	return;
  }

  if ((out = fopen(outfile,"w")) == NULL)
  {
	free(buffer);
	fprintf(stderr,"Unable to open %s for write.\n",outfile);
	return;
  }

  if ((head = fopen(headfile,"w")) == NULL)
  {
	free(buffer);
	fclose(out);
	fprintf(stderr,"Unable to open %s for write.\n",headfile);
	return;
  }

//  GUGInitialize();
//  GUGRestoreDisplay(buffer);

  fprintf(out,"/*****************************************/\n");
  fprintf(out,"/* PCX to C language output              */\n");
  fprintf(out,"/*****************************************/\n\n");

  fprintf(head,"/*****************************************/\n");
  fprintf(head,"/* PCX to C language output              */\n");
  fprintf(head,"/*****************************************/\n\n");

  fprintf(out,"char %s[] =\n",argv[1]);
  fprintf(out,"{\n");

  fprintf(head,"extern char %s[];\n",argv[1]);

  z = y = 0;
  for (x=0; x<64000L; ++x)
  {
	value = (unsigned short)buffer[x];
	if (z == 0)
	{
	  if (value > 15)
		fprintf(out,"  0x%2X",value);
	  else
		fprintf(out,"  0x0%1X",value);
	  z=1;
	}
	else
	{
	  if (value > 15)
		fprintf(out,",0x%2X",value);
	  else
		fprintf(out,",0x0%1X",value);
	}

	if (++y == 14)
	{
	  fprintf(out,",\n");
	  z = y = 0;
	}
  }

  fprintf(out,"\n};\n");

  for (x=0; x<strlen(argv[1]); ++x)
	argv[1][x] = toupper(argv[1][x]);
  fprintf(head,"#define MAX_%s_SIZE 64000\n",argv[1]);


  free(buffer);
  fclose(out);
  fclose(head);

//  GUGEnd();

  printf("Normal completion - 64000 bytes processed.\n");

}
