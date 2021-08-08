#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <time.h>

void clickthrough(int argc, char *argv[]); 
void linkpage(char *url);			 
void getad(int argc, char *argv[]); 
unsigned int getchecksum(char *buffer,int numbytes);

/*===========================================================================
	int random(int num) 
============================================================================*/
int random(int num) 
{
	return rand() % num;
}

/**************************************************************************
  void main(int argc, char *argv[])

  DESCRIPTION:

**************************************************************************/
void main(int argc, char *argv[]) 
{
	if(argc > 1) {
		if(*argv[1] == 'l' || *argv[1] == 'L') clickthrough(argc,argv);
		else if( *argv[1] == 'g' || *argv[1] == 'G') getad(argc,argv);
	}

}

/*===========================================================================
	void clickthrough(int argc, char *argv[]) 

	DESCRIPTION:

	  REVISIONS:
			1/3/00		Eric Jorgensen		Initial Version

============================================================================*/
void clickthrough(int argc, char *argv[]) 
{
	int adid = -1,id;
	FILE *input = NULL;
	char buffer[1000],*spot;


	if(argc > 2) adid = atoi(argv[2]);
	if(adid < 0) linkpage("/");

	input = fopen("clickthrough.dat","r");
	if(!input) linkpage("/");

	while(fgets(buffer,999,input)) {
		if(spot = strchr(buffer,'\n')) *spot = 0;
		sscanf(buffer,"%d",&id);
		if(id == adid) {
			spot = buffer;
			while(*spot && (isdigit(*spot) || isspace(*spot))) spot++;
			linkpage(spot);
			fclose(input);
			return;
		}
	}

	linkpage("/");

}

/*===========================================================================
	void linkpage(char *page)

	DESCRIPTION:	Send back an HTML document that will automatically refresh
					to the specified URL.

	  REVISIONS:
			1/3/00		Eric Jorgensen		Initial Version

============================================================================*/
void linkpage(char *url)
{
    printf("Content-type: text/html%c%c",10,10);
	printf("<HTML>\n");
	printf("<TITLE>Alpine Development Ad Page</TITLE>\n");
	printf("<meta http-equiv=\"refresh\"\n");
	printf("content=\"0;url=%s\">\n",url);
	exit(0);
}

/*===========================================================================
	void getad(int argc, char *argv[])

	DESCRIPTION:	Returns and as a binary html document

					Line 1 = Ad ID  (0 for no ad returned);
					Line 2 = Ad File Name
					Line 3 = Ad Checksum
					Line 4 = Start of ad data

	  REVISIONS:
			1/3/00		Eric Jorgensen		Initial Version

============================================================================*/
void getad(int argc, char *argv[])
{
	char adlist[1000][32],*spot;
	int numads = 0;
	char buffer[1000000],idbuffer[32];
	int pick= 0;
	time_t t;
	int numbytes;
	unsigned int checksum;	
	FILE *input;
								// Get the list of available ads
	input = _popen("dir /b ad_*.*","r");
	while(fgets(buffer,999,input)) {
		sscanf(buffer,"%s",adlist[numads]);
		numads++;
	}
	_pclose(input);

	if(!numads) return;

								// Pick a random ad and send it back
	srand(time(&t));
	pick = random(numads);

	input = fopen(adlist[pick],"rb");
	if(!input) return;

    printf("Content-type: binary%c%c",10,10);
	strcpy(idbuffer,adlist[pick]+3);
	if(spot = strchr(idbuffer,'.')) *spot = 0;
	printf("%s\n",idbuffer);
	printf("%s\n",adlist[pick]);
	numbytes = fread(buffer,1,999999,input);
	fclose(input);
	checksum = getchecksum(buffer,numbytes);
	printf("%u\n",checksum);
	fwrite(buffer,1,numbytes,stdout);
}

/*===========================================================================
	unsigned int getchecksum(char *buffer,int size)
============================================================================*/
unsigned int getchecksum(char *buffer,int numbytes)
{
	unsigned int checksum = numbytes;
	int i;

	for(i = 0; i < numbytes; i++) {
		checksum ^= ((unsigned int)(buffer[i]) << (i%23));
	}
	return checksum;
}


