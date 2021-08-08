/*
** return a pcx header
*/

#include <conio.h>
#include <io.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys\stat.h>

#include "../gug_pcx.h"

PCXHEAD *GUGGetPCXHeader(char *file)
{
  FILE *in;
  PCXHEAD *pcxheader;

  /* does the file exist? */
  if (access (file, 0))
    return(NULL);

  /* were we able to open the file? */
  if (!(in = fopen (file, "rb")))
    return(NULL);

  if (!(pcxheader = (PCXHEAD *)malloc (sizeof (PCXHEAD)))) {
    fclose (in);
    return(NULL);
  }

  /* read in the header */
  fread ((char *)pcxheader, sizeof (PCXHEAD), 1, in);

  fclose (in);
  return (pcxheader);
}
