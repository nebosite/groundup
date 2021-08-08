
/**************************************************************************

	MENUS.C

	For Varmint's Eitris
	Eric Jorgensen (1995)


**************************************************************************/
#include "tetris.h"
#include "hiscore.h"

void playersetup(void);
void showscores(void);
void egg2(void);

const int NUMOPTIONS = 6;
/**************************************************************************
	void mainmenu(void)

	DESCRIPTION:  Handles everything

**************************************************************************/
void mainmenu(void)
{
	int menuflag = 1,drawflag = 1,flag = 1;
	int opt = 0;
	static int egg2on = 0;
	int left,top;
	int i,byte1,byte2;
	int px,py,eddie=0;
	char easterstring[20] = {"                   "};
	char *option[] = {"PLAY","PLAYER SET UP","INSTRUCTIONS","HIGH SCORES",
										"ABOUT EITTRIS","QUIT"};
  char c=' ';

	easterstring[19] = 0;

	left = (maxx-800)/2;
	top = (maxy-600)/2;

	fillscreen(0);
	pcxput(SET,left,top,"title.pcx");
	byte1 = getpoint(left,top);
	byte2 = getpoint(left,top+1);
	localkey = byte1+byte2*256;
	if(!localkey) {
		localkey = (random(9000)+1) * 7;
		byte1 = localkey & 0xff;
		byte2 = localkey >> 8;
		drwpoint(SET,byte1,left,top);
		drwpoint(SET,byte2,left,top+1);
		pcxmake(left,top,left+799,top+599,"title.pcx");
	}
	drwline(SET,0,left,top,left,top+1);


	while(flag) {                         // main input loop
		if(drawflag) {                      // Put title page in the screen
			fillscreen(0);
			pcxput(SET,left,top,"title.pcx");
			drwline(SET,0,left,top,left,top+1);   // Hide secret key
//			print(SET,14,300,0,"Key: %u ",localkey);
																				// Keep this for when your title
																				// screen's black is not really black

			//pcxput(SET,0,0,"title.pcx");
			//i = getpoint(3,3);
			//fillcolor (3,3,i, 0);
			//pcxmake(0,0,maxx-1,maxy-1,"title.pcx");

			drawflag = 0;
    }
		if(menuflag) {                      // Draw the main menu
			drwfillbox(SET,0,left,top+150,left+520,maxy);

			for(i = 0; i < NUMOPTIONS; i++) { // Draw all the entries
				print(SET,2 + 12 + BLUE666,240,250 + i*18,option[i]);
      }
                                        // Draw player list
			print(SET,YELLOW666,230,380,"Current Players");
      for(i = 0;i < 4; i++) {
      	if(person[i]) {
					print(SET,GREEN666,200,400+i*16,person[i]->name);
					print(SET,GREEN666,350,400+i*16,
						person[i]->controltype=='C'?"Computer ":"Human     ");
				}
      }
			menuflag = 0;
    }
                                        // animate the palette while we
                                        // wait for the keyboard.
		while(!kbhit()) {
			blkput(SET,215,250+opt*18,shape[ANIMBASE + 2 + arrowseq[frame++ % 18]]);
			for(i = 0; i < 10; i++) {
				if(egg2on) egg2();
				else MilliDelay(3);
			}
		}

		menuclicksound(350);
		c = getch();                        // grab a keystroke
		if(!c  && kbhit()) c = getch();

																				// easter egg code
		if(c >= ' ') {
			for(i = 0; i < 18; i++) easterstring[i] = easterstring[i+1];
			easterstring[18] = tolower(c);
			if(strstr(easterstring,"eddietwo")) {
				drwfillcircle(SET,226,left+641,top+487,13);
				drwfillcircle(SET,226,left+680,top+480,13);
				drwcircle    (SET,217,left+641,top+487,13);
				drwcircle    (SET,217,left+680,top+480,13);
				eddie = 1;
			}
			if(strstr(easterstring,"snow")) {
				egg2on = 1;
			}
		}



		if(c == KEY_UP) {
			blkput(SET,215,250+opt*18,shape[0]);
			opt--;
			if(opt < 0) opt = NUMOPTIONS-1;
		}
		else if(c == KEY_DOWN) {
			blkput(SET,215,250+opt*18,shape[0]);
			opt++;
			if(opt >= NUMOPTIONS) opt = 0;
		}
		else if(c == ' ' || c == 13) {
			switch(opt) {
				case 0:                         // play a game
					playgame();
					menuflag=1;
					drawflag =1;
					break;
				case 1:                          // Setup
					playersetup();
					menuflag = 1;
					break;
				case 2:                            // Instructions
					drwfillbox(SET,0,left+0,top+150,left+520,maxy);
					print(SET,YELLOW666,left+10,top+151,"Instructions-");
					print(SET,CYAN666,left+10,top+165,
						"   Varmint's Eittris is a competitive game.  You can play for");
					print(SET,CYAN666,left+10,top+179,
						"points or for survival against human and/or computer");
					print(SET,CYAN666,left+10,top+193,
						"opponents.  The game play is pretty straight forward except");
					print(SET,CYAN666,left+10,top+207,
						"for twists provided by special pieces.  To activate one");
					print(SET,CYAN666,left+10,top+221,
						"of these special pieces, simply clear the row it is in.");

					print(SET,CYAN666,left+10,top+240,
						"   All specials are listed below-  You can have fun\n");
					print(SET,CYAN666,left+10,top+254,
						"figuring out on your own what they do:");

					print(SET,CYAN666,left+10,top+470,
						"Special keys you can press during play:");
					print(SET,YELLOW666,left+30,top+490,
						"F1  - Pause/Continue Game");
					print(SET,YELLOW666,left+30,top+504,
						"F2  - Toggle Music");
					print(SET,YELLOW666,left+30,top+518,
						"F3  - Toggle Sound Effects");
					print(SET,YELLOW666,left+30,top+532,
						"F4  - Toggle Turbo Mode");
					print(SET,YELLOW666,left+30,top+546,
						"ESC - End Round");


					for(i = 0 ; i < NUMBEROFSPECIALS; i++) {
						px = (i% 3) *150 + 30 + left;
						py = (i /3) *22 + 284 + top;
						blkput(SET,px,py,shape[SPECIALBASE+i]);
						print(SET,YELLOW666,px+25,py,"%s",specialname[i]);
					}
					getch();
					menuflag=1;
					break;
				case 3:
					drwfillbox(SET,0,left+0,top+150,left+520,maxy);
					showscores();
					menuflag = 1;
					break;
				case 4:                          // credits
					drwfillbox(SET,0,left+0,top+150,left+520,maxy);
					//drawbox(x1,y1,x2,y2,bw,hc,sc,bc)
					drawbox(left+30,top+240,left+510,top+500,5,215,120,43);
					print(SET,YELLOW666,left+50,top+250,
						"Varmint's EITTris %s",VERSION);
					print(SET,104,left+50,top+265,
						"Copyright (c) 1996,1997,1998 - Eric Jorgensen");
					print(SET,GREEN666,left+50,top+310,
						"Written by: Eric Jorgensen (varmint@ericjorgensen.com)");
					print(SET,GREEN666,left+50,top+330,
						"SVGA Graphics: SVGACC (2.4), Zephyr Software");
					print(SET,GREEN666,left+50,top+350,
						"Sound: Varmint's Audio Tools (%s), Ground Up",VAT_VERSION);
					print(SET,GREEN666,left+50,top+370,
						"Music: Various artists. (P.D. MODs and S3Ms)");
					print(SET,CYAN666,left+50,top+400,
						"World Wide Web Site:");
					print(SET,CYAN666,left+50,top+420,
						"     http://www.ericjorgensen.com/eittris");
					print(SET,RED666,left+50,top+460,
						"Maximum music file size: %lu Kb",farcoreleft()/1000);
					menuflag = 1;
					getch();
					break;
				case 5:                            // Quit
					flag = 0;
					break;
				default:
					break;
			}
		}
																					 // Easter egg on?
		if(eddie) {
			drwfillcircle(SET,226,left+641,top+487,11);
			drwfillcircle(SET,230,left+636,top+481+opt,5);
			drwfillcircle(SET,216,left+636,top+481+opt,2);
			drwcircle    (SET,224,left+636,top+481+opt,5);
			drwfillcircle(SET,226,left+680,top+480,11);
			drwfillcircle(SET,230,left+677,top+474+opt,5);
			drwfillcircle(SET,216,left+677,top+474+opt,2);
			drwcircle    (SET,224,left+677,top+474+opt,5);
		}

	}

}



