#include <conio.h>

extern int GUG_KBD_Installed;
extern int  GUGKeyHit(void);
extern char GUGGetKey(void);

void GUGWaitForKey(void)
{
    if (GUG_KBD_Installed)
	{
      while(!GUGKeyHit());
      GUGGetKey();
	}
	else
	{
	  do {} while (!kbhit());
	  getch();
	}
}


