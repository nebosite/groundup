/**************************************************************************
	COMPUTER.C


	Code for computer intelligence in Varmint's Eittris.


**************************************************************************/
#include "tetris.h"

#define MOVEERR -1000
#define MOVEPICK 2
#define BESTX 3

int countvoids(BYTE g[]);
int countdensity(BYTE g[]);
int condenseminigrid(BYTE spot[],int preserve);
int countblocks(BYTE spot[]);
void unsetpiece(int px, int py,PIECE *p,BYTE spot[]);
double trymove(void);
void thinkharder(void);
int csetpiece(int px, int py,PIECE *p,BYTE spot[]);
void advance(void);


																		// Local Globals
int x_empty=0,x_height=0,x_row=0,x_special=0,x_piece=0,x_px = 0;
int fastflag = 0;
THINK *t;
PLAYER *p;
double factor[15]= {
-3.912000   ,
9.026000    ,
-1.110252   ,
2.678196    ,
-14.728000  ,
-7.673000   ,
7.355270    ,
-13.078746  ,
2.849000    ,
1.270000    ,
-19.997882  ,
5.615556    ,
-12.499000  ,
10.999000   ,
-9.241104
};


ispeedgrid[10][2] = {								// Intelligence speed Grid
	{20,1},
	{12,1},
	{8,1},
	{6,1},
	{4,1},
	{2,1},
	{1,1},
	{1,4},
	{1,8},
	{1,16}
	};

int maxrotations[8] = {0,1,1,1,3,3,3,0};




/**************************************************************************
	int resolve(void)

	DESCRIPTION:  Handles move scoring.

**************************************************************************/
void resolve(void)
{
	double score;


	if(t->phase == PHASE_CONCENTRATION) {

		if(!p->computer_inposition) {
			return;
		}
																 // To add "humanity" to the intelligence,
																 // This piece of code adds random error
																 // the piece movement.
		if(p->computer_inposition == 1) {
																 // set this value to two so we don't
																 // keep trying to add random errors.
			p->computer_inposition = 2;
																			 // check accuracy
			if(random(1000)> p->computer_accuracy) {
				switch(random(2)) {
					case 0:
						p->computer_translation++;
						break;
					case 1:
						p->computer_translation--;
						break;
				}
				t->bestmovex = p->computer_translation;
			}
		}

		t->gx = t->bestmovex;   // Make sure move errors are noted.
		t->grot = 0;            // no more toations
	}

	score = trymove();



														// If we are concentrating, we want to look
														// for grid changes.
	if(t->phase == PHASE_CONCENTRATION) {
		t->movespecial = x_special;

														// MOVEERR means that this is the first
														// thought cycle during the concentration phase.
		if(t->cscore == MOVEERR) {
														// Definately want to start over if we arn't
														// clearing the same number of rows.
			if(t->rowscleared != x_row) {
				t->phase = PHASE_NEW;
				return;
			}
														// Keep our score for tracking.
			t->cscore = score;
			thinkharder();
		}
														// If score changes, the grid must have changed.
		if(score != t->cscore ) t->phase = PHASE_NEW;
														// We always want to think more about specials.
		if(x_special) {
			thinkharder();
		}
														// Smart computers don't always move as fast as
														// they can.
		if(p->py > grid_height/3 + (10 - p->computer_smarts))
			if(p->computer_droptime > 2) p->computer_droptime = 2;
		return;
	}

																		 // check local score
	if(score > t->bestmovescore) {
		t->bestmoverot=t->grot;
		t->bestmovex=t->gx;
		t->bestmovescore = score;
		t->bestmovelow=x_height;
		p->computer_rotations = t->bestmoverot;
		p->computer_translation = t->bestmovex;
		p->computer_inposition = FALSE;
		t->cscore = MOVEERR;
		t->rowscleared = x_row;
		t->movespecial = x_special;
	}

	return;
}


/**************************************************************************
	void advance(int score)

	DESCRIPTION:

**************************************************************************/
void advance(void)
{
																// If we are concentrating, then we
																// aren't moving the piece any more.
	if(t->phase == PHASE_CONCENTRATION) return;


	else if(t->phase == PHASE_QUICK) {
		t->gx++;                         // advance horistontal position

																// If we reach the edge, we need to
																// advance rotation.  If we are done
																// with the rotations, then we just
																// give up and use the first move.
		if(t->gx >= grid_width-2) {
			t->gx = -2;
			t->grot ++;

			if(t->grot > maxrotations[(p->active).type]) {
				t->phase = PHASE_CONCENTRATION;
				thinkharder();

				t->gx = -2;
				t->grot = 0;
			}
		}
	}

}


