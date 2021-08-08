#include "tetris.h"
#include "svgacc.h"
#include "conio.h"
#include <stdio.h>

#define ABORTKEY 0x01
#define PAUSEKEY 0x3b
#define MUSICKEY 0x3c
#define SOUNDKEY 0x3d
#define TURBOKEY 0x3e
#define SNAPSHOTKEY 0x3f
#define NUMFACTORS 15
#define LISTSIZE 20
#define NUMROUNDS 150
#define NUMPICS 30000
#define GENERATIONS 80
#define MUTATIONS 2

typedef struct factorset{
	double score;
	double rowaverage;
	long int high,low;
	long int above100;
	double factor[NUMFACTORS];
} FACTORSET;


int gene_gamesegment(void);
int condenseg(PLAYER *p);
void cogitate(PLAYER *plyr);

extern int bgcolor;


int gx,gy;
int graphicson=FALSE;
int gene_frame;
int pp;
BYTE pieceq[NUMPICS];
extern double factor[NUMFACTORS];

FACTORSET far fset[LISTSIZE];
FACTORSET far mfset = { 0,0,0,0,0,
	{
0.000000   ,
0.000000   ,
6.444000   ,
-1.271438  ,
-11.199992 ,
0.000000   ,
0.000000   ,
6.027201   ,
0.000000   ,
0.000000   ,
0.000000   ,
0.000000   ,
0.000000   ,
0.000000   ,
0.000000

			}};




/**************************************************************************
	void fileset(FACTORSET *fs)

	DESCRIPTION:

**************************************************************************/
int fileset(FACTORSET far *fs)
{
	int i,j;

	fs->score = fs->rowaverage + fs->low;
																	// Find our place
	for(i = 0; i < LISTSIZE && fset[i].score >= fs->score; i++);

	if(i == LISTSIZE) return 0;       // Off the end?

																	// Everybody move!
	for(j = LISTSIZE-1; j > i; j--) {
		memcpy(&fset[j],&fset[j-1],sizeof(FACTORSET));
	}
																	// put new one in
	memcpy(&fset[i],fs,sizeof(FACTORSET));
	return 1;
}


/**************************************************************************
	void writeit(void)

	DESCRIPTION: Writes out to the factor file

**************************************************************************/
void writeit(void)
{
	FILE *output;
	int j;
	static int x = 0;

	output = fopen("factors.txt","a");


	if(output) {                 // Write top factor
		fprintf(output,"NEWFACTOR\n");
		fprintf(output,"%.2lf\n",fset[0].rowaverage);
		for(j = 0; j < NUMFACTORS; j++) {
			fprintf(output,"%lf\n",fset[0].factor[j]);
		}
		fclose(output);
	}

	drwline(SET,14,x,maxy-2,x,maxy-fset[0].score/4);
	x++;
}


/**************************************************************************
	void writeall(void)

	DESCRIPTION:

**************************************************************************/
void writeall(void)
{
	FILE *output;
	int i,j;

	output = fopen("top20.txt","w");

	if(output) {
		for(i = 0; i < NUMFACTORS; i++) {
			fprintf(output,"NEWFACTOR\n");
			fprintf(output,"%.2lf,%ld,%ld,%ld\n",fset[i].rowaverage,
				fset[i].low,fset[i].high,fset[i].above100);
			for(j = 0; j < NUMFACTORS; j++) {
				fprintf(output,"%lf\n",fset[i].factor[j]);
			}


		}
		fclose(output);
	}
}


