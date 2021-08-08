#include "tetris.h"

char *shackledata[12] = {
	"0002222000",
	"0221111220",
	"2112222112",
	"2120000212",
	"1200000021",
	"1200000021",
	"1200000021",
	"1200000021",
	"2120000212",
	"2112222112",
	"0221111220",
	"0002222000"};
char *towerdata[12] = {
	"0110110110",
	"0111111110",
	"0111111110",
	"0011011100",
	"0011011100",
	"0011110100",
	"0011110100",
	"0010111100",
	"0010111100",
	"0011101100",
	"0011101100",
	"0011111100"};


int grad1[8] = {216,218,220,222,224,226,228,229};
/**************************************************************************
	void towergridanimation(PLAYER *p)

	DESCRIPTION:

**************************************************************************/
void towergridanimation(PLAYER *p)
{
	int x,y;

	if(p->ganimdata[1] == -1) {              // Clear the Tower
		if(soundtype == SBSOUND) dosound(10,100,60);
		else if(soundtype == PCSOUND) pcsound(200);
		for(x = 0; x < grid_width; x++) {
			for(y = 0; y < grid_height; y++) p->spot[x+y*grid_width] = 0;
		}
		drawgrid(p);
		p->ganimdata[1] = 20;
	}


	p->ganimdata[1]--;                        // delay
	if(p->ganimdata[1]) return;
	p->ganimdata[1] = 4;

																						// sound stuff
	if(soundtype == SBSOUND) dosound(18,100,80);
	else if(soundtype == PCSOUND) pcsound(150);


	p->ganimdata[0]--;                        // move up the grid
	y = p->ganimdata[0];
	for(x = 0; x < grid_width; x++) {
																					 // put the piece in
		if(*(towerdata[y]+x) == '1') {
			p->spot[x+(y+ grid_height-12)*grid_width] = 16;
			drawblock(x,y+ grid_height-12,p);
		}
		else  {
			p->spot[x+(y+ grid_height-12)*grid_width] = 0;
			eraseblock(x,y+ grid_height-12,p);
		}
	}
																						// Stop animation if we're
																						// at the end.
	if(!p->ganimdata[0]) p->gridanimation = NULL;

}
/**************************************************************************
	void shacklemation(PLAYER *p)

	DESCRIPTION:

**************************************************************************/
void shacklegridanimation(PLAYER *p)
{
	int x,y;


	p->ganimdata[1]--;                        // delay
	if(p->ganimdata[1]) return;
	p->ganimdata[1] = 4;


	if(soundtype == SBSOUND) dosound(19,100,200);
	else if(soundtype == PCSOUND) pcsound(3300);


	y = p->ganimdata[0];
	for(x = 0; x < grid_width; x++) {
																					 // put the piece in
		if(*(shackledata[y]+x) == '1') {
			p->spot[x+(y+ grid_height-12)*grid_width] = random(7)+1;
			drawblock(x,y+ grid_height-12,p);
		}
		else if(*(shackledata[y]+x) == '2') {
			p->spot[x+(y+ grid_height-12)*grid_width] = 0;
			eraseblock(x,y+ grid_height-12,p);
		}
	}
	p->ganimdata[0]++;                        // move down the grid
																						// Stop animation if we're
																						// at the end.
	if(p->ganimdata[0] == 12) p->gridanimation = NULL;

}

/**************************************************************************
	void eitomaticgridanimation(PLAYER *p)

	DESCRIPTION:

**************************************************************************/
void eitomaticgridanimation(PLAYER *p)
{
	int x,y,d;


	p->ganimdata[1]--;                        // delay
	if(p->ganimdata[1]) return;
	p->ganimdata[1] = 20;

														// move grid up
	for(x = 0; x < grid_width; x++) {
		for (y = 0; y < grid_height-1; y++ ) {
			p->spot[y*grid_width + x] =
				p->spot[(y+1)*grid_width + x];
		}
	}
														// Add row

	if(soundtype == SBSOUND) dosound(9,100,200);
	else if(soundtype == PCSOUND) pcsound(300);


	d = random(grid_width);                   // pick empty spot

	for(x = 0; x < grid_width; x++) {
																					 // put the piece in
		if(x == d) p->spot[x+y*grid_width] = 0;
		else p->spot[x+y*grid_width] = random(7)+1;
	}
	drawgrid(p);
	p->ganimdata[0]--;                        // move up the grid
																						// Stop animation if we're
																						// at the end.
	if(!p->ganimdata[0]) p->gridanimation = NULL;

}



