#include <stdio.h>
#include <string.h>

int main (int argc, char *argv[])
{
  FILE *lib;
  int matchlevel=0, count, gridoff=0, gupcoff=0, i, j;
  char c, gridstr[51], gupcstr[51], name[80], serial[80], *mark;

  if (!(lib = fopen ("vat.lib", "rb+"))) {
    printf ("Error opening vat.lib for registration.\n");
    exit (1);
  }

  memset (gridstr, 0, sizeof(gridstr));
  memset (gupcstr, 0, sizeof(gupcstr));

  while (!feof (lib)) {
    c = fgetc (lib);
    switch (matchlevel) {
    case 15:
      gupcstr[count++] = c;
      if (count >= 50)
        matchlevel = 0;
      break;
    case 14:
      if (c == ' ') {
        matchlevel++;
        count = 0;
        gupcoff = ftell (lib);
      } else
        matchlevel = 0;
      break;
    case 13:
      if (c == 'C') {
        matchlevel++;
        count = 0;
      } else
        matchlevel = 0;
      break;
    case 12:
      if (c == 'P')
        matchlevel++;
      else
        matchlevel = 0;
      break;
    case 5:
      gridstr[count++] = c;
      if (count >= 50)
        matchlevel = 0;
      break;
    case 4:
      if (c == ' ') {
        matchlevel++;
        count = 0;
        gridoff = ftell (lib);
      } else
        matchlevel = 0;
      break;
    case 3:
      if (c == 'D') {
        matchlevel++;
        count = 0;
      } else
        matchlevel = 0;
      break;
    case 2:
      if (c == 'I')
        matchlevel++;
      else
        matchlevel = 0;
      break;
    case 1:
      if (c == 'R')
        matchlevel++;
      else if (c == 'U')
        matchlevel = 12;
      else
        matchlevel = 0;
      break;
    case 0:
      if (c == 'G')
        matchlevel++;
      break;
    }
  }

  if (!gridoff || !gupcoff) {
    printf ("Fatal error - couldn't locate the registration strings.\n");
    exit (1);
  }

  printf ("\nPrevious registration:\n");
  printf ("  '%s'\n  '%s'\n", gridstr, gupcstr);
  for (i=0; i<50; i++)
    gupcstr[i] = gupcstr[i] ^ ((191 * (i+5)) % 256);
  printf ("  '%s'\n", gupcstr);

  if (argc == 1) {
    printf ("Enter the registrant's name; "
            "it will be truncated to 40 characters:\n > ");
    gets (name);
    if (!*name)
      exit (0);
    printf ("Enter the registrant's serial number; "
            "up to eight digits:\n > ");
    gets (serial);
    if (!*serial)
      exit (0);
  } else {
    *name = '\0';
    *serial = '\0';
    for (i=1; i<argc; i++) {
      if (mark = strchr (argv[i], ':')) {
        *mark++ = '\0';
        if (*name)
          strcat (name, " ");
        strcat (name, argv[i++]);
        strcpy (serial, mark);
        break;
      } else {
        if (*name)
          strcat (name, " ");
        strcat (name, argv[i]);
      }
    }
    for (; i<argc; i++) {
      if (*serial)
        strcat (serial, " ");
      strcat (serial, argv[i]);
    }
    if (!*name || !*serial)
      exit (0);
  }
  name[40] = '\0';
  serial[8] = '\0';

  memset (gridstr, ' ', 50);
  memset (gupcstr, ' ', 50);

  memcpy (gridstr, name, strlen(name));
  for (i=8-strlen(serial),j=0; serial[j]; i++,j++)
    gridstr[42+i] = serial[j];
  for (i=0; i<50; i++)
    gupcstr[i] = gridstr[i] ^ ((191 * (i+5)) % 256);

  fseek (lib, gridoff, 0);
  fwrite (gridstr, sizeof (char), 50, lib);
  fseek (lib, gupcoff, 0);
  fwrite (gupcstr, sizeof (char), 50, lib);
  fclose (lib);

  printf ("\nNew registration:\n");
  printf ("  '%s'\n  '%s'\n", gridstr, gupcstr);
  for (i=0; i<50; i++)
    gupcstr[i] = gupcstr[i] ^ ((191 * (i+5)) % 256);
  printf ("  '%s'\n", gupcstr);

  return 0;
}

