// Varmint's EITTRIS
// Copyright (C) 1996-2000, Purple Planet Software

#include "stdafx.h"
#include "eittris.h"
#include "dvutil.h"
#include <conio.h>

DVMOD *g_lpmod = NULL;
DVS3M *g_lps3m = NULL;

/**************************************************************************
	void playerinit(PLAYER *p)

  DESCRIPTION:  Initializes player values for a new round of play

**************************************************************************/
void playerinit(PLAYER *p)
{
	int i;

	for(i= 0; i < GRIDMEMSIZE; i++) p->spot[i] = 0;   // clear playing grid
	// initialize available specials
	for(i= 0; i < 60; i++) p->specialgrid[i] = specialgrid[i];
	p->active.type = 255;   									// reset pieces
	p->buffer.type = 255;

	p->countmaster = startspeed;              // piece falling rate
	p->countrate = startspeed;

	p->alive = TRUE;
	p->win = 0;
	p->gridanimation = NULL;
	p->enemy = NULL;
	p->rows = 0;
	setscore(p,0);
	p->lastscore = 0;
	p->tainted = 0;
	p->background = random(numbackgrounds);
	p->afflicted = 0;
	p->antedotes = 0;
	p->accstore = p->computer_accuracy;
	p->special_lifetime = special_lifetime;
	p->special_probability = maxtime_to_special; 

	for(i = 0; i < 5; i++) p->timer[i] = 0;

	p->computer_counter = 0;
	// Check for computer control
	if(p->controltype == 'C') {
		p->computer_counter = -1;
		p->special_lifetime =
			(WORD)(special_lifetime * (19 - p->computer_smarts*2 )/10.0);
		p->special_probability =
			(WORD)(maxtime_to_special * (19 - p->computer_smarts*2 )/10.0);
	}

}


/**************************************************************************
	void playgame(void)

	DESCRIPTION:

**************************************************************************/
void playgame(void)
{
	MSG winmsg;
	int pcount=0,i,j,k,tryagain;

																// Initialize total game stats
	for(i = 0; i < MAXPLAYERS; i++) {
		if(person[i]) {
			person[i]->wins = 0;
			person[i]->tscore = 0;
			person[i]->trows = 0;
			pcount++;
		}
	}

	if(pcount < 1) {               // Enough players?
		g_lpdvdrawobject->Print(col_Green,200,500,"You need to set up at least one player.");
		egetch();
		return;
	}
																 // Remap computer keystrokes.  If this
																 // does not happen, computers can
																 // interfere with each other.
	j = 120;
	for(i = 0; i < MAXPLAYERS; i++) {
		if(person[i] && person[i]->controltype == 'C') {
			for(k = 0; k < 8; k++) {
				person[i]->storekey[k] = person[i]->pkey[k];
				person[i]->pkey[k] = j++;
			}
		}
	}


																// Begin with a random tune
	currenttune = random(numtunes);

	for(currentround=1; currentround <= totalrounds; currentround++) {
		// Get music going
		tryagain = 5;
		while(numtunes && tryagain > 0) {
			currenttune++;
			if(currenttune >= numtunes) currenttune = 0;
			musictype = tune[currenttune].type;
			if(musictype == 'O') { // Mod music?

				g_lpmod = new DVMOD(tune[currenttune].name);
				if(!g_lpmod || !g_lpmod->m_bIsValid) {
					drawbox(100,100,700,300,5,
							g_lpdvdrawobject->RGBColor(255,150,150),
							g_lpdvdrawobject->RGBColor(50,0,0),
							g_lpdvdrawobject->RGBColor(100,0,0));
					g_lpdvdrawobject->Print(110,120,"Error with tune: %s",tune[currenttune].name);
					if(g_lpmod)	{
						g_lpdvdrawobject->Print(110,140,"MOD error: %s",g_lpmod->m_szErrorMessage);
						delete g_lpmod;
						g_lpmod = NULL;
					}
					g_lpdvdrawobject->Print(110,160,"Press any key to try another tune...");
					if(!stressmode) {
						g_lpdvinputobject->FlushKeyboard();
						i = egetch();
						if(i == 27) break;
					}
					else Sleep(3000);
					tryagain --;
				}
				else {
					tryagain = 0;
					g_lpdvsoundobject->ModPlay(g_lpmod);
					g_lpdvsoundobject->ModSetting(DVS_VOLUME,musicvolume * (musicon ? 1: 0));
				}
			}
			else if(musictype == 'S') { // S3M music?
				g_lps3m = new DVS3M(tune[currenttune].name);
				if(!g_lps3m || !g_lps3m->m_bIsValid) {
					drawbox(100,100,700,300,5,
							g_lpdvdrawobject->RGBColor(255,150,150),
							g_lpdvdrawobject->RGBColor(50,0,0),
							g_lpdvdrawobject->RGBColor(100,0,0));
					g_lpdvdrawobject->Print(110,120,"Error with tune: %s",tune[currenttune].name);
					if(g_lps3m)	{
						g_lpdvdrawobject->Print(110,140,"S3M error: %s",g_lps3m->m_szErrorMessage);
						delete g_lps3m;
						g_lps3m = NULL;
					}
					g_lpdvdrawobject->Print(110,160,"Press any key to try another tune...");
					if(!stressmode) {
						g_lpdvinputobject->FlushKeyboard();
						i = egetch();
						if(i == 27) break;
					}
					else Sleep(3000);
					tryagain --;
				}
				else {
					tryagain = 0;
					g_lpdvsoundobject->S3MPlay(g_lps3m);
					g_lpdvsoundobject->S3MSetting(DVS_VOLUME,musicvolume * (musicon ? 1: 0));
				}
			}
		}

		for(i = 0; i < MAXPLAYERS; i++) {     // initialize the players
			if(person[i]) {
				playerinit(person[i]);
				j = i;
				while(!person[i]->enemy){ // attach an enemy
					j++;
					if(j>=MAXPLAYERS) j = 0;
					person[i]->enemy = person[j];
				}
			}
		}
		prepgrids();                 // set up the playing fields
																 // Clear keyboard
		for(i = 0; i < 256; i++) charbuffer[i] = 0;

		TimerReset(EIT_TIMER_ID);
		while(gamesegment()){        // go!
			g_lpdvsoundobject->MixAhead(100);
									// Make sure windows messages make it out to the
									// other applications.
			while(PeekMessage(&winmsg, NULL, 0, 0, PM_REMOVE))	{

									// Capture windows keystroke messages.  These guys slow down 
									// the application alot.  This line will also prevent
									// Ctrl-alt-delete work from windowed mode.
				if(winmsg.message == WM_SYSCHAR || winmsg.message == WM_SYSKEYDOWN ) continue;	
							   
									// Handle the message properly.
				TranslateMessage(&winmsg);
				DispatchMessage(&winmsg);
			}
		}
		g_lpdvinputobject->FlushKeyboard();

		// Note: the music is stopped in the end of round stats function

	}

																 // Unmap vitual keycode for computers
	for(i = 0; i < MAXPLAYERS; i++) {
		if(person[i] && person[i]->controltype == 'C') {
			for(k = 0; k < 8; k++) person[i]->pkey[k] = person[i]->storekey[k];
		}
	}
}