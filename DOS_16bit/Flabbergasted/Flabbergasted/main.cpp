

// Flabbergasted.cpp : Defines the entry point for the Flabbergasted application.
//

#include "stdafx.h"
#include "dvwnd.h"

#ifdef _DEBUG
#define new DEBUNEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// The one and only application object

CWinApp theApp;

/*===========================================================================
	int main(int argc, char* argv[], char* envp[])

	DESCRIPTION:	Get things started here

	  REVISIONS:
			10/26/99		Eric Jorgensen		Initial Version

============================================================================*/
int main(int argc, char* argv[], char* envp[])
{
	int nRetCode = 0;
	CDVWnd dvwnd;

	// initialize MFC and print and error on failure
	if (!AfxWinInit(::GetModuleHandle(NULL), NULL, ::GetCommandLine(), 0))
	{
		// TODO: change error code to suit your needs
	}
	else
	{
								// Hide the console WIndow
		char lpcontitle[255];
		GetConsoleTitle(lpcontitle,255);
		HWND hconwnd = FindWindow("tty",lpcontitle);
		if(hconwnd) ::ShowWindow(hconwnd,SW_HIDE);

		// TODO: Check dvwnd.m_dvdrawobject.m_lpModeList 
		// for valid video modes

								// Crank up, do stuff, shut down
		dvwnd.CreateFullScreenWindow("DirectVarmint App");
		dvwnd.Initialize();
		dvwnd.Execute();
		dvwnd.Cleanup();

								// Bring the console window back so
								// it will go away cleanly.
		if(hconwnd) ::ShowWindow(hconwnd,SW_SHOW);

	}

	return nRetCode;
}