/**************************************************************************
	void thinkinit(void)

	DESCRIPTION:

**************************************************************************/
void thinkinit(void)
{
	int i,pl=-1,lowest=1000,num=-1;


																			 // Initialize thinking
	t->phase=PHASE_QUICK;
																			 // Set speed of thought
	t->ticksperturn = ispeedgrid[p->computer_smarts][0];
	t->thinksperturn= ispeedgrid[p->computer_smarts][1];
	t->thinktick = t->ticksperturn;
																			 // Start out test locations
	t->gx = -2;
	t->grot=0;
																			 // Initialize best moves

	t->bestmovex = random(10);
	t->bestmoverot = random(4);
	t->bestmovescore = MOVEERR;
	t->bestmovelow = MOVEERR;
	t->rowscleared = 0;

	t->empties = countvoids(p->spot);    // Count the number of "voids" in
																				 // The original grid.

	p->computer_droptime = 10000;
	p->computer_inposition = 0;
																			 // Did we just hose someone?  We
																			 // might want to pick a new enemy.
	if(p->computer_justhosed == 2 &&
		 p->computer_smarts > 4 ) {
																			 // Find best-off player
		for(i = 0; i < MAXPLAYERS && person[i] && person[i] != p && person[i]->alive; i++) {
			num = countblocks(person[i]->spot);
			if(num < lowest) {
				lowest = num;
				pl = i;
			}
		}

		if(pl > -1) p->enemy = person[pl];
	}

	p->computer_justhosed = 0;
}



/**************************************************************************
	void thinkharder(void)

	DESCRIPTION:  Processes some of the more esoteric thinking that happens
								when a move is picked.  This finction is called after the
								regular move logic is finished.

**************************************************************************/
void thinkharder()
{
	int dropnow=0;
	int olddrop;
																			// preliminary stuff

	olddrop = p->computer_droptime;     // Hold on to old droptime to
																			// prevent computer from reseting it.

																			// Mark that the computer is
																			// clearing aspecial with this drop
	if(t->movespecial) p->computer_justhosed = 1;


																			// standard computer drop
	p->computer_droptime = 10;



																			// If you are a really smart player,
																			// and you are going to clear a
																			// row on this move, make sure you
																			// wait for a special...
	if(p->computer_smarts > 7 && t->rowscleared && !t->movespecial)
		 p->computer_droptime = 1000;

																			// Are we highup?  Drop the piece
																			// quickly if we are not clearing a row.
	if(t->bestmovelow < grid_height/2 && !t->rowscleared) dropnow = TRUE;

																			// Are we way high up? drop now!
	if(t->bestmovelow < grid_height/3) dropnow = TRUE;



																			// special? Drop now!
																			// (Unless you are dumb)
	if(p->computer_smarts > 3 && t->movespecial) dropnow = TRUE;

																			// Check for a TETRIS
	if(t->rowscleared == 4) dropnow = TRUE;

																			// Donator?
	if(p->computer_smarts > 2 && p->timer[0]) dropnow = TRUE;

																			// Last player? Why wait?
	if(p->win) dropnow = TRUE;


	if(dropnow) p->computer_droptime = 2;

																			// If you have a switch screen
																			// special, don't switch if
																			// the other guy has a worse screen.
	if(p->computer_smarts > 3 &&  t->movespecial == SPECIALBASE +6) {
		if(countblocks(p->enemy->spot) - countblocks(p->spot) > 0) {
			olddrop = p->computer_droptime = 1000;
		}
	}

																			// Don't interrupt a drop
																			// in Progress.
	if(olddrop < p->computer_droptime) p->computer_droptime = olddrop;


}


/**************************************************************************
	void drwgrid(void)

	DESCRIPTION:  debugging code

**************************************************************************/
/*void drwgrid(void)
{
	int x,y,s,scale=4,yoff;

	yoff = maxy-grid_height*scale-1;
	drwfillbox(SET,0,p->gridx,yoff,p->gridx + scale * grid_width,maxy);
	s = 0;
	for(y = 0; y < grid_height; y++) {
		for(x = 0;x < grid_width; x++) {
			if(*(t->grid+s))
				drwfillbox(SET,YELLOW666,
					x*scale+p->gridx,
					y*scale+yoff,
					x*scale+p->gridx+scale-2,
					y*scale+yoff + scale-2);
			s++;
		}
	}



}  */

