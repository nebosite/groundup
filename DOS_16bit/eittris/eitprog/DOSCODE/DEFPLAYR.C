/**************************************************************************
	DEFPLAYR.C

**************************************************************************/
#include "tetris.h"


int cspeed[10] = {10,15,20,25,30,40,50,60,80,100};
int caccuracy[10] = {500,666,800,900,950,975,983,990,995,1000};
char *ctypes[10] = {"Senator","DoorKnob","Moron","Easy","Ordinary","Tough","Tougher","HONIG","Mr. EIT","Completely unfair"};

/**************************************************************************
	PLAYER *newplayer(int num)

	INPUT:
		num			Player number

  DESCRIPTION:  Generates a new player and sets default values

**************************************************************************/
PLAYER far *newplayer(int num)
{
	int i;
  PLAYER far *p;

  p = (PLAYER far *)farmalloc(sizeof(PLAYER));
  if(!p) return NULL;

  p->bw = block_width;                               // Set piece size
  p->bh = block_height;
  strcpy(p->name,names[random(13)]);                 // make a name
  p->controltype = 'H';
  p->computer_counter = 0;
  p->special_probability = maxtime_to_special;       // Av. num of ticks to next sp.
  p->special_lifetime = special_lifetime;   				 // LIfetime in ticks
  p->special_counter = 0;
	p->pkey[PKEYLEFT]     = 0x47; // 'KP7';
	p->pkey[PKEYRIGHT]		= 0x49; // 'KP9';
	p->pkey[PKEYDOWN]		 	= 0x4C; // 'KP5';
	p->pkey[PKEYDROP]		 	= 0x4B; // 'KP4';
	p->pkey[PKEYRLEFT]		= 0x48; // 'KP8';
	p->pkey[PKEYRRIGHT]	 	= 0x4D; // 'KP6';
	p->pkey[PKEYVICTIM]	 	= 0x4E; // 'KP+';
	p->pkey[PKEYANTEDOTE] = 0x4F; // 'KP1';
	p->computer_smarts = 0;
	p->computer_speed = cspeed[p->computer_smarts];
	p->computer_accuracy = caccuracy[p->computer_smarts];
  p->plaindraw = FALSE;
	for(i = 0; i < 5; i++) p->timer[i] = 0;
	p->gridx=5 + num * 200 + (maxx-800)/2;
	p->gridy=5 + (maxy - 600)/2;


  return(p);

}



