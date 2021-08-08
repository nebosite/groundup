#include <io.h>
#include <fcntl.h>
#include <sys\stat.h>

int GUGLoadPalette(char *fname,char *pal) {
  int handle;  

  if ((handle = open(fname,O_RDONLY | O_BINARY)) == -1) {
	 return(-1);
  }

  if (read(handle,pal,768) != 768) {
	 close(handle);
	 return(-2);
  }

  close(handle);
  return(1);

}