/**************************************************************************
	void cogitate(PLAYER *p)

	DESCRIPTION:  Dynamic computer player intelligence (DCPI)

								Criteria for best move:

									1) lowness      	(tie breaker)
									2) rows cleared   (+10 points per row)
									3) empty spaces generated (-2 pt per space)
									4) impossible  (MOVEERR points)
									5) specials +500 points (-50 for bad screen switch)
									6) height -5 points per row



**************************************************************************/
void cogitate(PLAYER *plyr)
{
	int i;

	if(!plyr) {
		print(SET,13,10,10,"Yikes!");
		return;
	}

	p = plyr;
	t = &(p->brain);

	if(t->phase == PHASE_NEW) {               // New thought!
		thinkinit();
	}
																				 // handle "think clock"
	t->thinktick--;
	if(t->thinktick > 0) {
		return;
	}
	t->thinktick = t->ticksperturn;

																				 // Think some...
	for(i = 0; i < t->thinksperturn; i++) {
		resolve();                   				// Resolve this grid
		advance();                      	   // advance the test piece
																				// Only one check needed for
																				// concentration.
		if(t->phase == PHASE_CONCENTRATION ||
			 t->phase == PHASE_NEW) i = t->thinksperturn;

	}

}


/**************************************************************************
	int trymove(void)

	DESCRIPTION:  Trys a move for a player and returns move "score"


**************************************************************************/
double trymove(void)
{
	int score;
	int k;
	BYTE *grid;
	PIECE hold;
	int rot,trans,x,y;
//	int empties;
//	double s_empty,s_height,s_row,s_special,s_piece,s_px;


//	empties = t->empties;

	x= p->px;
	y = p->py;
	copypiece(&hold,&(p->active));  // Make a copy of the active piece
	copygrid(t->grid,p->spot);

	rot = t->grot;
	trans = t->gx;
	grid = t->grid;
																			 // Error checking, but mostly for
																			 // diagnostics.
	if(rot < 0 || rot > 3 || trans < -2 || trans > 10) {
		//print(SET,14,10,10,"THINKING ERROR: R%d T%d",rot,trans);
		return MOVEERR;
	}

	score = 0;
	x_height = -1000;


																				// Do the rotation
	for(k = 0; k < rot; k++) {
		rotatepieceleft(&hold);
		if(collisioncheck(x,y,&hold,grid)) {
			return  MOVEERR;
		}
	}
																		 // Do the translation
	while(x != trans) {
		if(x < trans) x++;
		else x--;
		if(collisioncheck(x,y,&hold,grid)) {
			return MOVEERR;
		}
	}

																		 // Drop the piece
	while(!collisioncheck(x,y,&hold,grid)) y++;
	y--;
	score = 1000 - csetpiece(x,y,&hold,grid);
																		 // count rows cleared and new voids
/*	x_row = condenseminigrid(grid,0);
	x_empty = countvoids(grid)- empties;

	s_special = 0;

																		 // Calculate movement score
	s_row =    factor[0]*x_row*x_row + 			 factor[1]*x_row +    factor[2];
	s_empty =  factor[3]*x_empty*x_empty + 	 factor[4]*x_empty +  factor[5];
	s_height = factor[6]*x_height*x_height + factor[7]*x_height + factor[8];
	s_piece =  factor[9]*x_piece*x_piece + 	 factor[10]*x_piece + factor[11];
	s_px =     factor[12]*x_px*x_px + 			 factor[13]*x_px +    factor[14];


	score = s_row + s_special + s_empty + s_height + s_piece + s_px;
*/
	score -= countdensity(grid);
	x_row = condenseminigrid(grid,0);

	return score;
}



/**************************************************************************
	int countblocks(BYTE spot[])

	DESCRIPTION:  Counts the number of block in a grid

**************************************************************************/
int countblocks(BYTE spot[])
{
	int total = 0,i;

	for(i = 0; i < grid_height*grid_width; i++) {
		if(spot[i]) total++;
	}

	return total;
}

/**************************************************************************
	int condenseminigrid(BYTE spot[])

  DESCRIPTION:  finds filled rows and removes them from the input grid

	returns: number of rows dropped

**************************************************************************/
int condenseminigrid(BYTE spot[],int preserve)
{
	int i,j,k,tot= 0,s=0;


	x_special = 0;

	for(i = 0; i < grid_height; i++) {    // Loop each row to find full rows.

																				// check row for empties.
		for(j = 0; j< grid_width && spot[s + j]; j++);

		if(j == grid_width) {               //  Full?  Drop it!
			tot++;
																				// Is there a special?
			for(j = 0; j< grid_width  ; j++){
				if(spot[s + j] >= SPECIALBASE) x_special =spot[s + j];
			}
																				// Drop the blocks only if we say so
			if(!preserve) {
																					// drop the blocks logically
				for(j = 0; j < grid_width; j++) {
					for( k = i; k >= 0 ; k--) {
						if(k == 0) spot[k*grid_width + j] = 0;
						else spot[k*grid_width + j] = spot[(k-1)*grid_width + j];
					}
				}
			}
		}
		s += grid_width;
  }
	return tot;
}