/**************************************************************************
	int getfac(FILE *input, FACTORSET *fs)

	DESCRIPTION:

**************************************************************************/
int getfac(FILE *input, FACTORSET *fs)
{
	char str[1000];
	int flag = 1;
	int err;
	int i;

																			// Find next factor
	while(flag) {
		err = (int)fgets(str,255,input);
		if(!err) return 0;
		if(*str == 'N') flag = 0;
	}

	if(!fgets(str,255,input)) return 0; // Grab score
	sscanf(str,"%lf",&(fs->rowaverage));

	for(i = 0; i < NUMFACTORS; i++) {   // Get factors
		fgets(str,255,input);
		sscanf(str,"%lf",&(fs->factor[i]));
	}

	return 1;

}
/**************************************************************************
	void decide(void)

	DESCRIPTION:  Reads in fators from tryfac.txt and trys them all on a 100
								game stretch to see which is the best

**************************************************************************/
void decide(void)
{
	PLAYER *p;
	int i;
	char r;
	FACTORSET fs;
	char str[200];
	long int tried = 1;
	FILE *input;

	randomize();
	person[0] = newplayer(0);
	p = person[0];
	p->computer_smarts = 9;


																		// open input file
	input = fopen("tryfac.txt","r");
	if(!input) {
		restext();
		fprintf(stderr,"Error opening tryfac.txt\n");
		exit(0);
	}
																		// pick random piece list
	for(i = 0 ; i < NUMPICS; i++) pieceq[i] = pickpiece(0);
																	 // Clear out high scores
	for(i=0; i < LISTSIZE; i++) memset(&fset[i],0,sizeof(FACTORSET));

																	 // Make room for a grid map to draw
																	 // tetris grids


	while(getfac(input,&fs)) {                   // main loop
		if(fs.rowaverage < 100.0) continue;
																	// show where we are
		sprintf(str,"Try: %ld (%.1lf)   ",tried++,fs.rowaverage);
		drwstring(SET,15,0,str,400,100);
																	// Initialize total game stats
		p->wins = 0;
		p->tscore = 0;
		gy = 0;



																// Lock 'n load
		for(i = 0; i < NUMFACTORS; i++) {
			factor[i] = fs.factor[i];
		}
		p->trows = 0;
		fs.low = 1000;
		fs.high = 0;
		fs.above100 = 0;
		drwfillbox(SET,8,0,maxy,maxx,maxy-200);
		drwline(SET,7,0,maxy-20,maxx,maxy-20);
																	// Do the thinking for this factorset
		for(currentround=0; currentround < NUMROUNDS; currentround++) {
			pp = ((long)currentround*NUMPICS)/(long)NUMROUNDS;
			playerinit(p);              // Init player
			gx = 0;
			gy = 0;

			gene_frame = 0;
			drwline(SET,0,0,300,maxx,300);
			while(gene_gamesegment()) ; // play a round
			p->trows += p->rows;        // Tally score
			if(p->rows > 100) fs.above100++;
			if(p->rows < fs.low) fs.low = p->rows;
			if(p->rows > fs.high) fs.high = p->rows;
																	// Show what happened
			drwfillbox(SET,0,0,0,200,30);
			sprintf(str,"%d] %ld(%ld) - %ld    ",currentround,p->rows,p->trows,fs.above100);
			drwstring(SET,7,0,str,600,50);
			drwpoint(SET,14,currentround*3,maxy-p->rows/5);


			if(kbhit()) {               // Check for user input
				r = getch();
				if(r == 'e') {
					writeall();
					return;
				}
			}
		}

		fs.rowaverage = p->trows/(double)NUMROUNDS;
		if(fileset(&fs)){
																// Show what happened
			for(i = 0; i < LISTSIZE; i++) {
				sprintf(str,"%d] %.2lf (%ld,%ld) -%ld   ",i,fset[i].score,
					fset[i].low,fset[i].high,fset[i].above100);
				drwstring(SET,7,0,str,10,40+i*12);
			}
		}


	}

	fclose(input);
	writeall();
}

