/**************************************************************************
	UTILITY.C


  Random useful code for the game.


**************************************************************************/
#include "tetris.h"


int bgcolor = GRAY0 + 3;
int labelcolor = CYAN666 - BLUEUNIT - GREENUNIT*2;
int valuecolor = CYAN666;

long int scoretable[7] = { 1,7,49,343,2401,16807L,117649L};

/**************************************************************************
	void setscore(PLAYER *p,long int score)

	DESCRIPTION: 	Sets the internal player score struct based on base 7
								numbers plus some encoding.

**************************************************************************/
void setscore(PLAYER *p,long int score)
{
	int i;
	long int n,r;
													// Store the actual score
	r = score;
	for( i = 6; i >= 0; i--) {
		n = r/scoretable[i];
		r = r - n*scoretable[i];
		p->scoreblock[i+2] = (int)n;

	}
													// Add random bits to confuse cheaters
	p->scoreblock[i] += random(10);
	p->scoreblock[i+1] += random(10000);

													// Look for cheating.  The biggest jump in
													// score you can get is 16625. (4 *4 * 1000 + 25 *25)
	if(score	- p->lastscore > 20000L) {
		p->tainted = TRUE;
	}
													// Add some randomness to the last score to
													// make it harder to find.
	p->lastscore = score + random(1000) - 500;
}


/**************************************************************************
	long int getscore(PLAYER *p)

	DESCRIPTION: "decrypts" the real score from the score block

**************************************************************************/
long int getscore(PLAYER *p)
{
	int i;
	long int score = 0;

													// retrive the score
	for( i = 6; i >= 0; i--) {
		score +=  p->scoreblock[i+2]*scoretable[i];
	}

	return score;
}


/**************************************************************************
	void addtoscore(PLAYER *p,long int change)

	DESCRIPTION:	Adds an ammount to the score.

**************************************************************************/
void addtoscore(PLAYER *p,long int change)
{
	long int score;

	score = getscore(p);
	score += change;
	setscore(p,score);
}


/**************************************************************************
	int pickspecial(WORD sgrid[])

  DESCRIPTION:  Picks a special piece.  Only pieces with positive values
  							in sgrid will be picked.

**************************************************************************/
int pickspecial(WORD sgrid[])
{
	int i,p,count=0;

  i = random(100);                          // Check for antidote
  if(i < antedote_probability) return(13);

  i = random(60);               						// pick randomly
  p = random(60)+1;

  while(p) {            										// search for available pieces
  	i++;
    if(i >= 60) i = 0;
    if(sgrid[i]) p--;
    if(count++ > 6000) return(-1);
  }

  sgrid[i] --;                  // decrement counter and go home
  return(i);
}


/**************************************************************************
	void drawblock(int x, int y, PLAYER *p)

  DESCRIPTION:  Basic function for drawing each block in the playing
  						  grid.

**************************************************************************/
void drawblock(int x, int y, PLAYER *p)
{
	int s;

	s = p->spot[y*grid_width + x];

	if(HOSEDWITH(p,FREEZEDRIED)) {
		if(s < 8) {
			s +=7;
			eraseblock(x,y,p);
		}

	}
	else if(HOSEDWITH(p,TRANSPARENTGRIDBLOCKS)) {
		if(s < 8) {
			s = 15;
			eraseblock(x,y,p);
		}
	}

	spriteput(SET,TRANSCOLOR,p->gridx + x*p->bw,p->gridy + y*p->bh,
						shape[s+NORMALBASE]);
}
/**************************************************************************
	void eraseblock(int x, int y, PLAYER *p)

	DESCRIPTION:  Basic function for erasing each block in the playing
  						  grid. Also used to draw the background.

**************************************************************************/
void eraseblock(int x, int y, PLAYER *p)
{

	blkput(SET,p->gridx + x*p->bw,p->gridy + y*p->bh,
  			 bgrnd[p->background]->b[x%2][y%2]);
}


