#include <conio.h>
#include "..\gug.h"

int GUGVSync(void)
{
	int loop = 0;

  while(!(inp(0x3da)&0x08))
	{
		loop++;
  };                                // Wait for retrace to start

	while((inp(0x3da)&0x08));         // Wait for retrace to finish

  return(loop);
}