/**************************************************************************
	int evolve(void)

	DESCRIPTION:

**************************************************************************/
int evolve(void)
{
	PLAYER *p;
	int i,j;
	char r;
	FACTORSET fs;
	int flag=1;
	char str[200];
	long int tried = 1;
	int mutation;
	double alteration;
	static int tx = 0;

	person[0] = newplayer(0);
	p = person[0];
	p->computer_smarts = 9;

	for(i = 0 ; i < NUMPICS; i++) pieceq[i] = pickpiece(0);
	for(i = 0; i < NUMFACTORS; i++) {
		mfset.factor[i] = (random(32000)-16000)/1000.0;
	}

	for(i = 0; i < 8; i++) drwline(SET,7,0,maxy-1-i*25,maxx,maxy-1-i*25);
																	 // Clear out factorsets
	for(i=0; i < LISTSIZE; i++) memset(&fset[i],0,sizeof(FACTORSET));



	while(flag) {                   // main loop
																	// show where we are
		sprintf(str,"Tried: %ld  ",tried++);

		if(!(tried%GENERATIONS)) {
			writeit();    // WRite to disk!
			for(i = 0 ; i < NUMPICS; i++) pieceq[i] = pickpiece(0);
			for(i = 0; i < NUMFACTORS; i++) {
				mfset.factor[i] = (random(32000)-16000)/1000.0;
			}
																			 // Clear out factorsets
			for(i=0; i < LISTSIZE; i++) memset(&fset[i],0,sizeof(FACTORSET));
		}

		drwstring(SET,15,0,str,400,100);
																	// Initialize total game stats
		p->wins = 0;
		p->tscore = 0;
		gy = 0;

		for(mutation = 0; mutation < MUTATIONS; mutation ++) {
			pp =0;
			sprintf(str,"Mutation: %d/%d  ",mutation,MUTATIONS);
			drwstring(SET,15,0,str,400,115);
																	// Make a copy of master stats
			memcpy(&fs,&mfset,sizeof(FACTORSET));
																	// Mutate
			j = random(5) +1;
			i = random(1000);
			if(i < 50) {                // Randomize all factors?
				for(i = 0; i < NUMFACTORS; i++) {
					fs.factor[i] = (random(32000)-16000)/1000.0;
				}
			}
			else if(i < 300) {         // Randomize some factors?
				for(i = 0; i < j; i++) {
					fs.factor[random(NUMFACTORS)] = (random(32000)-16000)/1000.0;
				}
			}
			else {                      // tweak?
				for(i = 0; i < j; i++) {
					alteration = 1 + (random(4000)-2000)/5000.0;
					fs.factor[random(NUMFACTORS)] *= alteration;
				}

			}
																	// Lock 'n load
			for(i = 0; i < NUMFACTORS; i++) {
				factor[i] = fs.factor[i];
			}
			p->trows = 0;
			fs.low = 1000;
			fs.high = 0;
			fs.above100 = 0;
																		// Do the thinking for this factorset
			for(currentround=0; currentround < NUMROUNDS; currentround++) {
				pp = currentround * 2000;
				playerinit(p);              // Init player
				gx = 0;
				gy = 0;

				gene_frame = 0;
				drwline(SET,0,0,300,maxx,300);
				while(gene_gamesegment()) ; // play a round
				p->trows += p->rows;        // Tally score

				if(p->rows > 100) fs.above100++;
				if(p->rows < fs.low) fs.low = p->rows;
				if(p->rows > fs.high) fs.high = p->rows;


																		// Show what happened
				drwfillbox(SET,0,0,0,200,30);
				sprintf(str,"Rows = %ld(%ld)    ",p->rows,p->trows);
				drwstring(SET,(mutation%7)+8,0,str,200,40+currentround*12);

																		// Throw out bad cases
				if(currentround == 0 && p->trows < 15) currentround = NUMROUNDS;
				if(currentround == 5 && p->trows < 100) currentround = NUMROUNDS;
				if(currentround == 5 &&	p->trows < fset[NUMFACTORS-1].rowaverage*5 ) currentround = NUMROUNDS;
				if(currentround == 10 && p->trows < 250) currentround = NUMROUNDS;

				if(kbhit()) {               // Check for user input
					drwfillbox(SET,random(16),maxx-10,maxy-10,maxx,maxy);
					r = getch();
					if(r == 'q') {            // Quit this mutation sequence
						currentround = NUMROUNDS;
						mutation = 20;
						tried = (int)(tried/GENERATIONS) * GENERATIONS - 1;
					}
					if(r == 'e') {            // Bail out
						currentround=NUMROUNDS;
						mutation = 20;
						flag = 0;
					}
					if(r == 'n') {            // Try a new mutation
						for(i = 0; i < NUMFACTORS; i++) {
							mfset.factor[i] = (random(32000)-16000)/1000.0;
						}

					}
				}
			}

			fs.rowaverage = p->trows/(double)NUMROUNDS;
			if(fileset(&fs)){
																	// Show what happened
				for(i = 0; i < LISTSIZE; i++) {
					sprintf(str,"%d] %.2lf (%ld,%ld) -%ld   ",i,fset[i].score,
						fset[i].low,fset[i].high,fset[i].above100);
					drwstring(SET,7,0,str,10,40+i*12);
				}
			}
		}
		memcpy(&mfset,&fset[0],sizeof(FACTORSET));

	}

	writeit();
	return 0;
}
/**************************************************************************
	void setpiece(int px, int py,PIECE *p,BYTE spot[])

	DESCRIPTION:  special setpiece for this thinking stuff

	INPUTS
		px,py			grid coordinates of the piece
		p					pointer to piece structure
		spot			pointer to grid data array


**************************************************************************/
void setp(int px, int py,PIECE *p,BYTE spot[])
{
	int i,x,y;
	int *coords;

	coords = p->bloc[p->rotation];

	for(i = 0; i < 4; i++) {
		x = coords[i*2] ;
		y = coords[i*2+1] ;
		if(py+y >=0 ) {                      // Only set if the block
																						// is really in the grid.
			spot[(px+x)+(py+y)*grid_width] = YELLOW666;		}
	}

}


