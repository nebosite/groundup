/*============================================================================

       fftmisc.c  -  Don Cross <dcross@intersrv.com>

       http://www.intersrv.com/~dcross/fft.html

       Helper routines for Fast Fourier Transform implementation.
       Contains common code for fft_float() and fft_double().

       See also:
           fourierf.c
           fourierd.c
           ..\include\fourier.h

============================================================================*/

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "fourier.h"

#define TRUE  1
#define FALSE 0

#define BITS_PER_WORD   (sizeof(unsigned) * 8)


int IsPowerOfTwo ( unsigned x )
{
   unsigned i, y;

   for ( i=1, y=2; i < BITS_PER_WORD; i++, y<<=1 )
   {
      if ( x == y ) return TRUE;
   }

   return FALSE;
}


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


double Index_to_frequency ( unsigned NumSamples, unsigned Index )
{
   if ( Index >= NumSamples )
   {
      return 0.0;
   }
   else if ( Index <= NumSamples/2 )
   {
      return (double)Index / (double)NumSamples;
   }
   else
   {
      return -(double)(NumSamples-Index) / (double)NumSamples;
   }
}


/*--- end of file fftmisc.c---*/
