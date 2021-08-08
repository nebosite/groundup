

// eittris.cpp : Defines the entry point for the eittris application.
//

#include "stdafx.h"
#include "dvwnd.h"
#include "eittris.h"
#include "conio.h"
#include "hiscore.h"
#include "resource.h"


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
					 __argv
============================================================================*/
int main(int argc, char* argv[], char* envp[])
//int main()
//int _tmain(int argc, TCHAR* argv[], TCHAR* envp[])
{
	int nRetCode = 0;
	CDVWnd dvwnd; 
	CString msg;
	bool err = 0;
	bool canplay = false;

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


		printf("Varmint's EITtris Version 1.51\n\n");	  
		
								// Check the command line
		if(argc > 1) {
			strlwr(argv[1]);
			if(strstr(argv[1],"honig")) canplay = true;
		}
								// Only run this from the slpash program
		if(!canplay) {
			AfxMessageBox("Please run eittris.exe to play Varmint's EITtris.");
			printf("Please run eittris.exe to play Varmint's EITtris.");

			return 0;
		}

		printf("Initializing DirectX...\n");

		// TODO: Check dvwnd.m_dvdrawobject.m_lpModeList 
		// for valid video modes

		if(argc > 1 && tolower(*argv[1]) == 'd') eitdebugfile = fopen("eittris.log","w");
		else eitdebugfile = NULL;
		dvwnd.m_dvdrawobject.m_LogFileHandle = eitdebugfile;
		dvwnd.m_dvinputobject.m_LogFileHandle = eitdebugfile;
		dvwnd.m_dvsoundobject.m_LogFileHandle = eitdebugfile;

		debugf("EITTRIS MAIN: Starting EITtris debug information");

								// Get Configuration
		debugf("EITTRIS MAIN: Reading configuration...");
		readconfig();

								// Crank up, do stuff, shut down
		debugf("EITTRIS MAIN: Initializing DirectX...");
		dvwnd.CreateFullScreenWindow("DirectVarmint App");
		dvwnd.Initialize();
							   
		try {
			debugf("EITTRIS MAIN: Setting Handles");
			SetDrawHandle(&(dvwnd.m_dvdrawobject));
			SetInputHandle(&(dvwnd.m_dvinputobject));
			SetSoundHandle(&(dvwnd.m_dvsoundobject));

			debugf("EITTRIS MAIN: Setting Handles");
			if(dvwnd.m_bActive && eitsetup()) { 
				debugf("EITTRIS MAIN: Reading Player configuration");
				readplayerconfig();                 
				debugf("EITTRIS MAIN: Start Execution");
				dvwnd.Execute();
			}


			debugf("EITTRIS MAIN: Finished.  CLeaning up...");
			eitcleanup();
		}
		catch(DVERR &dve) {
									// Bring up a message box if there are  
									// initialization problems.
			printf("\n\nERROR: %s\n%s",dve.m_szErrorMessage,dve.m_szExtraInfo);
			err = true;
		}
		catch(...) {
			printf("\n\nERROR: There was a unhandled exception thrown.\n");
			err = true;
		}

		debugf("EITTRIS MAIN: Cleaning up DirectVarmint");
		dvwnd.Cleanup();
		dvwnd.ShowWindow(SW_HIDE);

								// Bring the console window back so
								// it will go away cleanly.
		if(hconwnd) ::ShowWindow(hconwnd,SW_SHOW);
		if(err) {
			printf("\n\n\nPress any key to close this program ...\n");
			getch();
		}
	}

	return nRetCode;
}



