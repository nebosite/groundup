#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <malloc.h>

#define MAXCHUNKSIZE 64000L
#define SAMPLE signed char far
#define BYTE    unsigned char
#define WORD    unsigned short int
#define DWORD   unsigned long int
#define CHAR		signed char
#define SHORT	  signed short int
#define LONG	  signed long int
#define VMALLOC farmalloc
#define VFREE   farfree
#define VFAR    far

typedef struct wave {
	LONG id;
	WORD sample_rate;
	WORD byte_rate;
	SAMPLE *data;
	DWORD chunk_size;                   // size of this chunk in bytes
	DWORD sample_size;                  // size of entire linked sample
	struct wave VFAR *next;             // points to next link.
	struct wave VFAR *head;             // points to top link.
} WAVE;


WAVE VFAR *LoadWave(CHAR *wavefile, CHAR *errstring);
char token[100] = {"mysound"};
LONG waveidseed= -1;


/**************************************************************************
	main(void)

	DESCRIPTION:  Converts a wave file to C code for Varmint's Audio Tools

**************************************************************************/
int main(int argc, char *argv[])
{
	int i=0,j,k,linelen;
	WAVE *w,*h;
	char err[255];
																			// Check sommand line arguments
	if( argc < 2) {
		printf("Usage:  wave2c [filename] [tokenname]\n");
		exit(1);
	}
																			// Load the wave file
	w = LoadWave(argv[1],err);
	if(!w) {
		printf("ERROR: %s\n",err);
		exit(1);
	}
																			// set up default token
	strcpy(token,argv[1]);
	i = 0;
	while(token[i] && token[i] != '.') i++;
	token[i] = 0;
																			// check if sound token was spec'd
	if(argc >2) strcpy(token,argv[2]);

																			// Dump the wave to stdout
	fprintf(stdout,"#include \"vat.h\"\n\n\n");

																			// Give length information
	h = w;
	i = 0;
	linelen = fprintf(stdout,"LONG ");
	while(w) {
		linelen += fprintf(stdout,"%s%dlength = %d",token,i++,w->chunk_size-1);
		if(linelen > 60) {
			fprintf(stdout,";\n");
			if(w->next) linelen = fprintf(stdout,"LONG ");
		}
		else if(w->next) fprintf(stdout,",");
		else fprintf(stdout,";\n\n");
		w = w->next;
	}

	i = 0;
	w = h;
																			// give the data
	while(w) {
		linelen = fprintf(stdout,"SAMPLE %s%d[]={",token,i++);
		for(j = 1; j < w->chunk_size; j++) {
			k = *(w->data+j);
			linelen += fprintf(stdout,"%d",k);
			if(j != w->chunk_size) linelen += fprintf(stdout,",");
			if(linelen > 70) {                // keep it nice and pretty
				fprintf(stdout,"\n");
				linelen = 0;
			}
		}
		fprintf(stdout,"};\n\n");
		w = w->next;
	}


	return 0;
}



/*********************************************************************
	WAVE VFAR *LoadWave(CHAR *wavefile, CHAR *errstring)

	DESCRIPTION:  Loads a wave files  (mono, 8bit)

	INTPUTS:

		wavefile  	filename of wave file
		errstring   preallocated string for storing errors (256 bytes min)

	RETURNS:
		pointer to data

**********************************************************************/
WAVE VFAR *LoadWave(CHAR *wavefile, CHAR *errstring)
{
	WORD ii;
	WAVE VFAR *newwave,*hold;
	BYTE dummydata[255];
	FILE *input;
	DWORD rlen,flen,blen,length,l;
	WORD s_per_sec,b_per_sec,num_channels,tag;
	CHAR riffid[5],waveid[5],fmtid[5],dataid[5];

	input = fopen(wavefile,"rb");
	if(!input) {                              // If unsuccesful...
		sprintf(errstring,"Cannot open file %s",wavefile);
		return(NULL);                           // REturn a null pointer
	}
																						// Get WAVE header data

	fread(riffid,1,4,input);                  // wave files staqrt with "Riff"
	riffid[4] = 0;
	fread(&rlen,1,4,input);                   // File size
	fread(waveid,1,4,input);                  // Wave id string  ("Wave")
	waveid[4] = 0;
	if(strcmp(waveid,"WAVE")) {               // is it a wave file?
		fclose(input);
		sprintf(errstring,"%s is not a WAVE file",wavefile);
		return(NULL);
	}

	fread(fmtid,1,4,input);                   // Format id string ("fmt ")
	fmtid[4] = 0;
	fread(&flen,1,4,input);                   // offset to data
	if(flen > 240) flen = 240;                // Just a precaution so that
																						// We do not overload dummydata

	fread(&tag,1,2,input);                    // tag
	fread(&num_channels,1,2,input);           // number of channels
	fread(&s_per_sec,1,2,input);              // sample rate (hz)
	fread(&b_per_sec,1,2,input);              // bytes per seconf rate
	fread(dummydata,1,(size_t)flen-8,input);          // Skip ahead
	fread(dataid,1,4,input);                  // Dataid string
	dataid[4] = 0;
	fread(&length,1,4,input);                  // length of data

																						// create top mem structure
	newwave = (WAVE VFAR *)VMALLOC(sizeof(WAVE));
	if(!newwave) {                            // out of mem?
		fclose(input);
		sprintf(errstring,"Out of memory");
		return(NULL);
	}
	hold = newwave;                           // Set working pointer
	hold->next = NULL;

	l = length;                               // dummy holder for length

	while(l > 0) {
		blen = MAXCHUNKSIZE;                    // Number of bytes to read
		if(l < MAXCHUNKSIZE) blen = l;

		hold->data = (SAMPLE *)VMALLOC(blen+1); // allocate memory for data
		if(!hold->data) {                       // oops.  Not enough mem!
			fclose(input);
			sprintf(errstring,"Out of memory");
			while(newwave){                       // deallocate what we have done
				if(newwave->data) VFREE(newwave->data);
				hold = newwave;
				newwave = newwave->next;
				VFREE(hold);
			}
			return(NULL);
		}


		fread(hold->data,1,(size_t)blen,input);    // read the data

		for(ii = 0; ii < blen; ii++) {       // convert to signed format
			*(hold->data + ii) = ((BYTE)*(hold->data + ii))-128;
		}
																				 // Fill in structure
		hold->id = waveidseed;
		hold->sample_rate = s_per_sec;
		hold->byte_rate = b_per_sec;
		hold->chunk_size = blen;             // size of this chunk in bytes
		hold->sample_size = length;          // size of entire linked sample
		hold->head = newwave;                // points to top link.

																				 // Allocate next link
		if(l-blen > 0) {
			hold->next = (WAVE VFAR *)VMALLOC(sizeof(WAVE));
			if(!hold->next) {                    // out of mem?
				fclose(input);
				sprintf(errstring,"Out of memory");
				while(newwave){                    // deallocate what we have done
					if(newwave->data) VFREE(newwave->data);
					hold = newwave;
					newwave = newwave->next;
					VFREE(hold);
				}
				return(NULL);
			}
			hold = hold->next;
			hold->next = NULL;
		}
		l -= blen;
	}

	fclose(input);                            // Wrap it up
	waveidseed --;
	return(newwave);
}
