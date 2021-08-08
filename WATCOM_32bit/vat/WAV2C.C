#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <io.h>
#include <ctype.h>
#include "vat.h"

#define BYTES_PER_LINE 16

void main(int argc, char *argv[])
{
  int  handle;
  char infile[132];
  char outfile[132];
  char headfile[132];
	char err[132],string[256];
  char *c;
	int  x,y,z,cx;
  WAVE  *snd;                         // pointer to the sound Struct
  unsigned short value;

  FILE *out;
  FILE *head;


	printf("\nWAV to C converter Ver 1.03\n");
  printf(" Copyright 1995-1996 Ground Up Software\n\n");

  if (argc < 2)
  {
    fprintf(stderr,"usage: wav2c filename\n");
    return;
  }

  if ((c = strstr(argv[1],".")) != NULL)
  {
    *c = '\0';
  }
  for (x=0; x<strlen(argv[1]); ++x)
	argv[1][x] = tolower(argv[1][x]);
  sprintf(infile  ,"%s.wav",argv[1]);
  sprintf(outfile ,"%s.c"  ,argv[1]);
  sprintf(headfile,"%s.h"  ,argv[1]);

  if ((snd = LoadWave(infile,err)) == NULL)
  {
    fprintf(stderr,"Unable to open %s for read.\n",infile);
    return;
  }

  if (snd->sample_size > 1000000) {
    fprintf (stderr, "Unable to compile %s: larger than 1M\n", infile);
    FreeWave (snd);
    return;
  }

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
  fprintf(out,"/* WAV to C language output              */\n");
  fprintf(out,"/*****************************************/\n\n");
  fprintf(out,"// Input file    %s.wav\n",argv[1]);
  fprintf(out,"// c output file %s.c\n"  ,argv[1]);
  fprintf(out,"// h output file %s.h\n\n"  ,argv[1]);
  fprintf(out,"#include <vat.h>\n\n");
  fprintf(out,"#ifdef __cplusplus\n");
  fprintf(out,"extern \"C\" {\n");
  fprintf(out,"#endif\n");
  fprintf(out,"\n");
 
  fprintf(head,"/*****************************************/\n");
  fprintf(head,"/* WAV to C language output              */\n");
  fprintf(head,"/*****************************************/\n\n");
  fprintf(head,"#ifdef __cplusplus\n");
  fprintf(head,"extern \"C\" {\n");
  fprintf(head,"#endif\n");
  fprintf(head,"\n");
  fprintf(head,"extern WAVE *%s;\n\n",argv[1]);

  fprintf(out,"WAVE %s_data = {\n",argv[1]);
  fprintf(out,"%8d, // ID\n",0);
  fprintf(out,"%8d, // Sample Rate\n",snd->sample_rate);
  fprintf(out,"%8d, // Byte Rate\n",snd->byte_rate);
  fprintf(out,"%8d, // Stereo Flag\n",snd->stereo);
  fprintf(out,"%8d, // Loaded From Flag (not with LoadWave)\n",0);

	fprintf(out,"(SAMPLE *)\n\"");

	cx = z = y = 0;

	for (x=0; x<snd->chunk_size; ++x)
	{
		value = (unsigned char)snd->data[x];
/*		sprintf(string,"%d",value);
		cx+= strlen(string);
		fprintf(out,string);*/
		fprintf(out,"\\%03o",value);

		if (++y == BYTES_PER_LINE)
		{
			fprintf(out,"\"\n\"");
			cx = 0;
			z += BYTES_PER_LINE;
			y = 0;
		}

	}

	fprintf(out,"\",\n");

  fprintf(out,"%8d, // Size of chunk\n",snd->chunk_size);
  fprintf(out,"%8d, // Sample Size\n",snd->sample_size);
  fprintf(out,"%8d, // Internal Pointer (not used here)\n",0);
  fprintf(out,"  &%s_data  // Internal 'head' pointer\n", argv[1]);


  fprintf(out,"};\n");
  fprintf(out,"\nWAVE *%s=&%s_data;\n\n", argv[1], argv[1]);

  for (x=0; x<strlen(argv[1]); ++x)
	argv[1][x] = toupper(argv[1][x]);
  fprintf(head,"#define MAX_%s_SIZE %ld\n",argv[1],snd->chunk_size);

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

  printf("Normal Completion, %ld bytes processed.\n",snd->chunk_size);

}
