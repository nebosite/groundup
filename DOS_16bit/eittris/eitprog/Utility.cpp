//	UTILITY.C
//  Random useful code for the game.
// Varmint's EITTRIS
// Copyright (C) 1996-2000, Purple Planet Software

#include "stdafx.h"
#include "eittris.h"

								// These colors are set in SetDrawHandle()
int bgcolor;
int labelcolor;
int valuecolor;

int scoretable[7] = { 1,7,49,343,2401,16807L,117649L};

/*===========================================================================
	int random(int max)

	DESCRIPTION:	Random number convenience function

	  REVISIONS:
			12/4/99		Eric Jorgensen		Initial Version

============================================================================*/
int random(int max)
{
	return rand() % max;
}

/**************************************************************************
	void setscore(PLAYER *p,int score)

	DESCRIPTION: 	Sets the internal player score struct based on base 7
								numbers plus some encoding.

**************************************************************************/
void setscore(PLAYER *p,int score)
{
	int i;
	int n,r;
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
	int getscore(PLAYER *p)

	DESCRIPTION: "decrypts" the real score from the score block

**************************************************************************/
int getscore(PLAYER *p)
{
	int i;
	int score = 0;

													// retrive the score
	for( i = 6; i >= 0; i--) {
		score +=  p->scoreblock[i+2]*scoretable[i];
	}

	return score;
}


/**************************************************************************
	void addtoscore(PLAYER *p,int change)

	DESCRIPTION:	Adds an ammount to the score.

**************************************************************************/
void addtoscore(PLAYER *p,int change)
{
	int score;

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

	g_lpdvdrawobject->SpritePut(p->gridx + x*p->bw,p->gridy + y*p->bh,
		0,shape[s+NORMALBASE]);
}
/**************************************************************************
	void eraseblock(int x, int y, PLAYER *p)

	DESCRIPTION:  Basic function for erasing each block in the playing
  						  grid. Also used to draw the background.

**************************************************************************/
void eraseblock(int x, int y, PLAYER *p)
{

	g_lpdvdrawobject->SpritePut(p->gridx + x*p->bw,p->gridy + y*p->bh,
		0,bgrnd[p->background]->b[x%2][y%2]);
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
		dopsycho(random(256),p->gridx,p->gridy,
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
	DVSPRITE *drawme;
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
		if(yy >= top) g_lpdvdrawobject->SpritePut(xx,yy,0,drawme);
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
		if(yy>=top) g_lpdvdrawobject->SpritePut(xx,yy,0,shape[p->type+NORMALBASE]);
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
	p->type = pnum;						// Set the piece type for the
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

	g_lpdvdrawobject->DrawFillRectangle(bc,x1,y1,x2,y2); 	// blank the window

	for(i=0; i< bw; i++) {           // loop through border thickness
		g_lpdvdrawobject->DrawLine(sc,x1+i,y2-i,x2-i,y2-i);  // right side
		g_lpdvdrawobject->DrawLine(sc,x2-i,y2-i,x2-i,y1+i);  // bottom

		g_lpdvdrawobject->DrawLine(hc,x1+i,y2-i,x1+i,y1+i);  // left side
		g_lpdvdrawobject->DrawLine(hc,x1+i,y1+i,x2-i,y1+i);  // top
	}
}

/********************************************************************
	void drawpit(x1,y1,x2,y2,bw,hc,sc,bc)

	DESCRIPTION:  This draws a generic pyramid-type(sunken) grey rectangle

********************************************************************/
void drawpit(int x1,int y1,int x2,int y2,int bw,int hc, int sc, int bc)
{
	int i;

	g_lpdvdrawobject->DrawFillRectangle(bc,x1,y1,x2,y2); // blank the window

	for(i=0; i< bw; i++) {           // loop through border thickness

		g_lpdvdrawobject->DrawLine(hc,x1+i,y2-i,x2-i,y2-i);  // right side
		g_lpdvdrawobject->DrawLine(hc,x2-i,y2-i,x2-i,y1+i);  // bottom

		g_lpdvdrawobject->DrawLine(sc,x1+i,y2-i,x1+i,y1+i);  // left side
		g_lpdvdrawobject->DrawLine(sc,x1+i,y1+i,x2-i,y1+i);  // top
	}
}




/**************************************************************************
	void prepgrids(void)

  DESCRIPTION:  Prepares the screen for play

**************************************************************************/
void prepgrids(void)
{
	int i,x,y,w,h,bw,bh,tw;

	g_lpdvdrawobject->Clear(0);                 // blank screen

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
			drawbox(x-4,y-4,x+w+4,y+h+4,3,col_Gray[14],col_Gray[4],col_Gray[11]);
			drawgrid(person[i]);
			// Draw status frame
			drawbox(x-4,y+h+5,x+w+4,maxy-(maxy-600)/2,3,col_Gray[12],col_Gray[4],bgcolor);
			// Future piece box
			drawpit(x+5,y+h+58,x+85,y+h+145,2,col_Gray[14],col_Gray[4],col_Gray[0]);
			// Timer
			drawpit(x+90,y+h+120,x+189,y+h+142,2,col_Gray[14],col_Gray[4],col_Gray[0]);

			// Labels   ======================
			tw= g_lpdvdrawobject->GetTextWidth(person[i]->name)/2;
			g_lpdvdrawobject->Print(col(200,200,0),x+100 - tw + 1, y+h+11 + 1,person[i]->name );
			g_lpdvdrawobject->Print(col(200,200,0),x+100 - tw + 1, y+h+11,person[i]->name );
			g_lpdvdrawobject->Print(col(200,200,0),x+100 - tw, y+h+11 + 1,person[i]->name );
			g_lpdvdrawobject->Print(col(col_Gray[14],col_Gray[14],0),x+100 - tw, y+h+11,person[i]->name);

			// Set off the name with cool boxes
			drawpit(x+5    ,y+h+15,x+100 - tw - 5    ,y+h+25,1,col_Gray[14],col_Gray[3],col(150,150,0));
			drawpit(x+103 + tw,y+h+15,x+190,y+h+25,1,col_Gray[14],col_Gray[3],col(150,150,0));

			g_lpdvdrawobject->Print(labelcolor,x+9,y+h+128,"Next");
			g_lpdvdrawobject->Print(labelcolor,x+5,y+h+33,"Victim:");
			g_lpdvdrawobject->Print(labelcolor,x+90,y+h+55," Rows");
			g_lpdvdrawobject->Print(labelcolor,x+90,y+h+70,"Score");

			dostats(person[i]);
		}
	}

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
		if(py+y >=0 ) {                 // Only set if the block
										// is really in the grid.
			spot[(px+x)+(py+y)*grid_width] = p->type;		
		}
	}
}

