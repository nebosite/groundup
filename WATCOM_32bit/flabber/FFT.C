// FFT routines for flabbergasted

#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <math.h>
#include <malloc.h>
#include <mem.h>
#include "flabber.h"
#include "\watcom\gug\lib1\gug.h"
#include "\watcom\gug\lib1\colors.h"
#include "\watcom\gug\lib1\keydefs.h"
#include "\watcom\vat\vat.h"
#include "util.h"

#define ASIZE 1050
#define TRUE  1
#define FALSE 0

#define  DDC_PI  (3.14159265358979323846)


#define BITS_PER_WORD   (sizeof(unsigned) * 8)
#define CHECKPOINTER(p)  CheckPointer(p,#p)

void player(char *musicfile);
void channelbits(void);

//extern DWORD dma_bufferlen;         // Handles to Vat mix buffer
//extern BYTE  *dma_buffer[2];

BYTE 				bigbuffer[BIGBUFFERSIZE];        // Big buffer to hold long segment of sound
double 			outdata[ASIZE],outidata[ASIZE];
char 				grabbuffer[32000];
int 				leftchannel[5000];
int 				rightchannel[5000];
double			lfac[5000];
int 				numsamples=256;
char 				errstring[256];
int 				colorlist[100] =
					 {0 ,33,33,34,34,34,34,35,35,35,
						35,36,36,36,36,37,37,37,37,38,
						38,38,38,39,38,39,39,39,39,39,
						39,39,39, 3, 3, 3, 3, 4, 4, 4,
						 5, 5, 6, 6, 7, 7, 15};
int					colorlistsize = 47;

#ifdef __cplusplus
extern "C" {
#endif

/*
**   fft() computes the Fourier transform or inverse transform
**   of the complex inputs to produce the complex outputs.
**   The number of samples must be a power of two to do the
**   recursive decomposition of the FFT algorithm.
**   See Chapter 12 of "Numerical Recipes in FORTRAN" by
**   Press, Teukolsky, Vetterling, and Flannery,
**   Cambridge University Press.
**
**   Notes:  If you pass ImaginaryIn = NULL, this function will "pretend"
**           that it is an array of all zeroes.  This is convenient for
**           transforming digital samples of real number data without
**           wasting memory.
*/

void fft_double
         ( unsigned NumSamples,         /* must be a power of 2 */
					 signed int *RealIn,              /* array of input's real samples */
					 double *ImaginaryIn,         /* array of input's imag samples */
           double *RealOut,             /* array of output's reals */
					 double *ImaginaryOut );      /* array of output's imaginaries */


int IsPowerOfTwo ( unsigned x );
unsigned NumberOfBitsNeeded ( unsigned PowerOfTwo );
unsigned ReverseBits ( unsigned index, unsigned NumBits );

/*
**   The following function returns an "abstract frequency" of a
**   given index into a buffer with a given number of frequency samples.
**   Multiply return value by sampling rate to get frequency expressed in Hz.
*/
double Index_to_frequency ( unsigned NumSamples, unsigned Index );

#ifdef __cplusplus
}
#endif





/**************************************************************************
	int IsPowerOfTwo ( unsigned x )

	DESCRIPTION:

**************************************************************************/
int IsPowerOfTwo ( unsigned x )
{
   unsigned i, y;

   for ( i=1, y=2; i < BITS_PER_WORD; i++, y<<=1 )
	 {
      if ( x == y ) return TRUE;
   }

   return FALSE;
}



/**************************************************************************
	unsigned NumberOfBitsNeeded ( unsigned PowerOfTwo )

	DESCRIPTION:

**************************************************************************/
unsigned NumberOfBitsNeeded ( unsigned PowerOfTwo )
{
	 unsigned i;

   if ( PowerOfTwo < 2 )
   {
      fprintf ( stderr,
                ">>> Hosed in fftmisc.c: NumberOfBitsNeeded(%d)\n",
                PowerOfTwo );

      exit(1);
   }

   for ( i=0; ; i++ )
   {
      if ( PowerOfTwo & (1 << i) )
			{
         return i;
      }
	 }
}




/**************************************************************************
	unsigned ReverseBits ( unsigned index, unsigned NumBits )

	DESCRIPTION:

**************************************************************************/
unsigned ReverseBits ( unsigned index, unsigned NumBits )
{
   unsigned i, rev;

   for ( i=rev=0; i < NumBits; i++ )
   {
      rev = (rev << 1) | (index & 1);
      index >>= 1;
   }

   return rev;
}



