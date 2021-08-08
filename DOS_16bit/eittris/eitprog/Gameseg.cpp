// Varmint's EITTRIS
// Copyright (C) 1996-2000, Purple Planet Software

#include "stdafx.h"
#include "eittris.h"
#include "dvutil.h"

const int ABORTKEY = DIK_ESCAPE; 
const int PAUSEKEY = DIK_F1;
const int MUSICKEY = DIK_F2;
const int SOUNDKEY = DIK_F3;
const int TURBOKEY = DIK_F4;
const int SNAPSHOTKEY = DIK_F5;

void cogitate(PLAYER *p);
int getcurrentmovescore(PLAYER *plyr);

BYTE ghold[GRIDMEMSIZE];

long unsigned int current_frame = 0;
extern int bgcolor;
int turbo = FALSE;


/**************************************************************************
	void activatespecial(int special,PLAYER *p)

	DESCRIPTION:

**************************************************************************/
void activatespecial(int special,PLAYER *p)
{
	WORD i,x,y;
	int ihold;

	if(special >= 0) {
		p->special_counter = 0;           // Do this first or get screwed up
										  // when switching grids
	}
	else special = -1 *special;         // Negative specials are caused by
										// a tetris event and so the
										// special block (if there is one)
										// should ne be erased.

	p->ganimdata[9] = 10;								// the last animation data spot is
																// resorved for a PC sound parameter.

	// No enemy? Then just do things
	// to yourself.
	if(!p->enemy) {
		switch(special) {
		case 1:													  // Slowdown
			// Slow yourself down in
			// proportion to how soon
			// you got the special.
			p->countmaster = (int)(p->countmaster * (1.5 +
				(1.0 * p->special_counter/p->special_lifetime)));
			p->countrate = p->countmaster;
			dostats(p);

			dosound(21,100,100);
			break;
		case 13:												// Antedote
			p->antedotes++;
			if(p->antedotes < 6) {
				g_lpdvdrawobject->SpritePut(p->gridx + 90 + (p->antedotes-1) *20,
					p->gridy+ grid_height * p->bh + 90,0,
					shape[SPECIALBASE+13]);
			}

			dosound(16,100,100);

			break;
		case 16:                        // Clearscreen
			FINISHANIM(p);
			p->gridanimation = clearscreengridanimation;
			p->ganimdata[0] = 15;
			p->ganimdata[1] = 3;
			dosound(9,100,100);
			break;

		}
		return;
	}
	////// Specials with enemy selected

	switch(special) {
	case 0:													  // Speedup
		// Speed up the enemy in
		// proportion to how soon
		// you got the special.
		p->enemy->countmaster = (int)(p->enemy->countmaster * (.6 -
			(0.4 * p->special_counter/p->special_lifetime)));
		p->enemy->countrate = p->enemy->countmaster;
		dostats(p->enemy);

		dosound(11,100,100);

		break;
	case 1:													  // Slowdown
		// Slow yourself down in
		// proportion to how soon
		// you got the special.
		p->countmaster = (int)(p->countmaster * (1.5 +
			(1.0 * p->special_counter/p->special_lifetime)));
		p->countrate = p->countmaster;
		dostats(p);

		dosound(21,100,100);
		break;
	case 2:													// Escalator
		FINISHANIM(p->enemy);
		p->enemy->gridanimation = staircasegridanimation;
		p->enemy->ganimdata[0] = 0;
		p->enemy->ganimdata[1] = 5;
		p->enemy->ganimdata[2] = random(2);
		p->enemy->ganimdata[9] = 1;
		break;
	case 3:													// The Wall
		FINISHANIM(p->enemy);
		p->enemy->gridanimation = wallgridanimation;
		p->enemy->ganimdata[0] = grid_height-1;
		p->enemy->ganimdata[1] = 5;
		p->enemy->ganimdata[9] = 1;
		break;
	case 4:                         // Jumble
		FINISHANIM(p->enemy);
		p->enemy->gridanimation = jumblegridanimation;
		p->enemy->ganimdata[0 ] = grid_width*grid_height-1;
		p->enemy->ganimdata[9] = 1;
		break;
	case 5:													// Crazy Ivan
		if(!HOSEDWITH(p->enemy,CRAZYIVAN)) p->enemy->computer_accuracy = (int)(p->enemy->computer_accuracy * 0.95);
		HOSE(p->enemy,CRAZYIVAN);
		dosound(12,100,100);
		g_lpdvdrawobject->SpritePut(p->enemy->gridx+50,
			p->enemy->gridy+grid_height * p->enemy->bh + 150,0,
			shape[SPECIALBASE+5]);

		break;
	case 6:													// switch screens
		FINISHANIM(p);
		FINISHANIM(p->enemy);
		copygrid(ghold,p->spot);
		copygrid(p->spot,p->enemy->spot);
		copygrid(p->enemy->spot,ghold);

		ihold = p->special_counter;
		p->special_counter = p->enemy->special_counter;
		p->enemy->special_counter = ihold;

		p->ganimdata[0] = grid_height*grid_width-1;
		p->enemy->ganimdata[0] = grid_height*grid_width-1;
		p->gridanimation = freezedrygridanimation;
		p->enemy->gridanimation = freezedrygridanimation;

		dosound(2,100,100);
		break;
	case 7:													// EIT-O-Matic
		dosound(7,100,100);
		for(i = 0; i < 5; i++) {
			g_lpdvdrawobject->SpritePut(p->gridx+92 + i*19,p->gridy+grid_height*p->bh + 122,0,
				shape[SPECIALBASE+7]);
		}
		p->timer[0] = 285;
		break;
	case 8:													// inverter
		FINISHANIM(p->enemy);
		copygrid(ghold,p->enemy->spot);

		// find top of pieces
		for(y = 0; y < grid_height; y++) {
			for(x = 0; x < grid_width; x++) {
				if(ghold[x+y*grid_width]) break;
			}
			if(x < grid_width) break;
		}

		if(y == grid_height) break;
		i = y;
		// Flip the grid
		for(; y < grid_height; y++) {
			for(x = 0; x < grid_width; x++) {
				p->enemy->spot[x+(grid_height - y + i -1) * grid_width] =
					ghold[x+y*grid_width];
			}
		}

		p->enemy->gridanimation = freezedrygridanimation;
		p->enemy->ganimdata[0] = grid_width*grid_height-1;
		p->enemy->ganimdata[9] = 3;
		dosound(16,100,45);
		dosound(16,100,60);
		dosound(16,100,95);


		break;
	case 9:													// Freeze Dried Blocks
		if(!HOSEDWITH(p->enemy,FREEZEDRIED)) p->enemy->computer_accuracy = (int)(p->enemy->computer_accuracy * 0.95);
		HOSE(p->enemy,FREEZEDRIED);
		FINISHANIM(p->enemy);
		p->enemy->gridanimation = freezedrygridanimation;
		p->enemy->ganimdata[0] = grid_width*grid_height-1;
		p->enemy->ganimdata[9] = 1;
		g_lpdvdrawobject->SpritePut(p->enemy->gridx+70,
			p->enemy->gridy+grid_height * p->enemy->bh + 150,0,
			shape[SPECIALBASE+9]);
		break;
	case 10:                        // Invisible pieces
		if(!HOSEDWITH(p->enemy,INVISIBLEPIECES)) p->enemy->computer_accuracy = (int)(p->enemy->computer_accuracy * 0.95);
		HOSE(p->enemy,INVISIBLEPIECES);
		dosound(8,100,100);
		g_lpdvdrawobject->SpritePut(p->enemy->gridx+90,
			p->enemy->gridy+grid_height * p->enemy->bh + 150,0,
			shape[SPECIALBASE+10]);
		break;
	case 11:                        // Future piece hiding
		if(!HOSEDWITH(p->enemy,FUTUREPIECEHIDING)) p->enemy->computer_accuracy = (int)(p->enemy->computer_accuracy * 0.95);
		HOSE(p->enemy,FUTUREPIECEHIDING);
		dosound(4,100,100);
		g_lpdvdrawobject->SpritePut(p->enemy->gridx+110,
			p->enemy->gridy+grid_height * p->enemy->bh + 150,0,
			shape[SPECIALBASE+11]);
		break;
	case 12:                        // Change enemie's background
		p->enemy->background = random(numbackgrounds);
		drawgrid(p->enemy);
		dosound(10,100,100);
		break;
	case 13:												// Antedote
		p->antedotes++;
		if(p->antedotes < 6) {
			g_lpdvdrawobject->SpritePut(p->gridx + 90 + (p->antedotes-1) *20,
				p->gridy+ grid_height * p->bh + 90,0,
				shape[SPECIALBASE+13]);
		}

		dosound(16,100,100);

		break;
	case 14:												// bridge
		FINISHANIM(p->enemy);
		p->enemy->gridanimation = bridgegridanimation;
		p->enemy->ganimdata[0] = 999;
		p->enemy->ganimdata[1] = 5;
		p->enemy->ganimdata[9] = 1;
		break;
	case 15:												// Transparent grid blocks
		if(!HOSEDWITH(p->enemy,TRANSPARENTGRIDBLOCKS)) p->enemy->computer_accuracy = (int)(p->enemy->computer_accuracy * 0.95);
		HOSE(p->enemy,TRANSPARENTGRIDBLOCKS);
		FINISHANIM(p->enemy);
		p->enemy->gridanimation = freezedrygridanimation;
		p->enemy->ganimdata[0] = grid_width*grid_height-1;
		p->enemy->ganimdata[9] = 2;
		g_lpdvdrawobject->SpritePut(p->enemy->gridx+130,
			p->enemy->gridy+grid_height * p->enemy->bh + 150,0,
			shape[SPECIALBASE+15]);
		break;
	case 16:                        // Clearscreen
		FINISHANIM(p);
		p->gridanimation = clearscreengridanimation;
		p->ganimdata[0] = 15;
		p->ganimdata[1] = 3;
		dosound(9,100,100);
		break;
	case 17:                        // Randomize grid
		FINISHANIM(p->enemy);
		p->enemy->gridanimation = randomizegridanimation;
		p->enemy->ganimdata[0] = grid_width*grid_height-1;
		p->enemy->ganimdata[1] = 0;
		p->enemy->ganimdata[9] = 1;
		break;
	case 18:													// Zee virus
		HOSE(p->enemy,ZEEVIRUS);
		dosound(6,100,100);
		g_lpdvdrawobject->SpritePut(p->enemy->gridx+150,
			p->enemy->gridy+grid_height * p->enemy->bh + 150,0,
			shape[SPECIALBASE+18]);
		break;
	case 19:													// Psycho
		if(!HOSEDWITH(p->enemy,PSYCHO)) p->enemy->computer_accuracy = (int)(p->enemy->computer_accuracy * 0.95);
		HOSE(p->enemy,PSYCHO);
		dosound(1,100,160);
		g_lpdvdrawobject->SpritePut(p->enemy->gridx+170,
			p->enemy->gridy+grid_height * p->enemy->bh + 150,0,
			shape[SPECIALBASE+19]);
		break;
	case 20:												// Shackle
		FINISHANIM(p->enemy);
		p->enemy->gridanimation = shacklegridanimation;
		p->enemy->ganimdata[0] = 0;
		p->enemy->ganimdata[1] = 5;
		break;
	case 21:												// Tower of EIT
		FINISHANIM(p->enemy);
		p->enemy->gridanimation = towergridanimation;
		p->enemy->ganimdata[0] = 12;
		p->enemy->ganimdata[1] = -1;
		break;
	default:
		break;
	}

}

