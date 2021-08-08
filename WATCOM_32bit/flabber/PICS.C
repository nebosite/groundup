/********************************************************************

	FLABBERGASTED!

	Eric Jorgensen 1997

	Sounds.c

	Sound access routines

*********************************************************************/

#include <stdio.h>
#include "flabber.h"
#include "\watcom\gug\lib1\gug.h"
// pics and sprites
#include "pics\flabbig.h"
#include "pics\flabsm.h"
#include "pics\urd.h"
#include "pics\mc_sqare.h"
#include "pics\mc_circl.h"
#include "pics\mc_slash.h"
#include "pics\mc_slant.h"
#include "pics\mc_spray.h"
#include "pics\mc_X.h"
#include "pics\mc_plus.h"
#include "pics\mc_fill.h"
#include "pics\easthead.h"


RasterBlock *flabbersprite[50];



/**************************************************************************
	void drawwatermark(void)

	DESCRIPTION:

**************************************************************************/
void drawwatermark(void)
{
#ifdef DEMOVERSION
	GUGBlockGet(0,maxy-20,maxx-1,maxy-1,grbTemp[0]);
	GUGPutFGSprite(5,maxy-18,(char *)flabbersprite[9]);
	GUGPutFGSprite(flabbersprite[9]->width + 15,maxy-18,(char *)flabbersprite[10]);
#endif

}

/**************************************************************************
	void drawwatermark(void)

	DESCRIPTION:

**************************************************************************/
void erasewatermark(void)
{
#ifdef DEMOVERSION
	GUGPutBGSprite(0,maxy-20,(char *)grbTemp[0]);
#endif

}



/**************************************************************************
	void loadsounds(void)

	DESCRIPTION: Loads all sounds needed for flabbergasted

**************************************************************************/
void loadsprites(void)
{

	printf("Loading Sprites\n");

	flabbersprite[0] = (RasterBlock *)flabbig_0;
	flabbersprite[1] = (RasterBlock *)mc_sqare_0;
	flabbersprite[2] = (RasterBlock *)mc_circl_0;
	flabbersprite[3] = (RasterBlock *)mc_slash_0;
	flabbersprite[4] = (RasterBlock *)mc_slant_0;
	flabbersprite[5] = (RasterBlock *)mc_spray_0;
	flabbersprite[6] = (RasterBlock *)mc_x_0;
	flabbersprite[7] = (RasterBlock *)mc_plus_0;
	flabbersprite[8] = (RasterBlock *)mc_fill_0;
	flabbersprite[9] = (RasterBlock *)flabsm_0;
	flabbersprite[10] = (RasterBlock *)urd_0;
	flabbersprite[11] = (RasterBlock *)easthead_0;
}