/**************************************************************************
	double Index_to_frequency ( unsigned NumSamples, unsigned Index )

	DESCRIPTION:

**************************************************************************/
double Index_to_frequency ( unsigned NumSamples, unsigned Index )
{
	if ( Index >= NumSamples ) return 0.0;
	else if ( Index <= NumSamples/2 )return (double)Index / (double)NumSamples;
	else return -(double)(NumSamples-Index) / (double)NumSamples;
}


/**************************************************************************
	static void CheckPointer ( void *p, char *name )

	DESCRIPTION:

**************************************************************************/
static void CheckPointer ( void *p, char *name )
{
   if ( p == NULL )
   {
      fprintf ( stderr, "Error in fft_double():  %s == NULL\n", name );
      exit(1);
   }
}



/**************************************************************************
	void fft_double ( unsigned NumSamples,

	DESCRIPTION:

**************************************************************************/
void fft_double ( unsigned int NumSamples,
									signed int *RealIn,
									double *ImagIn,
                  double *RealOut,
                  double *ImagOut )
{
	 unsigned int NumBits;    /* Number of bits needed to store indices */
	 unsigned int i, j, k, n;
	 unsigned int BlockSize, BlockEnd;

	 double angle_numerator = 2.0 * DDC_PI;
   double delta_angle;
   double alpha, beta;  /* used in recurrence relation */
   double delta_ar;
   double tr, ti;     /* temp real, temp imaginary */
   double ar, ai;     /* angle vector real, angle vector imaginary */

	 ImagIn = ImagIn;

	 if ( !IsPowerOfTwo(NumSamples) )
   {
//      fprintf ( stderr,"Error in fft():  NumSamples=%u is not power of two\n",NumSamples );
//      exit(1);
			return;
   }


//	 CHECKPOINTER ( RealIn );
//   CHECKPOINTER ( RealOut );
//	 CHECKPOINTER ( ImagOut );

   NumBits = NumberOfBitsNeeded ( NumSamples );

   /*
   **   Do simultaneous data copy and bit-reversal ordering into outputs...
   */

   for ( i=0; i < NumSamples; i++ )
   {
			j = ReverseBits ( i, NumBits );

			RealOut[j] = RealIn[i];
			ImagOut[j] = 0.0;
	 }

	 /*
	 **   Do the FFT itself...
	 */

	 BlockEnd = 1;
	 for ( BlockSize = 2; BlockSize <= NumSamples; BlockSize <<= 1 )
	 {
			delta_angle = angle_numerator / (double)BlockSize;
			alpha = sin ( 0.5 * delta_angle );
			alpha = 2.0 * alpha * alpha;
			beta = sin ( delta_angle );


			for ( i=0; i < NumSamples; i += BlockSize )
			{
				 ar = 1.0;   // cos(0)
				 ai = 0.0;   // sin(0)

				 for ( j=i, n=0; n < BlockEnd; j++, n++ )
				 {
						k = j + BlockEnd;
						tr = ar*RealOut[k] - ai*ImagOut[k];
						ti = ar*ImagOut[k] + ai*RealOut[k];


						RealOut[k] = RealOut[j] - tr;
						ImagOut[k] = ImagOut[j] - ti;

						RealOut[j] += tr;
						ImagOut[j] += ti;

						delta_ar = alpha*ar + beta*ai;
						ai -= (alpha*ai - beta*ar);
						ar -= delta_ar;
				 }
			}

			BlockEnd = BlockSize;
	 }

}


void testfft(void)
{
	int testarray[256];

	fft_double ( numsamples,testarray,NULL,outdata,outidata);

}

/**************************************************************************
	void dofft(int *inarray)

	DESCRIPTION:  No brainer FFT.  Calculate FFT on input array and
		returns it in the same array.

	INPUT
		inarray			Pointer to _SIGNED_ array of integers (sample data).
								Must be at least 256 integers of data.
								FFT is returned back in integers 1-127 in the range
								of 0-100.

**************************************************************************/
void dofft(int *inarray)
{
	int i,n;
	int smoothfactor = 0.5;
	int max = 99;

	fft_double ( numsamples,inarray,NULL,outdata,outidata);

	for(i = 1; i < numsamples/2; i++) {

													 // This takes the real and imaginary

													 // data and calculates a magnitude
		n = (outdata[i]*outdata[i] + outidata[i]* outidata[i])/4000;
		inarray[i] = QuickSqrt(n)*2;// /lfac[i];
		if(inarray[i] > max) inarray[i] = max;



													 // Perform time smoothing.
													 // Time smoothing seems to make the FFT
													 // look prettier.  The
													 // smoothing coefficient should run from
													 // 0 to 1.0: 0 = no smoothing, 1.0 =
													 // extreme smoothing.

//		inarray[i] *= smoothfactor;
//		inarray[i] += outdata[i]*(1.0-smoothfactor);
	}


}

