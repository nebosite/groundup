#include <stdio.h>
#include <io.h>
#include <fcntl.h>
#include <sys\stat.h>
#include <stdlib.h>

int GUGLoadSprite(char *fname,char *sprites[]) {
  int handle;
  char  size_buf[8];
  int x,y,size,sprite,max,type,bytes;

  if ((handle = open(fname, O_RDONLY | O_BINARY)) == -1) {
	 return(-1);
  }

  sprite = 0;

  // How many sprites were stored in the file
  if (read(handle,size_buf,2) != 2) {
	 close(handle);
	 return(-2);
  }
  if ((size_buf[0] == 'G') && (size_buf[1] == 'R'))
  {
//    printf("new format\n");
//    do {} while (!(kbhit()));
//	getch();
    lseek(handle,35,SEEK_SET);
    if (read(handle,size_buf,2) != 2) {
	   close(handle);
	   return(-2);
    }
  }
  max  = size_buf[0];   // number of sprites in file
  type = size_buf[1];	// sprite storage type

  while ((!eof(handle)) && (sprite <= max)) {

	 if (read(handle,size_buf,2) != 2) {
		 close(handle);
		 return(-2);
	 }

	 bytes  = size_buf[0];
     bytes += size_buf[1]*256;

      // malloc() space st store the sprite
	  if ((sprites[sprite] = (char *)malloc(bytes)) == NULL)
	  {
	    close(handle);
	    return(-3);
	  }
      // and load it into the malloc()ed space
	  if (read(handle,sprites[sprite],bytes) != bytes) {
	  	close(handle);
	  	return(-4);
	  }

	 sprite++;
  }

  close(handle);
  return(sprite);
}
