#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "vat.h"



main(void)
{
	int i,j,k;
	WAVE *testwave;
	char errstring[256];


	testwave  = LoadWave("varmint.wav",errstring);

	if(testwave) {
		SaveWave("varmint2.wav",testwave,errstring);
		SaveWave("varmint3.wav",testwave,errstring);
		FreeWave(testwave);
	}

	return 0;
}