/**************************************************************************
	PLSETUP.C

**************************************************************************/
#include"tetris.h"

/**************************************************************************
	void playersetup(void)

	DESCRIPTION:  Handles user input for managing the player list

**************************************************************************/
void playersetup(void)
{
	int flag=1,drawflag = 1,i,x,y,opt = 0;
  char string[100],r;
  FILE *output;
  PLAYER *p;

																	// Center coordinates
	x = (maxx-800)/2 + 140;
	y = (maxy-600)/2 + 260;

																	// Main loop
  while(flag) {
    if(drawflag) {                // Draw the player list
			drwfillbox(SET,0,0,y-100,x+380,maxy);     // clear area
																						// Draw labels
			print(SET,BLUE666,x,y,"SLOT");
			print(SET,BLUE666,x+40,y,"PLAYER");
			print(SET,BLUE666,x+160,y,"TYPE");
			drwline(SET,BLUE666,x,y+18,x+230,y+18);
																						// Draw players
      for(i = 0; i < 4; i++) {
				if(person[i]) sprintf(string,"%d)   %s",i+1,person[i]->name);
				else sprintf(string,"%d)  >>EMPTY<<",i+1);
				print(SET,YELLOW666,x,y+i*20+20,string);
				print(SET,YELLOW666,x+160,y+i*20+20,
					person[i]->controltype=='C'?"Computer ":"Human     ");
			}
																						// Other choices
			print(SET,YELLOW666,x,y+100,"Number of rounds: %d",totalrounds);
			print(SET,YELLOW666,x,y+120,"Save player configuration.");
			print(SET,CYAN666,x,y+140,"Done");
			drawflag = 0;
    }

		while(!kbhit()) {
			blkput(SET,x-25,y+opt*20+20,shape[ANIMBASE + 2 + arrowseq[frame++ % 18]]);
			MilliDelay(30);
		}
		menuclicksound(500);

		r = getch();                            // grab a keystroke
		if(!r  && kbhit()) r = getch();

		if(r ==27 || toupper(r) == 'Q') flag = 0;
		else if(r == KEY_UP) {
			blkput(SET,x-25,y+opt*20+20,shape[0]);
			opt--;
			if(opt < 0) opt = 6;
		}
		else if(r == KEY_DOWN) {
			blkput(SET,x-25,y+opt*20+20,shape[0]);
			opt++;
			if(opt > 6) opt = 0;
		}
		else if(r == ' ' || r == 13) {
			switch(opt) {
				case 0:
				case 1:
				case 2:
				case 3:
					defineplayer(opt);
					drawflag = 1;
					break;
				case 4:
					string[0] = 0;
					getinput(x,y+180,GRAY0+15,0,"Enter number of rounds: ",string,11);
					totalrounds = atoi(string);
					drawflag = 1;
					break;
				case 5:                             // Save player config
					output=fopen(playerfile,"w");
					if(output) {
						for(i= 0; i < MAXPLAYERS; i++) {
							if(person[i]) {
								p = person[i];
								fprintf(output,"PLAYER %d\n",i);
								fprintf(output,"NAME %s\n",p->name);
								fprintf(output,"CONTROLTYPE %c\n",p->controltype);
								fprintf(output,"KEYS %X %X %X %X %X %X %X %X\n",
									p->pkey[PKEYLEFT],p->pkey[PKEYRIGHT],p->pkey[PKEYDOWN],
									p->pkey[PKEYDROP],p->pkey[PKEYRLEFT],p->pkey[PKEYRRIGHT],
									p->pkey[PKEYVICTIM],p->pkey[PKEYANTEDOTE]);
								fprintf(output,"SMARTS %d\n",p->computer_smarts);
							}
						}
						fclose(output);
					}
					break;
				case 6:
					flag = 0;
					break;
				default:
					break;
			}
		}
	}

}