/**************************************************************************
	void defineplayer(int num)

	DESCRIPTION:  Allows the users to set player options

	char name[20];
	char controltype;
	int computer_speed,computer_accuracy;

**************************************************************************/
void defineplayer(int num)
{
	int drawflag=1,flag = 1,color,choice = 0,x,y;
  char r;
  char instring[255];
  PLAYER *p;

																		// Center coordinates
	x = (maxx-800)/2 + 150;
	y = (maxy-600)/2 + 200;

	if(!person[num]) {                      // Slot empty?
		person[num] = newplayer(num);            // Make a new player
																					// set up playing grid location
	}

  p = person[num];                        // abbreviated pointer name



	while(flag) {                           // Main input loop

  	if(drawflag) {                        //  Draw choices
			drwfillbox(SET,0,0,y-50,x+370,maxy);   // clear area
			color = GRAY0+14;                   //  Light gray color for valid stats
			print(SET,color,x,y,"Name:          %s",p->name);
			print(SET,color,x,y + 20,"Controltype:   %s",
						(p->controltype == 'H')?"Human   ":"Computer");
      if(p->controltype == 'C') color = GRAY0+8;
			print(SET,color,x,y+ 40,"Key controls: Left: %s",
						scancodename[p->pkey[PKEYLEFT]]);
			print(SET,color,x,y+60, "             Right: %s",
						scancodename[p->pkey[PKEYRIGHT]]);
			print(SET,color,x,y+80, "              Down: %s",
						scancodename[p->pkey[PKEYDOWN]]);
			print(SET,color,x,y+100,"              Drop: %s",
						scancodename[p->pkey[PKEYDROP]]);
			print(SET,color,x,y+120,"       Rotate Left: %s",
						scancodename[p->pkey[PKEYRLEFT]]);
			print(SET,color,x,y+140,"      Rotate Right: %s",
						scancodename[p->pkey[PKEYRRIGHT]]);
			print(SET,color,x,y+160,"     Change Victim: %s",
						scancodename[p->pkey[PKEYVICTIM]]);
			print(SET,color,x,y+180,"      Use Antedote: %s",
						scancodename[p->pkey[PKEYANTEDOTE]]);

			if(p->controltype == 'C') color = GRAY0+14;
			else color = GRAY0+8;

			print(SET,color,x,y+200,"Intelligence:         [%d]  %s   ",
						p->computer_smarts+1,ctypes[p->computer_smarts]);
			color = GREEN666;                   // Green for action items
			print(SET,color,x,y+220,"Delete this Player");
			print(SET,color,x,y+240,"Done -> Go back");
      drawflag = 0;
    }
                                          // Grab a keystroke
		while(!kbhit()) {
			blkput(SET,x-25,y+choice*20,shape[ANIMBASE + 2 + arrowseq[frame++ % 18]]);
			MilliDelay(30);
		}
		menuclicksound(500);
		r = getch();
		if(!r  && kbhit()) r = getch();

		if(r == 27 || toupper(r) == 'Q') flag = 0;
		else if(r == KEY_UP) {                        // Down
			blkput(SET,x-25,y+choice*20,shape[0]);
			choice --;
			if(choice == 9) choice = 2;
			if(choice < 0) choice = 12;
    }
    else if(r == KEY_DOWN) {                  // Up
			blkput(SET,x-25,y+choice*20,shape[0]);
			choice ++;
			if(choice == 3)  choice = 10;
			if(choice > 12) choice = 0;
		}
		else if(r == 13 || r == ' ' ) {       // Choose it!
			switch(choice) {
				case 0:                           // name
					instring[0] = 0;
					getinput(x,y+300,GRAY0+15,0,"Enter player name: ",instring,15);
					strcpy(p->name,instring);
					drawflag = 1;
					break;
				case 1:                           // control type
        	if(p->controltype == 'H') p->controltype = 'C';
          else p->controltype = 'H';
					drawflag = 1;
					break;
      	case 2:                           // Key Controls
        	startkeyboard();
					drwfillbox(SET,0,x,y+300,x+300,y+320);
					print(SET,GRAY0+15,x,y+300,"Key to Move Left:");
					p->pkey[PKEYLEFT] = getscancode();
					drwfillbox(SET,0,x,y+300,x+300,y+320);
					print(SET,GRAY0+15,x,y+300,"Key to Move Right:");
					p->pkey[PKEYRIGHT] = getscancode();
					drwfillbox(SET,0,x,y+300,x+300,y+320);
					print(SET,GRAY0+15,x,y+300,"Key to Move Down:");
					p->pkey[PKEYDOWN] = getscancode();
					drwfillbox(SET,0,x,y+300,x+300,y+320);
					print(SET,GRAY0+15,x,y+300,"Key to Drop:");
					p->pkey[PKEYDROP] = getscancode();
					drwfillbox(SET,0,x,y+300,x+300,y+320);
					print(SET,GRAY0+15,x,y+300,"Key to Rotate Left:");
					p->pkey[PKEYRLEFT] = getscancode();
					drwfillbox(SET,0,x,y+300,x+300,y+320);
					print(SET,GRAY0+15,x,y+300,"Key to Rotate Right:");
					p->pkey[PKEYRRIGHT]= getscancode();
					drwfillbox(SET,0,x,y+300,x+300,y+320);
					print(SET,GRAY0+15,x,y+300,"Key to Change Victim:");
					p->pkey[PKEYVICTIM]= getscancode();
					drwfillbox(SET,0,x,y+300,x+300,y+320);
					print(SET,GRAY0+15,x,y+300,"Key to Use Antedote:");
					p->pkey[PKEYANTEDOTE]= getscancode();
					stopkeyboard();
					drawflag = 1;
					break;
				case 10:                           // Intelligence
					p->computer_smarts++;
					if(p->computer_smarts > 9) p->computer_smarts= 0;
					p->computer_speed = cspeed[p->computer_smarts];
					p->computer_accuracy = caccuracy[p->computer_smarts];
					drawflag = 1;
					break;
				case 11:                          // Delete
					farfree(person[num]);
					person[num] = NULL;
					flag = 0;
					break;
				case 12:                          // Done
					flag = 0;
					break;
				default: break;
			}
		}
	}

}

