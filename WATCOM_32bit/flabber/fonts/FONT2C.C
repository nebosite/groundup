
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>



main(int argc, char *argv[])
{
	int i,j,k;
	FILE *input;
	FILE *output;
	unsigned char filename[256],fontname[256],fontdata[10000],inputname[256];
	char string[256];
	char *spot;
	int length;

																 // Process arguments
	if(argc < 2) {
		printf("USAGE:  font2c (fontfile)\n");
		exit(1);
	}

	strcpy(filename,argv[1]);
	strcpy(fontname,argv[1]);
	spot = strchr(fontname,'.');
	if(!spot) strcat(filename,".fon");
	else *spot = 0;
																 // Open font file
	input = fopen(filename,"rb");
	if(!input) {
		fprintf(stderr,"ERROR: Cannot open font file: %s\n",filename);
		exit(1);
	}
	strcpy(inputname,filename);
																 // Read it
	printf("FONT2C - Eric Jorgensen\n");
	printf("Processing %s\n",filename);

	length = fread(fontdata,1,9999,input);
	fclose(input);
																 // Write header
	printf("Writing header file...\n");
	sprintf(filename,"%s.h",fontname);
	output = fopen(filename,"w");
	if(!output) {
		fprintf(stderr,"ERROR: Could not write to header file\n");
		exit(1);
	}

	fprintf(output,"// FONT2C-generated header file\n"
					"\n"
					"#ifdef __cplusplus\n"
					"extern \"C\" {\n"
					"#endif\n"
					"\n"
					"extern char *font_%s;\n"
					"\n"
					"#ifdef __cplusplus\n"
					"};\n"
					"#endif\n",fontname);
	fclose(output);

	printf("Writing source file...\n");
	sprintf(filename,"%s.c",fontname);
	output = fopen(filename,"w");
	if(!output) {
		fprintf(stderr,"ERROR: Could not write to source file");
		exit(1);
	}

	fprintf(output,"// FONT2C-generated source file\n"
					"\n"
					"// Input file    %s\n"
					"// c output file %s.c\n"
					"// h output file %s.h\n"
					"\n"
					"#ifdef __cplusplus\n"
					"extern \"C\" {\n"
					"#endif\n"
					"\n"
					"char *font_%s = {\n",inputname,fontname,fontname,fontname);

	for(i = 0; i< length; i++) {
		if(i && i%16 == 0) fprintf(output,"\" //  %d\n",i);
		if(i%16 == 0) fprintf(output,"\"");

		sprintf(string,"\\%3o",fontdata[i]);
		for(j = 0; j < strlen(string); j++) {
			if(string[j] == ' ') string[j] = '0';
		}
		fprintf(output,string);
	}
	fprintf(output,"\" //  %d\n"
					"};\n"
					"\n"
					"#ifdef __cplusplus\n"
					"};\n"
					"#endif\n",i);
	fclose(output);


	return 0;
}