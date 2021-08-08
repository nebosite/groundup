// fl.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "fl.h"
#include "flDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

								// External Functions
void runminidemo(HINSTANCE hInstance,HWND hparent);
void ChangePassword();


/////////////////////////////////////////////////////////////////////////////
// CFlApp

BEGIN_MESSAGE_MAP(CFlApp, CWinApp)
	//{{AFX_MSG_MAP(CFlApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFlApp construction

CFlApp::CFlApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CFlApp object

CFlApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CFlApp initialization

BOOL CFlApp::InitInstance()
{

	char		flag = 'N';		// Default action is normal operation
	SetDialogBkColor(RGB(255,255,255));
	CFlDlg dlg;




								// Figure out the option flag passed to us
	if(__argc > 1) flag	= *__argv[1];
	if(flag == '/') flag = *(__argv[1]+1);
	flag = toupper(flag);

	switch(toupper(flag)) {
	case 'S':					// 'S' means run the screen saver
		dlg.m_iOperation = FLOP_SCREENSAVER;
		break;	
	case 'C':					// 'C' means configure the screensaver
		dlg.m_iOperation = FLOP_SSCONFIG;
		break;
	case 'P':					// 'P' means show someting in the preview window
		dlg.m_iOperation = FLOP_PREVIEW;
		break;
	case 'A':					// 'A' means change the password (win95 only)
		dlg.m_iOperation =FLOP_CHANGEPASSWORD;
		break;
	default:
	case 'N':
		dlg.m_iOperation = FLOP_NORMAL;
	}

								// See if I am already running, refuse to run if so...
	HWND hExisting = NULL;


	hExisting = FindWindowEx( NULL, NULL, NULL, "Flabbergasted!" );
	
	if ( !hExisting )
		hExisting = FindWindowEx( NULL, NULL, "tty", "Fl" );

	if ( hExisting ) {
		if(dlg.m_iOperation != FLOP_SCREENSAVER) 
			AfxMessageBox("Flabbergasted! is already running.");

		return FALSE;	
	}

	if(dlg.m_iOperation == FLOP_PREVIEW) {
		HWND parent = (HWND)atoi(__argv[2]);
		runminidemo(AfxGetInstanceHandle(),parent);
		return 0;
	}
	else if(dlg.m_iOperation == FLOP_CHANGEPASSWORD) {
		ChangePassword();
		return 0;
	}


	m_pMainWnd = &dlg;
	int nResponse = dlg.DoModal();

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}
