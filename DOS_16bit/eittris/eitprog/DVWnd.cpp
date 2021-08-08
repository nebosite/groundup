// DVWnd.cpp : implementation file
//

#include "stdafx.h"
#include "DVWnd.h"
#include "eittris.h"
#include "dvutil.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDVWnd

/*===========================================================================
	CDVWnd::CDVWnd()

============================================================================*/
CDVWnd::CDVWnd()
{
								// Make sure this window has the same Icon 
								// as the parent
//	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_hIcon = NULL;

	m_bActive = FALSE;		   
	m_dFPS = 0; 
	m_iFrame = 0;
		
	m_iResX = 800;	
	m_iResY = 600;      
	m_iResBitDepth = 16;
}

/*===========================================================================
	CDVWnd::~CDVWnd()

============================================================================*/
CDVWnd::~CDVWnd()
{
}


BEGIN_MESSAGE_MAP(CDVWnd, CWnd)
	//{{AFX_MSG_MAP(CDVWnd)
	ON_WM_SETFOCUS()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/*** FUNCTION HEADER *********************************************************
*	BOOL CDVWnd::CreateFullScreenWindow(char *WindowName,CWnd *parentwnd)
* 
*   DESCRIPTION:	Creates the window object needed by the Direct Draw routines
					for full screen operation.  Call this to set up a window
					before you call Execute().

*
*        INPUTS:	windowname	Title of this window
					wnd			Optionl pointer to parent window.  If no
								Parent is specified, the desktop will be
								the parent.
*
*       RETURNS:	TRUE on success
*
\******************************************************************************/
BOOL CDVWnd::CreateFullScreenWindow(char *WindowName,CWnd *parentwnd)
{
	RECT			windowmetrics;
	BOOL			result;
	CString			classname;

	if(!parentwnd) parentwnd = GetDesktopWindow();

										// Set up our window so that we can do
										// a full-screen, exclusive DirectDraw
										// Interface.

    classname = AfxRegisterWndClass(CS_HREDRAW | CS_VREDRAW,(HCURSOR)m_hIcon,0,m_hIcon) ;
		
	windowmetrics.left = 0;
	windowmetrics.top = 0;
	windowmetrics.right =  	GetSystemMetrics( SM_CXSCREEN );
	windowmetrics.bottom = 	GetSystemMetrics( SM_CYSCREEN );

	result =  CreateEx(
		WS_EX_TOPMOST , 
		classname, 
		WindowName, 
		WS_POPUP | WS_TABSTOP, 
		windowmetrics, 
		parentwnd,
		NULL);

	if(!result) {
		AfxMessageBox("Could Not Create Direct Varmint Window.");
		return FALSE;
	}

	return TRUE;
}

/*===========================================================================
	void CDVWnd::Initialize()

	DESCRIPTION:	Setup code to be called before we start doing
					real work.

============================================================================*/
void CDVWnd::Initialize()
{
	HINSTANCE		hInstance = AfxGetInstanceHandle();
	CString msg;

								// Set up the frame rate counters. The ticks
								// per frame is designed to to make the frame rate
								// a little faster than what we want so the
								// animation is smoother.  Picking the exact 
								// value causes us to miss the vertical retrace 
								// sometimes and the animation skips.
	m_dwTicksPerFrame = (int)(1000.0/(m_dFrameRate*1.1));	
	if(m_dwTicksPerFrame > 1000) m_dwTicksPerFrame = 1000;
	if(m_dwTicksPerFrame < 1) m_dwTicksPerFrame = 1;

								// By default, the window is active.  If there
								// are any problems in setup, we'll
								// set this to false.
	m_bActive = TRUE;


								// ********************************************* 
								// 
								//		INSTANTIATE DIRECT VARMINT OBJECTS
								// 
								// *********************************************

								// The order of instantiation is not really that
								// important.  I only recommend that you destroy
								// the direct varmint objects in First In,
								// Last Out order.
	try {
		m_dvdrawobject.CreateFullScreen(m_iResX,m_iResY,m_iResBitDepth,m_hWnd,BUFFERTYPE_SINGLE);
		m_dvinputobject.Create(hInstance, m_hWnd, NULL, DVINPUT_KEYBOARD);
	}
	catch(DVERR &dve) {
								// Bring up a message box if there are  
								// initialization problems.
		msg.Format("ERROR: %s\n%s",dve.m_szErrorMessage,dve.m_szExtraInfo);
		AfxMessageBox(msg);
		m_bActive = false;
		return;
	}
	catch(...) {
		AfxMessageBox("Whoa, there was a unknown exception thrown.");	
		m_bActive = false;
		return;
	}
			   
								// Start up directsound seperately so
								// we can ignore errors
	try {
		m_dvsoundobject.Create(m_hWnd,FREQ_44KHZ);
	}
	catch(DVERR &dve) {
								// Bring up a message box if there are  
								// initialization problems.
		msg.Format("ALERT: %s\n%s",dve.m_szErrorMessage,dve.m_szExtraInfo);
		AfxMessageBox(msg);
	}

								// Configure the mouse to match the graphics mode.
	m_dvinputobject.SetMouseLimits( m_dvdrawobject.m_iMaxx-1,m_dvdrawobject.m_iMaxy-1);

								// Attach the icon to our window
	SetIcon(m_hIcon,TRUE);				
	SetIcon(m_hIcon,FALSE);


								// ********************************************* 
								// 
								//			LOAD DATA, INITILIZE STUFF 
								// 
								// ********************************************* 

	// TODO:  Initialize you data objects here such as sprites, fonts, 
	// waves, etc.  If there are any failures, set m_bActive = FALSE 
	// and return.

}

