/**************************************************************************
	ENDROUND.C

**************************************************************************/

#include "tetris.h"
#include "hiscore.h"

/**************************************************************************
	void endround(void)

	DESCRIPTION:  Ends the current round and shows player stats.

**************************************************************************/
void endround(void)
{
	int x,y,i,j,winner=-1,left,top,winleft,wintop;
  PLAYER *p;
	char r;
	HISCORE far *hs;
	int writesc = 0;
	int rkey;
	long int hashkey;
	FILE *output;
	int gwidth=600,gheight=8;             // gheight starts with min # of rows

	winleft = (maxx-500)/2;
	wintop = (maxy-200)/2;



	nosound();                             // Turn off any PC sounds


  if(soundtype == SBSOUND && numtunes) { // Stop any music
		if(musictype == 'O' && mod_data ) {  // Stop mod music
																				 // Fade out
			while(mod_volume > 0) {
				mod_volume--;
				MilliDelay(20);
			}

			ModCommand(v_stop);                // Stop music and free it up
			FreeMod(mod_data);
      mod_data = NULL;
    }
		else if(musictype == 'S' && s3m_data ) {  // Stop mod music
																				 // Fade out
			while(s3m_volume > 0) {
				s3m_volume--;
				MilliDelay(20);
			}

			S3MCommand(v_stop);                // Stop music and free it up
			FreeS3M(s3m_data);
			s3m_data = NULL;
    }
	}

																				 // condense stats/ Clean up
	for(i = 0; i < MAXPLAYERS; i++) {
		if(person[i]) {
			gheight++;
			p = person[i];
			p->computer_accuracy = p->accstore;
			p->afflicted = 0;
			p->tscore += getscore(p);
			p->trows += p->rows;
			p->dummtdata[5] = 0;
																					 // Hi score stuff
																					 // Only check if human and high
																					 // score are on and player hasn't
																					 // sheated.
			if(p->controltype == 'H' && highscoreson && !p->tainted) {
																					 // Generate a high score struct
				hs = newscore(p->name,getscore(p),(int)(p->rows));
																					 // Try to insert it
				p->dummtdata[5] = insertscore(&scores,hs);
				if(p->dummtdata[5] < 100) {
					writesc = 1;
					gheight++;
																				 // If this is the number one score
																				 // and this is not a slow computer,
																				 // the user gets a code to enter
																				 // high scores.
					if(p->dummtdata[5] == 1 && !slowcomputer) {
																				 // Get verification code for score
						rkey = localkey;
						hashkey = hihash(NULL, getscore(p), (int)(p->rows),(int)rkey);
																				 // Draw a blank box

						drawbox(winleft,wintop,winleft+500,wintop+200,2,
							REDUNIT*5 + GREENUNIT*3 + BLUEUNIT *3,
							REDUNIT,REDUNIT*2);
																				 // Let the player know what happened
						x = winleft+10;
						y = wintop+10;
						print(SET,YELLOW666,x,y,
							"All right %s!  You got the number 1 high score!\n",p->name);
						y += 20;
						print(SET,CYAN666,x,y,
							" You can see how you stack up against EITTris players from\n"
							"around the globe! Submit your score from the EITTris \n"
							"WWW home page:\n"
							"    http://www.ericjorgensen.com/eittris\n");
						y+= 70;
						print(SET,GRAY0+10,x,y,
							" You will need this information (saved in webscore.txt):\n"
							"Score: %ld\n"
							"Rows: %ld\n"
							"Validation code: %4.4X%8.8lX\n",getscore(p),p->rows,rkey,hashkey);
						y+= 75;
																				// Store high score info into
																				// a file so they don't forget it.
						output = fopen("webscore.txt","w");
						if(output) {
							fprintf(output,
								"High Score information.\n"
								"Enter this at http://www.ericjorgensen.com/eittris\n"
								"Score: %ld\n"
								"Rows: %ld\n"
								"Validation code: %4.4X%8.8lX\n",getscore(p),p->rows,rkey,hashkey);


							fclose(output);
						}
																				 // Make the player wait, then
																				 // get input
						if(soundtype == SBSOUND) {
							for(j = 0; j < 50; j++) {
								dosound(random(21),100,random(40)+80);
								MilliDelay(50);
							}

						}
						else if(soundtype == PCSOUND) {
							for(j = 0; j < 25; j++) {
								pcsound(1000+j*100);
								MilliDelay(10);
								nosound();
								MilliDelay(90);
							}
						}
						MilliDelay(2000);
						flushkey();
						print(SET,GRAY0+13,x+50,y,"Press a key to continue.");

						getscancode();


					}
				}
			}
    }
	}

	if(writesc) {
		writescores(scores);
		gheight++;                          // One row for the header
	}


																				 // Search for the survivor
	for(winner = 0; winner < MAXPLAYERS; winner++) {
		if(person[winner] && person[winner]->win) {
			person[winner]->wins++;
			break;
		}
	}

	gheight *= 20;                         // Figure out the height of the box
	left = (maxx-gwidth)/2;
	top = (maxy-gheight)/2;
																				 // Draw a blank box
	drawbox(left,top,left+gwidth,top+gheight,5,104,0,6);

	x = left+10,y = top+10;
                                         // Put up the stats
	print(SET,GRAY0+10,x,y,"END OF ROUND %d out of %d.",currentround,totalrounds);
	y += 20;
	print(SET,YELLOW666,x,y,"The victor is: %s",
				(winner < MAXPLAYERS) ? person[winner]->name : "** Nobody **");
	y+=30;
	print(SET,GRAY0+10,x,y," PLAYER");
	print(SET,GRAY0+10,x+150,y,"SCORE (TOTAL)");
	print(SET,GRAY0+10,x+300,y,"ROWS (TOTAL)");
	print(SET,GRAY0+10,x+450,y,"TOTAL WINS");
  y+= 20;
	for(i = 0; i < MAXPLAYERS; i++) {
		if(person[i]) {
			p = person[i];
			print(SET,CYAN666,x+10,y,"%s",p->name);
			print(SET,CYAN666,x+150,y,"%ld (%ld)",getscore(p),p->tscore);
			print(SET,CYAN666,x+300,y,"%ld (%ld)",p->rows,p->trows);
			print(SET,CYAN666,x+490,y,"%d",p->wins);
			y+=16;
		}
	}
	y+=20;

	if(writesc) {                         // Any high scores to mention?
		print(SET,YELLOW666,x,y,"PLAYERS WITH HIGH SCORES");
		y += 20;
		for(i = 0; i < MAXPLAYERS; i++) {
			if(person[i]) {
				p = person[i];
				if(p->dummtdata[5] && p->dummtdata[5] < 101) {
					print(SET,GRAY0+15,x+10,y,"%s",p->name);
					print(SET,CYAN666,x+150,y,"(position %d)",p->dummtdata[5]);
					y+=16;
				}
			}
		}
		y += 20;
	}



	if(!stressmode) MilliDelay(500);
  flushkey();                        // empty the keyboard buffer
  if(!stressmode) {
		print(SET,GRAY0+10,x+130,y,
			"Press virtually any key to continue.\n"
			"    ('Q' will end the game.)");
    r = getscancode();
    if(r == 0x10) currentround = totalrounds;
  }

  else {                             // Pressing '1' in stress mode
                                     // will get us out.
  	if(stressmode == 2) {
    	currentround = totalrounds;
      stressmode = 1;
    }
  }

}