/**************************************************************************
	void drawgrid(PLAYER *p)

  DESCRIPTION: redraws the player grid.

**************************************************************************/
void drawgrid(PLAYER *p)
{
 	int i,j;
                                    // Draw the blocks
  for(i = 0 ; i < grid_width; i ++ ) {
  	for(j = 0; j < grid_height; j++) {
    	if(p->spot[i+j*grid_width]) drawblock(i,j,p);
      else eraseblock(i,j,p);
    }
  }
                                   // Draw the piece
  if(p->active.type != 255) {
  	drawpiece(&p->active,p->gridx + p->px * p->bw,
		                    p->gridy + p->py * p->bh,
												p->bw,p->bh,p->gridy);
  }

	if(HOSEDWITH(p,PSYCHO))
	drwfillbox(XOR,random(256),p->gridx,p->gridy,
			p->gridx+grid_width*p->bw,p->gridy+grid_height*p->bh);


}


/**************************************************************************
	void rotatepieceright(PIECE *p)

  DESCRIPTION: rotates a tetris piece to the right

**************************************************************************/
void rotatepieceright(PIECE *p)
{
	p->rotation++;
	if(p->rotation >= 4) p->rotation = 0;

}
/**************************************************************************
	void rotatepieceleft(PIECE *p)

  DESCRIPTION: rotates a tetris piece to the left

**************************************************************************/
void rotatepieceleft(PIECE *p)
{
	p->rotation--;
	if(p->rotation <0 || p->rotation >4) p->rotation = 3;

}


/**************************************************************************
	void erasepiece(PIECE *p,int x, int y, int w, int h,int top)

  DESCRIPTION: Erases a tetris piece at the specified spot on the screen

  INPUT:
  	p			Data for the piece we want to draw.  A piece is divided up
          into 25 blocks in a 5x5 grid.
    x,y		upper left corner of piece data area
    gx,gy player grid upper left of piece
    w,h   dimensions of a single block.
    top   logical top og the playing grid (used for clipping)



**************************************************************************/
void erasepiece(PIECE *p,int x, int y,int gx,int gy, int w, int h,int top,int background)
{
	int i,xx,yy,bx,by;
	RasterBlock far *drawme;
	int *coords;

	coords = p->bloc[p->rotation];

	if(background >= 0) drawme = shape[background];


	for(i = 0; i < 4; i++) {
			bx = coords[i*2];
			by = coords[i*2+1];
			xx = x+ bx * w;
			yy = y+ by * h;
			if(background < 0)
				drawme = bgrnd[(-background)-1]->b[(gx+bx)%2][(gy+by)%2];
			if(yy >= top) blkput(SET,xx,yy,drawme);
	}

	p->visible = 0;
}
/**************************************************************************
	void drawpiece(PIECE *p,int x, int y, int w, int h,int top)

  DESCRIPTION: Draws a tetris piece at the specified spot on the screen

  INPUT:
  	p			Data for the piece we want to draw.  A piece is divided up
          into 25 blocks in a 5x5 grid.
    x,y		upper left corner of piece data area
    w,h   dimensions of a single block.
    top   logical top of the grid. (used for clipping)



**************************************************************************/
void drawpiece(PIECE *p,int x, int y, int w, int h,int top)
{
 	int i,xx,yy;
	int *coords;

	coords = p->bloc[p->rotation];

	for(i = 0; i < 4; i++) {
		xx = x+ coords[i*2] * w;
		yy = y+ coords[i*2+1] * h;
		if(yy>=top) blkput(SET,xx,yy,shape[p->type+NORMALBASE]);
  }

	p->visible = 1;
}



/**************************************************************************
	void copypiece(PIECE *p1, PIECE *p2)

  DESCRIPTION:  Copies the contents of piece2 to piece1


**************************************************************************/
void copypiece(PIECE *p1, PIECE *p2)
{
	memcpy(p1,p2,sizeof(PIECE));


}



/**************************************************************************
	void generatepiece(PIECE *p, BYTE pnum)

	DESCRIPTION:  Fills a piece array with the specified piece

**************************************************************************/
void generatepiece(PIECE *p, BYTE pnum)
{
	int rot,i;

	for(rot = 0; rot < 4; rot++) {
		for(i = 0; i < 8; i++) p->bloc[rot][i] = piecedata[pnum][rot][i];
	}
	p->rotation = 0;
  p->type = pnum;											// Set the piece type for the
  																		// Rotation functions
	p->visible = 0;
}