/**************************************************************************
	void showscores(void)

	DESCRIPTION: Displays high score for the user

**************************************************************************/
void showscores(void)
{
	int scorespot= 0,tempspot,i,j;
	HISCORE far *hs,*prinths;
	int flag = 1;
	char str[56],r;
	int left, top;

	left = (maxx-800)/2;
	top = (maxy-600)/2;

	print(SET,CYAN666,left+20,top+220,
		"-HIGH SCORES- Use arrows to scroll. ESC exits.");
	drwstring(SET,YELLOW666,0,
	"PLACE   NAME                  SCORE   ROWS" ,left + 20, top + 250);
	drwline(SET,YELLOW666,left + 20, top + 265, left+420, top+265);
																 // Main loop
	while(flag) {
																 // Find where we are
		tempspot = 0;
		hs = scores;
		while(tempspot < scorespot && hs->next) {
			hs = hs->next;
			tempspot++;
		}
																 // keep us off the edge
		if(!hs->next) scorespot = tempspot;

																 // print up scores
		prinths = hs;
		for(i = 0; i < 20; i++) {
			memset(str,' ',50);        // clear string;
			str[50] = 0;
																 // Fill it with score info
			if(prinths) {
				sprintf(str,"%d)",++tempspot);
				sprintf(str+8,"%s",prinths->name);
				sprintf(str+30,"%6ld",prinths->score);
				sprintf(str+38,"%3d",prinths->rows);
				for(j = 0; j < 50; j++) {
					if(!str[j]) str[j] = ' ';
				}
				prinths = prinths->next;
			}
			drwstring(SET,CYAN666,0,str,left + 20, top + 270 + i* 16);

		}
																			// get a keystroke
		r = getch();
		if(!r  && kbhit()) r = getch();
		menuclicksound(550);

		if(r == KEY_UP) {
			scorespot -= 10;
			if(scorespot < 0) scorespot = 0;
		}
		else if(r == KEY_DOWN) {
			scorespot += 10;
		}
		else if(r == 27 || r == 13 || r == ' ')		flag = 0;
	}

}





