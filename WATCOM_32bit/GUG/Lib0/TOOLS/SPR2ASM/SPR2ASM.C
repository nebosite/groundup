#include <stdio.h>
#include <i86.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <string.h>
#include <gug.h>
#include <mode.h>

#define MAX                   100

void main(int argc,char *argv[]) {
  char  *spr[MAX];
  char  txt[80];
  char  c1,c2,c3,c4;
  int   i,x,y,x_size,y_size,os,bytes,count;
  char  out_name[80];
  FILE  *out;
  char  csource_name[80];
  FILE  *csource;
  char  hsource_name[80];
  FILE  *hsource;
  char  *p;
  char  spr_name[80];
  char  name[80];

  if (argc < 3) {
    printf("\n\nSprite Compiler Beta - Version 0.4 - GUG Version %s\n",GUGVersion());
	printf("  Copyright 1995-1996 Ground Up Software\n");
    printf("  usage: spr2asm array_name spr_name [out_name]\n\n\n");
	return;
  }

  for (i=0; i<argc; ++i)
  {
    for (x=0; x<strlen(argv[i]); ++x)
	{
	  argv[i][x] = tolower(argv[i][x]);
	}
  }

  for (i=0; i<MAX; ++i) {
    spr[i] = NULL;
  }

  if (argc == 4) {
    strcpy((char *)out_name,argv[3]);
    strcpy((char *)csource_name,argv[3]);
	strcpy((char *)hsource_name,argv[3]);
    strcpy((char *)name,argv[3]);
    strcpy((char *)spr_name,argv[2]);
  }
  else {
    strcpy((char *)out_name,argv[2]);
    strcpy((char *)csource_name,argv[2]);
	strcpy((char *)hsource_name,argv[2]);
	strcpy((char *)name,argv[2]);
    strcpy((char *)spr_name,argv[2]);
  }

  csource_name[6] = '\0';
  hsource_name[6] = '\0';
  out_name[6]    = '\0';

  p = strchr((char *)out_name,'.');
  if (p != NULL) {
    strcpy(p,"_A.ASM");
  }
  else {
    strcat((char *)out_name,"_A.ASM");
  }

  p = strchr((char *)csource_name,'.');
  if (p != NULL) {
    strcpy(p,"_C.C");
  }
  else {
    strcat((char *)csource_name,"_C.C");
  }

  p = strchr((char *)hsource_name,'.');
  if (p != NULL) {
    strcpy(p,"_C.H");
  }
  else {
    strcat((char *)hsource_name,"_C.H");
  }

  p = strchr((char *)spr_name,'.');
  if (p == NULL) {
    strcat((char *)spr_name,".SPR");
  }

  if ((count = GUGLoadSprite(spr_name,(char **)spr)) < 1) {
    printf("Loaded %d sprites\n",count);
    printf("Error - Sprite file not found\n");
	return;
  }

  if ((out = fopen(out_name,"w")) == NULL) {
    printf("Error - Can't open %s for write\n",out_name);
	return;
  }

  fprintf(out,"; Compiled Sprites output from spr2asm\n");
  fprintf(out,";  command line : spr2asm %s %s %s\n",
          argv[1],argv[2],argv[3]);
  fprintf(out,";  entry point name : %s\n",argv[1]);
  fprintf(out,";  asm output file  : %s\n",out_name);
  fprintf(out,";  c   output file  : %s\n",csource_name);
  fprintf(out,";  spr input  file  : %s\n",spr_name);
  fprintf(out,";\n");

  if ((csource = fopen(csource_name,"w")) == NULL) {
    printf("Error - Can't open %s for write\n",csource_name);
	return;
  }

  if ((hsource = fopen(hsource_name,"w")) == NULL) {
    printf("Error - Can't open %s for write\n",hsource_name);
	return;
  }

  GUGInitialize();

  fprintf(csource,"// Compiled Sprites output from spr2asm\n");
  fprintf(csource,"//  command line : spr2asm %s %s %s\n",
          argv[1],argv[2],argv[3]);
  fprintf(csource,"//  entry point name : %s\n",argv[1]);
  fprintf(csource,"//  asm output file  : %s\n",out_name);
  fprintf(csource,"//  c   output file  : %s\n",csource_name);
  fprintf(csource,"//  h   output file  : %s\n",hsource_name);
  fprintf(csource,"//  spr input  file  : %s\n",spr_name);
  fprintf(csource,"\n");
  fprintf(csource,"#ifdef __cplusplus\n");
  fprintf(csource,"extern \"C\" {\n");
  fprintf(csource,"#endif\n");
  fprintf(csource,"\n");
  fprintf(csource,"typedef void (*GUG_CSprFunc) (char *where);  // Function Pointer Type\n");
  fprintf(csource,"\n");
  
  fprintf(hsource,"// Compiled Sprites output from spr2asm\n");
  fprintf(hsource,"//  command line : spr2asm %s %s %s\n",
          argv[1],argv[2],argv[3]);
  fprintf(hsource,"//  entry point name : %s\n",argv[1]);
  fprintf(hsource,"//  asm output file  : %s\n",out_name);
  fprintf(hsource,"//  c   output file  : %s\n",csource_name);
  fprintf(hsource,"//  h   output file  : %s\n",hsource_name);
  fprintf(hsource,"//  spr input  file  : %s\n",spr_name);
  fprintf(hsource,"\n");
  fprintf(hsource,"#ifdef __cplusplus\n");
  fprintf(hsource,"extern \"C\" {\n");
  fprintf(hsource,"#endif\n");
  fprintf(hsource,"\n");

 
  fprintf(out,".386\n");
  fprintf(out,"DGROUP group _DATA\n");
  fprintf(out,"_DATA  segment 'DATA'\n");
  fprintf(out,"_DATA  ends\n");
  fprintf(out,"_TEXT  segment BYTE PUBLIC USE32 'CODE'\n");
  fprintf(out,"       ASSUME CS:_TEXT\n");
  fprintf(out,"       ASSUME DS:DGROUN\n\n");

  for (i=0; i<MAX && (spr[i] > NULL); ++i)
  {
    GUGClearDisplay();
    GUGPutFGSprite(0,80,spr[i]);
    x_size = spr[i][0] + (spr[i][1]*256);
	y_size = spr[i][2] + (spr[i][3]*256);
    sprintf((char *)txt,"Sprite %3d  -  x:%2d by y:%2d",i,x_size,y_size);
	GUGPutText(20,190,20,(char *)txt);
	for (y=0; y<y_size; y++) {
	  for (x=0; x<x_size; ++x) {
        if (spr[i][(y*x_size)+x+4] > NULL) {
          GUGSetPixel(x+80,y,spr[i][(y*x_size)+x+4]);
		  GUGPutText(35+(x*8),y*8,GUGGetPixel(x,y+80),"#");	 // 20
		}
      }
	}
    GUGCopyToDisplay();
 
    fprintf(out,"PUBLIC %s_%1d_\n",argv[1],i);
	fprintf(out,"%s_%1d_ PROC\n",argv[1],i);

    fprintf(csource,"extern void %s_%1d(char *where);  // Sprite %1d\n",
	     	argv[1],i,i);

 	for (y=0; y<y_size; y++) {
	  for (x=0; x<x_size; ++x) {
        bytes = 0;
		c1    = spr[i][(y*x_size)+x+4]; 
		c2    = spr[i][(y*x_size)+x+5]; 
		c3    = spr[i][(y*x_size)+x+6]; 
 		c4    = spr[i][(y*x_size)+x+7]; 
        if (c1 != 0) {
          bytes++;
		  if (((x+1)<x_size) && (c2 != 0)) bytes++; 
		  if (((x+2)<x_size) && (c3 != 0) && (bytes == 2)) bytes++; 
 		  if (((x+3)<x_size) && (c4 != 0) && (bytes == 3)) bytes++; 

          os = (y*X_WRAP_SIZE) + x;

          if (bytes == 1) {
            fprintf(out,"  mov BYTE  PTR eax+0x%1x,",os);
            if (c1 < 16) fprintf(out,"0x0%1x;\n",c1); 
			else		 fprintf(out,"0x%2x;\n",c1);
          }
		  else if (bytes < 4) {	  // must be 2 or 3 bytes
            fprintf(out,"  mov WORD  PTR eax+0x%1x,",os);
            if (c2 < 16) fprintf(out,"0x0%1x",c2); 
			else		 fprintf(out,"0x%2x",c2);
            if (c1 < 16) fprintf(out,"0%1x;\n",c1); 
			else		 fprintf(out,"%2x;\n",c1);
            x += 1;
  		  }
		  else {  // bytes must = 4
            fprintf(out,"  mov DWORD PTR eax+0x%1x,",os);
           if (c4 < 16) fprintf(out,"0x0%1x",c4); 
			else		 fprintf(out,"0x%2x",c4);
            if (c3 < 16) fprintf(out,"0%1x",c3); 
			else		 fprintf(out,"%2x",c3);
            if (c2 < 16) fprintf(out,"0%1x",c2); 
			else		 fprintf(out,"%2x",c2);
            if (c1 < 16) fprintf(out,"0%1x;\n",c1); 
			else		 fprintf(out,"%2x;\n",c1);
            x += 3;
   		  }

		}
      }
	}
    fprintf(out,"  ret\n");
    fprintf(out,"%s_%1d_ ENDP\n\n",argv[1],i);

//    while (!kbhit());
//    getch();	
  }

  fprintf(out,"_TEXT ENDS\n");
  fprintf(out,"END\n");
  fclose(out);

  fprintf(csource,"\n\n");
  fprintf(csource,"static GUG_CSprFunc %s[] = {\n",argv[1]);
  for (x=0; x<(i-1); ++x) {
    fprintf(csource,"  %s_%1d,\n",argv[1],x);
  }
  fprintf(csource,"  %s_%1d\n",argv[1],i-1);
  fprintf(csource,"};\n");
  fprintf(csource,"\n\n");

  fprintf(hsource,"extern void draw_%s(int who, int x, int y);\n\n",argv[1]);
  fprintf(hsource,"extern int %s_height[];\n",argv[1]);
  fprintf(hsource,"extern int %s_width[];\n",argv[1]);
  
  fprintf(csource,"int %s_height[] = {\n",argv[1]);
  for (x=0; x<i-1; ++x)
    fprintf(csource,"  %1d,\n",GUGSpriteHeight(spr[x]));
  fprintf(csource,"  %1d };\n\n",GUGSpriteHeight(spr[i-1]));

  fprintf(csource,"int %s_width[] = {\n",argv[1]);
  for (x=0; x<i-1; ++x)
    fprintf(csource,"  %1d,\n",GUGSpriteWidth(spr[x]));
  fprintf(csource,"  %1d };\n\n",GUGSpriteWidth(spr[i-1]));

  fprintf(csource,"void draw_%s(int who, int x, int y) {\n",argv[1]);
  fprintf(csource,"  extern char *VGA_START;\n");
  fprintf(csource,"  char *where;\n");
  fprintf(csource,"\n");
  fprintf(csource,"  // make sure it's a valid sprite\n");
  fprintf(csource,"  if (who > %d) return;\n",i-1);
  fprintf(csource,"\n");
  fprintf(csource,"  // Clip the x coordinate\n");
//  fprintf(csource,"  x += 31;\n");
  fprintf(csource,"  if (x > %d) return;\n",(MAX_X_SIZE-1));
  fprintf(csource,"  if (x < (0-%s_width[who])) return;\n",argv[1]);
  fprintf(csource,"\n");
  fprintf(csource,"  // Clip the y coordinate\n");
//  fprintf(csource,"  y += 31;\n");
  fprintf(csource,"  if (y > %d) return;\n",(MAX_Y_SIZE-1));
  fprintf(csource,"  if (y < (0-%s_height[who])) return;\n",argv[1]);
  fprintf(csource,"\n");
  fprintf(csource,"  // Write sprite starting at\n");
  fprintf(csource,"  where = VGA_START + (y * %d) + x;\n",X_WRAP_SIZE);
  fprintf(csource,"\n");
  fprintf(csource,"  // call the sprite\n");
  fprintf(csource,"  %s[who](where);\n",argv[1]);
  fprintf(csource,"}\n");
  fprintf(csource,"\n");

  fprintf(csource,"#ifdef __cplusplus\n");
  fprintf(csource,"};\n");
  fprintf(csource,"#endif\n");
  fprintf(csource,"\n");

  fclose(csource);

  for (x=0; x<strlen(name); ++x)
    name[x] = toupper(name[x]);

  fprintf(hsource,"#define MAX_%s_SPRITES %d\n",name,i-1);
  fprintf(hsource,"\n");
  fprintf(hsource,"#ifdef __cplusplus\n");
  fprintf(hsource,"};\n");
  fprintf(hsource,"#endif\n");
  fprintf(hsource,"\n");
  fclose(hsource);

  GUGClearDisplay();
  GUGCopyToDisplay();
  GUGEnd();
  printf("Processed file : %s\n",spr_name);
  printf("Created files  : %s\n",out_name);
  printf("               : %s\n",csource_name);
  printf("               : %s\n",hsource_name);
  printf("Program Terminated Normally\n");

}
