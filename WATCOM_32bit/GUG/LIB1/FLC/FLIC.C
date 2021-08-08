#include <io.h>
#include <fcntl.h>
#include <malloc.h>
#include <dos.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include "..\flic.h"
#include "..\vga\mode.h"

extern char *VGA_START;    // Points into the double buffer
extern char *VGA_POINTER;  // Points into the VGA Memory

//*************** DEFINES ***************//
#define fli_magic       0xAF11
#define flc_magic       0xaf12
#define prefix_id       0xf100
#define frame_magic     0xF1Fa

#define FLI_COLOR256    4
#define FLI_SS2         7
#define FLI_COLOR       11
#define FLI_LC          12
#define FLI_BLACK       13
#define FLI_BRUN        15
#define FLI_COPY        16
#define FLI_PSTAMP      18

//*************** VARIABLES ***************//
unsigned char *fli_pal;
int fli_use_pal = 1;

//*************** STRUCTURES ***************//
#pragma pack(1);
// fli file header, have to use byte structure packing
typedef struct fli_header_typ {
  unsigned long size;
  unsigned short int magic;
  unsigned short int frames;
  unsigned short int width;
  unsigned short int height;
  unsigned short int depth;
  unsigned short int flags;
  unsigned short int speed;
  unsigned long    next;
  unsigned long    frit;
  char    reserved[102];
} fli_header, *fli_header_ptr;

typedef struct flc_header_typ {
  unsigned long size;
  unsigned short int magic;
  unsigned short int frames;
  unsigned short int width;
  unsigned short int height;
  unsigned short int depth;
  unsigned short int flags;
  unsigned long speed;
  char reserved0[2];
  long created;
  char creator[4];
  long updated;
  char updater[4];
  short int aspectx;
  short int aspecty;
  char reserved1[38];
  long oframe1;
  long oframe2;
  char reserved[40];
} flc_header, *flc_header_ptr;

typedef struct frame_header_typ {
  unsigned long size;
  unsigned short int magic;
  unsigned short int chunks;
  char expand[8];
} frame_header, *frame_header_ptr;

typedef struct chunk_header_typ {
  unsigned long size;
  unsigned short int type;
} chunk_header, *chunk_header_ptr;
#pragma pack(); //use the default packing method

//*************** FUNCTIONS ***************//
GUG_fli_ptr GUGLoadFLI(char *filename, enum fli_source playtype) {
  short int handle;
  GUG_fli_ptr ptr; 
  char *ptr1;
  fli_header header;
  frame_header pfix;
  flc_header_ptr flc;

  // load the 128 byte fli/flc header
  if ((handle = open (filename,O_RDONLY | O_BINARY))==-1) 
    return NULL;
  read (handle, &header, sizeof (fli_header));
  flc=(flc_header_ptr)&header;
  switch (header.magic) {
  case fli_magic:
    break;
  case flc_magic:
    lseek (handle, flc->oframe1, SEEK_SET);
    break;
  default: 
    close (handle);
    return (NULL);
  }
  if (playtype != FLI_DISK) {
    // try to allocate ram for the entire fli
    if ((ptr=(GUG_fli_ptr)malloc (header.size))==NULL) {
      if (playtype == FLI_RAM) {
        close (handle);
        return NULL;
      }
      playtype = FLI_DISK;
    } else 
      playtype=FLI_RAM;
  }
  // try to allocate ram just for the fli descriptor
  if (playtype == FLI_DISK)
    if ((ptr=(GUG_fli_ptr)malloc (sizeof (fli))) == NULL) {
      close(handle);
      return NULL;
    }
  // initialise the fli descriptor
  if (header.magic == fli_magic) {
    ptr->frames = header.frames;
    ptr->width = header.width;
    ptr->height = header.height;
    ptr->speed = header.speed;
  } else {
    ptr->frames = flc->frames;
    ptr->width = flc->width;
    ptr->height = flc->height;
    ptr->speed = (flc->speed*7/100);
    if (ptr->speed < 1)
      ptr->speed = 1;
  }
  ptr->current = 0;
  ptr->crntoff = (long)sizeof (fli);
  if (playtype == FLI_RAM)
    ptr->handle = 0;
  else 
    ptr->handle = handle;

  if (playtype == FLI_RAM) {
    // load the entire fli into ram
    ptr1 = (char *)ptr + sizeof (fli);
    while (read (handle, ptr1, 32700) == 32700) 
      ptr1 += 32700;
    close (handle);
  }

  // return the pointer to the fli
  return (GUG_fli_ptr)ptr;
}