/**************************************************************************
	int animation8(int signal)


	DESCRIPTION: Does a time-varying fft


**************************************************************************/
int animation8(int signal)
{
	WORD skip;                          // #bytes to skip in dma buffer
	int width = 128, height = 50;       // window sizes
	int rawy = 145, ffty = 90;          // y value for frame location
	static DWORD vt=0;                  // vclock timer varaible
	static int shortpos;							// Tracks fft rate
	double xcon;                        // X axis conversion varaible
	int i,j,k;                          // counter
	char r= ' ';                        // user input holder
	int animateraw = 1;                 // Animation toggle holder
	int animatefft = 1;                 // Animation toggle holder
	int animatetimefft = 1;             // Animation toggle holder
	int animatebits = 0;                // Animation toggle holder
	static int x;                  			// x value for fft time display
	double hfac;                     		// used for raw data drawing
	int ix;
	int index;

	if(signal == signal_start) {
		x= 0;
		vt = 0;
		shortpos = 0;
		for(i = 0; i < numsamples; i++) {
													 // lfac is a correction factor I use
													 // because the FFT signal is really strong
													 // and noisy in the low frequency region.
													 // This factor chops the low frequency
													 // signals and allows the higher frequency
													 // signals to stand out.
			if(i == 0 ) lfac[i] = 1.0;
			else lfac[i] = (numsamples/.01)/(i/(numsamples/16.0)+0.6)+(numsamples);
		}
		return 0;
	}


																		// =========== Prepare varaibles

																		// skip = Number of bytes to skip
																		// while gathering data drom DSP buffer.
																		// High skip values will tend to wash
																		// out low frequency signals, and low
																		// skip values will clip high frequency
																		// signals.  samplerate/skip will give
																		// you the fft max frequency.
	skip = SampleRate()/2812.0 + 0.5;
	skip = 8;
																		// Main loop.


	if(vt != vclock) {              // has vat mixed a new 1/2 buffer?
		vt = vclock;
																	// Grab next bytes

															// Copy Data
		shortpos = longbufferpointer;
		for(i = 0; i < numsamples; i++) {
			leftchannel[i]  = bigbuffer[shortpos % longbuffersize]-127;
			rightchannel[i] = bigbuffer[shortpos % longbuffersize+1]-127;
			shortpos -= skip *2;
			if(shortpos < 0) shortpos += longbuffersize;
		}

																// Draw things!
		if(animateraw) {
																// Show raw sample data
			xcon = (double)width/numsamples;
			GUGDrawFillRectangle(SET,2,5,rawy,5+ width,rawy+height);
			GUGDrawRectangle(SET,7,5,rawy,5+ width,rawy+height);
			GUGDrawFillRectangle(SET,2,165,rawy,165+ width,rawy+height);
			GUGDrawRectangle(SET,7,165,rawy,165+ width,rawy+height);
			hfac = height/256.0;
			shortpos = longbufferpointer;
			for(i = 0 ; i < width-1; i++) {
				GUGDrawPoint(SET,	5,6+i,(bigbuffer[shortpos % longbuffersize]-127)* hfac +int(rawy+height/2));
				GUGDrawPoint(SET,	5,166+i,(bigbuffer[shortpos % longbuffersize+1]-127)* hfac +int(rawy+height/2));
				shortpos -=6;
				if(shortpos < 0) shortpos += longbuffersize;
			}
		}
																// Do the transform
		if(animatefft || animatetimefft) {


			dofft(leftchannel);
			dofft(rightchannel);

		}
															 // Animate bar graph fft
		if(animatefft) {
			xcon = (double)width/(numsamples/2.0);

																// Show FFT graphicly
			GUGDrawFillRectangle(SET,0,5,ffty,5+ width,ffty+height);
			GUGDrawRectangle(SET,15,5,ffty,5+ width,ffty+height);
			GUGDrawFillRectangle(SET,0,165,ffty,165+ width,ffty+height);
			GUGDrawRectangle(SET,15,165,ffty,165+ width,ffty+height);

			for(i = 1; i <width-1; i++) {
				ix = i+6;
				k = leftchannel[i]/2;
				for(j = 0 ; j < k; j++) {
					GUGDrawPoint(SET,colorlist[(j*colorlistsize)/50],ix,ffty+height-j-1);
				}
				ix = 166+i;
				k = rightchannel[i]/2;
				for(j = 0 ; j < k; j++) {
					GUGDrawPoint(SET,colorlist[(j*colorlistsize)/50],ix,ffty+height-j-1);
				}
			}
		}

															 // Animate chromatic time-varying fft
		if(animatetimefft) {

			GUGDrawRectangle(SET,31,5,5,5+width,ffty-5);
			GUGDrawRectangle(SET,31,165,5,165+width,ffty-5);

			GUGBlockGet(6,7,5+width-1,ffty-5-1,(RasterBlock *)grabbuffer);
			GUGPutBGSprite(6,6,(char *)grabbuffer);

			GUGBlockGet(166,7,165+width-1,ffty-5-1,(RasterBlock *)grabbuffer);
			GUGPutBGSprite(166,6,(char *)grabbuffer);

			for(i = 1; i < width; i++) {
				index = (leftchannel[i]*colorlistsize)/100;
				if(index < 0) index = 0;
				if(index >= colorlistsize) index = colorlistsize-1;
				GUGDrawPoint(SET,colorlist[index],i+5,ffty-6);
				index = (rightchannel[i]*colorlistsize)/100;
				if(index < 0) index = 0;
				if(index >= colorlistsize) index = colorlistsize-1;
				GUGDrawPoint(SET,colorlist[index],i+165,ffty-6);
			}
		}

		if(animatebits) {
			channelbits();           // Do that nifty bit thing

		}
		shortpos = 0;

	}
	return 0;
}


