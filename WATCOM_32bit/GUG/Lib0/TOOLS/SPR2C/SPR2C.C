#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <io.h>
#include <ctype.h>
#include <gug.h>

void main(int argc, char *argv[])
{
  int  handle;
  char infile[132];
  char outfile[132];
  char headfile[132];
  char *c;
  int  x,y,z,count,s;
  int  len;                               // length of sprite
  unsigned char *spr[1024];                 // pointer to the sprites
  unsigned short value;

  FILE *out;
  FILE *head;


  printf("\nSPR to C converter Ver 1.00\n");
  printf(" Copyright 1995-1996 Ground Up Software\n\n");

  if (argc < 2)
  {
	fprintf(stderr,"usage: spr2c filename\n");
	return;
  }

  if ((c = strstr(argv[1],".")) != NULL)
  {
	*c = '\0';
  }
  for (x=0; x<strlen(argv[1]); ++x)
	argv[1][x] = tolower(argv[1][x]);
  sprintf(infile  ,"%s.spr",argv[1]);
  sprintf(outfile ,"%s.c"  ,argv[1]);
  sprintf(headfile,"%s.h"  ,argv[1]);

  if ((count=GUGLoadSprite(infile,spr)) < 1)
  {
	fprintf(stderr,"Unable to open %s for read.\n",infile);
	return;
  }

  printf("Loaded %d Sprites\n\n",count);

  if ((out = fopen(outfile,"w")) == NULL)
  {
	fprintf(stderr,"Unable to open %s for write.\n",outfile);
	return;
  }

  if ((head = fopen(headfile,"w")) == NULL)
  {
	fclose(out);
	fprintf(stderr,"Unable to open %s for write.\n",headfile);
	return;
  }

  fprintf(out,"/*****************************************/\n");
  fprintf(out,"/* SPR to C language output              */\n");
  fprintf(out,"/*****************************************/\n\n");
  fprintf(out,"#ifdef __cplusplus\n");
  fprintf(out,"extern \"C\" {\n");
  fprintf(out,"#endif\n");
  fprintf(out,"\n");
 
  fprintf(head,"/*****************************************/\n");
  fprintf(head,"/* SPR to C language output              */\n");
  fprintf(head,"/*****************************************/\n\n");
  fprintf(head,"#ifdef __cplusplus\n");
  fprintf(head,"extern \"C\" {\n");
  fprintf(head,"#endif\n");
  fprintf(head,"\n");
 
  for (s=0; s<count; ++s)
  {

  fprintf(out,"char %s_%1d[] =\n",argv[1],s);
  fprintf(out,"{\n");

  fprintf(head,"extern char %s_%1d[];\n",argv[1],s);

  z = y = 0;
  len = GUGSpriteSize(spr[s]);
  for (x=0; x<len; ++x)
  {
	 value = (unsigned short)spr[s][x];
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
  fprintf(head,"#define MAX_%s_%d_SIZE %ld\n",argv[1],s,len);

  }

  fprintf(head,"#ifdef __cplusplus\n");
  fprintf(head,"};\n");
  fprintf(head,"#endif\n");
  fprintf(head,"\n");
  fclose(head);
  fprintf(out,"#ifdef __cplusplus\n");
  fprintf(out,"};\n");
  fprintf(out,"#endif\n");
  fprintf(out,"\n");
  fclose(out);

  printf("Normal Completion, %ld bytes processed.\n",len);

}
