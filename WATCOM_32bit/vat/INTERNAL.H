#ifndef _INTERNAL_H
#define _INTERNAL_H


#define VMALLOC        malloc
#define VFREE          free
#define VINPORTB(X)    inp(X)
#define VOUTPORTB(X,Y) outp(X,Y)

#define ARRAYTYPE unsigned int


#define MAXSOUNDS        16       // max number of Waves playing at once
#define MAXVOICETOKENS   64       // max number of Voices queued at once
#define MAXSOUNDTOKENS   256       // max number of Waves queued at once
																	 // (includes chained sounds)
#define MAXSTOREDVOICES  256       // max number of handled Midi voices

#define MAXCHUNKSIZE 1000000L     // max size of Wave before VAT will split
                                   // it up into linked chunks


#endif

