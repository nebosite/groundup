#include <stdio.h>
#include <io.h>
#include <fcntl.h>
#include <sys\stat.h>
#include <sys\types.h>
 
int GUGSpriteSize(char *);

int GUGSaveSprite(char *fname,char *sprites[],int count) {
  int handle;
  int size,sprite;
               // 01234567890123456789012345678901234
  char ftype[] = "GROUND UP sprite file 1.00         ";
  ftype[32] = (char)10;
  ftype[33] = (char)13;
  ftype[34] = (char)26;

  if ((handle = open(fname, 
                     O_CREAT | O_WRONLY | O_TRUNC | O_BINARY,
                     S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP)) == -1) {
	 return(-1);
  }

  if (write(handle,(char *)ftype,35) != 35) {
     close(handle);
	 return(-3);
  }

  if (write(handle,(char *)&count,2) != 2) {
	 close(handle);
	 return(-3);
  }

  for (sprite=0; sprite<=count; ++sprite) {
	 size = GUGSpriteSize(sprites[sprite]);
//	 printf("sprite %d is %d bytes\n",sprite,size);
	 if (write(handle,(char *)&size,2) != 2) {
		close(handle);
		return(-4);
	 }
	 if (write(handle,sprites[sprite],size) != size) {
		 close(handle);
		 return(-2);
	 }
  }

  close(handle);
  return(1);
}