/**************************************************************************
	void jumblegridanimation(PLAYER *p)

  DESCRIPTION:

**************************************************************************/
void jumblegridanimation(PLAYER *p)
{
	int x,y,d,d2,x2,y2,movelist[4],maxmoves=0;

	d = p->ganimdata[0];                      // convenience holder



  while(p->spot[d] &&  d > 0) d--;          // find an empty spot

  p->ganimdata[0] = d;
  if(p->ganimdata[0] < 0) {
		p->gridanimation = NULL;
    return;
  }
  p->ganimdata[0]--;



  x = d % grid_width;                       // get grid spot
  y = d / grid_width;

  d2 = d+1;
  if(d2 < grid_height*grid_width && p->spot[d2])  {  //move right?
    movelist[maxmoves] = 0;
    maxmoves++;
  }

  d2 = d-1;
  if(d2 > 0 && p->spot[d2])  {  											//move left?
    movelist[maxmoves] = 1;
    maxmoves++;
  }

  d2 = d+grid_width;
  if(d2 < grid_height*grid_width && p->spot[d2])  {  //move down?
    movelist[maxmoves] = 2;
    maxmoves++;
  }

  d2 = d-grid_width;
  if(d2 > 0 && p->spot[d2])  {  											//move up?
    movelist[maxmoves] = 3;
    maxmoves++;
  }

  movelist[maxmoves] = 4;
  maxmoves++;

  switch(movelist[random(maxmoves)]) {
  	case 0: // right
		  d2 = d+1;
      x2=x+1;
      y2 =y;
      if(x2 >= grid_width) {
			  x2 = 0;
        y2++;
      }
      break;
  	case 1: // left
		  d2 = d-1;
      x2=x-1;
      y2 =y;
      if(x2 < 0) {
			  x2 = grid_width-1;
        y2 --;
      }
      break;
  	case 2: // down
		  d2 = d+grid_width;
      x2=x;
      y2 =y+1;
      break;
  	case 3: // up
		  d2 = d-grid_width;
      x2=x;
      y2 =y-1;
      break;
    default:
    	return;
	}

  p->spot[d] = p->spot[d2];
  p->spot[d2] = 0;
	drawblock(x,y,p);
 	eraseblock(x2,y2,p);
																											// Sounds
  if(p->ganimdata[9] == 1) {
    if(p->spot[d]) {
			if(soundtype == PCSOUND) pcsound(random(1000)+2000);
			else if(soundtype == SBSOUND && ! (d%3) )
				dosound(17,100,random(50) + 75);
		}
  }


                                            // at the end.

}
/**************************************************************************
	void randomizegridanimation(PLAYER *p)

  DESCRIPTION:

**************************************************************************/
void randomizegridanimation(PLAYER *p)
{
	int i,x,y,d;

                                           // find the top
  if(!p->ganimdata[1]) {
  	d = 0;
    for(y = 0; y < grid_height; y++) {     // look row by row from top
    	for(x = 0; x < grid_width; x++) {
      	if(p->spot[x+y*grid_width]) d = 1; // block there?  set the flag
      }
      if(d) break;
    }
    if (y < (grid_height/3)) y = grid_height/3;
    if (y > (2*grid_height/3)) y = 2*grid_height/3;
  	p->ganimdata[1] = y;
  }

  for(i = 0; i < 3; i++ ) {                 // speed it up by doing 3 blocks
                                            // at once.
	  d = p->ganimdata[0];                    // convenience holder

    x = d % grid_width;
    y = d / grid_width;

    if(random(100) < 25 && y > p->ganimdata[1]) p->spot[d] = random(7)+1;
    else p->spot[d] = 0;

 	  if(p->spot[d]) drawblock(x,y,p);        // draw this block if there.
    else eraseblock(x,y,p);                 // erase it if there isn't.

    p->ganimdata[0]--;                      // move up the grid
                                            // Stop animation if we're
    																				// at the end.
    if(p->ganimdata[0] < 0) {
			p->gridanimation = NULL;
      return;
    }
  }

  if(p->ganimdata[9] == 1) {
    if(p->spot[d]) {
			if(soundtype == PCSOUND) pcsound(random(1000)+5000);
			else if(soundtype == SBSOUND) dosound(10,100,random(50)+75);
		}
  }

}