/********************************************************************
	void drawbox(x1,y1,x2,y2,bw,hc,sc,bc)

	DESCRIPTION:  This draws a generic pyramid-type grey rectangle

********************************************************************/
void drawbox(int x1,int y1,int x2,int y2,int bw,int hc, int sc, int bc)
{
	int i;

	drwfillbox(SET,bc,x1,y1,x2,y2); 	// blank the window

	for(i=0; i< bw; i++) {           // loop through border thickness
		drwline(SET,sc,x1+i,y2-i,x2-i,y2-i);  // right side
		drwline(SET,sc,x2-i,y2-i,x2-i,y1+i);  // bottom

		drwline(SET,hc,x1+i,y2-i,x1+i,y1+i);  // left side
		drwline(SET,hc,x1+i,y1+i,x2-i,y1+i);  // top
	}
}

/********************************************************************
	void drawpit(x1,y1,x2,y2,bw,hc,sc,bc)

	DESCRIPTION:  This draws a generic pyramid-type(sunken) grey rectangle

********************************************************************/
void drawpit(int x1,int y1,int x2,int y2,int bw,int hc, int sc, int bc)
{
	int i;

	drwfillbox(SET,bc,x1,y1,x2,y2); // blank the window

	for(i=0; i< bw; i++) {           // loop through border thickness

		drwline(SET,hc,x1+i,y2-i,x2-i,y2-i);  // right side
		drwline(SET,hc,x2-i,y2-i,x2-i,y1+i);  // bottom

		drwline(SET,sc,x1+i,y2-i,x1+i,y1+i);  // left side
		drwline(SET,sc,x1+i,y1+i,x2-i,y1+i);  // top
	}
}




/**************************************************************************
	void prepgrids(void)

  DESCRIPTION:  Prepares the screen for play

**************************************************************************/
void prepgrids(void)
{
	int i,x,y,w,h,bw,bh,tw;

	palioauto(palette,0,255,-10);   // fade to black

	fillscreen(0);                 // blank screen

	for(i = 0; i < MAXPLAYERS; i++) {
  	if(person[i] && person[i]->alive) {
                                 // Set up variables for convenience
			x = person[i]->gridx;
      y = person[i]->gridy;
      bw = person[i]->bw;
      bh = person[i]->bh;
      w = bw*grid_width;
      h = bh*grid_height;
                                 // draw playing field
			drawbox(x-4,y-4,x+w+4,y+h+4,3,228,218,227);
			drawgrid(person[i]);
																 // Draw status frame
			drawbox(x-4,y+h+5,x+w+4,maxy-(maxy-600)/2,3,228,218,bgcolor);
																 // Future piece box
			drawpit(x+5,y+h+58,x+85,y+h+145,2,228,218,216);
																 // Timer
			drawpit(x+90,y+h+120,x+189,y+h+142,2,228,218,216);

																 // Labels   ======================
			tw= textwidth(person[i]->name)/2;
			print(SET,YELLOW666 - GREENUNIT*2 - REDUNIT *2,x+100 - tw + 1,
							y+h+11 + 1,person[i]->name );
			print(SET,YELLOW666 - GREENUNIT*1 - REDUNIT *1,x+100 - tw,
							y+h+11,person[i]->name);

																// Set off teh name with cool boxes
			drawpit(x+5    ,y+h+15,x+100 - tw - 5    ,y+h+25,1,230,219,
				YELLOW666 - GREENUNIT*3 - REDUNIT *3);
			drawpit(x+103 + tw,y+h+15,x+190,y+h+25,1,230,219,
				YELLOW666 - GREENUNIT*3 - REDUNIT *3);

			print(SET,labelcolor,x+9,y+h+128,"Next");
			print(SET,labelcolor,x+5,y+h+33,"Victim:");
			print(SET,labelcolor,x+90,y+h+55," Rows");
			print(SET,labelcolor,x+90,y+h+70,"Score");

			dostats(person[i]);
    }
	}

	palioauto(palette,0,255,8);

}



