// Include file for Ground Up's Mouse handler
//

extern union  REGS inregs, outregs;
extern struct SREGS segreg;

// Primary Functions
void GUGMouseReset(int *mstatus, unsigned int *nbutton);
void GUGMouseShow(void);
void GUGMouseHide(void);
void GUGMousePosition(unsigned int *mpressed, unsigned int *mx, 
                      unsigned int *my);
void GUGMouseButtonPress(unsigned int mbutton, unsigned int *mbstate,
	                     unsigned int *numpress, unsigned int *mx, 
	                     unsigned int *my);
void GUGMouseButtonRelease(unsigned int mbutton, unsigned int *mbstatus,
	                       unsigned int *numrelease, unsigned int *mx, 
	                       unsigned int *my);
void GUGMouseHorizontalLimit(unsigned int min, unsigned int max);
void GUGMouseVerticalLimit(unsigned int min, unsigned int max);
void GUGMousePut(unsigned int mx, unsigned int my);
void GUGMouseGraphicsCursor(int *cursor, unsigned int hotx, unsigned int hoty);
void GUGMouseTextCursor(unsigned int type, unsigned int screen, 
                        unsigned int cursor);
void GUGMouseReadMotion(unsigned int *hcount, unsigned int *vcount);
void GUGMouseDefineInterupt(void far *routine, unsigned int mask);
void GUGMouseLightPenOn(void);
void GUGMouseLightPenOff(void);
void GUGMouseMickeyToPixel(unsigned int mickeyx, unsigned int mickeyy);
void GUGMouseDefineUpdate(unsigned int tlx, unsigned int tly, unsigned int brx,
	                  unsigned int bry);
void GUGMouseDefineThreshold(unsigned int speed);
void far *GUGMouseExchangeInterupt(void far *subroutine, unsigned int mask);
void GUGMouseDriverSpace(void far *buffer);
void GUGMouseSaveDriver(void far *buffer);
void GUGMouseRestoreDriver(void far *buffer);
int  GUGMouseAlternteInterupt(void far *routine, unsigned int mask);
void GUGMouseSensitivity(unsigned int hnum, unsigned int vnum, 
                         unsigned int dst);
void GugMouseReadSensitivity(unsigned int *hnum, unsigned int *vnum, 
                             unsigned int *dst);
void GUGMouseSetInteruptRate(unsigned int rate);
void GUGMouseDefinePage(unsigned int page);
unsigned int GUGMouseReturnPage(void);
void far *GUGMouseDisableDriver(void);
int  GUGMouseReenableDriver(void);
int  GUGMouseSoftwareReset(void);
void GUGMouseSetLanguage(unsigned int number);
unsigned int GUGMouseGetLanguage(void);
void GUGMouseReadInfo(unsigned int *major, unsigned int *minor, 
                      unsigned int *type,  unsigned int *irq);
void GUGMouseReadDriverInfo(unsigned int *info, unsigned int *fCursorLock,
	                    unsigned int *fInMouseCode, 
                            unsigned int *fMouseBusy);
void GUGMouseReadMAXVDC(unsigned int *enable, unsigned int *xmax, 
                        unsigned int *ymax);
void GUGMouseReadCursor(unsigned int *screen, unsigned int *cursor,
                        unsigned int *hcount, unsigned int *vcount);
unsigned int GUGMouseSetVideoMode(unsigned int mode, unsigned int font);
void far *GUGMouseListVideoModes(void);
void GUGMouseReadHotSpot(unsigned int *fCursor, unsigned int *hhot, 
                         unsigned int *vhot,	unsigned int *type);
unsigned int GUGMouseLoadCurves(unsigned int number, void far *curves);
void far *GUGMouseSaveCurves(unsigned int *curve, unsigned int *success);
char far *GUGMouseActiveCurves(int number, unsigned int *success,
                               unsigned int *curve);
int  GUGMouseHardReset(void);
void GUGMouseBallPoint(unsigned int command, int rotation, int *status,
                       unsigned int *angle, unsigned int *masks);
void GUGMouseGetVSC(unsigned int *xmin, unsigned int *ymin,unsigned int *xmax,
                    unsigned int *ymax);
unsigned int GUGMouseGetAdvanced(void);
int *GUGMouseSwitch(unsigned int *size);
char far *GUGMouseLocateINI(void);