/*===========================================================================
	void dopsycho(DWORD color,int x1,int y1,int x2,int y2)

	DESCRIPTION:	XOR's the area with the specified color

	  REVISIONS:
			12/25/99		Eric Jorgensen		Initial Version

============================================================================*/
void dopsycho(DWORD color,int x1,int y1,int x2,int y2)
{
	DWORD xorc,*dwdata,*endspot;
	int temp,size,i;
	DVSPRITE *xorme;

								// make sure coords are in the right order
	if(x1 > x2) {
		temp = x2;
		x2 = x1;
		x1 = temp;
	}
	if(y1 > y2) {
		temp = y2;
		y2 = y1;
		y1 = temp;
	}
								// Get the sprite from the screen  and
								// prepare data.
	xorme = g_lpdvdrawobject->SpriteGet(NULL,x1,y1,x2,y2);
	if(!xorme) return;

	xorc = color + (color << 16);
	dwdata = (DWORD *)xorme->GetPointer();
	size = (y2-y1) * xorme->m_iPitch/2;

								// Xor the whole thing.
	if(dwdata) {
		for(endspot = dwdata+size; dwdata < endspot; dwdata++) {
			*dwdata ^= xorc;
		}
	}
	xorme->ReleasePointer();
	

								// Put the sprite back
	g_lpdvdrawobject->SpritePut(x1,y1,0,xorme);
	delete xorme;
  
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

	return(7);              // default piece just in case
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
	g_lpdvdrawobject->DrawFillRectangle(bgcolor,x+65,y+h+35,x+65+100,y+h+35+16);
	g_lpdvdrawobject->Print(x+65,y+h+35,string);

	sprintf(string,"%ld              ",p->rows);                // rows cleared
	string[7] = 0;
	g_lpdvdrawobject->DrawFillRectangle(bgcolor,x+135,y+h+57,x+135+55,y+h+57+14);
	g_lpdvdrawobject->Print(x+135,y+h+57,string);

	sprintf(string,"%ld                ",getscore(p));             // score
	string[7] = 0;
	g_lpdvdrawobject->DrawFillRectangle(bgcolor,x+135,y+h+72,x+135+55,y+h+72+14);
	g_lpdvdrawobject->Print(x+135,y+h+72,string);


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


/*************************************************************************
	inkey();

	DESCRIPTION: Works like the BASIC function inkey$. It returns the top
							 character in the keyboard buffer, and NULL if the buffer
							 is empty.

**************************************************************************/
char inkey(void)
{
	g_lpdvinputobject->Refresh(DVINPUT_KEYBOARD);
	if(g_lpdvinputobject->KeyHit()) {
		return(g_lpdvinputobject->GetKey());
	}
	else return 0;
}

/**************************************************************************
	getinput(x,y,fc,bc,prompt,string,maxlength);

	DESCRIPTION: This gets string input from the user. This function
							 fills the variable 'string' with text information.
							 If string already has text information in it, getinput()
							 will use it.

	fc,bc = 		foregroundcolor, backgroundcolor
  *prompt = Text to prompt the user
  *string = Output buffer.  Should already containa default value
  maxlength = maxiumum length of input

**************************************************************************/
void getinput(int x,int y,int fc,int bc,
			char *prompt,char *string,int maxlength)
{
	int w,h,wx,wy,c,flag,dd=0,color;
	char buffer[255],minibuff[2];
	int r;
	int timeout = 0;
	int cx;

	minibuff[1] = 0;                      // clear small string buffer

	w = g_lpdvdrawobject->GetTextWidth("a");
	h = g_lpdvdrawobject->GetTextHeight();
	wx = x+g_lpdvdrawobject->GetTextWidth(prompt)+2;          		// get location if leftmost input char
	wy = y;
	cx = wx;

	sprintf(buffer,"%s%s",prompt,string);
	g_lpdvdrawobject->Print(fc,x,y,buffer);        // display prompt and default string

	strcpy(buffer,string);     							// copy string for editing */

	c = strlen(buffer);
	flag = 1;

	while(flag) {                          	// ANIMATED STRING EDITOR LOOP
		if(dd > 100) color = fc;       	 		 	// Blink cursor
		else color = bc;                      // draw cursor
		g_lpdvdrawobject->DrawFillRectangle(color,cx, wy, cx+w, wy+h);

		Sleep(10);                        		// control blink rate
		dd += 5;
		if(dd > 199) dd = 0;

		r = inkey();
		if(r) {                      					// look for a key stroke
			if( r >= ' ' && c < maxlength) {           	// If r is a regular alpha-numeric
				// character, add it to the name
				// string.
				buffer[c] = r;
				// move the cursor
				g_lpdvdrawobject->DrawFillRectangle(bc,cx, wy, cx+w, wy+h);   // erase cursor
				g_lpdvdrawobject->DrawFillRectangle(bc,wx,wy,cx+w,wy+h); 		 // erase string
				buffer[c+1] = 0;              		// extend string terminator
				g_lpdvdrawobject->Print(fc,wx,wy,buffer);  		// draw the new string
				cx += g_lpdvdrawobject->GetTextWidth(buffer+c);
				c++;                      				// move cursor index

			}
			else if(r == 13) flag = 0;    			// return = finished
			else if( r == 8 && c) {             			// backspace
				g_lpdvdrawobject->DrawFillRectangle(bc,cx, wy, cx+w, wy+h);  // erase cursor
				g_lpdvdrawobject->DrawFillRectangle(bc,wx,wy,cx+w,wy+h);  // erase string
				c--;                      				// move string index
				cx -= g_lpdvdrawobject->GetTextWidth(buffer+c);
				if(c < 0) c = 0;          				// don't go off te end!
				buffer[c] = 0;            				// move back string terminator
				g_lpdvdrawobject->Print(fc,wx,wy,buffer); 		// draw the new string
			}
			else if(r == 27)	{									// escape key
				flag = 0;                         // end loop
				buffer[0] = 0;                    // clear input string
			}
		}
	}
	strcpy(string,buffer);                  // store new string
	*(string+maxlength) = 0;                // make sure string is of this length
}

/*** FUNCTION HEADER *********************************************************
	void debugf(char *szFormat, ...)
* 
*   DESCRIPTION:	Convenience function for logging output.
*
* [REVISIONS]
*		5/14/98		Eric Jorgensen		InitialVersion
*
\******************************************************************************/
void debugf(char *szFormat, ...)
{
	va_list		ap;
	char		szMessage[4096] = {""};

								// See if output is turned on
	if(!eitdebugfile) return;
								// Build the output string
	va_start(ap, szFormat);						// Init Variable argument list
	vsprintf(szMessage, szFormat, ap);// Create the output string
	va_end(ap);									// Close up argument list
	
								// Dumpt the string.
	strcat(szMessage,"\n");
	fprintf(eitdebugfile,"%s",szMessage);
	fflush(eitdebugfile);
}

/*===========================================================================
	bool eitkbhit()

	DESCRIPTION:	Works like old dos eitkbhit

	  REVISIONS:
			12/4/99		Eric Jorgensen		Initial Version

============================================================================*/
bool eitkbhit()
{
	g_lpdvinputobject->Refresh(DVINPUT_KEYBOARD);
	return g_lpdvinputobject->KeyHit() ? true : false;
}

/*===========================================================================
	int egetch()

	DESCRIPTION:	Works like old DOS getch();

	  REVISIONS:
			12/4/99		Eric Jorgensen		Initial Version

============================================================================*/
int egetch()
{
	g_lpdvinputobject->Refresh(DVINPUT_KEYBOARD);
	while(!g_lpdvinputobject->KeyHit()) {
		g_lpdvinputobject->Refresh(DVINPUT_KEYBOARD);
	}
	return 	g_lpdvinputobject->GetKey();
}

/*===========================================================================
	int getscancode()

	DESCRIPTION:

	  REVISIONS:
			12/4/99		Eric Jorgensen		Initial Version

============================================================================*/
int getscancode()
{
//	g_lpdvinputobject->FlushKeyboard();
	g_lpdvinputobject->Refresh(DVINPUT_KEYBOARD);
	while(!g_lpdvinputobject->ScanKeyHit()) {
		g_lpdvinputobject->Refresh(DVINPUT_KEYBOARD);
	}
	return 	g_lpdvinputobject->GetScanCode();
}

/*===========================================================================
	bool scankeyhit()

	DESCRIPTION:	Checks for scan keysstrokes

	  REVISIONS:
			12/6/99		Eric Jorgensen		Initial Version

============================================================================*/
bool scankeyhit()
{
	g_lpdvinputobject->Refresh(DVINPUT_KEYBOARD);
	return g_lpdvinputobject->ScanKeyHit() ? true : false;
}

