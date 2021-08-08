#include <stdio.h>
#include <math.h>
#include <i86.h>
#include <dos.h>
#include <stdlib.h>
#include <direct.h>
#include <bios.h>
#include <gug.h>
#include <colors.h>
#include <widgets.h>
#include <keydefs.h>
#include "sship_c.h"
#include "gu_c.h"

extern char *gug;

#define MAX   20
#define PLEN  40

#define DRIVE_UP       1
#define DRIVE_DOWN     2
#define CHANGE_PATH   11
#define ABORT_INSTALL 21
#define DO_INSTALL    22

#define MIN_FREE_NEEDED 2000000

void get_new_path(char drive,char *str,int len);
int  do_install(char drive,char *path);
int  make_path(char *path);
int  crit_err_handler(unsigned deverr,
                      unsigned errcode,
                      unsigned *devhrd);

///////////////////////////////////////////////////////////////////////////
main()
{
    char   install_drive;
    char   install_path[PLEN];
    struct GUG_cntrl *install[MAX];
    int    loop = 1;
    int    who;
    unsigned int mx,my,mb;
    int    status;
    char   mes[80];
    FILE   *in;
    struct diskfree_t *disk_data;
    struct diskinfo_t *disk_info;
    unsigned short dd_handle;
    unsigned short di_handle;
    int    dfree;
    //unsigned short dstatus;
    unsigned char dstatus;
    char     *buf;
    unsigned short buf_handle;


    disk_data = (struct diskfree_t *)GUTRealMalloc(sizeof(struct diskfree_t),
                                                          &dd_handle);
    if (disk_data == NULL)
    {
      printf("Error in GUTRealMalloc()\n");
      return;
    }

    disk_info = (struct diskinfo_t *)GUTRealMalloc(sizeof(struct diskinfo_t),
                                                          &di_handle);
    if (disk_info == NULL)
    {
      printf("Error in GUTRealMalloc()\n");
      GUTRealFree(dd_handle);
      return;
    }

    buf = (char *)GUTRealMalloc(1024,&buf_handle);
    if (buf == NULL)
    {
      printf("Error in GUTRealMalloc()\n");
      GUTRealFree(dd_handle);
      GUTRealFree(di_handle);
      return;
    }



//    _harderr(crit_err_handler); // Install the error handler

    GUGInitControl(install,MAX);

    GUGRegControlText( 50,100,DRIVE_DOWN   ," Previous ",B_BLUE ,install);
    GUGRegControlText(200,100,DRIVE_UP     ,"   Next   ",B_BLUE ,install);
    GUGRegControlText( 50,140,CHANGE_PATH  ,"   Path   ",B_BLUE ,install);
    GUGRegControlText( 50,180,ABORT_INSTALL,"   Exit   ",B_RED  ,install);
    GUGRegControlText(200,180,DO_INSTALL   ," Install! ",B_GREEN,install);
    GUGRegHidden(150,145,150,10,CHANGE_PATH,install);

    install_drive = 'c';
    strcpy(install_path,"gu\\spin");

    GUGInitialize();                      // Fire up GUG
    GUGMouseReset(&status,&mb);
    if (status == 0)
    {
      GUGEnd();
      printf("/n/nThe installer requires a mouse to run!\n");
      GUTRealFree(dd_handle);
      GUTRealFree(di_handle);
      GUTRealFree(buf_handle);
      return;
    }
    GUGStartKeyboard();                   // Install the KBD handler

    do
    {
      GUGClearDisplay();
      draw_gu(0,0,0);
      draw_gu(0,319-gu_width[0],0);

      draw_sship(0,160-(sship_width[0]/2),20);

      GUGCenterText(5,YELLOW,"Ground Up's SPIN Installer");

      sprintf(mes,"%c:\\",install_drive);
      GUGPutText(150,105,B_BLUE,mes);

//      disk_info->drive    = (install_drive-'c')+128;
//      disk_info->head     = 1;
//      disk_info->track    = 1;
//      disk_info->sector   = 1;
//      disk_info->nsectors = 1;
//      disk_info->buffer   = NULL;
//      dstatus = _bios_disk(_DISK_VERIFY,disk_info);






      dstatus =  GUTDiskStatus((install_drive-'c')+128);

      sprintf(mes,"%x",dstatus);
      GUGCenterText(50,RED,mes);

//      if (dstatus == 0x00)
      {
        if (_dos_getdiskfree((install_drive-'a'+1),disk_data) == 0)

        {
          dfree =  (disk_data->avail_clusters * disk_data->sectors_per_cluster);
          dfree *= disk_data->bytes_per_sector;
        }
        else
        {
          dfree = 0;
        }
      } 
//      else
//      {
//         dfree = 0;
//      }

     sprintf(mes,"Free Space: %1dmeg",dfree/(1024*1024));
     if (free < MIN_FREE_NEEDED)
        GUGCenterText(120,B_RED,mes);
     else
        GUGCenterText(120,B_BLUE,mes);

     sprintf(mes,"%c:\\%s",install_drive,install_path);
     GUGPutText(150,145,B_BLUE,mes);

     GUGMouseShow();
     who = GUGProcessControls(install,&mx,&my,&mb);
     GUGMouseHide();

      switch(who)
      {
	    case DRIVE_DOWN:    if (install_drive > 'c') --install_drive ;
	                        break;
	    case DRIVE_UP:      if (install_drive  < 'z') ++install_drive ;
	                        break;
	    case CHANGE_PATH:   get_new_path(install_drive,install_path,PLEN);
                                break;
	    case ABORT_INSTALL: GUGMouseShow();
	                        loop = GUGMessageBox("Really Exit?"," Yes | No ");
                    		GUGMouseHide();
	                        break;
	    case DO_INSTALL:    if (dfree < MIN_FREE_NEEDED)
                                {
                                   GUGMouseShow();
                                   GUGMessageBox("The selected drive does|not have enough free space!"," Ok ");
                                   GUGMouseHide();
                                   break;
                                }
                                else
                                {
	                          status = do_install(install_drive,install_path);
	                          if (status == 1) loop = 0;
	                          break;
                                }
      }
    }
    while (loop);

    GUGStopKeyboard();				      // shut down the keyboard handler
    GUGMouseReset(&who,&mb);
    GUGEnd();						      // shutdown GUG

    if (status == 1)
    {
      if ((in = fopen("readme.txt","r")) > NULL)
      {
        fclose(in);
        system("edit readme.txt >> NUL");
        printf("\n\nType  SPIN  to play!\n\n");
      }
      else
      {
        printf("\n\nSPIN has not installed correctly!\n");
      }
    }

    GUTRealFree(dd_handle);
    GUTRealFree(di_handle);
    GUTRealFree(buf_handle);

}       // end main