/**************************************************************************
	int autobrush1(int signal)


	DESCRIPTION: Simple FFT brush


**************************************************************************/
int autobrush1(int signal)
{
	WORD skip;                          // #bytes to skip in dma buffer
	static DWORD vt=0;                  // vclock timer varaible
	static int shortpos;							// Tracks fft rate
	int i;                          // counter
	char r= ' ';                        // user input holder
	static int localnumsamples;
	static int x[4] = {0,160,160,319},y[4] = {100,100,100,100};
	static int xm[4],ym[4];
	int rx,ry;
	int color;
	double t;

	if(signal == signal_start) {
		for(i = 0; i < 4; i++) {
			xm[i] = random(5)+1;
			if(random(2)) xm[i] = -xm[i];
			ym[i] = random(5)+1;
			if(random(2)) ym[i] = -ym[i];
		}

		localnumsamples = 64;
		vt = 0;
		shortpos = 0;
		for(i = 0; i < numsamples; i++) {
													 // lfac is a correction factor I use
													 // because the FFT signal is really strong
													 // and noisy in the low frequency region.
													 // This factor chops the low frequency
													 // signals and allows the higher frequency
													 // signals to stand out.
			if(i == 0 ) lfac[i] = 1.0;
			else lfac[i] = (numsamples/.01)/(i/(numsamples/16.0)+0.6)+(numsamples);
		}
		return 0;
	}


																		// =========== Prepare varaibles

																		// skip = Number of bytes to skip
																		// while gathering data drom DSP buffer.
																		// High skip values will tend to wash
																		// out low frequency signals, and low
																		// skip values will clip high frequency
																		// signals.  samplerate/skip will give
																		// you the fft max frequency.
	skip = SampleRate()/2812.0 + 0.5;
	skip = 2;


																		// Main loop.


	if(vt != vclock) {              // has vat mixed a new 1/2 buffer?
		vt = vclock;
																	// Grab next bytes



															// Copy Data
		shortpos = longbufferpointer;
		for(i = 0; i < localnumsamples; i++) {
			leftchannel[i]  = bigbuffer[shortpos % longbuffersize]-127;
			rightchannel[i] = bigbuffer[shortpos % longbuffersize+1]-127;
			shortpos -= skip *2;
			if(shortpos < 0) shortpos += longbuffersize;
		}

																// Do the transform
		dofft(leftchannel);
		dofft(rightchannel);

															 // Animate chromatic time-varying fft
		for(i = 1; i < localnumsamples/2; i++) {
			t = (double)i/(localnumsamples/2.0);

			leftchannel[i] *= 3;
			if(leftchannel[i] > 99) leftchannel[i] = 99;

			color = (leftchannel[i] * 16)/100 + (giWorkingColor/16)*16;
			rx = x[0] + (x[1]-x[0])* t;
			ry = y[0] + (y[1]-y[0])* t;
			if(leftchannel[i] > 8) GUGDrawFillCircle(SET,color,rx,ry,3);

			rightchannel[i] *= 3;
			if(rightchannel[i] > 99) rightchannel[i] = 99;

			color = (rightchannel[i] * 16)/100 + (giWorkingColor/16)*16;
			rx = x[2] + (x[3]-x[2])* t;
			ry = y[2] + (y[3]-y[2])* t;
			if(rightchannel[i] > 8)GUGDrawFillCircle(SET,color,rx,ry,3);
		}

		for(i = 0; i < 4; i++) {
			x[i] += xm[i];
			if(x[i] < 0) {
				xm[i] = random(5)+1;
				x[i] = 0;
//				ym[i] = random(5)+1;
//				if(random(2)) ym[i] = -ym[i];
			}
			if(x[i] >= maxx) {
				xm[i] = -(random(5)+1);
				x[i] = maxx;
//				ym[i] = random(5)+1;
//				if(random(2)) ym[i] = -ym[i];
			}

			y[i] += ym[i];
			if(y[i] < 0) {
				ym[i] = random(5)+1;
				y[i] = 0;
//				xm[i] = random(5)+1;
//				if(random(2)) xm[i] = -xm[i];
			}
			if(y[i] >= maxy) {
				ym[i] = -(random(5)+1);
				y[i] = maxy;
//				xm[i] = random(5)+1;
//				if(random(2)) xm[i] = -xm[i];
			}
//			print(SET,7,0,0,i*12,"%d,%d %d,%d    ",x[i],y[i],xm[i],ym[i]);
		}

//		GUGDrawLine(SET,7,x[0],y[0],x[1],y[1]);
//		GUGDrawLine(SET,15,x[2],y[2],x[3],y[3]);



		shortpos = 0;
	}
	return 0;
}

