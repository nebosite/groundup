// Varmint's EITTRIS
// Copyright (C) 1996-2000, Purple Planet Software

#include "stdafx.h"
#include "eittris.h"
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
	HISCORE *hs;
	int writesc = 0;
	int rkey,v;
	int hashkey;
	FILE *output;
	int gwidth=600,gheight=8;             // gheight starts with min # of rows

	winleft = (maxx-500)/2;
	wintop = (maxy-200)/2;

	if(numtunes) { // Stop any music
		if(musictype == 'O' && g_lpmod ) {  // Stop mod music
			v = musicvolume * (musicon ? 1: 0);
			// Fade out
			while(v > 0) {
				g_lpdvsoundobject->ModSetting(DVS_VOLUME,v--);
				g_lpdvsoundobject->MixAhead(50);
				Sleep(20);
			}
			g_lpdvsoundobject->MixAhead(0);		// Clear the mixing buffer

			g_lpdvsoundobject->ModCommand(DVS_REMOVE);                // Stop any mod music and free it up 
			delete 	g_lpmod;
			g_lpmod = NULL;
		}
		if(musictype == 'S' && g_lps3m ) {  // Stop mod music
			v = musicvolume * (musicon ? 1: 0);
			// Fade out
			while(v > 0) {
				g_lpdvsoundobject->S3MSetting(DVS_VOLUME,v--);
				g_lpdvsoundobject->MixAhead(50);
				Sleep(20);
			}
			g_lpdvsoundobject->MixAhead(0);		// Clear the mixing buffer

			g_lpdvsoundobject->S3MCommand(DVS_REMOVE);                // Stop any mod music and free it up 
			delete 	g_lps3m;
			g_lps3m = NULL;
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
					if(p->dummtdata[5] == 1) {
						// Get verification code for score
						rkey = localkey;
						hashkey = hihash(NULL, getscore(p), (int)(p->rows),(int)rkey);
						// Draw a blank box

						drawbox(winleft,wintop,winleft+500,wintop+200,2,
							g_lpdvdrawobject->RGBColor(255,150,150),
							g_lpdvdrawobject->RGBColor(50,0,0),
							g_lpdvdrawobject->RGBColor(100,0,0));
						// Let the player know what happened
						x = winleft+10;
						y = wintop+10;
						g_lpdvdrawobject->Print(col_Yellow,x,y,
							"All right %s!  You got the number 1 high score!\n",p->name);
						y += 20;

						g_lpdvdrawobject->Print(col_Cyan,x,y,
							" You can see how you stack up against EITTris players from around the globe! \n"
							"Submit your score from the EITTris home page:  www.eittris.com\n");

						y+= 70;
						g_lpdvdrawobject->Print(g_lpdvdrawobject->RGBColor(160,160,160),x,y,
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
								"Enter this at http://www.eittris.com\n"
								"Score: %ld\n"
								"Rows: %ld\n"
								"Validation code: %4.4X%8.8lX\n",getscore(p),p->rows,rkey,hashkey);


							fclose(output);
						}
						// Make the player wait, then
						// get input
						for(j = 0; j < 50; j++) {
							dosound(random(21),100,random(40)+80);
							Sleep(50);
						}
						Sleep(2000);
						g_lpdvinputobject->FlushKeyboard();
						g_lpdvdrawobject->Print(g_lpdvdrawobject->RGBColor(220,220,220),x+50,y,"Press a key to continue.");

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
	drawbox(left,top,left+gwidth,top+gheight,5,
		g_lpdvdrawobject->RGBColor(100,255,100),
		col_Black,
		g_lpdvdrawobject->RGBColor(0,100,0));

	x = left+10,y = top+10;
	// Put up the stats
	g_lpdvdrawobject->Print(col_Gray[10],x,y,"END OF ROUND %d out of %d.",currentround,totalrounds);
	y += 20;
	g_lpdvdrawobject->Print(col_Yellow,x,y,"The victor is: %s",
		(winner < MAXPLAYERS) ? person[winner]->name : "** Nobody **");
	y+=30;
	g_lpdvdrawobject->Print(col_Gray[10],x,y," PLAYER");
	g_lpdvdrawobject->Print(col_Gray[10],x+150,y,"SCORE (TOTAL)");
	g_lpdvdrawobject->Print(col_Gray[10],x+300,y,"ROWS (TOTAL)");
	g_lpdvdrawobject->Print(col_Gray[10],x+450,y,"TOTAL WINS");
	y+= 20;
	for(i = 0; i < MAXPLAYERS; i++) {
		if(person[i]) {
			p = person[i];
			g_lpdvdrawobject->Print(col_Cyan,x+10,y,"%s",p->name);
			g_lpdvdrawobject->Print(col_Cyan,x+150,y,"%ld (%ld)",getscore(p),p->tscore);
			g_lpdvdrawobject->Print(col_Cyan,x+300,y,"%ld (%ld)",p->rows,p->trows);
			g_lpdvdrawobject->Print(col_Cyan,x+490,y,"%d",p->wins);
			y+=16;
		}
	}
	y+=20;

	if(writesc) {                         // Any high scores to mention?
		g_lpdvdrawobject->Print(col_Yellow,x,y,"PLAYERS WITH HIGH SCORES");
		y += 20;
		for(i = 0; i < MAXPLAYERS; i++) {
			if(person[i]) {
				p = person[i];
				if(p->dummtdata[5] && p->dummtdata[5] < 101) {
					g_lpdvdrawobject->Print(col_White,x+10,y,"%s",p->name);
					g_lpdvdrawobject->Print(col_Cyan,x+150,y,"(position %d)",p->dummtdata[5]);
					y+=16;
				}
			}
		}
		y += 20;
	}



	if(!stressmode) Sleep(500);
	g_lpdvinputobject->FlushKeyboard();                        // empty the keyboard buffer
	if(!stressmode) {
		g_lpdvdrawobject->Print(col_Gray[10],x+130,y,
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