///////////////////////////////////////////////////////////////////////////
void get_new_path(char drive,char *str,int len)
{
  int c = 0;
  int y;
  char buf[80];
  char mes[80];

  do
  {
    if (strlen(str) == (len-1)) return;

    if (GUG_key_table[KEY_RETURN] == KEY_IS_DOWN) return;
    if (GUG_key_table[NUM_ENTER]  == KEY_IS_DOWN) return;

    if (GUGKeyHit())
    {
      if (GUG_key_table[KEY_BS] == KEY_IS_DOWN)
      {
        GUG_key_table[KEY_BS] = KEY_IS_UP;
        y = strlen(str);
        if (y > 0)
        {
          str[y-1] = '\0';
        }
      }
      else
      {
        sprintf(buf,"%c",GUGGetKey());
        buf[0] = tolower(buf[0]);
        if ((buf[0] > 31) && (buf[0] < 127))
        {
          strcat(str,buf);
        }
      }
    }
    GUGFillRectangle(150,145,319,155,0);
    sprintf(mes,"%c:\\%s",drive,str);
	GUGPutText(150,145,B_RED,mes);
    c++;
	if (c > 20)
    {
	  GUGFillRectangle(150+((strlen(str)+3)*7)+1,145,
	                   150+((strlen(str)+3)*7)+7,152,B_RED);
    }
	if (c >= 40) c = 0;
	GUGCopyToDisplay();
  }
  while (1 == 1);
}
//////////////////////////////////////////////////////////////////////////
int do_install(char drive,char *path)
{
  char full[80];
  int  f,x,go;

  sprintf(full,"Install too:||%c:\\%s",drive,path);
  x = strlen(full);
  if (full[x] != '\\')
  {
    strcat(full,"\\");
  }

  GUGMouseShow();
  go = GUGMessageBox(full," Yes | No ");
  GUGMouseHide();

  if (go == 1) return(0);

  sprintf(full,"%c:\\%s",drive,path);
  x = strlen(full);
  if (full[x] != '\\')
  {
    strcat(full,"\\");
  }
  f = make_path(full);

  if (f == 1)
  {
    GUGMouseShow();
    GUGMessageBox("SPIN was installed!"," OK ");
    GUGMouseHide();
  }
  return(f);
}
///////////////////////////////////////////////////////////////////////////
int make_path(char *path)
{
  char  newp[80];
  unsigned int   x,m,f;
  char  mes[80];
  char  cwd[80];
  int   handle;
  FILE  *in;

  GUGCenterText(50,B_GREEN,"Creating Directories");
  GUGCopyToDisplay();

  getcwd(cwd,80);

  for (x=3; x<strlen(path); ++x)
  {
    if (path[x] == '\\')
	{
	  strcpy(newp,path);
	  newp[x] = '\0';

      mkdir(newp);
//      sprintf(mes,"mkdir %s >> NUL",newp);
//      system(mes);
    }
  }
  _dos_getdrive(&f);   // Get current drive

  x = path[0];
  x = x - 'a' + 1;
  _dos_setdrive(x,&m); // make the default drive where we install too

  chdir(path);		   // set the default path to the install path

  if ((in = fopen("spin.exe","r")) > NULL)
  {
    fclose(in);
    GUGMouseShow();
    x = GUGMessageBox("An old installation of SPIN|was found!||Reinstall SPIN?"," Yes | No ");
    GUGMouseHide();
    if (x == 1) return(0);
  }

  GUGCenterText(60,B_GREEN,"Unzipping Archive");
  GUGCopyToDisplay();

  if (cwd[strlen(cwd)-1] == '\\') // does the cwd end in a '/'?
    sprintf(mes,"pkunzip -d -o %sspin.zip >> NUL",cwd);
  else
    sprintf(mes,"pkunzip -d -o %s\\spin.zip >> NUL",cwd);

  system(mes);  // unzip the ZIP file to the install directory

  return(1);
}

////////////////////////////////////////////////////////////////////////////
int  crit_err_handler(unsigned deverr,
                      unsigned errcode,
					  unsigned *devhrd)
{
  return(_HARDERR_FAIL);
}