/**************************************************************************
	int condensegrid(PLAYER *p)

  DESCRIPTION:  finds filled rows and removes them from the player grid

  returns: number of rows dropped

**************************************************************************/
int condensegrid(PLAYER *p)
{
	int i,j,k,tot= 0,preflag,specialflag =0;


	for(i = 0; i < grid_height; i++) {    // Loop each row to find full rows.

		preflag = 0;                        // reset flag for secial check.
		// check row for empties.
		for(j = 0; j< grid_width && p->spot[i*grid_width + j]; j++){
			// Special? set the preflag?
			if(p->spot[i*grid_width + j] >= SPECIALBASE)
				preflag = p->spot[i*grid_width + j];
		}

		if(j == grid_width) {               //  Full?  Drop it!
			FINISHANIM(p);

			if(preflag) specialflag = preflag;// Did we zap a special brick?
			tot++;
			p->ganimdata[tot] = i;            // store the row number for animation

			// drop the blocks logically
			for(j = 0; j < grid_width; j++) {
				for( k = i; k >= 0 ; k--) {
					if(k == 0) p->spot[k*grid_width + j] = 0;
					else p->spot[k*grid_width + j] = p->spot[(k-1)*grid_width + j];
				}
			}
		}
	}

	if(tot)		{
		p->ganimdata[0] = tot;                // store the number of full rows
		p->ganimdata[tot+1]=0;                //  reset the grid animation
		p->ganimdata[9] = 5;								  // the last animation data spot is
		// resorved for a PC sound parameter.
		p->gridanimation = standardgridanimation;
	}


	if(specialflag) activatespecial(specialflag-SPECIALBASE,p);


	return tot;
}




