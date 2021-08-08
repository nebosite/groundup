#include <stdio.h>

#include <io.h>
#include <fcntl.h>
#include <sys\stat.h>

int GUGSavePalette(char *fname,char *pal) {
  int handle;  

  if ((handle = open(fname,
                     O_CREAT | O_WRONLY | O_BINARY | O_TRUNC,
                     S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP)) == -1) {
	 return(-1);
  }

  if (write(handle,pal,768) != 768) {
	 close(handle);
	 return(-2);
  }

  close(handle);
  return(1);

}