/**************************************************************************
	void clearscreengridanimation(PLAYER *p)

  DESCRIPTION:

**************************************************************************/
void clearscreengridanimation(PLAYER *p)
{
	int i;

  p->ganimdata[1]--;                     // delay
  if(p->ganimdata[1]) return;
  p->ganimdata[1] = 3;
                                         // Flash thingy
  if(p->ganimdata[0]) {
  	drwfillbox(SET,p->ganimdata[0]+216,p->gridx,p->gridy,
    							 p->gridx+p->bw*grid_width,
                   p->gridy+p->bh*grid_height);
    p->ganimdata[0]--;
  }
  else {
  	for(i = 0; i < grid_width * grid_height; i++) p->spot[i] = 0;
    drawgrid(p);
    p->gridanimation = NULL;
  }

}



/**************************************************************************
	void wallgridanimation(PLAYER *p)

	DESCRIPTION:

**************************************************************************/
void wallgridanimation(PLAYER *p)
{
	int x,y,d;

  p->ganimdata[1]--;
  if(p->ganimdata[1]) return;
  p->ganimdata[1] = 5;

                                                // Sounds
  if(p->ganimdata[9] == 1) {
		if(soundtype == PCSOUND) pcsound(150);
		else if(soundtype == SBSOUND) dosound(14,100,100);
  }


  y = p->ganimdata[0];

  d = random(grid_width);                   // pick empty spot

  for(x = 0; x < grid_width; x++) {
    if(x == d) {
			p->spot[x+y*grid_width] = 0;
      eraseblock(x,y,p);
    }
  	else {
			p->spot[x+y*grid_width] = random(7)+1;
      drawblock(x,y,p);
    }
  }

  p->ganimdata[0]--;                        // move up the grid
                                            // Stop animation if we're
                                            // at the end.
  if(p->ganimdata[0] <= (grid_height/2)) p->gridanimation = NULL;

}
/**************************************************************************
	void staircasegridanimation(PLAYER *p)

  DESCRIPTION:

**************************************************************************/
void staircasegridanimation(PLAYER *p)
{
	int x,y,d;

  p->ganimdata[1]--;                          // delay
  if(p->ganimdata[1]) return;
  p->ganimdata[1] = 5;
                                              // Sounds
  if(p->ganimdata[9] == 1) {
		if(soundtype == PCSOUND) pcsound(p->ganimdata[0]*100+1000);
		else if(soundtype == SBSOUND) dosound(15,100,p->ganimdata[0]*12 + 80);
	}

                                              // left to right
  if(p->ganimdata[2]) {
	  x = p->ganimdata[0];                      // get x and y of stairstep
    y = grid_height-x-1;
    d = x+y*grid_width;                       // calculate data location

    p->spot[d] = random(7)+1;                 //  create stair
    drawblock(x,y,p);
    if(x < grid_width -1) {                   // erase underneath
		  p->spot[d+1] = 0;
      eraseblock(x+1,y,p);
    }
  }
  else {                                      // right to left
	  x = grid_width - 1 - p->ganimdata[0];     // get x and y of stairstep
    y = grid_height - p->ganimdata[0]-1;
    d = x+y*grid_width;                       // calculate data location

    p->spot[d] = random(7)+1;                 //  create stair
    drawblock(x,y,p);
    if(x >0) {                   // erase underneath
		  p->spot[d-1] = 0;
      eraseblock(x-1,y,p);
    }
  }

  p->ganimdata[0]++;                        // move up the grid
                                            // Stop animation if we're
                                            // at the end.
  if(p->ganimdata[0] == grid_width) p->gridanimation = NULL;

}
/**************************************************************************
	void bridgegridanimation(PLAYER *p)

  DESCRIPTION:

**************************************************************************/
void bridgegridanimation(PLAYER *p)
{
	int x,y,d;
                                           // find the top
  if(p->ganimdata[0] > grid_height) {
  	d = 0;
    for(y = 0; y < grid_height; y++) {     // look row by row from top
    	for(x = 0; x < grid_width; x++) {
      	if(p->spot[x+y*grid_width]) d = 1; // block there?  set the flag
      }
      if(d) break;
    }
  	p->ganimdata[0] = y;
    if(y == grid_height) p->ganimdata[0]--; // don't go off teh bottom
    p->ganimdata[2] = 0;
  }

  p->ganimdata[1]--;                        // delay
  if(p->ganimdata[1]) return;
  p->ganimdata[1] = 5;

  y = p->ganimdata[0];
  if(y < 0) {
  	p->gridanimation = NULL;
    return;
  }

	if(soundtype == SBSOUND && p->ganimdata[9] == 1) dosound(20,100,100);
	else if(soundtype == PCSOUND) pcsound(300);


  d = random(grid_width);                   // pick empty spot

  for(x = 0; x < grid_width; x++) {
                                           // make a sound

                                           // put the piece in
    if(x == d) {
			p->spot[x+y*grid_width] = 0;
      eraseblock(x,y,p);
    }
  	else {
			p->spot[x+y*grid_width] = random(7)+1;
      drawblock(x,y,p);
    }
  }

  p->ganimdata[0]--;                        // move up the grid
  p->ganimdata[2]++;
                                            // Stop animation if we're
                                            // at the end.
  if(p->ganimdata[2] == 2) p->gridanimation = NULL;

}

