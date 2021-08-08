#include <stdio.h>
#include <gug.h>
#include <colors.h>

///////////////////
main(int argc,char *argv[])
{
    GUG_PCX *gug_pcx;
    PCXHEAD *pcx_header;

    if (argc < 2)
    {
      printf("\n\nGUG PCX Viewer - Version 0.2 - GUG Version %s\n",GUGVersion());
      printf("  Copyright 1995-1996 Ground Up Software\n");
      printf("  usage: showpcx pcxfile.PCX\n\n\n");
      return;
    }

    GUGInitialize();                      // Fire up GUG

    if ((pcx_header = GUGGetPCXHeader(argv[1])) == NULL)  // Attempt to load Header
    {
      GUGEnd();
      printf("Error reading %s's header!\n",argv[1]);
      return;
    }

//    printf("Dump from GUGGetPCXHeader()\n");
//    printf("manufacturer:%d\n",(int)pcx_header->manufacturer);
//    printf("encoding    :%d\n",(int)pcx_header->encoding);
//    printf("b_p_p       :%d\n",(int)pcx_header->bits_per_pixel);

//    printf("xmin:%d ymin:%d\n",(int)pcx_header->xmin,(int)pcx_header->ymin);
//    printf("xmax:%d ymax:%d\n",(int)pcx_header->xmax,(int)pcx_header->ymax);

//    printf("hres:%d vres:%d\n",(int)pcx_header->hres,(int)pcx_header->vres);
//    printf("check_one   :%x check_two:%x\n",
//           (int)pcx_header->check_one,(int)pcx_header->check_two);
//    printf("sname       :%s\n",pcx_header->sname);

//    printf("c_p         :%d\n",(int)pcx_header->color_planes);
//    printf("b_p_l       :%d\n",(int)pcx_header->bytes_per_line);
//    printf("p_t         :%d\n",(int)pcx_header->palette_type);
//    printf("\n\n");

//    GUGWaitForKey();

    if ((gug_pcx = GUGReadPCX(argv[1])) == NULL)        // Attempt to load the PCX
    {
      GUGEnd();
      printf("Error loading %s\n",argv[1]);
      return;
    }

//    printf("Dump from GUGReadPCX()\n");
//    printf("manufacturer:%d\n",(int)gug_pcx->pcxheader.manufacturer);
//    printf("encoding    :%d\n",(int)gug_pcx->pcxheader.encoding);
//    printf("b_p_p       :%d\n",(int)gug_pcx->pcxheader.bits_per_pixel);

//    printf("xmin:%d ymin:%d\n",(int)gug_pcx->pcxheader.xmin,(int)gug_pcx->pcxheader.ymin);
//    printf("xmax:%d ymax:%d\n",(int)gug_pcx->pcxheader.xmax,(int)gug_pcx->pcxheader.ymax);

//    printf("hres:%d vres:%d\n",(int)gug_pcx->pcxheader.hres,(int)gug_pcx->pcxheader.vres);
//    printf("check_one   :%x check_two:%x\n",
//           (int)gug_pcx->pcxheader.check_one,(int)gug_pcx->pcxheader.check_two);
//    printf("sname       :%s\n",gug_pcx->pcxheader.sname);

//    printf("c_p         :%d\n",(int)gug_pcx->pcxheader.color_planes);
//    printf("b_p_l       :%d\n",(int)gug_pcx->pcxheader.bytes_per_line);
//    printf("p_t         :%d\n",(int)gug_pcx->pcxheader.palette_type);
//    printf("\n");
//    printf("x_size:%d y_size:%d\n",(int)gug_pcx->x_size,(int)gug_pcx->y_size);
//    printf("\n\n");
//    GUGWaitForKey();

    GUGStartKeyboard();                   // Install the KBD handler
    GUGSetPalette(gug_pcx->palette);      // change to the PCX's palette

    GUGShowPCX(0,0,gug_pcx);              // Place the PCX in the buffer
    GUGCopyToDisplay();                   // copy the buffer to the VGA memory
    GUGWaitForKey();                      // wait for a key press

//    GUGRotatePCX90(gug_pcx);
//    GUGClearDisplay();
//    GUGShowPCX(0,0,gug_pcx);            // Place the PCX in the buffer
//    GUGCopyToDisplay();                 // copy the buffer to the VGA memory
//    GUGWaitForKey();                    // wait for a key press

//    GUGRotatePCX90(gug_pcx);
//    GUGClearDisplay();
//    GUGShowPCX(0,0,gug_pcx);            // Place the PCX in the buffer
//    GUGCopyToDisplay();                 // copy the buffer to the VGA memory
//    GUGWaitForKey();                    // wait for a key press

//    GUGRotatePCX90(gug_pcx);
//    GUGClearDisplay();
//    GUGShowPCX(0,0,gug_pcx);            // Place the PCX in the buffer
//    GUGCopyToDisplay();                 // copy the buffer to the VGA memory
//    GUGWaitForKey();                    // wait for a key press

//    GUGRotatePCX90(gug_pcx);
//    GUGClearDisplay();
//    GUGShowPCX(0,0,gug_pcx);            // Place the PCX in the buffer
//    GUGCopyToDisplay();                 // copy the buffer to the VGA memory
//    GUGWaitForKey();                    // wait for a key press

//    GUGWritePCX("10x10.pcx",0,0, 9, 9,gug_pcx->palette);
//    GUGWritePCX("11x11.pcx",0,0,10,10,gug_pcx->palette);

    GUGStopKeyboard();                    // shut down the keyboard handler
    GUGEnd();                             // shutdown GUG
}       // end main

