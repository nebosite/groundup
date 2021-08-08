#include "tetris.h"
#include "hiscore.h"

char hiscorefile[]={"hiscores.dat"};

HISCORE far *scores = NULL;


/**************************************************************************
	void generatescores()

	DESCRIPTION: Debugging function for generating bogus high scores

**************************************************************************/
void generatescores()
{
/*	long int score;
	long int key;
	long int rows;
	int i;

	for(i = 1; i <= 10; i++) {
		score = i*55000;
		rows = i*22;
		key = hihash(NULL, score, rows,(int)localkey);
		printf("%ld, %ld, %4.4X%8.8lX\n",score,rows,localkey,key);
	}
*/
}

/**************************************************************************
	HISCORE far *newscore(char *name,long int score, int rows)

	DESCRIPTION:  Utility function for setting up a high score structure.

**************************************************************************/
HISCORE far *newscore(char *name,long int score, int rows)
{
	HISCORE far *hs;
																		// Allocate a struct
	hs = (HISCORE far *)farmalloc(sizeof(HISCORE));
	if(!hs) return NULL;              // out of memory?

																		// Allocate space for a name
	hs->name = (char far *)calloc(1,strlen(name)+1);
	if(!hs->name) {
		farfree(hs);
		return NULL;
	}
																		// Assign values
	strcpy(hs->name,name);
	hs->score = score;
	hs->rows = rows;
	hs->next = NULL;

	return hs;
}



/**************************************************************************
	void freescore(HISCORE far *hs)

	DESCRIPTION:  Frees memory allocated for a high score struct

**************************************************************************/
void freescore(HISCORE far *hs)
{
	farfree(hs->name);
	farfree(hs);
}



/**************************************************************************
	long int hihash(char *name, long int score, int rows)

	DESCRIPTION:

**************************************************************************/
long int hihash(char *name, long int score, long int rows, int rnum)
{
	long int key = 0;
	int i;
	long int xorspot = 222;
																			// hash in the name if there is one
	if(name) {
		for(i = 0; i < strlen(name); i++) {
			key += ((int)name[i]) ^ xorspot++;
		}
	}

	xorspot ^= rows;
	rows += xorspot;
																			// hash in score and rows
	key += score*44532L + score%9874;
	key += rows + rows * 1000L;
	key ^= (long int)rnum * rnum;
	key ^= 0xEBFDE521L;

	return ~key;                        // return mangled key
}


/**************************************************************************
	int insertscore(HISCORE far **head,HISCORE far *hs)

	DESCRIPTION: Inserts a hiscore into a specified list.

	RETURNS:  Location of score on the list.

**************************************************************************/
int insertscore(HISCORE far **head,HISCORE far *hs)
{
	HISCORE far *temp1,*temp2;
	int spot = 1;

	temp1 = NULL;                   // initialize search
	temp2 = *head;
																	// Cruise the list
	while(temp2 && temp2->score >= hs->score) {
		spot++;
		if(spot > 100) {              // Don't keep more than 100 scores
			freescore(hs);
			return spot;
		}
		temp1 = temp2;
		temp2 = temp2->next;
	}

	hs->next = temp2;

	if(!temp1) *head = hs;          // First on list should replace head;
	else temp1->next = hs;          // Any other score just goes in list;

	return spot;                    // Return position
}

/**************************************************************************
	HISCORE far *readscores(void)

	DESCRIPTION: Reads hiscores from gile into a list.

**************************************************************************/
HISCORE far *readscores(void)
{
	HISCORE *head = NULL,*temp;
	FILE *input;
	char name[256];
	long int score;
	int rows;
	long int rnum;
	long int key;
	int flag = 1;
	int bytesread;
	BYTE charcount;
																			// open the high score file
	input = fopen(hiscorefile,"rb");
	if(!input) {
		head = newscore("Honig",0,0);
		return head;
	}
																			// Reading loop
	while(flag) {
																			// read in number of characters in name
		bytesread = fread(&charcount,1,1,input);
		if(!bytesread) {
			flag = 0;
			continue;
		}

		fread(name,1,charcount,input);    // Read name
		fread(&score,1,4,input);          // Read score
		fread(&rows,1,2,input);           // Read rows
		fread(&rnum,1,2,input);           // Read Random key
		fread(&key,1,4,input);            // Read verification key

																			// Test agaist a reconstructed key
		if(key == hihash(name,score,rows,(int)rnum)) {
																			// make a new score and insert in
																			// the list;
			temp = newscore(name,score,rows);
			if(!temp) {
				flag = 0;
				continue;
			}
			insertscore(&head,temp);
		}


	}

	fclose(input);
	if(!head) head = newscore("Honig",0,0);

	return head;
}



/**************************************************************************
	void writescores(HISCORE *hs)

	DESCRIPTION:

**************************************************************************/
void writescores(HISCORE *hs)
{
	FILE *output;
	long int key,rnum;
	BYTE charnum;
	int outcount = 0;
																							 // Open hi score file
	output = fopen(hiscorefile,"wb");
	if(!output) {
		return;
	}

	while(hs && outcount < 100) {
		charnum = strlen(hs->name) + 1;             // get length of name
		fwrite(&charnum,1,1,output);                // write name length
		fwrite(hs->name,1,charnum,output);          // write name
		fwrite(&(hs->score),1,4,output);            // write score
		fwrite(&(hs->rows),1,2,output);             // write rows
																								// Pick a random number
		rnum = random(0xFFFF);
		key = hihash(hs->name,hs->score,hs->rows,(int)rnum);  // get verification key
		fwrite(&rnum,1,2,output);                   // write key
		fwrite(&key,1,4,output);                    // write key

		hs = hs->next;
		outcount++;
	}

	fclose(output);
}