/**************************************************************************
	int autobrush2(int signal)


	DESCRIPTION: Polar Coordinate Wave form brush

**************************************************************************/
int autobrush2(int signal)
{
	static double x=160,y=100,xx,yy;
	static double xm,ym;
	static int c = 63;
	static int coloroff = 0;
	int shortpos;
	int r,i;

	coloroff++;
	if(coloroff > 15) coloroff = 0;
																		// Handle cycling colors

	if(signal == signal_start) {
		c = giWorkingColor;
		xm = (random(200)+21)/100.0;
		if(random(2)) xm = -xm;
		ym = (random(200)+21)/100.0;
		if(random(2)) ym = -ym;

		return 0;
	}
	if (c >= 64) c = (int)(c/16)*16 + coloroff;

	shortpos=longbufferpointer;
	for(i = 0; i < 360; i++) {
		r = bigbuffer[shortpos % longbuffersize]/2-64;
		xx = x + r * getcos(i);
		yy = y + r * getsin(i);
		if(r) GUGDrawPoint(SET,c,xx,yy);
		r = bigbuffer[shortpos % longbuffersize+1]/2-64;
		xx = x + r * getcos(i);
		yy = y + r * getsin(i);
		if(r) GUGDrawPoint(SET,c,maxx-xx,maxy-yy);

		shortpos-= 2;
		if(shortpos < 0) shortpos += longbuffersize;
	}

	x += xm;
	if(x < 0 || x > maxx) xm = -xm;
	y += ym;
	if(y< 0 || y > maxy) ym = -ym;

	return 0;
}

/**************************************************************************
	void channelbits(void)

	DESCRIPTION: This shows all of the bits used in a channel structure.

**************************************************************************/
void channelbits(void)
{
	int size;
	int height,width;
	CHANNEL *chan;
	int i,j,b,color;
	WORD *wd,val;
																			// Grab the right channels
	if(ModStatus() == v_started) {
		chan = ModChannels();
	}
	else if(S3MStatus() == v_started) {
		chan = S3MChannels();

  }

	size = sizeof(CHANNEL);             // Get number of cytes in channel struct
	height = size/2+1;                  // Figure window height
	width = 36;                         // Enough width for 16 bits

																			// Draw first 4 channels
	for( i = 0; i < 4; i++) {

		wd = (WORD *)(&chan[i]);          // get start address of channel
																			// Draw a frame
		GUGDrawRectangle(SET,8,i*(width+5)+120,10,i*(width+5)+120+width,10+height);

																			// loop down channel by words
		for(j = 0; j < size/2; j++) {
			val = *wd;                      // grab a word
			wd++;                           // move to next word
																			// clear this line
			GUGDrawLine(SET,8,i*(width+5)+120,11+j,i*(width+5)+120+width,11+j);
																			// draw bits in this word
			for(b = 0; b < 16; b++) {
				color = (val & 0x01) *14;
				if(!color) color = 6;
				GUGDrawPoint(SET,color,i*(width+5)+122+b*2,11+j);
				val >>= 1;
			}
		}
	}

}
