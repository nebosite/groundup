/**************************************************************************
	RPLAYER.C

**************************************************************************/
#include "tetris.h"

extern int cspeed[];
extern int caccuracy[];


/**************************************************************************
	void readplayerconfig(void)

	DESCRIPTION:  Reads in the player configuration.

**************************************************************************/
void readplayerconfig(void)
{
	FILE *input;
  PLAYER *p;
  int j;
  char string[255],string2[255];

  input = fopen(playerfile,"r");      // Read in player setup
  if(input) {
    j = 0;
    p = NULL;
    while(fgets(string,255,input)) {
      if(strstr(string,"PLAYER")) {
      	sscanf(string,"%s %d",string2,&j);
        if(!person[j]) {
					person[j] = newplayer(j);      // Make a new player
				}
        p = person[j];
      }
      else if(p && strstr(string,"NAME")) {
      	string[strlen(string)-1] = 0;  // Cut off carraige return
        strcpy(p->name,&string[5]);
      }
      else if(p && strstr(string,"CONTROLTYPE")) {
      	sscanf(string,"%s %c",string2,&p->controltype);
      }
      else if(p && strstr(string,"KEYS")) {
				sscanf(string,"%s %X %X %X %X %X %X %X %X",string2,
							 &p->pkey[PKEYLEFT],&p->pkey[PKEYRIGHT],&p->pkey[PKEYDOWN],
							 &p->pkey[PKEYDROP],&p->pkey[PKEYRLEFT],&p->pkey[PKEYRRIGHT],
							 &p->pkey[PKEYVICTIM],&p->pkey[PKEYANTEDOTE]);
      }
			else if(p && strstr(string,"SMARTS")) {
				sscanf(string,"%s %d",string2,&p->computer_smarts);
				if(p->computer_smarts <0) p->computer_smarts = 0;
				if(p->computer_smarts >9) p->computer_smarts = 9;
				p->computer_speed = cspeed[p->computer_smarts];
				p->computer_accuracy = caccuracy[p->computer_smarts];
			}
      else if(p && strstr(string,"ACCURACY")) {
      	sscanf(string,"%s %d",string2,&p->computer_accuracy);
      }
    }
    fclose(input);
  }
}
