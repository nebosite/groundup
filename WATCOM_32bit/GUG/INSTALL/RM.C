#include <stdio.h>
#include <dos.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <ctype.h>
#include <malloc.h>

void GUGRealFree(unsigned short handle);
void *GUGRealMalloc(unsigned int size,unsigned short* handle);

//
//  unsigned short realhandle;
//  char *buffer;
//  buffer = (char *)real_malloc(dma_bufferlen*2+5,&realhandle);
//  real_free(realhandle);
//

/************************************************************************
  void *GUGRea;Malloc(unsigned short size,int* handle)

  description:this function allocates memory from the low 640k
              at this point no error checking is done to verify it works
*************************************************************************/

void *GUGRealMalloc(unsigned int size,unsigned short* handle)
{
  union REGS dos;

  dos.x.eax=0x100;  //function in dpmi to allocate real memory
  dos.x.ebx=(size+15)>>4; //change it to 16 byte block

  int386(0x31,&dos,&dos);
   //ax holds segment
   //dx holds base selector of allocated block

  if (dos.x.cflag)
     return(NULL);

  *handle=dos.w.dx;
  return((void*)((dos.x.eax &0xffff)<<4));
  //change segement to a protected mode pointer
}

/*************************************************************************
  void GUGRealFree(int handle)

  description: this function frees up memory allocated by
               the real malloc function.
**************************************************************************/

void GUGRealFree(unsigned short handle)
{
  union REGS dos;
  dos.w.ax=0x101;
  dos.w.dx=handle;
  int386(0x31,&dos,&dos);
}