/**************************************************************************
	void antedotegridanimation(PLAYER *p)

  DESCRIPTION:

**************************************************************************/
void antedotegridanimation(PLAYER *p)
{
	int x,y,d;

	d = p->ganimdata[0];                      // convenience holder


 	if(p->spot[d]) {                          // draw this block if there.
  	x = d % grid_width;
    y = d / grid_width;
    drawblock(x,y,p);
  }
  p->ganimdata[0]--;                        // move up the grid
                                            // Stop animation if we're
                                            // at the end.
	if(p->ganimdata[0] < 0) {
		p->gridanimation = NULL;
		drawgrid(p);
	}

}

/**************************************************************************
	void freezedrygridanimation(PLAYER *p)

  DESCRIPTION:  Fades out a grid when a person dies

**************************************************************************/
void freezedrygridanimation(PLAYER *p)
{
	int i,x,y,d,flag =0;



  for(i = 0; i < 3; i++) {
		d = p->ganimdata[0];                      // convenience holder
    x = d % grid_width;
    y = d / grid_width;
 	  if(p->spot[d]) {
			drawblock(x,y,p);  											// draw this block if there.
      flag = 1;
    }
    else eraseblock(x,y,p);

    p->ganimdata[0]--;                        // move up the grid
                                              // Stop animation if we're
                                              // at the end.
    if(p->ganimdata[0] < 0) {
			p->gridanimation = NULL;
      return;
    }
  }

	if(soundtype == SBSOUND && p->ganimdata[9] == 1 && flag) {
		dosound(19,100,100);
  }
	else if(soundtype == SBSOUND && p->ganimdata[9] == 2 && flag) {
		dosound(15,100,100);
  }
	else if(soundtype == PCSOUND && flag) {
		pcsound(3000);
  }

}
/**************************************************************************
	void fadegridanimation(PLAYER *p)

  DESCRIPTION:

**************************************************************************/
void fadegridanimation(PLAYER *p)
{
  int i,j;
																			// Play dying sound
  if(soundtype == SBSOUND && p->ganimdata[9] == 5000) {
		dosound(3,100,100);
  }
  else if(soundtype == PCSOUND) {
		pcsound(p->ganimdata[9]);
  }
  p->ganimdata[9] -=5;

                                      // Fade a row.
  for(i = p->ganimdata[0] ; i < (p->ganimdata[0] +4)&& i < maxy; i++) {
  	blkget(p->gridx-5,i,p->gridx+grid_width*p->bw+4,i,dummy[0]);
    for(j = 0; j < grid_width*p->bw+9; j++) {
    	*(dummy[0]->data + j) = bwfade[*(dummy[0]->data + j)];
    }
    blkput(SET,p->gridx-5,i,dummy[0]);
	}
  p->ganimdata[0] += 4;
  if (i == maxy) p->gridanimation = NULL;
}