/**************************************************************************
	void copygrid(BYTE g1[], BYTE g2[])

	DESCRIPTION:  Copies one playing grid to another

  INPUTS:

		g1   	pointer to destination grid
    g2 		pointer to source grid

**************************************************************************/
void copygrid(BYTE g1[], BYTE g2[])
{
	memmove(g1,g2,grid_width*grid_height );
}


/**************************************************************************
	int countvoids(BYTE g[])

  DESCRIPTION:  Counts the number of void spaces in a grid.  A void space
								is an empty space beneath a block.

**************************************************************************/
int countvoids(BYTE g[])
{
	int i,j,s,empties = 0;

	for(i = 0; i < grid_width; i++) {   // loop over the columns
																			// Find the first block
		s = i;
		for(j = 0; j < grid_height && !g[s]; j++,s+=grid_width);
																			// count the voids
		for(; j < grid_height ; j++,s+=grid_width) if(!g[s])
			empties++;
	}

	return(empties);
}



/**************************************************************************
	int countdensity(BYTE g[])

	DESCRIPTION: 	A little different scoring method based on the density of
								the whole grid.

**************************************************************************/
int countdensity(BYTE g[])
{
	int i,j,s,empties = 0,emptyscore = 0;
	int area = 0;
	int topmost = grid_height;

																		// Find the topmost piece
	for(j = 0; j < grid_height; j++) {
		for(i = 0; i < grid_width && !g[i+j*grid_width]; i++);
		if(i < grid_width) {
			topmost = j;
			break;
		}
	}

	for(i = 0; i < grid_width; i++) {   // loop over the columns
																			// Find the first block
		s = i + topmost * grid_width;
		for(j = topmost; j < grid_height && !g[s]; j++,s+=grid_width);
																			// count the voids
		empties = 0;

		for(; j < grid_height ; j++,s+=grid_width) {
			area+=grid_height-j;

			if(!g[s]) empties++;
		}
		if(empties) empties = 10;

		emptyscore+= empties;
	}

	return(emptyscore + (grid_height-topmost)*grid_width);
//	return emptyscore;
}

/**************************************************************************
	void unsetpiece(int px, int py,PIECE *pc,BYTE spot[])

	DESCRIPTION:  UnSets the active piece permanently in the player grid

  INPUTS
  	px,py			grid coordinates of the piece
		pc					pointer to piece structure
		spot			pointer to grid data array


**************************************************************************/
void unsetpiece(int px, int py,PIECE *pc,BYTE spot[])
{
 	int i,x,y;
	int *coords;

	coords = pc->bloc[pc->rotation];

	for(i = 0; i < 4; i++) {
		x = coords[i*2] ;
		y = coords[i*2+1] ;
		if(py+y >=0 ) {                      // Only set if the block
																						// is really in the grid.
				spot[(px+x)+(py+y)*grid_width] = 0;
    }
  }
}

/**************************************************************************
	int csetpiece(int px, int py,PIECE *p,BYTE spot[])

	DESCRIPTION:  Sets the active piece permanently in the player grid

	INPUTS
		px,py			grid coordinates of the piece
		p					pointer to piece structure
		spot			pointer to grid data array


**************************************************************************/
int csetpiece(int px, int py,PIECE *p,BYTE g[])
{
	int i,x,y,pscore=0;
	int *coords;
	int lowness = 0,lowest = -1000;


	coords = p->bloc[p->rotation];

	for(i = 0; i < 4; i++) {
		x = coords[i*2] ;
		y = coords[i*2+1] ;
		lowness += (4-y);

//		pscore += -y;

		if(py+y>lowest) lowest = py+y;           // look at bottom of piece
		if(py+y >=0 ) {                      // Only set if the block
																						// is really in the grid.
			g[(px+x)+(py+y)*grid_width] = p->type;		}
	}
//	pscore += (grid_height-py);

	x_piece = lowness;
	if(lowest > x_height) x_height = lowest;
	return pscore;
}
