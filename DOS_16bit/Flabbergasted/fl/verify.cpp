#include "stdafx.h"
#include <windows.h>


BOOL g_pwdverified = FALSE;

/*** FUNCTION HEADER *********************************************************
*	BOOL VerifyPWD(HWND hwnd)
* 
*   DESCRIPTION:	This function brings up the verify password dialog in Win95.
*
*
* [REVISIONS]
*		6/29/98		Eric Jorgensen		InitialVersion
*
\******************************************************************************/
BOOL VerifyPWD(HWND hwnd)
{ 

	HINSTANCE hpwdcpl=::LoadLibrary("PASSWORD.CPL");
	if (hpwdcpl==NULL) {
		return TRUE;
	}
  
	typedef BOOL (WINAPI *VERIFYSCREENSAVEPWD)(HWND hwnd);
	VERIFYSCREENSAVEPWD VerifyScreenSavePwd;
	VerifyScreenSavePwd=(VERIFYSCREENSAVEPWD)GetProcAddress(hpwdcpl,"VerifyScreenSavePwd");
  
	if (VerifyScreenSavePwd==NULL) {
		FreeLibrary(hpwdcpl);
		return TRUE;
	}

	BOOL bres=VerifyScreenSavePwd(hwnd); 
	FreeLibrary(hpwdcpl);
  
	return bres;
}

/*** FUNCTION HEADER *********************************************************
*	LRESULT CALLBACK SaverWindowProc(HWND hwnd,UINT msg,WPARAM wParam,LPARAM lParam)
* 
*   DESCRIPTION:	Handles Messages for the Password Verification Screensaver
*
* [REVISIONS]
*		6/29/98		Eric Jorgensen		InitialVersion
*
\******************************************************************************/
LRESULT CALLBACK SaverWindowProc(HWND hwnd,UINT msg,WPARAM wParam,LPARAM lParam)
{ 
	static BOOL pwddlgActive = FALSE;
	switch (msg){ 
//    case WM_ACTIVATE: 
//	case WM_ACTIVATEAPP: 
//	case WM_NCACTIVATE:
//		if (!wParam && ! pwddlgActive) {
//			PostMessage(hwnd,WM_CLOSE,TRUE,0);
//			return FALSE;
//		}
//		break;
	case WM_SETCURSOR:
		if(!pwddlgActive) SetCursor(NULL);
		else SetCursor(LoadCursor(NULL,IDC_ARROW));
		break;
//    case WM_LBUTTONDOWN: 
//	case WM_MBUTTONDOWN: 
//	case WM_RBUTTONDOWN: 
//		if(!pwddlgActive) PostMessage(hwnd,WM_CLOSE,TRUE,0);
//		return FALSE;
//		break;
//	case WM_SYSCOMMAND:
//		if(wParam == SC_SCREENSAVE || wParam ==  SC_CLOSE) return FALSE;
//		break;
	case WM_CLOSE:
		if (wParam && !pwddlgActive){ 
			BOOL CanClose=TRUE;
			pwddlgActive = TRUE;
			g_pwdverified=VerifyPWD(hwnd); 
			pwddlgActive = FALSE;
			DestroyWindow(hwnd);
		}
		return FALSE; 
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}

	return DefWindowProc(hwnd,msg,wParam,lParam);
}


/*** FUNCTION HEADER *********************************************************
*	void DoSaver(HWND hparwnd)
* 
*   DESCRIPTION:	Generates a new screen saver that can handle the 
					Verify password dialog.

					VARMINT SAYS:

					This is a hack.  DirectX presents some complications
					when attempting to bring up the Verify Password dialog
					box.  One way to get around DirectX is to simply exit
					completely from the DirectX part of the screensaver
					and bring up a second, normal windows screensaver which in
					turn brings up the password dialog.  It is not the
					cleanest solution in the world, but it works, so stop
					complaining.

					PS:  All this password stuff is for Win95 ONLY.  NT 
					handles passwords for you.
*
* [REVISIONS]
*		6/29/98		Eric Jorgensen		InitialVersion
*
\******************************************************************************/
BOOL DoVerifySaver(HINSTANCE hInstance)
{ 
	UINT oldval;
								// Since NT handles the password for us, we 
								// quit immediately if the OS is NT.
	OSVERSIONINFO osv; 
	osv.dwOSVersionInfoSize=sizeof(osv); 

	GetVersionEx(&osv);
	if (osv.dwPlatformId==VER_PLATFORM_WIN32_NT) return TRUE;

								// Let's set up a window for the screensaver
	WNDCLASS wc;
	HWND hVerifyWnd;

	wc.style=CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc=SaverWindowProc;
	wc.cbClsExtra=0;
	wc.cbWndExtra=0;
	wc.hInstance=hInstance;
	wc.hIcon=NULL;
	wc.hCursor=NULL;
	wc.hbrBackground=(HBRUSH)GetStockObject(BLACK_BRUSH);
	wc.lpszMenuName=NULL;
	wc.lpszClassName="FooVerifyPWDClass";

	RegisterClass(&wc);

	int cx=GetSystemMetrics(SM_CXSCREEN), cy=GetSystemMetrics(SM_CYSCREEN);

    hVerifyWnd=CreateWindowEx(
		WS_EX_TOPMOST,
		"FooVerifyPWDClass",
		"Verify Screensaver Password",
		WS_POPUP|WS_VISIBLE,
		0,0,cx,cy,
		NULL,
		NULL,
		hInstance,
		NULL
		);
  
	if (hVerifyWnd==NULL) return TRUE;  

								
								// Initialization...
	g_pwdverified = FALSE;

								// We want to close this screensaver right 
								// to bring up the Verify Password Dialog.
	PostMessage(hVerifyWnd,WM_CLOSE,TRUE,0);

								// Crank up the message loop.
	SystemParametersInfo(SPI_SCREENSAVERRUNNING,1,&oldval,0);
	MSG msg;
	while (GetMessage(&msg,NULL,0,0)) { 
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	SystemParametersInfo(SPI_SCREENSAVERRUNNING,0,&oldval,0);

								// All Done!
	return g_pwdverified;
}

/*** FUNCTION HEADER *********************************************************
*	void ChangePassword()
* 
*   DESCRIPTION:	Brings up the change password dialog box.	This only 
					ever gets called under '95, when started with 
					the /a option.
*
\******************************************************************************/
void ChangePassword()
{ 				 
								// Get a handle to the library, then the change
								// password function.
	HINSTANCE hmpr=::LoadLibrary("MPR.DLL");
	if (hmpr==NULL) return;

	typedef VOID (WINAPI *PWDCHANGEPASSWORD) (LPCSTR lpcRegkeyname,HWND hwnd,UINT uiReserved1,UINT uiReserved2);
	PWDCHANGEPASSWORD PwdChangePassword;
	PwdChangePassword=(PWDCHANGEPASSWORD)::GetProcAddress(hmpr,"PwdChangePasswordA");
	
	if (PwdChangePassword==NULL) {
		FreeLibrary(hmpr); 
		return;
	}
								// Do it.
	PwdChangePassword("SCRSAVE",GetDesktopWindow(),0,0); 
	FreeLibrary(hmpr);
}