/**************************************************************************
	int gamesegment(void)

	DESCRIPTION: handles a single moment of time on the game. This is designed
  						 to be called XXX times per second.

	BYTE spot[GRIDMEMSIZE];
  int gridx,gridy,bw,bh;

  PIECE active,buffer;
	int px,py,count,countmaster;

  char name[20];
  int score;


**************************************************************************/
int gamesegment(void)
{
	int i,j,pcount = 0,numrows,r,g,b,s;
	int flag,ox,oy,nx,ny,statsflag  = 0,x,y;
	// int k,gx,gy;
	PIECE phold;
	PLAYER *p;
	static int paused = FALSE;


	if(!stressmode && !turbo) {
		if (TimerCheck(EIT_TIMER_ID) < (DWORD)(gamespeed * 1000)) return TRUE;
		TimerReset(EIT_TIMER_ID);
	}

	// DWORD soundid;
	// static char str[22] ={"a"};

	// TODO: handle music volume here
	g_lpdvsoundobject->ModSetting(DVS_VOLUME,musicvolume * (musicon ? 1: 0));

//	s3m_volume = mod_volume = musicvolume * (musicon ? 1: 0);

	current_frame++;                      // Keep track of the frames

	// Dump the keyboard into a big
	// character bucket.
	while(scankeyhit()) charbuffer[getscancode()]++;
	// Process special keys
	if(charbuffer[ABORTKEY]) {            // abort game?
		if(paused) {
			paused=0;
			dosound(8,100,40);
		}
		turbo = 0;
		charbuffer[ABORTKEY]--;
		for(i = 0; i < MAXPLAYERS; i++) { // Finish any animations.
			p = person[i];
			if(p) {
				FINISHANIM(p);
			}

		}

		endround();                         // draw round stats
		return(0);
	}
	if(charbuffer[PAUSEKEY]) {            // abort game?
		charbuffer[PAUSEKEY]--;
		paused ^= 1;
		if(paused) {
			r = random(255);
			g = random(255);
			b = random(255);
			dosound(1,60,60);
			g_lpdvdrawobject->Clear(g_lpdvdrawobject->RGBColor(r,g,b));
		}
		else {
			dosound(8,100,40);
			prepgrids();
		}


	}
	if(charbuffer[MUSICKEY]) {            // stop music?
		charbuffer[MUSICKEY]--;
		musicon  ^= 1;
	}
	if(charbuffer[SOUNDKEY]) {            // stop sound?
		charbuffer[SOUNDKEY]--;
		soundon ^= 1;
	}
	if(charbuffer[TURBOKEY]) {            // fast compters?
		charbuffer[TURBOKEY]--;
		turbo ^= 1;
	}

	if(paused) {
		g_lpdvdrawobject->Print(col_Black,10,10,"Varmint's EITtris.\n"
												"The game is paused. press <F1> to resume.\n\n\n"
												"The current tune is: %s",tune[currenttune].name);
		
		return(1);                
	}

	// Make sure enemies are not messed
	// up.  ie: you can't be your own
	// enemy and your enemy cannot be
	// dead.
	for(i = 0; i < MAXPLAYERS; i++) {
		p = person[i];
		if(!p || !p->alive) continue;
		// If player is there own enemy
		// or if they have a dead enemy
		if(p == p->enemy || (p->enemy && !(p->enemy)->alive)) {
			for(j = 0; j < MAXPLAYERS; j++) {
				if(person[j] && person[j]->alive && person[j] != p)
					p->enemy = person[j];
			}
			if(p == p->enemy) p->enemy = NULL;
			dostats(p);
		}

	}


	for(i= 0; i< MAXPLAYERS; i++) {								// Loop over all the players
		p = person[i];                    	// This is to clean up the code a bit
		if(!p) continue;
		if(!p->alive) {
			if(p->gridanimation) p->gridanimation(p);
			continue;
		}
		pcount ++;

		if(p->active.type == 255) {     		// is there an active piece?

			if(p->buffer.type == 255) {   		// Do we need a new piece?
				// Create a piece in the buffer
				if(HOSEDWITH(p,ZEEVIRUS)) generatepiece(&(p->buffer),random(2)+2);
				else generatepiece(&(p->buffer),pickpiece(i));
			}
			// Move buffer piece to active spot
			copypiece(&(p->active),&(p->buffer));
			// erase buffer piece
			erasepiece(&p->buffer,p->gridx+4 ,p->gridy + (grid_height) * p->bh +43 ,
				0,0,p->bw,p->bh,p->gridy,0);

			// Put a new piece in the buffer
			if(HOSEDWITH(p,ZEEVIRUS)) generatepiece(&(p->buffer),random(2)+2);
			else generatepiece(&(p->buffer),pickpiece(i));
			// Draw the piece in the buffer
			if(!HOSEDWITH(p,FUTUREPIECEHIDING))
				drawpiece(&p->buffer,p->gridx+4 ,p->gridy + (grid_height) * p->bh +43,
				p->bw,p->bh,p->gridy);


			p->count = p->countmaster;
			p->px = random(4)+1;
			p->py = -2;
			// put our boy on the screen!

			DRAW(&(p->active));
			p->fallstart = grid_height;   		// This variable keeps track of
			// where the player dropped
			// the piece.

			// collision check. Person dies
			// if there is one here.

			if(collisioncheck(p->px,p->py, &(p->active),p->spot)) {
				FINISHANIM(p);
				p->gridanimation = fadegridanimation;  // fade out the  grid
				p->ganimdata[0] = 0;
				p->ganimdata[9] = 5000;
				p->alive = 0;                   // kill them logically

				// Close the player loop
				for(j = 0; j < MAXPLAYERS; j++) {
					if(person[j] && person[j]->enemy == p) {
						person[j]->enemy = p->enemy;
						dostats(person[j]);
					}
				}
				p->enemy = NULL;
				continue;
			}

			p->brain.phase = PHASE_NEW;



		}
		///// DEBUGGING computer intelligence!  //////////////
//if(charbuffer[DIK_F5]) {  
//charbuffer[DIK_F5]--;
//activatespecial(21,p);
//}

		if(p->controltype != 'C') {

//			s =  getcurrentmovescore(p);
//			if(s > p->timer[4]) p->timer[4] = s;
//			g_lpdvdrawobject->DrawFillRectangle(0,300,0,400,22);
//			g_lpdvdrawobject->Print(300,0,"S: %d",s);
//			g_lpdvdrawobject->Print(300,10,"H: %d",p->timer[4]);
//
//			if(p->py < 0) p->timer[4] = 0;
		}

		/////// END DEBUGGING ///////////////////////////////

		// ------------------------- Timers ---------------------

		if(p->timer[0] && !(current_frame % 15)) {  // EIT -o - matic?
			p->timer[0] -= 2;
			if(p->timer[0] < 0) p->timer[0] = 0;
			g_lpdvdrawobject->DrawLine(0,p->gridx+92+p->timer[0]/3,p->gridy+grid_height*p->bh+122,
				p->gridx+92+p->timer[0]/3,p->gridy+grid_height*p->bh+140);
		}



		// ------------------------- SPECIAL BLOCKS -------------------------

		// Deal with special pieces
		if(p->special_counter) {        		// Is there already a special?
			p->special_counter--;         		// age the special.
			if(!p->special_counter) {     		// time for special to go away?
				x = 0; y = 0;
				for(j = 0; j < grid_width*grid_height && p->spot[j] < SPECIALBASE; j++);

				if(j < grid_width*grid_height) {// if a special was found...
					x = j % grid_width;
					y = j/grid_width;
					p->spot[j] = random(7)+1;   	// pick a random normal peice
					drawblock(x,y,p);             // Draw it.
				}
			}
		}
		// Else, if the special does not
		// exist check a random number
		// and make one.
		else if(!p->special_probability--) {
			p->special_probability = random(maxtime_to_special)+1;
			if(gridhaspieces(p)) {
				p->special_counter = p->special_lifetime;
				j = random((grid_width*grid_height)-1)+1;
				x = 0; y = 0;
				while(j) {
					x++;
					if(x >= grid_width) {
						x = 0;
						y++;
						if(y >= grid_height) y = 0;
					}

					if(p->spot[x+y*grid_width]) j--;
				}
				j = pickspecial(p->specialgrid); // pick the special piece
				if(j != -1){
					p->spot[x+grid_width*y] = j+SPECIALBASE;	// put it in the grid
					drawblock(x,y,p);              /// Draw it
				}
			}
		}

		// -------------------- PIECE MOVEMENT ---------------------------

		p->count--;
		// Handle  invisibility affliction
		if(HOSEDWITH(p,INVISIBLEPIECES) &&
			p->active.visible &&
			random(100) < 60) ERASE(&(p->active));


		if(!p->count) {                 // time to move the piece?
			ERASE(&(p->active));          // erase current position

			p->py++;                      // move it down
			flag = collisioncheck(p->px,p->py,
				&(p->active),p->spot);    // check for a collision

			if(flag) {                    // did it collide?
				p->py--;                    // move it back up and stick it
				setanddrawpiece(&(p->active),p);
				sticksound(i);              // make a noise
				p->active.type = 255;
				if(HOSEDWITH(p,PSYCHO))
					dopsycho(g_lpdvdrawobject->RGBColor(random(256),random(256),random(256)),
					p->gridx,p->gridy,
					p->gridx+grid_width*p->bw,p->gridy+grid_height*p->bh);
			}
			// draw the piece
			else {
				DRAW(&(p->active));
			}

			p->count = p->countrate;

			if(flag) {                    // if a piece landed
				numrows = condensegrid(p);  // clear any filled rows
				if(numrows == 4) {          // TETRIS?
					activatespecial(-tetrisspecial,p);
					dosound(5,120,100);
				}
				// Handle EIT-o-matic
				if(numrows && p->timer[0] && p->enemy) {  // active?
					// Finish any animation
					while(p->enemy->gridanimation) p->enemy->gridanimation(p->enemy);

					p->enemy->ganimdata[0] = numrows;
					p->enemy->ganimdata[1] = 20;
					p->enemy->gridanimation = eitomaticgridanimation;
				}
				// Signal computer to find a new victim
				if(numrows && p->controltype == 'C') {
					if(p->computer_justhosed == 1) p->computer_justhosed = 2;
				}
				// reset the piece
				p->countrate = p->countmaster;
				// calclate score changes:
				// 1 point automatically for landing
				// any piece. 1  point for every row
				// the piece fell after being 'dropped'.
				// numrows^2 * 10 points for clearing rows.
				j = p->py-p->fallstart;
				if(j < 0) j = 0;
				addtoscore(p, numrows * numrows * 1000 + (j+1) * (j + 1));
				p->rows += numrows;
				dostats(p);     						// update stats
				continue;
			}
		}
		// ----------------------- SPEED CHANGES ----------------------

		// speed changes
		if(!(current_frame % frames_per_speedup)){
			p->countmaster =  (int)(p->countmaster * speedup);
			if(p->countmaster < 2) p->countmaster = 2;
			if(p->countrate > p->countmaster) p->countrate = p->countmaster;
		}


		// -------------------- Process any animtion ----------------------


		if(p->gridanimation) p->gridanimation(p);

		// ----------------------- COMPUTER MOVEMENT ----------------------
		// Let's think!
		if(p->controltype == 'C') {
			cogitate(p);
		}
		// Let's move!
		if(p->computer_counter) {
			p->computer_counter--;
			// handle computer speed and see if the
			// computer will act on this frame
			if(p->computer_counter % (600/p->computer_speed) == 0) {
				// Computer, heal thyself!
				if(p->afflicted && p->antedotes) charbuffer[p->pkey[PKEYANTEDOTE]]++;
				//  rotates, then translates, then drops
				if(p->computer_rotations) {
					charbuffer[p->pkey[PKEYRLEFT]]++;
					p->computer_rotations--;
				}
				else if(p->px > p->computer_translation) charbuffer[p->pkey[PKEYLEFT]]++;
				else if(p->px < p->computer_translation) charbuffer[p->pkey[PKEYRIGHT]]++;
				else if(p->computer_droptime) {
					// tell the computer the piece is
					// ready to be dropped
					if(!p->computer_inposition) p->computer_inposition = 1;
					p->computer_droptime--;
					if(!p->computer_droptime) charbuffer[p->pkey[PKEYDROP]]++;
				}
			}
		}

		// -------------------------- KEYSTROKES --------------------------

		// Process Keystrokes

		copypiece(&phold,&(p->active));   // Make a copy to work with
		ox = p->px;
		oy = p->py;

		flag = 0;
		// Handle crazy Ivan key convolutions
		if(HOSEDWITH(p,CRAZYIVAN) && p->controltype != 'C') {
			if(charbuffer[p->pkey[PKEYLEFT]]) {
				charbuffer[p->pkey[PKEYLEFT]]--;
				charbuffer[p->pkey[PKEYRIGHT]]++;
			}
			else if(charbuffer[p->pkey[PKEYRIGHT]]) {
				charbuffer[p->pkey[PKEYRIGHT]]--;
				charbuffer[p->pkey[PKEYLEFT]]++;
			}
			else if(charbuffer[p->pkey[PKEYRRIGHT]]) {
				charbuffer[p->pkey[PKEYRLEFT]]++;
				charbuffer[p->pkey[PKEYRRIGHT]]--;
			}
			else if(charbuffer[p->pkey[PKEYRLEFT]]) {
				charbuffer[p->pkey[PKEYRLEFT]]--;
				charbuffer[p->pkey[PKEYRRIGHT]]++;
			}
		}
		//  Handle each key
		if(charbuffer[p->pkey[PKEYLEFT]]) {
			charbuffer[p->pkey[PKEYLEFT]]--;
			p->px--;
			flag++;
		}
		else if(charbuffer[p->pkey[PKEYRIGHT]]) {
			charbuffer[p->pkey[PKEYRIGHT]]--;
			p->px++;
			flag++;
		}
		else if(charbuffer[p->pkey[PKEYDOWN]]) {
			charbuffer[p->pkey[PKEYDOWN]]--;
			p->py++;
			flag++;
		}
		else if(charbuffer[p->pkey[PKEYDROP]]) {
			charbuffer[p->pkey[PKEYDROP]]--;
			p->countrate = 1;
			p->count = 1;
			p->fallstart = p->py;
			flag++;
		}
		else if(charbuffer[p->pkey[PKEYRLEFT]]) {
			charbuffer[p->pkey[PKEYRLEFT]]--;
			rotatepieceleft(&(p->active));
			flag++;
		}
		else if(charbuffer[p->pkey[PKEYRRIGHT]]) {
			charbuffer[p->pkey[PKEYRRIGHT]]--;
			rotatepieceright(&(p->active));
			flag++;
		}
		// Choose a new victim
		else if(charbuffer[p->pkey[PKEYVICTIM]]) {
			charbuffer[p->pkey[PKEYVICTIM]]--;
			// Find current enemy
			for(j = 0; j < MAXPLAYERS; j++) {
				if(!p->enemy && person[j] && person[j] == p) break;  // Null ememy?
				else if(person[j] && person[j] == p->enemy) break;   // real enemy
			}
			// find next opponent
			j++;
			if(j >= MAXPLAYERS) j = 0;             // Don't go off edge!

			while(1) {                             // Find first live person
				if(person[j] && person[j]->alive) break;
				j++;
				if(j >= MAXPLAYERS) j = 0;
			}
			if(person[j] == p) p->enemy = NULL;
			else p->enemy = person[j];
			dostats(p);

			flag++;
		}
		else if(charbuffer[p->pkey[PKEYANTEDOTE]]) {
			// Handle antedote stuff
			charbuffer[p->pkey[PKEYANTEDOTE]]--;
			if(p->antedotes) {                      // Any left?
				FINISHANIM(p);
				// Subtract and draw it
				p->antedotes--;
				if(p->antedotes < 5) {
					g_lpdvdrawobject->DrawFillRectangle(bgcolor,p->gridx + 90 + p->antedotes *20,
						p->gridy+ grid_height * p->bh + 90,
						p->gridx + 90 + p->antedotes *20 +19,
						p->gridy+ grid_height * p->bh + 90 +19);
				}
				// Handle computer accuracy
				p->computer_accuracy = p->accstore;
				p->afflicted = 0;
				p->gridanimation = antedotegridanimation;
				p->ganimdata[0] = grid_width*grid_height-1;
				g_lpdvdrawobject->DrawFillRectangle(bgcolor,p->gridx+50,p->gridy+grid_height * p->bh + 150,
					p->gridx+193,p->gridy+grid_height * p->bh + 170);

				// Sounds
				dosound(0,100,100);

			}
		}

		if(flag) {
			// Valid move?
			if(!collisioncheck(p->px,p->py,
				&(p->active),p->spot)) {
				nx = p->px;
				ny = p->py;
				p->px = ox;
				p->py = oy;
				ERASE(&phold);
				p->px = nx;
				p->py = ny;
				DRAW(&(p->active));
			}
			// No? go back!
			else {
				copypiece(&(p->active),&phold);
				p->px = ox;
				p->py = oy;
				p->computer_translation = ox;  // make sure computer doesn't get stuck
			}
		}
		if(statsflag) dostats(p);           // update player statistics
	}

	// Exit condition in stressmode
	// press the '1' jey
	if(stressmode && charbuffer[2]) {
		charbuffer[2] = 0;
		pcount = 0;
		stressmode =2;
	}
	// To take a snapshot, press F5
	if(snapshotmode && charbuffer[SNAPSHOTKEY] ) {
		charbuffer[SNAPSHOTKEY] = 0;
		// TODO: add code to take screen shot here
	}

	if(pcount == 1) {                   // Just one left?
					// Find the winner
		for(i = 0; i < MAXPLAYERS; i++) {
			if(!person[i]) continue;
			if(person[i]->alive) {
				person[i]->win = true;
				break;
			}
		}
	}
	else if(pcount ==0) {               // no players left?
		for(i = 0; i < MAXPLAYERS; i++) { // Finish any animations.
			p = person[i];
			if(p) {
				FINISHANIM(p);
			}

		}

		endround();                         // draw round stats
		turbo = FALSE;
		pcount = 0;
	}

	return pcount;

}


/**************************************************************************
	int gridhaspieces(PLAYER *p)

  DESCRIPTION:  Returns the numbers of occupied  blocks in a grid.

**************************************************************************/
int gridhaspieces(PLAYER *p)
{
	int i,j,t=0;

	for(i  = 0; i < grid_width; i++) {
		for(j = 0; j < grid_height; j++) {
			if(p->spot[i + grid_width * j]) t++;
		}
	}

	return(t);
}