/*===========================================================================
	void CDVWnd::Cleanup()

	DESCRIPTION:	Clean up stuff created in the initialize function

============================================================================*/
void CDVWnd::Cleanup()
{
	// TODO:  Delete all of your data objects that you allocated in 
	// your initialize function.

								// Destroy Direct Varmint objects.  If you don't 
								// do this, the system will be left in a funny 
								// state.  Most notably, the graphics mode will
								// be messed up and you won't be able to launch
								// a full-screen directX app until you reboot.
	m_dvsoundobject.Destroy();
	m_dvinputobject.Destroy();
	m_dvdrawobject.Destroy();

}

/*===========================================================================
	void CDVWnd::Execute()

	DESCRIPTION:	Entry point function for running your DirectX app.

============================================================================*/
void CDVWnd::Execute()
{
	MSG winmsg;

								// A window handle must have been set up
								// before we can start.
	_ASSERT(m_hWnd);


	mainmenu();                 


// ---------------------------IGNORE ------------------------------

								// Pump the Windows message loop while this window
								// is active so that out parent windows can
								// recieve windows messages.
//	while(m_bActive ) {
//								// Draw this frame
//		DoFrame();

		//TODO:  Handle your program logic here


		// TODO:  If you want windows keystrokes such as Alt-tab and 
		// ctrl-alt-delete to work, uncomment the next 4 lines.
// 		while(PeekMessage(&winmsg, NULL, 0, 0, PM_REMOVE))	{
//			TranslateMessage(&winmsg);
//			DispatchMessage(&winmsg);
//		}
//	}
								
    return;
}

/*===========================================================================
	BOOL CDVWnd::CheckNextFrame()

	DESCRIPTION:	Returns true if it is time to draw a new frame
					
============================================================================*/
BOOL CDVWnd::CheckNextFrame()
{
 	static DWORD nexttick;								// Clock value place holder
	DWORD tick;
	DWORD count;				
	
	tick = GetTickCount();

								// Look at the current tick state and compare 
								// it to the last time we checked.
	if(nexttick > tick + m_dwTicksPerFrame*2) 			// Delay too big??
		nexttick = tick + m_dwTicksPerFrame;
	if(tick < nexttick) return false;					// Not time yet??

								// Calculate frame rate	 
								// (check every 30th frame)
	if(!(m_iFrame % 30)) {
		count=TimerCheck(DVMAX_TIMERS-1);
		TimerReset(DVMAX_TIMERS-1);
		if(count <1) count = 1;
		m_dFPS = 1000000.0 / count * 30.0;
	}

								// reset the tick marker
	nexttick = GetTickCount() + m_dwTicksPerFrame;
	return true;
}

/////////////////////////////////////////////////////////////////////////////
// CDVWnd message handlers

/*===========================================================================
	void CDVWnd::OnSetFocus(CWnd* pOldWnd) 

============================================================================*/
void CDVWnd::OnSetFocus(CWnd* pOldWnd) 
{
								// Make sure we get the palette back.
	m_dvdrawobject.RealizePalette();
	CWnd::OnSetFocus(pOldWnd);
}
