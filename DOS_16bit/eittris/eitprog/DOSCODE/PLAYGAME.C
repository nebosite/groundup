/**************************************************************************
	PLAYGAME.C

**************************************************************************/
#include "tetris.h"

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

	for(i = 0; i < 5; i++) p->timer[i] = 0;

	p->computer_counter = 0;
																	// Check for computer control
	if(p->controltype == 'C') {
		p->computer_counter = -1;
		p->special_lifetime =
			special_lifetime * (19 - p->computer_smarts*2 )/10.0;
		p->special_probability =
			maxtime_to_special * (19 - p->computer_smarts*2 )/10.0;;
	}

}


/**************************************************************************
	void playgame(void)

	DESCRIPTION:

**************************************************************************/
void playgame(void)
{
	int pcount=0,i,j,k,tryagain;
	char err[255];

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
		print(SET,GREEN666,200,500,"You need to set up at least one player.");
		getch();
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


	startkeyboard();              // Start up scan code handler

																// Begin with a random tune
	currenttune = random(numtunes);

	for(currentround=1; currentround <= totalrounds; currentround++) {
																// Get music going
		tryagain = 5;
		while((soundtype == SBSOUND) && numtunes && tryagain) {
			currenttune++;
			if(currenttune >= numtunes) currenttune = 0;
			musictype = tune[currenttune].type;
			if(musictype == 'O') { // Mod music?
				mod_data = LoadMod(tune[currenttune].name,err);
				if(mod_data) {
					mod_data->repeatmusic = -1;
					mod_volume = musicvolume * (musicon ? 1: 0);
					ModCommand(v_play);
					tryagain = 0;
				}
				else{
					drawbox(100,100,700,300,5,104,12,18);
					print(SET,0,110,120,"Error with tune: %s",tune[currenttune].name);
					print(SET,0,110,140,"MOD error: %s",err);
					print(SET,0,110,160,"Press any key to try another tune...");
					if(!stressmode) {
						flushkey();
						getkey();
					}
					else MilliDelay(3000);
					tryagain --;
				}
			}
			else if(musictype == 'S') { // S3M music?
				s3m_data = LoadS3M(tune[currenttune].name,err);
				if(s3m_data) {
					s3m_data->repeatmusic = -1;
					s3m_volume = musicvolume * (musicon ? 1: 0);
					S3MCommand(v_play);
					tryagain = 0;
				}
				else{
					drawbox(100,100,700,300,5,104,12,18);
					print(SET,0,110,120,"Error with tune: %s",tune[currenttune].name);
					print(SET,0,110,140,"S3M error: %s",err);
					print(SET,0,110,160,"Press any key to try another tune...");
					if(!stressmode) {
						flushkey();
						getkey();
					}
					else MilliDelay(3000);
					tryagain--;
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
		if(stressmode) {
			print(SET,215,20,maxy-16,"R: %d (%lukb free)",currentround,farcoreleft()/1000L);
		}
																 // Clear keyboard
		for(i = 0; i < 256; i++) charbuffer[i] = 0;

		while(gamesegment()){        // go!
			if(soundtype == PCSOUND) nosound();
		}
		if(soundtype == PCSOUND) nosound();
		// Note: the music is stopped in the end of round stats function

	}
	stopkeyboard();
																 // Unmap vitual keycode for computers
	for(i = 0; i < MAXPLAYERS; i++) {
		if(person[i] && person[i]->controltype == 'C') {
			for(k = 0; k < 8; k++) person[i]->pkey[k] = person[i]->storekey[k];
		}
	}
}