/**************************************************************************
	void standardgridanimation(PLAYER *p)

  DESCRIPTION:  Seed function for animating the grid when a row or
  						  rows are cleared.

	INPUTS:
  	p			pointer to player structure

  DATA ASSIGNMENTS for p->ganimdata[]
  	0				 		contains number of rows to clear (n)
    1 - n       contains the row numbers of the rows to clear
    n + 1       contains stage number of the animation
    n + 2       contains first animation progress number

  ANIMATION SEQUENCE:
  	1)  clear out full rows
    2)  drop everything above lowest empty row
    	  when the lowest empty row is closed, move the animation
        up to any empty rows that might e higher.
    3)  repeat #2 until done

**************************************************************************/
void standardgridanimation(PLAYER *p)
{
  int i,j,t;
  int x,y;

  t = p->ganimdata[0];					// set total number of line for easy access
  i = p->ganimdata[t+2];

  if(soundtype == PCSOUND) {
  	if(p->ganimdata[9]) {
    	p->ganimdata[9]--;
			pcsound(p->ganimdata[9]*500+4000);
    }
  }
  else if (soundtype == SBSOUND) {
		if(i%2  && i >0 && i < 100) dosound(13,80,100+i*6);
	}

  switch(p->ganimdata[t+1]) {
  	case 0:											// Initialize animation
    	p->ganimdata[t+2] = -7;
      p->ganimdata[t+1] = 1;
    case 1:                     // Erase the rows
    	for(j = 0; j < t; j++ ) {
                                // set x and y for left block
      	y = p->gridy + p->ganimdata[j+1]*p->bh;
        x = p->gridx + p->ganimdata[t+2];
                                // Clip the view and put the dizzolve shape
        setview(p->gridx,0,p->gridx+(grid_width*p->bw)/2+1,maxy);
        blkput(SET,x,y,shape[SH_DIZZOLVE+1+ANIMBASE]);
                                // set the x for the right block
        x = p->gridx + p->bw * grid_width - p->ganimdata[t+2]-16;
                                // Clip the view and put the dizzolve shape
        setview(p->gridx+(grid_width*p->bw)/2+1,0,p->gridx+(grid_width*p->bw),maxy);
        blkput(SET,x,y,shape[SH_DIZZOLVE+ANIMBASE]);
      }
      setview(0,0,maxx,maxy);   // put the clipping back to normal
      p->ganimdata[t+2]+=3;     // increment animation location
      if(p->ganimdata[t+2] > (p->bw * grid_width)/2) p->ganimdata[t+1]=2;
      break;
    case 2:
    	p->gridanimation = NULL;
      drawgrid(p);
      break;
    default:
    	break;
  }

}