void flicolor (char *data)
{
  short int i, j, k, change;
  unsigned char current = 0;

  i = *data;
  data += 2;

  if (fli_use_pal) {
    for (j = 0; j < i; j++) {
      current += *data++;
      change = *data++;
      if (!change)
        change = 256;
      outp(0x03c8, current);
      for (k = 0; k < change * 3; k++) 
        outp(0x03c9, *data++);
    }
  } else {
    for (j=0; j<i; j++) {
      current += *data++;
      change = *data++;
      if (!change)
        change = 256;
      for (k = 0; k < change * 3; k++)
        fli_pal[(int)current * 3 + k] = *data++;
    }
  } 
}


// converts from 0 to 255 range to 0 to 63 color range for each r,g,b color
void flicolor256to64 (char *data)
{
  short int i, j, k, change;

  i = *data;
  data += 2;

  for (j = 0; j < i; j++) {
    data++;
    change = *data++;
    if (!change)
      change=256;
    for (k = 0; k < change * 3; k++)
      *(data++) /= 4;
  }
}

void flibrun (char *data, char *dest, short int xsize, short int ysize)
{
  short int i, j, k;
  char ppl, dt, *dest1;
  signed char sc;

  for (i = 0; i < ysize; i++) {
    ppl = *(data++);
    dest1 = dest;
    for (j = 0; j < ppl; j++) {
      sc = *(data++);
      if (sc < 0)
        for(k = 0; k < -sc; k++)
          *(dest++) = *(data++);
        else {  
          dt = *(data++);
          for(k = 0; k < sc; k++)
            *(dest++) = dt;
        }
    }
    dest = dest1 + xsize;
  }
}

void flilc (char *data, char *dest, short int xsize, char *finaldata)
{
  short int j,k,l,m;
  char dt,*dest1;
  signed char sc;
  unsigned char ppl;

  do {
    j = *(short int *)(data);
    data += 2;
    dest += j * xsize;
    m = *(short int *)(data);
    data += 2;
    for (l = 0; l < m; l++) {
      ppl = *(data++);
      dest1 = dest;
      for (j = 0; j < ppl; j++) {
        dest += (char)*(data++);
        sc = *(data++);
        if (sc > 0) 
          for(k = 0; k < sc; k++)
            *(dest++) = *(data++);
          if (sc < 0) {  
            dt = *(data++);
            for(k = 0; k < -sc; k++)
              *(dest++) = dt;
          }
          if (data >= finaldata)
            return;
      }
      dest = dest1 + xsize;
    }
  } while (data < finaldata);
}

void fliss2 (char *data, char *dest, short int xsize)
{
  short int j, k, cl, l, m, p, ppl, ppl1, dt;
  char *dest1;
  signed char sc;

  cl = *(short int *)data;
  data += 2;
  for (l = 0; l < cl; l++) {
    ppl = *(short int *)data;
    data += 2;
    while ((ppl & LINE_SKIP) == LINE_SKIP) {
      dest -= xsize * ppl;
      ppl = *(short int *)data;
      data += 2;
    }

    dest1 = dest;
    ppl1 = ppl;
    if (ppl < 0) {
      ppl1 = *(short int *)data;
      data += 2;
    }

    for (p = 0; p < ppl1; p++) {
      dest += *(data++);
      sc = *(data++);
      if (sc > 0)
        for(k = 0; k < sc; k++) {
          *(short int *)dest = *(short int *)data;
          dest += 2;
          data += 2;
        }
      if (sc < 0) {
        dt = *(short int *)data;
        data += 2;
        for(k = 0; k < -sc; k++) {
          *(short int *)dest = dt;
          dest += 2;
        }
      }
    }

  if (ppl < 0)
    *dest = ppl;
    dest = dest1 + xsize;
  }
}


