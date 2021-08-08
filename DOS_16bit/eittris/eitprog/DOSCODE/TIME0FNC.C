#include "vatfree.h"
#include "svgacc.h"
#include <stdio.h>
#include <stdlib.h>


DWORD eitclock=0;
long int integritycount = 0;
int integritytest = FALSE;


/**************************************************************************
	void eittimer(void)

	DESCRIPTION:  Timer0 function for game speed and integrity checks

**************************************************************************/
void eittimer(void)
{
	eitclock ++;

	if(integritytest) {
		integritycount++;
		if(integritycount > 3000) {   // 3 seconds til something is wrong
			restext();                  // go to text mode
																	// alert user
			printf(
			"\nZOINKS!  The Sound Blaster Routines are failing in a big way.\n"
			"Read the file TROUBLE.TXT for help in correcting the problem.\n"
			"\n"
			"The system may be unstable at this point, so you should probably\n"
			"shut down and restart before attempting to run EITTris again.\n"
			"\n");
			RemoveTimer0();							// remove timer
			DropDeadVarmint();          // remove SB stuff
			SBCleanUp();
			exit(1);
		}
	}
	else integritycount = 0;


}
