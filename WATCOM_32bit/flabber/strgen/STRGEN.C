#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>

int giDemoDays;
char gcUserName[255];


/**************************************************************************
	void regvalidate(char *valstr)

	DESCRIPTION: Validates the command-line registration string to confirm
							 that this code is being run from the right Windows executable.

	Format:  						-@ "Coded-string"
	Uncoded format:     FLABBERGASTED^Registered user name^Days left^checksum
	Checksum:						checksum = strlen(user_name) + totalascii + days left
	Coding:							nc = 158-oc;  // Reject nc < 32 && nc > 126

**************************************************************************/
void regvalidate(char *valstr)
{
	int i;
	char 	*flabbertoken = NULL,
				*nametoken = NULL,
				*daystoken = NULL,
				*checksumtoken = NULL,
				*nullstring={""};
	int days, checksum;
	int cs = 0;

	printf("Validating...\n");
																 // Decode the string
	for(i = 0; i < strlen(valstr); i++) {
		*(valstr + i) = 158 - *(valstr+i);
	}
//	printf("S: %s\n",valstr);
																 // Grab tokens
	flabbertoken = strtok(valstr,"^");
	nametoken = strtok(NULL,"^");
	daystoken = strtok(NULL,"^");
	checksumtoken = strtok(NULL,"^");

	if(!flabbertoken || !nametoken || !daystoken || !checksumtoken) return;


																 // See if string is a flabbergasted key
	if(strcmp(flabbertoken,"FLABBERGASTED")) return;

	days = atoi(daystoken);
	checksum = atoi(checksumtoken);

	printf("D=%d, C=%d\n",days,checksum);

																 // Verify checksum
	cs = strlen(nametoken);
	printf("cs=%d\n",cs);
	for(i = 0; i < strlen(nametoken); i++) cs += *(nametoken+i);
	printf("cs=%d\n",cs);
	cs += days;
	printf("cs=%d\n",cs);


	if(cs != checksum) return;

																 // We made it!  Set the eveluation days
																 // and the username.
	giDemoDays = days;
	strcpy(gcUserName,nametoken);

	printf("Success!!\n");
}


main(int argc, char *argv[])
{
	int i,j,k;
	char name[255] = {"Fooname"};
	char string[255];
	int checksum = 0;
	int days = 15;


	printf("------------------------------------------------------\n");
	printf("Arg1=%s\n",argv[1]);
	regvalidate(argv[1]);

	checksum = strlen(name);
	for(i = 0; i < strlen(name); i++) checksum += name[i];
	checksum += days;

	sprintf(string,"FLABBERGASTED^%s^%d^%d",name,days,checksum);

	printf("STRING=%s\n",string);

	for(i = 0; i < strlen(string); i++) {
		string[i] = 158-string[i];
	}
	printf("STRING=%s\n",string);

	regvalidate(string);

	return 0;
}