// I assume this only works in 320x200 animations (fli) and as such
// it assumes there is only 64000 bytes to copy to virtual screen
// and sizex >= 320 and that the destination is contigous
void flicopy (char *src, char *dest, short int sizex)
{
  int i;
    
  for (i = 0; i < 200; i++) {
    memcpy(dest, src, 320);
    dest += sizex;
    src += 320;
  }
}

// well this only work on 320x200 animations but I made it 
// compatible with any size animations
// i never seen this chunk type in any of the anims i tested, so this
// func is untested ...
void fliblack (char *dest, short int sizex, short int xsize, short int ysize)
{
  while (ysize > 0) {
    memset (dest, 0, xsize); 
    dest += sizex;
    ysize--;
  }
}

short int GUGPlayFLIToBuffer(GUG_fli_ptr Pfli)
{
  return(GUGPlayFLI(Pfli,VGA_START));
}

short int GUGPlayFLIToDisplay(GUG_fli_ptr Pfli)
{
  return(GUGPlayFLI(Pfli,VGA_POINTER));
}

short int GUGPlayFLI(GUG_fli_ptr Pfli, char *dest)
{
  frame_header frame1;
  frame_header_ptr frame;
  chunk_header_ptr chunk, chunk1;
  short int i;
  short int sizex = 320;

  if (dest == VGA_START)
    sizex = X_WRAP_SIZE;

  if (Pfli->handle == 0) {
    // if playing from ram, setup pointers for the next frame
    frame = (frame_header *)((char *)Pfli+Pfli->crntoff);
    chunk=(chunk_header *)((char *)frame+sizeof(frame_header));
    Pfli->current++;
  } else {
    // if playing from disk, read the next frame
    read (Pfli->handle, &frame1, sizeof(frame_header));
    frame = &frame1;
    if (frame1.chunks>0) {
       // if there are chunks to load, load em
       if ((chunk = (chunk_header *)malloc \
         (frame1.size - sizeof (frame_header))) == NULL)
         return 1;
       chunk1 = chunk;
       read (Pfli->handle, chunk, frame1.size - sizeof (frame_header));
     }
     Pfli->current++;
     if (Pfli->current == Pfli->frames) {
       Pfli->current = 0;
       if (lseek (Pfli->handle, sizeof (fli_header), SEEK_SET) == -1)
         return 1;
     }
   }

   // play the current frame into the destination buffer
   if (frame->magic == frame_magic)
     for (i = 0; i < frame->chunks; i++) {
        switch (chunk->type) {
        case FLI_COLOR256:
          // this fixes up the color pal and if playing from ram
          // this is done only once
          flicolor256to64 ((char *)chunk + sizeof (chunk_header));
          chunk->type = FLI_COLOR;
          flicolor ((char *)chunk + sizeof (chunk_header));
          break;
        case FLI_SS2:
          fliss2 ((char *)chunk + sizeof (chunk_header), dest, sizex);
          break;
        case FLI_COLOR:
          flicolor ((char *)chunk + sizeof (chunk_header));
          break;
        case FLI_LC:
          flilc ((char *)chunk + sizeof (chunk_header),\
            dest, sizex, (char *)chunk + chunk->size - 1);
          break;
        case FLI_BLACK:
          fliblack (dest, sizex, Pfli->width, Pfli->height);
          break; 
        case FLI_BRUN:
          flibrun ((char *)chunk + sizeof (chunk_header),\
            dest, sizex, Pfli->height);
          break;
        case FLI_COPY:
             flicopy ((char *)chunk + sizeof (chunk_header), dest, sizex);
        break; 
        case FLI_PSTAMP:
          break; // ignore the stamps
        default:
          // undefined chunk type, ignore it
          break;
        }

        chunk = (chunk_header *)((char *)chunk + chunk->size);
      }

    // if playing from the disk, free the previous frame data
    if (Pfli->handle != 0) {
      if (!frame1.chunks) 
        free(chunk1);
    } else {
      if (Pfli->current > Pfli->frames) {
        Pfli->current = 1;
        Pfli->crntoff = (long)sizeof (fli);
        frame = (frame_header *)((char *)Pfli + Pfli->crntoff);
      } 
      Pfli->crntoff += frame->size;
    }
  return 0;
}

void GUGCloseFLI(GUG_fli_ptr Pfli)
{
  if (Pfli->handle != 0) 
    close(Pfli->handle);
  free(Pfli);
}

