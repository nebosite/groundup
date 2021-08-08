// flabsavr.cpp
//
// Screen saver stub file for flabbergasted.
#include <windows.h>
#include <winbase.h>
#include <winreg.h>
#include <ctype.h>
#include <tchar.h>
#include <stdio.h>
								// Globals
char g_szIPath[256] = {"C:\\"};
BOOL g_bStartWithMusic = TRUE;

/*===========================================================================
	BOOL SetConfiguration()

	DESCRIPTION:	Reads the purple planet registry to set up flabbergasted
					for a run.

	      NOTES:

	  REVISIONS:
			6/13/98		Eric Jorgensen		Initial Version

============================================================================*/
BOOL SetConfiguration()
{
	LONG rval;
	HKEY regkey;
	DWORD dwsize,dwType;
	TCHAR *lpszPathValueName = _T("Install Path");

								// Get handle to the Flabbergasted reg key
	rval = RegOpenKeyEx(
		HKEY_LOCAL_MACHINE,
		_T("Software\\Purple Planet Software\\Flabbergasted!"),
		0,
		KEY_READ,
		&regkey);

	if(rval != ERROR_SUCCESS) return FALSE;

								// Extract Values
	rval =  RegQueryValueEx(
		regkey,
		lpszPathValueName,
		NULL,
		NULL,
		(LPBYTE)g_szIPath,
		&dwsize);

	if(rval != ERROR_SUCCESS) {
		RegCloseKey(regkey);
		return FALSE;
	}
							

								// All done
	RegCloseKey(regkey);
	return(TRUE);
}

/*===========================================================================
	int PASCAL WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance,LPSTR lpCmdLine, int nCmdShow)

	DESCRIPTION:

	      NOTES:

	  REVISIONS:
			6/13/98		Eric Jorgensen		Initial Version

============================================================================*/
int PASCAL WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance,LPSTR lpCmdLine, int nCmdShow)
{
	char flag = 'S';
	int err;
								// Read flabbergasted info from registry
	if(!SetConfiguration()) return 0;

								// Find out the option flag;
	if(__argc > 1) {
		char *spot = __argv[1];
		while(*spot && !isalpha(*spot)) spot++;
		if(*spot) flag = toupper(*spot);
	}
								// The only flag we support is straight
								// screen saver mode.
	if(flag == 'S') {
		TCHAR runme[500];
		TCHAR arguments[500] = _T(" -@ \"XR]\\\\\\\\YLW]KJYZ@X//0=19@mi@gkm\"");
		
		wsprintf(runme,_T("%s\\program\\flabber.exe"),g_szIPath);

								// Set up arguments and run flabbergasted.
								// Nothing seems to be working here.  
								

//		int rval = WinExec(runme,SW_SHOW);
//		ShellExecute(
//			NULL,
//			_T("open"),
//			runme,
//			arguments,
//			NULL,
//			SW_SHOW
//
//			);
//		if(rval < 32) {
//			int err = rval;	
//		}

//		BOOL bret = CreateProcess(
//			runme,
//			arguments,
//			NULL,
// 			NULL,
//			FALSE,
//			CREATE_DEFAULT_ERROR_MODE,
//			NULL,
//			NULL,
//			NULL, // pointer to STARTUPINFO 
//			NULL  // pointer to PROCESS_INFORMATION 
//		);
//		if(!bret) {
//			err = GetLastError();
//		}
	}

	return 0;
}