/**************************************************************************
	int condensegrid(PLAYER *p)

	DESCRIPTION:  finds filled rows and removes them from the player grid

	returns: number of rows dropped

**************************************************************************/
int condenseg(PLAYER *p)
{
	int i,j,k,tot= 0;


	for(i = 0; i < grid_height; i++) {    // Loop each row to find full rows.

																				// check row for empties.
		for(j = 0; j< grid_width && p->spot[i*grid_width + j]; j++);

		if(j == grid_width) {               //  Full?  Drop it!
			FINISHANIM(p);

			tot++;

																				// drop the blocks logically
			for(j = 0; j < grid_width; j++) {
				for( k = i; k >= 0 ; k--) {
					if(k == 0) p->spot[k*grid_width + j] = 0;
					else p->spot[k*grid_width + j] = p->spot[(k-1)*grid_width + j];
				}
			}
		}
	}


	return tot;
}



/**************************************************************************
	int gene_gamesegment(void)

	DESCRIPTION:  Fast game segment for thinking about stuff

**************************************************************************/
int gene_gamesegment(void)
{
	PLAYER *p;
	int ccount;

																// Check if player 1 is assigned and alive.
																// (Work only with player 1)
	p = person[0];
	if(!p) return 0;

	if(pp > NUMPICS -10) pp = 0;
																		// a little infinite loop prevention
																		// here.
	gene_frame++;
	if(gene_frame > 100 && p->rows == 0 ) p->alive = 0;



	if(p->buffer.type == 255) {   		// Is there a piece in the buffer?
		generatepiece(&(p->buffer),pieceq[pp++]);
	}
																		// Move buffer piece to active spot
	copypiece(&(p->active),&(p->buffer));

																		// Put a new piece in the buffer
	generatepiece(&(p->buffer),pieceq[pp++]);

	p->px = random(4)+1;
	p->py = -2;
																		// collision check. Person dies
																		// if there is one here.
	if(collisioncheck(p->px,p->py, &(p->active),p->spot)) p->alive = 0;
	p->brain.phase = PHASE_NEW;       // Initialize thinking


																		// Think until we have a decision.
	ccount = 0;
	while(p->brain.phase != PHASE_CONCENTRATION && ccount < 10) {
		cogitate(p);
		ccount++;
	}
	drwline(SET,0,0,0,10,0);

	if(ccount >= 100) {
		print(SET,12,400,10,"Cogitation ERROR: %d  ",p->brain.phase);
		sound(1000);
		delay(100);
		nosound();
		//getch();
	}
																		// Rotate and move piece
	for(; p->computer_rotations;p->computer_rotations--) rotatepieceleft(&(p->active));
	p->px = p->computer_translation;
																		// Drop Piece
	p->py++;
	while(!collisioncheck(p->px,p->py, &(p->active),p->spot)) p->py++;
	p->py--;
	setp(p->px,p->py,&(p->active),p->spot);

																		// Condense Grid
	p->rows += condenseg(p);          // Add rows to score
	drwpoint(SET,14,p->rows,300);
	if(p->rows > 1400) {
		p->alive = 0;   // All right already!
		p->rows = 1400;
	}

																		// draw grid with bitmap
/*	if(graphicson) {
		drwfillbox(SET,GRAY0+15,gx,gy,gx+grid_width+1,gy+grid_height+1);
		memcpy(gridmap->data,p->spot,grid_height*grid_width);
		blkput(SET,gx+1,gy+1,gridmap);
		gx += grid_width+1;
		if(gx > 800-grid_width) {
			gx = 0;
			gy += grid_height+2;
			if(gy > 500 - grid_height) gy = 0;
		}
	} */
	return p->alive;
}



