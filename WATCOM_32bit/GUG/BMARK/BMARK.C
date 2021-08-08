#include <stdio.h>
#include <dos.h>
#include <conio.h>
#include <stdlib.h>
#include <math.h>
#include <malloc.h>

#include "..\lib1\gug.h"
#include "..\lib1\pi.h"
#include "..\lib1\keydefs.h"
#include "..\lib1\colors.h"
#include "..\lib1\fixed.h"

#include "bench_c.h"

#define SL 23*7

void main(int argc,char *argv[])
{
  float rt,rt100,min,max;
  int   x,y,l;
  char  *mes;
  char  *buffer;
  char  *tmp;
  FILE  *out;
  char  *spr[10];
  // For FP math
  int   fp1,fp2,fp3;
  float	f1,f2,f3;

  buffer = (char *)malloc(64000);
  tmp    = (char *)malloc(64000);
  mes    = (char *)malloc(80);

  // Open an output file
  out = fopen("bmark.txt","w");

  if (GUGLoadSprite("bench.spr",spr) < 1)
  {
    printf("Fatal error - bench.spr not found!\n");
	return;
  }
  
  printf("\n\n\n");
  printf("GUG VGA Benchmark Utility 0.1\n");
  printf("\n");
  printf("For accurate results do NOT run from a Windows DOS shell!!!\n");
  printf("Should only be run from DOS!!!!!!\n");
  printf("\n");
 
  printf("Hit a key to continue\n");
  do {} while (!kbhit());
  getch();

  // initialize the graphics system
  GUGInitialize();
  GUGStartKeyboard();
  GUGInitTimer();


  // Put up the title screen
  GUGCenterText(0,BLUE,"GUG Benchmark Utility 0.1");

  fprintf(out,"                       GUG Benchmark Utility 0.1 Results\n");
  fprintf(out,"                               GUG Version %s\n",GUGVersion());
  fprintf(out,"\n");
  fprintf(out,"After filling in this form please email it to nbreeden@groundup.com\n");
  fprintf(out,"\n");
 
  fprintf(out,"CPU Type:________________________  (IE: 486DX2-66)\n");
  fprintf(out,"VGA Type:________________________  (IE: Trident 8900)\n");
  fprintf(out,"VGA BUSS:________________________  (IE: ISA 16-bit)\n");
  fprintf(out,"\n");

  fprintf(out,"                  1     100   Min   Max\n");
  fprintf(out,"function          Run   Avg   Seen  Seen  Notes\n");
  fprintf(out,"----------------- ----- ----- ----- ----- --------------------------\n");
  GUGCopyToDisplay();
  GUGSaveDisplay(buffer);

  ////////////////////////////////////////////////////////////////////////
  // GUGFastClear() Tests
  y = 10;
  GUGStartTimer();
  GUGFastClear(VGA_START);
  rt = GUGStopTimer();
  rt = rt / 1193.0;
  sprintf(mes,"GUGFastClear      %5.2f",rt);

  GUGCopyToBuffer(buffer);
  GUGPutText(0,y,GREEN,mes);
  fprintf(out,"%s",mes);
  GUGCopyToDisplay();
  GUGSaveDisplay(buffer);

  rt100 =      0.0;
  min    = 999999.0;
  max    =      0.0;
  for (x=0; x<100; ++x)
  {
     GUGStartTimer();
     GUGFastClear(VGA_START);
     rt = GUGStopTimer();
	 if (rt > max) max = rt;
	 if (rt < min) min = rt;
	 rt100 += rt;
  }
  min = min / 1193.0;
  max = max / 1193.0;
  rt100 = rt100 / 100.0;
  rt100 = rt100 / 1193.0;
  sprintf(mes," %5.2f %5.2f %5.2f BPS:%d",rt100,min,max,(int)((1000.0/rt100)*64000.0));
  GUGCopyToBuffer(buffer);
  GUGPutText(SL,y,GREEN,mes);
  fprintf(out,"%s\n",mes);
  GUGCopyToDisplay();
  GUGSaveDisplay(buffer);

  ////////////////////////////////////////////////////////////////////////
  // GUGFastCopy() Test
  y += 8;
  GUGStartTimer();
  GUGFastCopy(VGA_START);
  rt = GUGStopTimer();
  rt = rt / 1193.0;
  sprintf(mes,"GUGFastCopy       %5.2f",rt);

  GUGCopyToBuffer(buffer);
  GUGPutText(0,y,GREEN,mes);
  fprintf(out,"%s",mes);
  GUGCopyToDisplay();
  GUGSaveDisplay(buffer);

  rt100 =      0.0;
  min    = 999999.0;
  max    =      0.0;
  for (x=0; x<100; ++x)
  {
     GUGStartTimer();
     GUGFastCopy(VGA_START);
     rt = GUGStopTimer();
	 if (rt > max) max = rt;
	 if (rt < min) min = rt;
	 rt100 += rt;
  }
  min = min / 1193.0;
  max = max / 1193.0;
  rt100 = rt100 / 100.0;
  rt100 = rt100 / 1193.0;
  sprintf(mes," %5.2f %5.2f %5.2f BPS:%d",rt100,min,max,(int)((1000.0/rt100)*64000.0));
  GUGCopyToBuffer(buffer);
  GUGPutText(SL,y,GREEN,mes);
  fprintf(out,"%s\n",mes);
  GUGCopyToDisplay();
  GUGSaveDisplay(buffer);

  ////////////////////////////////////////////////////////////////////////
  // GUGSetDisplay Test
  y += 8;
  GUGStartTimer();
  GUGSetDisplay(BLUE);
  rt = GUGStopTimer();
  rt = rt / 1193.0;
  sprintf(mes,"GUGSetDisplay     %5.2f",rt);

  GUGCopyToBuffer(buffer);
  GUGPutText(0,y,GREEN,mes);
  fprintf(out,"%s",mes);
  GUGCopyToDisplay();
  GUGSaveDisplay(buffer);

  rt100 =      0.0;
  min    = 999999.0;
  max    =      0.0;
  for (x=0; x<100; ++x)
  {
     GUGStartTimer();
     GUGSetDisplay(BLUE);
     rt = GUGStopTimer();
	 if (rt > max) max = rt;
	 if (rt < min) min = rt;
	 rt100 += rt;
  }
  min = min / 1193.0;
  max = max / 1193.0;
  rt100 = rt100 / 100.0;
  rt100 = rt100 / 1193.0;
  sprintf(mes," %5.2f %5.2f %5.2f",rt100,min,max);
  GUGCopyToBuffer(buffer);
  GUGPutText(SL,y,GREEN,mes);
  fprintf(out,"%s\n",mes);
  GUGCopyToDisplay();
  GUGSaveDisplay(buffer);

  ////////////////////////////////////////////////////////////////////////
  // GUGSaveDisplay Test
  y += 8;
  GUGStartTimer();
  GUGSaveDisplay(tmp);
  rt = GUGStopTimer();
  rt = rt / 1193.0;
  sprintf(mes,"GUGSaveDisplay    %5.2f",rt);

  GUGCopyToBuffer(buffer);
  GUGPutText(0,y,GREEN,mes);
  fprintf(out,"%s",mes);
  GUGCopyToDisplay();
  GUGSaveDisplay(buffer);

  rt100 =      0.0;
  min    = 999999.0;
  max    =      0.0;
  for (x=0; x<100; ++x)
  {
     GUGStartTimer();
     GUGSaveDisplay(tmp);
     rt = GUGStopTimer();
	 if (rt > max) max = rt;
	 if (rt < min) min = rt;
	 rt100 += rt;
  }
  min = min / 1193.0;
  max = max / 1193.0;
  rt100 = rt100 / 100.0;
  rt100 = rt100 / 1193.0;
  sprintf(mes," %5.2f %5.2f %5.2f",rt100,min,max);
  GUGCopyToBuffer(buffer);
  GUGPutText(SL,y,GREEN,mes);
  fprintf(out,"%s\n",mes);
  GUGCopyToDisplay();
  GUGSaveDisplay(buffer);

  ////////////////////////////////////////////////////////////////////////
  // GUGRestoreDisplay Test
  y += 8;
  GUGStartTimer();
  GUGRestoreDisplay(tmp);   // ***************************************
  rt = GUGStopTimer();
  rt = rt / 1193.0;
  //           -----------------
  sprintf(mes,"GUGRestoreDisplay %5.2f",rt);

  GUGCopyToBuffer(buffer);
  GUGPutText(0,y,GREEN,mes);
  fprintf(out,"%s",mes);
  GUGCopyToDisplay();
  GUGSaveDisplay(buffer);

  rt100 =      0.0;
  min    = 999999.0;
  max    =      0.0;
  for (x=0; x<100; ++x)
  {
     GUGStartTimer();
     GUGRestoreDisplay(tmp);   // ******************************
     rt = GUGStopTimer();
	 if (rt > max) max = rt;
	 if (rt < min) min = rt;
	 rt100 += rt;
  }
  min = min / 1193.0;
  max = max / 1193.0;
  rt100 = rt100 / 100.0;
  rt100 = rt100 / 1193.0;
  sprintf(mes," %5.2f %5.2f %5.2f",rt100,min,max);
  GUGCopyToBuffer(buffer);
  GUGPutText(SL,y,GREEN,mes);
  fprintf(out,"%s\n",mes);
  GUGCopyToDisplay();
  GUGSaveDisplay(buffer);

  ////////////////////////////////////////////////////////////////////////
  // GUGCopyToBuffer Test
  y += 8;
  GUGStartTimer();
  GUGCopyToBuffer(tmp);   // ***************************************
  rt = GUGStopTimer();
  rt = rt / 1193.0;
  //           -----------------
  sprintf(mes,"GUGCopyToBuffer   %5.2f",rt);

  GUGCopyToBuffer(buffer);
  GUGPutText(0,y,GREEN,mes);
  fprintf(out,"%s",mes);
  GUGCopyToDisplay();
  GUGSaveDisplay(buffer);

  rt100 =      0.0;
  min    = 999999.0;
  max    =      0.0;
  for (x=0; x<100; ++x)
  {
     GUGStartTimer();
     GUGCopyToBuffer(tmp);   // ******************************
     rt = GUGStopTimer();
	 if (rt > max) max = rt;
	 if (rt < min) min = rt;
	 rt100 += rt;
  }
  min = min / 1193.0;
  max = max / 1193.0;
  rt100 = rt100 / 100.0;
  rt100 = rt100 / 1193.0;
  sprintf(mes," %5.2f %5.2f %5.2f",rt100,min,max);
  GUGCopyToBuffer(buffer);
  GUGPutText(SL,y,GREEN,mes);
  fprintf(out,"%s\n",mes);
  GUGCopyToDisplay();
  GUGSaveDisplay(buffer);

////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////

  // Put up the title screen
  GUGFastClear(VGA_START);
  GUGCenterText(0,BLUE,"GUG Benchmark Utility");
  GUGCopyToDisplay();
  GUGSaveDisplay(buffer);

  ////////////////////////////////////////////////////////////////////////
  // GUGVLine Test
  y = 10;
  GUGStartTimer();
  GUGVLine(0,199,100,GREEN);   // ***************************************
  rt = GUGStopTimer();
  rt = rt / 1193.0;
  //           -----------------
  sprintf(mes,"GUGVLIne          %5.2f",rt);

  GUGCopyToBuffer(buffer);
  GUGPutText(0,y,GREEN,mes);
  fprintf(out,"%s",mes);
  GUGCopyToDisplay();
  GUGSaveDisplay(buffer);

  rt100 =      0.0;
  min    = 999999.0;
  max    =      0.0;
  for (x=0; x<100; ++x)
  {
     GUGStartTimer();
     GUGVLine(0,199,100,GREEN);   // ******************************
     rt = GUGStopTimer();
	 if (rt > max) max = rt;
	 if (rt < min) min = rt;
	 rt100 += rt;
  }
  min = min / 1193.0;
  max = max / 1193.0;
  rt100 = rt100 / 100.0;
  rt100 = rt100 / 1193.0;
  sprintf(mes," %5.2f %5.2f %5.2f",rt100,min,max);
  GUGCopyToBuffer(buffer);
  GUGPutText(SL,y,GREEN,mes);
  fprintf(out,"%s\n",mes);
  GUGCopyToDisplay();
  GUGSaveDisplay(buffer);

  ////////////////////////////////////////////////////////////////////////
  // GUGHLine Test
  y += 8;
  GUGStartTimer();
  GUGHLine(0,199,100,GREEN);   // ***************************************
  rt = GUGStopTimer();
  rt = rt / 1193.0;
  //           -----------------
  sprintf(mes,"GUGHLIne          %5.2f",rt);  // **************************

  GUGCopyToBuffer(buffer);
  GUGPutText(0,y,GREEN,mes);
  fprintf(out,"%s",mes);
  GUGCopyToDisplay();
  GUGSaveDisplay(buffer);

  rt100 =      0.0;
  min    = 999999.0;
  max    =      0.0;
  for (x=0; x<100; ++x)
  {
     GUGStartTimer();
     GUGHLine(0,199,100,GREEN);   // ******************************
     rt = GUGStopTimer();
	 if (rt > max) max = rt;
	 if (rt < min) min = rt;
	 rt100 += rt;
  }
  min = min / 1193.0;
  max = max / 1193.0;
  rt100 = rt100 / 100.0;
  rt100 = rt100 / 1193.0;
  sprintf(mes," %5.2f %5.2f %5.2f",rt100,min,max);
  GUGCopyToBuffer(buffer);
  GUGPutText(SL,y,GREEN,mes);
  fprintf(out,"%s\n",mes);
  GUGCopyToDisplay();
  GUGSaveDisplay(buffer);

  ////////////////////////////////////////////////////////////////////////
  // GUGLine Test
  y += 8;
  GUGStartTimer();
  GUGLine(0,0,199,199,GREEN);   // ***************************************
  rt = GUGStopTimer();
  rt = rt / 1193.0;
  //           -----------------
  sprintf(mes,"GUGLIne           %5.2f",rt);  // **************************

  GUGCopyToBuffer(buffer);
  GUGPutText(0,y,GREEN,mes);
  fprintf(out,"%s",mes);
  GUGCopyToDisplay();
  GUGSaveDisplay(buffer);

  rt100 =      0.0;
  min    = 999999.0;
  max    =      0.0;
  for (x=0; x<100; ++x)
  {
     GUGStartTimer();
     GUGLine(0,0,199,199,GREEN);   // ******************************
     rt = GUGStopTimer();
	 if (rt > max) max = rt;
	 if (rt < min) min = rt;
	 rt100 += rt;
  }
  min = min / 1193.0;
  max = max / 1193.0;
  rt100 = rt100 / 100.0;
  rt100 = rt100 / 1193.0;
  sprintf(mes," %5.2f %5.2f %5.2f",rt100,min,max);
  GUGCopyToBuffer(buffer);
  GUGPutText(SL,y,GREEN,mes);
  fprintf(out,"%s\n",mes);
  GUGCopyToDisplay();
  GUGSaveDisplay(buffer);

  ////////////////////////////////////////////////////////////////////////
  // GUGBLine Test
  y += 8;
  GUGStartTimer();
  GUGBLine(0,0,199,199,GREEN);   // ***************************************
  rt = GUGStopTimer();
  rt = rt / 1193.0;
  //           -----------------
  sprintf(mes,"GUGBLIne          %5.2f",rt);  // **************************

  GUGCopyToBuffer(buffer);
  GUGPutText(0,y,GREEN,mes);
  fprintf(out,"%s",mes);
  GUGCopyToDisplay();
  GUGSaveDisplay(buffer);

  rt100 =      0.0;
  min    = 999999.0;
  max    =      0.0;
  for (x=0; x<100; ++x)
  {
     GUGStartTimer();
     GUGBLine(0,0,199,199,GREEN);   // ******************************
     rt = GUGStopTimer();
	 if (rt > max) max = rt;
	 if (rt < min) min = rt;
	 rt100 += rt;
  }
  min = min / 1193.0;
  max = max / 1193.0;
  rt100 = rt100 / 100.0;
  rt100 = rt100 / 1193.0;
  sprintf(mes," %5.2f %5.2f %5.2f",rt100,min,max);
  GUGCopyToBuffer(buffer);
  GUGPutText(SL,y,GREEN,mes);
  fprintf(out,"%s\n",mes);
  GUGCopyToDisplay();
  GUGSaveDisplay(buffer);

  ////////////////////////////////////////////////////////////////////////
  // GUGRectangle Test
  y += 8;
  GUGStartTimer();
  GUGRectangle(0,0,199,199,GREEN);   // ***************************************
  rt = GUGStopTimer();
  rt = rt / 1193.0;
  //           -----------------
  sprintf(mes,"GUGRectangle      %5.2f",rt);  // **************************

  GUGCopyToBuffer(buffer);
  GUGPutText(0,y,GREEN,mes);
  fprintf(out,"%s",mes);
  GUGCopyToDisplay();
  GUGSaveDisplay(buffer);

  rt100 =      0.0;
  min    = 999999.0;
  max    =      0.0;
  for (x=0; x<100; ++x)
  {
     GUGStartTimer();
     GUGRectangle(0,199,0,199,GREEN);   // ******************************
     rt = GUGStopTimer();
	 if (rt > max) max = rt;
	 if (rt < min) min = rt;
	 rt100 += rt;
  }
  min = min / 1193.0;
  max = max / 1193.0;
  rt100 = rt100 / 100.0;
  rt100 = rt100 / 1193.0;
  sprintf(mes," %5.2f %5.2f %5.2f",rt100,min,max);
  GUGCopyToBuffer(buffer);
  GUGPutText(SL,y,GREEN,mes);
  fprintf(out,"%s\n",mes);
  GUGCopyToDisplay();
  GUGSaveDisplay(buffer);

  ////////////////////////////////////////////////////////////////////////
  // GUGFillRectangle Test
  y += 8;
  GUGStartTimer();
  GUGFillRectangle(0,0,199,199,GREEN);   // ***************************************
  rt = GUGStopTimer();
  rt = rt / 1193.0;
  //           -----------------
  sprintf(mes,"GUGFillRectangle  %5.2f",rt);  // **************************

  GUGCopyToBuffer(buffer);
  GUGPutText(0,y,GREEN,mes);
  fprintf(out,"%s",mes);
  GUGCopyToDisplay();
  GUGSaveDisplay(buffer);

  rt100 =      0.0;
  min    = 999999.0;
  max    =      0.0;
  for (x=0; x<100; ++x)
  {
     GUGStartTimer();
     GUGFillRectangle(0,0,199,199,GREEN);   // ******************************
     rt = GUGStopTimer();
	 if (rt > max) max = rt;
	 if (rt < min) min = rt;
	 rt100 += rt;
  }
  min = min / 1193.0;
  max = max / 1193.0;
  rt100 = rt100 / 100.0;
  rt100 = rt100 / 1193.0;
  sprintf(mes," %5.2f %5.2f %5.2f",rt100,min,max);
  GUGCopyToBuffer(buffer);
  GUGPutText(SL,y,GREEN,mes);
  fprintf(out,"%s\n",mes);
  GUGCopyToDisplay();
  GUGSaveDisplay(buffer);

////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////

  // Put up the title screen
  GUGFastClear(VGA_START);
  GUGCenterText(0,BLUE,"GUG Benchmark Utility");
  GUGCopyToDisplay();
  GUGSaveDisplay(buffer);

  ////////////////////////////////////////////////////////////////////////
  // draw_bench() Test
  y = 10;
  GUGStartTimer();
  draw_bench(0,10,10);   // ***************************************
  rt = GUGStopTimer();
  rt = rt / 1193.0;
  //           -----------------
  sprintf(mes,"draw_bench        %5.2f",rt);

  GUGCopyToBuffer(buffer);
  GUGPutText(0,y,GREEN,mes);
  fprintf(out,"%s",mes);
  GUGCopyToDisplay();
  GUGSaveDisplay(buffer);

  rt100 =      0.0;
  min    = 999999.0;
  max    =      0.0;
  for (x=0; x<100; ++x)
  {
     GUGStartTimer();
     draw_bench(0,10,10);   // ******************************
     rt = GUGStopTimer();
	 if (rt > max) max = rt;
	 if (rt < min) min = rt;
	 rt100 += rt;
  }
  min = min / 1193.0;
  max = max / 1193.0;
  rt100 = rt100 / 100.0;
  rt100 = rt100 / 1193.0;
  sprintf(mes," %5.2f %5.2f %5.2f",rt100,min,max);
  GUGCopyToBuffer(buffer);
  GUGPutText(SL,y,GREEN,mes);
  fprintf(out,"%s\n",mes);
  GUGCopyToDisplay();
  GUGSaveDisplay(buffer);

  ////////////////////////////////////////////////////////////////////////
  // GUGPutFGSprite Test
  y += 8;
  GUGStartTimer();
  GUGPutFGSprite(0,10,spr[0]);   // ***************************************
  rt = GUGStopTimer();
  rt = rt / 1193.0;
  //           -----------------
  sprintf(mes,"GUGPutFGSprite    %5.2f",rt);

  GUGCopyToBuffer(buffer);
  GUGPutText(0,y,GREEN,mes);
  fprintf(out,"%s",mes);
  GUGCopyToDisplay();
  GUGSaveDisplay(buffer);

  rt100 =      0.0;
  min    = 999999.0;
  max    =      0.0;
  for (x=0; x<100; ++x)
  {
     GUGStartTimer();
     GUGPutFGSprite(0,10,spr[0]);   // ******************************
     rt = GUGStopTimer();
	 if (rt > max) max = rt;
	 if (rt < min) min = rt;
	 rt100 += rt;
  }
  min = min / 1193.0;
  max = max / 1193.0;
  rt100 = rt100 / 100.0;
  rt100 = rt100 / 1193.0;
  sprintf(mes," %5.2f %5.2f %5.2f",rt100,min,max);
  GUGCopyToBuffer(buffer);
  GUGPutText(SL,y,GREEN,mes);
  fprintf(out,"%s\n",mes);
  GUGCopyToDisplay();
  GUGSaveDisplay(buffer);

  ////////////////////////////////////////////////////////////////////////
  // GUGPutBGSprite Test
  y += 8;
  GUGStartTimer();
  GUGPutBGSprite(0,10,spr[0]);   // ***************************************
  rt = GUGStopTimer();
  rt = rt / 1193.0;
  //           -----------------
  sprintf(mes,"GUGPutBGSprite    %5.2f",rt);

  GUGCopyToBuffer(buffer);
  GUGPutText(0,y,GREEN,mes);
  fprintf(out,"%s",mes);
  GUGCopyToDisplay();
  GUGSaveDisplay(buffer);

  rt100 =      0.0;
  min    = 999999.0;
  max    =      0.0;
  for (x=0; x<100; ++x)
  {
     GUGStartTimer();
     GUGPutBGSprite(0,10,spr[0]);   // ******************************
     rt = GUGStopTimer();
	 if (rt > max) max = rt;
	 if (rt < min) min = rt;
	 rt100 += rt;
  }
  min = min / 1193.0;
  max = max / 1193.0;
  rt100 = rt100 / 100.0;
  rt100 = rt100 / 1193.0;
  sprintf(mes," %5.2f %5.2f %5.2f",rt100,min,max);
  GUGCopyToBuffer(buffer);
  GUGPutText(SL,y,GREEN,mes);
  fprintf(out,"%s\n",mes);
  GUGCopyToDisplay();
  GUGSaveDisplay(buffer);

  ////////////////////////////////////////////////////////////////////////
  // GUGPutMNSprite Test
  y += 8;
  GUGStartTimer();
  GUGPutMNSprite(0,10,RED,spr[0]);   // ***************************************
  rt = GUGStopTimer();
  rt = rt / 1193.0;
  //           -----------------
  sprintf(mes,"GUGPutMNSprite    %5.2f",rt);

  GUGCopyToBuffer(buffer);
  GUGPutText(0,y,GREEN,mes);
  fprintf(out,"%s",mes);
  GUGCopyToDisplay();
  GUGSaveDisplay(buffer);

  rt100 =      0.0;
  min    = 999999.0;
  max    =      0.0;
  for (x=0; x<100; ++x)
  {
     GUGStartTimer();
     GUGPutMNSprite(0,10,RED,spr[0]);   // ******************************
     rt = GUGStopTimer();
	 if (rt > max) max = rt;
	 if (rt < min) min = rt;
	 rt100 += rt;
  }
  min = min / 1193.0;
  max = max / 1193.0;
  rt100 = rt100 / 100.0;
  rt100 = rt100 / 1193.0;
  sprintf(mes," %5.2f %5.2f %5.2f",rt100,min,max);
  GUGCopyToBuffer(buffer);
  GUGPutText(SL,y,GREEN,mes);
  fprintf(out,"%s\n",mes);
  GUGCopyToDisplay();
  GUGSaveDisplay(buffer);

  ////////////////////////////////////////////////////////////////////////
  // GUGSpriteHeight Test
  y += 8;
  GUGStartTimer();
  GUGSpriteHeight(spr[0]);   // ***************************************
  rt = GUGStopTimer();
  rt = rt / 1193.0;
  //           -----------------
  sprintf(mes,"GUGSpriteHeight   %5.2f",rt);

  GUGCopyToBuffer(buffer);
  GUGPutText(0,y,GREEN,mes);
  fprintf(out,"%s",mes);
  GUGCopyToDisplay();
  GUGSaveDisplay(buffer);

  rt100 =      0.0;
  min    = 999999.0;
  max    =      0.0;
  for (x=0; x<100; ++x)
  {
     GUGStartTimer();
     GUGSpriteHeight(spr[0]);   // ******************************
     rt = GUGStopTimer();
	 if (rt > max) max = rt;
	 if (rt < min) min = rt;
	 rt100 += rt;
  }
  min = min / 1193.0;
  max = max / 1193.0;
  rt100 = rt100 / 100.0;
  rt100 = rt100 / 1193.0;
  sprintf(mes," %5.2f %5.2f %5.2f",rt100,min,max);
  GUGCopyToBuffer(buffer);
  GUGPutText(SL,y,GREEN,mes);
  fprintf(out,"%s\n",mes);
  GUGCopyToDisplay();
  GUGSaveDisplay(buffer);

  ////////////////////////////////////////////////////////////////////////
  // GUGWidthHeight Test
  y += 8;
  GUGStartTimer();
  GUGSpriteWidth(spr[0]);   // ***************************************
  rt = GUGStopTimer();
  rt = rt / 1193.0;
  //           -----------------
  sprintf(mes,"GUGSpriteWidth    %5.2f",rt);

  GUGCopyToBuffer(buffer);
  GUGPutText(0,y,GREEN,mes);
  fprintf(out,"%s",mes);
  GUGCopyToDisplay();
  GUGSaveDisplay(buffer);

  rt100 =      0.0;
  min    = 999999.0;
  max    =      0.0;
  for (x=0; x<100; ++x)
  {
     GUGStartTimer();
     GUGSpriteWidth(spr[0]);   // ******************************
     rt = GUGStopTimer();
	 if (rt > max) max = rt;
	 if (rt < min) min = rt;
	 rt100 += rt;
  }
  min = min / 1193.0;
  max = max / 1193.0;
  rt100 = rt100 / 100.0;
  rt100 = rt100 / 1193.0;
  sprintf(mes," %5.2f %5.2f %5.2f",rt100,min,max);
  GUGCopyToBuffer(buffer);
  GUGPutText(SL,y,GREEN,mes);
  fprintf(out,"%s\n",mes);
  GUGCopyToDisplay();
  GUGSaveDisplay(buffer);

////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////

  // Put up the title screen
  GUGFastClear(VGA_START);
  GUGCenterText(0,BLUE,"GUG Benchmark Utility");
  GUGCopyToDisplay();
  GUGSaveDisplay(buffer);

  ////////////////////////////////////////////////////////////////////////
  // GUGSetPixel() Test
  y = 10;
  GUGStartTimer();
  for (l=0; l<1000; ++l)
  {
    GUGSetPixel(0,10,BLUE);   // ***************************************
  }
  rt = GUGStopTimer();
  rt = rt / 1193.0;
  //           -----------------
  sprintf(mes,"GUGSetPixel 1K    %5.2f",rt);

  GUGCopyToBuffer(buffer);
  GUGPutText(0,y,GREEN,mes);
  fprintf(out,"%s",mes);
  GUGCopyToDisplay();
  GUGSaveDisplay(buffer);

  rt100 =      0.0;
  min    = 999999.0;
  max    =      0.0;
  for (x=0; x<100; ++x)
  {
     GUGStartTimer();
     for (l=0; l<1000; ++l)
     {
       GUGSetPixel(0,10,BLUE);   // ******************************
     }
     rt = GUGStopTimer();
	 if (rt > max) max = rt;
	 if (rt < min) min = rt;
	 rt100 += rt;
  }
  min = min / 1193.0;
  max = max / 1193.0;
  rt100 = rt100 / 100.0;
  rt100 = rt100 / 1193.0;
  sprintf(mes," %5.2f %5.2f %5.2f",rt100,min,max);
  GUGCopyToBuffer(buffer);
  GUGPutText(SL,y,GREEN,mes);
  fprintf(out,"%s\n",mes);
  GUGCopyToDisplay();
  GUGSaveDisplay(buffer);


  ////////////////////////////////////////////////////////////////////////
  // GUGFastSetPixel() Test
  y += 8;
  GUGStartTimer();
  for (l=0; l<1000; ++l)
  {
    GUGFastSetPixel(0,10,BLUE);   // ***************************************
  }
  rt = GUGStopTimer();
  rt = rt / 1193.0;
  //           -----------------
  sprintf(mes,"GUGFastSetPixel   %5.2f",rt);

  GUGCopyToBuffer(buffer);
  GUGPutText(0,y,GREEN,mes);
  fprintf(out,"%s",mes);
  GUGCopyToDisplay();
  GUGSaveDisplay(buffer);

  rt100 =      0.0;
  min    = 999999.0;
  max    =      0.0;
  for (x=0; x<100; ++x)
  {
     GUGStartTimer();
     for (l=0; l<1000; ++l)
     {
       GUGFastSetPixel(0,10,BLUE);   // ******************************
     }
     rt = GUGStopTimer();
	 if (rt > max) max = rt;
	 if (rt < min) min = rt;
	 rt100 += rt;
  }
  min = min / 1193.0;
  max = max / 1193.0;
  rt100 = rt100 / 100.0;
  rt100 = rt100 / 1193.0;
  sprintf(mes," %5.2f %5.2f %5.2f",rt100,min,max);
  GUGCopyToBuffer(buffer);
  GUGPutText(SL,y,GREEN,mes);
  fprintf(out,"%s\n",mes);
  GUGCopyToDisplay();
  GUGSaveDisplay(buffer);

  ////////////////////////////////////////////////////////////////////////
  // GUGGetPixel() Test
  y += 8;
  GUGStartTimer();
  GUGGetPixel(0,10);   // ***************************************
  rt = GUGStopTimer();
  rt = rt / 1193.0;
  //           -----------------
  sprintf(mes,"GUGGetPixel       %5.2f",rt);

  GUGCopyToBuffer(buffer);
  GUGPutText(0,y,GREEN,mes);
  fprintf(out,"%s",mes);
  GUGCopyToDisplay();
  GUGSaveDisplay(buffer);

  rt100 =      0.0;
  min    = 999999.0;
  max    =      0.0;
  for (x=0; x<100; ++x)
  {
     GUGStartTimer();
     GUGGetPixel(0,10);   // ******************************
     rt = GUGStopTimer();
	 if (rt > max) max = rt;
	 if (rt < min) min = rt;
	 rt100 += rt;
  }
  min = min / 1193.0;
  max = max / 1193.0;
  rt100 = rt100 / 100.0;
  rt100 = rt100 / 1193.0;
  sprintf(mes," %5.2f %5.2f %5.2f",rt100,min,max);
  GUGCopyToBuffer(buffer);
  GUGPutText(SL,y,GREEN,mes);
  fprintf(out,"%s\n",mes);
  GUGCopyToDisplay();
  GUGSaveDisplay(buffer);

  ////////////////////////////////////////////////////////////////////////
  // GUGTestPixel() Test
  y += 8;
  GUGStartTimer();
  GUGTestPixel(0,10,BLUE);   // ***************************************
  rt = GUGStopTimer();
  rt = rt / 1193.0;
  //           -----------------
  sprintf(mes,"GUGTestPixel      %5.2f",rt);

  GUGCopyToBuffer(buffer);
  GUGPutText(0,y,GREEN,mes);
  fprintf(out,"%s",mes);
  GUGCopyToDisplay();
  GUGSaveDisplay(buffer);

  rt100 =      0.0;
  min    = 999999.0;
  max    =      0.0;
  for (x=0; x<100; ++x)
  {
     GUGStartTimer();
     GUGTestPixel(0,10,BLUE);   // ******************************
     rt = GUGStopTimer();
	 if (rt > max) max = rt;
	 if (rt < min) min = rt;
	 rt100 += rt;
  }
  min = min / 1193.0;
  max = max / 1193.0;
  rt100 = rt100 / 100.0;
  rt100 = rt100 / 1193.0;
  sprintf(mes," %5.2f %5.2f %5.2f",rt100,min,max);
  GUGCopyToBuffer(buffer);
  GUGPutText(SL,y,GREEN,mes);
  fprintf(out,"%s\n",mes);
  GUGCopyToDisplay();
  GUGSaveDisplay(buffer);

////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////

  // Put up the title screen
  GUGFastClear(VGA_START);
  GUGCenterText(0,BLUE,"GUG Benchmark Utility");
  GUGCopyToDisplay();
  GUGSaveDisplay(buffer);

  ////////////////////////////////////////////////////////////////////////
  // GUGPutText() Test
  y = 10;
  GUGStartTimer();
  GUGPutText(0,10,BLUE,"This is a test");   // ***************************************
  rt = GUGStopTimer();
  rt = rt / 1193.0;
  //           -----------------
  sprintf(mes,"GUGPutText     14 %5.2f",rt);

  GUGCopyToBuffer(buffer);
  GUGPutText(0,y,GREEN,mes);
  fprintf(out,"%s",mes);
  GUGCopyToDisplay();
  GUGSaveDisplay(buffer);

  rt100 =      0.0;
  min    = 999999.0;
  max    =      0.0;
  for (x=0; x<100; ++x)
  {
     GUGStartTimer();
     GUGPutText(0,10,BLUE,"This is a test");   // ******************************
     rt = GUGStopTimer();
	 if (rt > max) max = rt;
	 if (rt < min) min = rt;
	 rt100 += rt;
  }
  min = min / 1193.0;
  max = max / 1193.0;
  rt100 = rt100 / 100.0;
  rt100 = rt100 / 1193.0;
  sprintf(mes," %5.2f %5.2f %5.2f",rt100,min,max);
  GUGCopyToBuffer(buffer);
  GUGPutText(SL,y,GREEN,mes);
  fprintf(out,"%s\n",mes);
  GUGCopyToDisplay();
  GUGSaveDisplay(buffer);

  ////////////////////////////////////////////////////////////////////////
  // GUGPrintWhite6x8() Test
  y += 8;
  GUGStartTimer();
  GUGPrintRed6x8(0,10,"This is a test");   // ***************************************
  rt = GUGStopTimer();
  rt = rt / 1193.0;
  //           -----------------
  sprintf(mes,"GUGPrintRed6x8 14 %5.2f",rt);

  GUGCopyToBuffer(buffer);
  GUGPutText(0,y,GREEN,mes);
  fprintf(out,"%s",mes);
  GUGCopyToDisplay();
  GUGSaveDisplay(buffer);

  rt100 =      0.0;
  min    = 999999.0;
  max    =      0.0;
  for (x=0; x<100; ++x)
  {
     GUGStartTimer();
     GUGPrintRed6x8(0,10,"This is a test");   // ******************************
     rt = GUGStopTimer();
	 if (rt > max) max = rt;
	 if (rt < min) min = rt;
	 rt100 += rt;
  }
  min = min / 1193.0;
  max = max / 1193.0;
  rt100 = rt100 / 100.0;
  rt100 = rt100 / 1193.0;
  sprintf(mes," %5.2f %5.2f %5.2f",rt100,min,max);
  GUGCopyToBuffer(buffer);
  GUGPutText(SL,y,GREEN,mes);
  fprintf(out,"%s\n",mes);
  GUGCopyToDisplay();
  GUGSaveDisplay(buffer);



////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////

  // Put up the title screen
  GUGFastClear(VGA_START);
  GUGCenterText(0,BLUE,"GUG Benchmark Utility");
  GUGCopyToDisplay();
  GUGSaveDisplay(buffer);

  ////////////////////////////////////////////////////////////////////////
  // GUGFPMul() Test
  fp1 = GUGFPAssignFloat(3.12);
  fp2 = GUGFPAssignFloat(24.02);

  y = 10;
  GUGStartTimer();
  for (l=0; l<1000; ++l)
  {
    fp3 = GUGFPMul(fp1,fp2);
  }
  rt = GUGStopTimer();
  rt = rt / 1193.0;
  //           -----------------
  sprintf(mes,"GUGFPMul          %5.2f",rt);

  GUGCopyToBuffer(buffer);
  GUGPutText(0,y,GREEN,mes);
  fprintf(out,"%s",mes);
  GUGCopyToDisplay();
  GUGSaveDisplay(buffer);

  rt100 =      0.0;
  min    = 999999.0;
  max    =      0.0;
  for (x=0; x<100; ++x)
  {
     GUGStartTimer();
	 for (l=0; l<1000; ++l)
	 {
       fp3 = GUGFPMul(fp1,fp2);
	 }
     rt = GUGStopTimer();
	 if (rt > max) max = rt;
	 if (rt < min) min = rt;
	 rt100 += rt;
  }
  min = min / 1193.0;
  max = max / 1193.0;
  rt100 = rt100 / 100.0;
  rt100 = rt100 / 1193.0;
  sprintf(mes," %5.2f %5.2f %5.2f Result:%f",rt100,min,max,GUGFPGetFloat(fp3));
  GUGCopyToBuffer(buffer);
  GUGPutText(SL,y,GREEN,mes);
  fprintf(out,"%s\n",mes);
  GUGCopyToDisplay();
  GUGSaveDisplay(buffer);

  // mul Test
  f1 =  3.12;
  f2 = 24.02;

  y += 8;
  GUGStartTimer();
  for (l=0; l<1000; ++l)
  {
    f3 = f1 * f2;
  }
  rt = GUGStopTimer();
  rt = rt / 1193.0;
  rt = rt / 1000.0;
  //           -----------------
  sprintf(mes,"FPU Multiply      %5.2f",rt);

  GUGCopyToBuffer(buffer);
  GUGPutText(0,y,GREEN,mes);
  fprintf(out,"%s",mes);
  GUGCopyToDisplay();
  GUGSaveDisplay(buffer);

  rt100 =      0.0;
  min    = 999999.0;
  max    =      0.0;
  for (x=0; x<100; ++x)
  {
     GUGStartTimer();
     for (l=0; l<1000; ++l)
	 {
       f3 = f1 * f2;
	 }
     rt = GUGStopTimer();
	 if (rt > max) max = rt;
	 if (rt < min) min = rt;
	 rt100 += rt;
  }
  min = min / 1193.0;
  max = max / 1193.0;
  rt100 = rt100 / 100.0;
  rt100 = rt100 / 1193.0;
  sprintf(mes," %5.2f %5.2f %5.2f Result:%f",rt100,min,max,f3);
  GUGCopyToBuffer(buffer);
  GUGPutText(SL,y,GREEN,mes);
  fprintf(out,"%s\n",mes);
  GUGCopyToDisplay();
  GUGSaveDisplay(buffer);

  ////////////////////////////////////////////////////////////////////////
  // GUGFPDiv() Test
  fp1 = GUGFPAssignFloat(3.12);
  fp2 = GUGFPAssignFloat(2.02);

  y += 8;
  GUGStartTimer();
  for (l=0; l<1000; ++l)
  {
    fp3 = GUGFPDiv(fp1,fp2);
  }
  rt = GUGStopTimer();
  rt = rt / 1193.0;
  //           -----------------
  sprintf(mes,"GUGFPDiv          %5.2f",rt);

  GUGCopyToBuffer(buffer);
  GUGPutText(0,y,GREEN,mes);
  fprintf(out,"%s",mes);
  GUGCopyToDisplay();
  GUGSaveDisplay(buffer);

  rt100 =      0.0;
  min    = 999999.0;
  max    =      0.0;
  for (x=0; x<100; ++x)
  {
     GUGStartTimer();
	 for (l=0; l<1000; ++l)
	 {
       fp3 = GUGFPDiv(fp1,fp2);
	 }
     rt = GUGStopTimer();
	 if (rt > max) max = rt;
	 if (rt < min) min = rt;
	 rt100 += rt;
  }
  min = min / 1193.0;
  max = max / 1193.0;
  rt100 = rt100 / 100.0;
  rt100 = rt100 / 1193.0;
  sprintf(mes," %5.2f %5.2f %5.2f Result:%f",rt100,min,max,GUGFPGetFloat(fp3));
  GUGCopyToBuffer(buffer);
  GUGPutText(SL,y,GREEN,mes);
  fprintf(out,"%s\n",mes);
  GUGCopyToDisplay();
  GUGSaveDisplay(buffer);

  // mul Test
  f1 = 3.12;
  f2 = 2.02;

  y += 8;
  GUGStartTimer();
  for (l=0; l<1000; ++l)
  {
    f3 = f1 / f2;
  }
  rt = GUGStopTimer();
  rt = rt / 1193.0;
  rt = rt / 1000.0;
  //           -----------------
  sprintf(mes,"FPU Divide        %5.2f",rt);

  GUGCopyToBuffer(buffer);
  GUGPutText(0,y,GREEN,mes);
  fprintf(out,"%s",mes);
  GUGCopyToDisplay();
  GUGSaveDisplay(buffer);

  rt100 =      0.0;
  min    = 999999.0;
  max    =      0.0;
  for (x=0; x<100; ++x)
  {
     GUGStartTimer();
     for (l=0; l<1000; ++l)
	 {
       f3 = f1 / f2;
	 }
     rt = GUGStopTimer();
	 if (rt > max) max = rt;
	 if (rt < min) min = rt;
	 rt100 += rt;
  }
  min = min / 1193.0;
  max = max / 1193.0;
  rt100 = rt100 / 100.0;
  rt100 = rt100 / 1193.0;
  sprintf(mes," %5.2f %5.2f %5.2f Result:%f",rt100,min,max,f3);
  GUGCopyToBuffer(buffer);
  GUGPutText(SL,y,GREEN,mes);
  fprintf(out,"%s\n",mes);
  GUGCopyToDisplay();
  GUGSaveDisplay(buffer);

  do {} while (GUG_key_table[ESC] == KEY_IS_UP);

  // shut down the graphics system
  GUGEnd();
  GUGStopKeyboard();

  fclose(out);

  printf("Please edit   bmark.txt  and fill in your system info.\n");
  printf("Please email  bmark.txt  to nbreeden@groundup.com\n");
  printf("\n");

  printf("Hit a key to continue\n");
  do {} while (!kbhit());
  getch();

  free(buffer);
  free(mes);
  free(tmp);
}