/**************************************************************************
	void setanddrawpiece(PIECE *pc,PLAYER *p)

  DESCRIPTION:  Sets the active piece permanently in the player grid and
  							draws the new blocks

  INPUTS
		pc				pointer to piece structure
		p					pointer to player structure


**************************************************************************/
void setanddrawpiece(PIECE *pc,PLAYER *p)
{
 	int i,x,y;
	int *coords;

	coords = pc->bloc[pc->rotation];

	for(i = 0; i < 4; i++) {
		x = coords[i*2] ;
		y = coords[i*2+1] ;
		if(p->py+y >=0 ) {                      // Only set if the block
																						// is really in the grid.
			p->spot[(p->px+x)+(p->py+y)*grid_width] = pc->type;
			drawblock(p->px+x,p->py+y,p);
		}
	}

}
/**************************************************************************
	void setpiece(int px, int py,PIECE *p,BYTE spot[])

	DESCRIPTION:  Sets the active piece permanently in the player grid

	INPUTS
		px,py			grid coordinates of the piece
		p					pointer to piece structure
		spot			pointer to grid data array


**************************************************************************/
void setpiece(int px, int py,PIECE *p,BYTE spot[])
{
	int i,x,y;
	int *coords;

	coords = p->bloc[p->rotation];

	for(i = 0; i < 4; i++) {
		x = coords[i*2] ;
		y = coords[i*2+1] ;
		if(py+y >=0 ) {                      // Only set if the block
																						// is really in the grid.
			spot[(px+x)+(py+y)*grid_width] = p->type;		}
	}


}

/**************************************************************************
	int collisioncheck(int px, int py,PIECE *p,BYTE spot[])

  DESCRIPTION:  Detects to see if active piece is in a legal position

  INPUTS
  	px,py			grid coordinates of the piece
		p					pointer to piece structure
		spot			pointer to grid data array

**************************************************************************/
int collisioncheck(int px, int py,PIECE *p,BYTE spot[])
{
 	int i,x,y;
	int *coords;

	coords = p->bloc[p->rotation];

	for(i = 0; i < 4; i++) {
		x = coords[i*2] ;
		y = coords[i*2+1] ;
		if(px+x < 0) return(TRUE);            // off left edge?
		if(px+x >= grid_width) return(TRUE);  // off right edge?
		if(py+y >= grid_height) return(TRUE); // off bottom?
                                            // Is it on the grid and
																						// a block already there?
		if(py+y >= 0 && spot[(px+x)+(py+y)*grid_width]) return(TRUE);
  }

	return FALSE;
}



/**************************************************************************
	int pickpiece(int p)

  DESCRIPTION:  Picks a piece randomly based on appearance stats

  INPUTS:

		p = playernum

**************************************************************************/
int pickpiece(int p)
{
	int i,total,num;
	static int last_pick[16]  = {2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2};

                                       // Check the probability that the
                                       // last piece will be repeated.
	if(random(100) < repeatprob[last_pick[p]]) {
		return last_pick[p];
  }
                                       // Initialize for a fully random pick
  total = 0;
  for(i = 0; i < 8; i++) total+=pprob[i];

  num = random(total)+1;

  total = 0;
                                       // Perform a cumulative probability
                                       // random pick.
  for(i =1; i< 8; i++) {
  	if(total + pprob[i] >= num) {
    	last_pick[p] = i;
      return(i);
    }
    total += pprob[i];
  }

  return(7);                           // default piece just in case
																			 // things fail.
}

/**************************************************************************
	void dostats(PLAYER *p)

	DESCRIPTION:  updates the statistics window during game play

**************************************************************************/
void dostats(PLAYER *p)
{
	int x,y,h,bh;
	//int bw;
	char string[80];

	if(!p) return;             // No null players!

														 // Set up variables for convenience
	x = p->gridx;
	y = p->gridy;
//  bw = p->bw;
	bh = p->bh;
	h = bh*grid_height;
														 // Update player statistics
																															 // enemy
	if(p->enemy) sprintf(string,"%s              ",p->enemy->name);
	else sprintf(string,"[*NOBODY*]              ",p->enemy->name);
	string[15] = 0;
	drwstring(SET,valuecolor,bgcolor,string,x+65,y+h+35);

	sprintf(string,"%ld              ",p->rows);                // rows cleared
	string[7] = 0;
	drwstring(SET,valuecolor,bgcolor,string,x+135,y+h+57);

	sprintf(string,"%ld                ",getscore(p));             // score
	string[7] = 0;
	drwstring(SET,valuecolor,bgcolor,string,x+135,y+h+72);


}


/**************************************************************************
	int countbits(DWORD num)

	DESCRIPTION: Returns the number of set bits in a number

**************************************************************************/
int countbits(DWORD num)
{
	int total=0;

	while(num) {
		if(num &0x01) total++;
		num >>= 1;
	}
	return total;
}