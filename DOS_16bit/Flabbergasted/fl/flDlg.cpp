// flDlg.cpp : implementation file
//

#include "stdafx.h"
#include "fl.h"
#include "flDlg.h"
#include <direct.h>
#include <tchar.h>
#include <stdio.h>
#include <stdlib.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

BOOL DoVerifySaver(HINSTANCE hInstance);


// BITMAP STUFF

/*===========================================================================
	void CMyBitmap::Draw(CDC *pDC,int x, int y)

	DESCRIPTION:

	      NOTES:

	  REVISIONS:
			7/3/98		Eric Jorgensen		Initial Version

============================================================================*/
void CMyBitmap::Draw(CDC *pDC,int x, int y)
{
	BITMAP bm;
	GetObject(sizeof(BITMAP), &bm);
	CPoint size(bm.bmWidth,bm.bmHeight);
	pDC->DPtoLP(&size);

	CPoint org(0,0);
	pDC->DPtoLP(&org);

	CDC dcMem;
	dcMem.CreateCompatibleDC(pDC);
	CBitmap* pOldBitmap = dcMem.SelectObject(this);
	dcMem.SetMapMode(pDC->GetMapMode());

	pDC->BitBlt(x,y,size.x,size.y,&dcMem,org.x,org.y,SRCCOPY);
	dcMem.SelectObject(pOldBitmap);

}


CMyBitmap::CMyBitmap()
{

}

CMyBitmap::~CMyBitmap()
{

}

/////////////////////////////////////////////////////////////////////////////
// CFlDlg dialog

CFlDlg::CFlDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CFlDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CFlDlg)
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CFlDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFlDlg)
	DDX_Control(pDX, IDOK, m_btnOK);
	DDX_Control(pDX, IDC_BUTTON_WINKEYS, m_btnWinKeys);
	DDX_Control(pDX, IDC_BUTTON_URL, m_btnURL);
	DDX_Control(pDX, IDC_BUTTON_STARTMUSIC, m_btnStartMusic);
	DDX_Control(pDX, IDC_BUTTON_SFX, m_btnSFX);
	DDX_Control(pDX, IDC_BUTTON_QQQUIT, m_btnQQQuit);
	DDX_Control(pDX, IDC_BUTTON_NICEMOUSE, m_btnNiceMouse);
	DDX_Control(pDX, IDC_BUTTON_MUSIC, m_btnMusic);
	DDX_Control(pDX, IDC_BUTTON_HQSOUND, m_btnHQSound);
	DDX_Control(pDX, IDC_COMBO_MUSICLIST, m_MusicList);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CFlDlg, CDialog)
	//{{AFX_MSG_MAP(CFlDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_DRAWITEM()
	ON_BN_CLICKED(IDC_BUTTON_HQSOUND, OnButtonHqsound)
	ON_BN_CLICKED(IDC_BUTTON_MUSIC, OnButtonMusic)
	ON_BN_CLICKED(IDC_BUTTON_QQQUIT, OnButtonQqquit)
	ON_BN_CLICKED(IDC_BUTTON_SFX, OnButtonSfx)
	ON_BN_CLICKED(IDC_BUTTON_STARTMUSIC, OnButtonStartmusic)
	ON_BN_CLICKED(IDC_BUTTON_URL, OnButtonUrl)
	ON_BN_CLICKED(IDC_BUTTON_WINKEYS, OnButtonWinkeys)
	ON_BN_CLICKED(IDC_BUTTON_NICEMOUSE, OnButtonNicemouse)
	ON_WM_MOUSEMOVE()
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFlDlg message handlers

BOOL CFlDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here


								// Initialize buttons
	m_btnOK.m_ID			= IDOK;
	m_btnWinKeys.m_ID		= IDC_BUTTON_WINKEYS;
	m_btnURL.m_ID			= IDC_BUTTON_URL;
	m_btnStartMusic.m_ID	= IDC_BUTTON_STARTMUSIC;
	m_btnSFX.m_ID			= IDC_BUTTON_SFX;
	m_btnQQQuit.m_ID		= IDC_BUTTON_QQQUIT;
	m_btnNiceMouse.m_ID		= IDC_BUTTON_NICEMOUSE;
	m_btnMusic.m_ID			= IDC_BUTTON_MUSIC;
	m_btnHQSound.m_ID		= IDC_BUTTON_HQSOUND;
	m_MusicList.m_ID		= IDC_COMBO_MUSICLIST;


								// Set default options
	m_bPlaySFX = TRUE;
	m_bPlayMusic = TRUE;
	m_bStartWithMusic = TRUE;
	m_bQqQuit = FALSE;
	m_bAllowWinkeys = FALSE;
	m_bBetterSound = TRUE;
	m_bNiceMouse = TRUE;
	m_bDemoExpired = FALSE;

	m_iMusicSelection = 0;

	m_hkeyRegSetup = 0;
	m_hkeyRegOptions = 0;

	if(!SetupRegistry()) {
		AfxMessageBox("There has been a resgistry Error.  Flabbergasted will not be able to start.");
		EndDialog(0);
		return FALSE;
	}
	else {
		int n = FillMusicCombo();
		if(m_iMusicSelection > n-1) m_iMusicSelection = n-1;
		if(m_iMusicSelection < 0) m_iMusicSelection = 0;
		m_MusicList.SetCurSel(m_iMusicSelection);
	}

	if(!REGISTERED && m_iDaysSinceInstall > EVAL_PERIOD_DAYS) m_bDemoExpired = TRUE;

								// Load bitmaps
	m_bmPlaySFX[0].LoadBitmap(IDB_PLAY_SFX_0);
	m_bmPlayMusic[0].LoadBitmap(IDB_PLAY_MUSIC_0);
	m_bmStartWithMusic[0].LoadBitmap(IDB_START_WITH_MUSIC_0);
	m_bmQqQuit[0].LoadBitmap(IDB_QQ_0);
	m_bmAllowWinkeys[0].LoadBitmap(IDB_ALLOW_WINKEYS_0);
	m_bmBetterSound[0].LoadBitmap(IDB_BETTER_SOUND_0);
	m_bmNiceMouse[0].LoadBitmap(IDB_NICE_MOUSE_0);

	m_bmPlaySFX[1].LoadBitmap(IDB_PLAY_SFX_1);
	m_bmPlayMusic[1].LoadBitmap(IDB_PLAY_MUSIC_1);
	m_bmStartWithMusic[1].LoadBitmap(IDB_START_WITH_MUSIC_1);
	m_bmQqQuit[1].LoadBitmap(IDB_QQ_1);
	m_bmAllowWinkeys[1].LoadBitmap(IDB_ALLOW_WINKEYS_1);
	m_bmBetterSound[1].LoadBitmap(IDB_BETTER_SOUND_1);
	m_bmNiceMouse[1].LoadBitmap(IDB_NICE_MOUSE_1);

	m_bmURL.LoadBitmap(IDB_URL);
	m_bmCancel.LoadBitmap(IDB_CANCEL);

	if(m_bDemoExpired) 
		m_bmOK.LoadBitmap(IDB_REGISTER);
	else if(m_iOperation == FLOP_SSCONFIG)
		m_bmOK.LoadBitmap(IDB_DONE);
	else 
		m_bmOK.LoadBitmap(IDB_START);
	
	if(m_iOperation == FLOP_SSCONFIG) {
		CWnd *lpItem;
		lpItem = GetDlgItem(IDC_BUTTON_QQQUIT);
		lpItem->EnableWindow(FALSE);
		lpItem->ShowWindow(SW_HIDE);

		lpItem = GetDlgItem(IDC_BUTTON_WINKEYS);
		lpItem->EnableWindow(FALSE);
		lpItem->ShowWindow(SW_HIDE);

		lpItem = GetDlgItem(IDC_BUTTON_NICEMOUSE);
		lpItem->EnableWindow(FALSE);
		lpItem->ShowWindow(SW_HIDE);

	}
	SetWindowText("Flabbergasted!"); 

								// Set up a timer to display registration messages.
	SetTimer(1,500,NULL);		

	if(m_iOperation == FLOP_SCREENSAVER && ! m_bDemoExpired)  {
		int oldval;

		while(1) {
			SystemParametersInfo(SPI_SCREENSAVERRUNNING,1,&oldval,0); 
			SpawnFlabber();
 			SystemParametersInfo(SPI_SCREENSAVERRUNNING,0,&oldval,0); 
									// Check the password...	



			if(DoVerifySaver(AfxGetInstanceHandle())) break;
		}
		EndDialog(0);
	}


	return TRUE;  // return TRUE  unless you set the focus to a control
}

/*===========================================================================
	BOOL CFlDlg::DestroyWindow() 

	DESCRIPTION:

	      NOTES:

	  REVISIONS:
			7/4/98		Eric Jorgensen		Initial Version

============================================================================*/
BOOL CFlDlg::DestroyWindow() 
{
	RegCloseKey(m_hkeyRegSetup);
	RegCloseKey(m_hkeyRegOptions);
	return CDialog::DestroyWindow();
}

/*===========================================================================
	HKEY GetRegKey(HKEY root,TCHAR *szKey)

	DESCRIPTION:	Convenience function to get a handle to a registry key

	      NOTES:

	  REVISIONS:
			7/17/98		Eric Jorgensen		Initial Version

============================================================================*/
HKEY GetRegKey(HKEY root,TCHAR *szKey)
{
	HKEY newkey;
	DWORD disp=0;
	LONG rval;

	rval = RegCreateKeyEx(
		root,
		szKey,
		0,
		NULL,
		REG_OPTION_NON_VOLATILE,
		KEY_ALL_ACCESS,
		NULL,
		&newkey,
		&disp);

	if(rval != ERROR_SUCCESS) newkey = 0;

	return newkey;

}

/*===========================================================================
	BOOL CFlDlg::SetupRegistry()

	DESCRIPTION:

	      NOTES:

	  REVISIONS:
			7/4/98		Eric Jorgensen		Initial Version

============================================================================*/
BOOL CFlDlg::SetupRegistry()
{
	LONG rval;
	DWORD boolsize = sizeof(BOOL);
	DWORD intsize = sizeof(int);
	DWORD strsize = 512;
	TCHAR szKey[256] = _T("SOFTWARE\\Purple Planet Software\\Flabbergasted!\\Options");
	TCHAR szStr[512] = _T("");	
	int iday=0,today=0;
	time_t t;	 
	HKEY hkeyLocalSetup;


	time(&t);
	CTime ct(t);
	today = ct.GetDay() + ct.GetMonth()*31 + ct.GetYear()*365;

								// Get days since the install
	if(!REGISTERED)  {
		hkeyLocalSetup = GetRegKey(HKEY_CURRENT_USER,_T("SOFTWARE\\Purple Planet Software\\Flabbergasted!"));
		if(	hkeyLocalSetup) {
			RegQueryValueEx(hkeyLocalSetup,_T("SetupNum"),0,NULL,(LPBYTE)&iday,&intsize);
			if(!iday) {
				iday = today;
				RegSetValueEx(hkeyLocalSetup,_T("SetupNum"),0,REG_DWORD,(LPBYTE)&iday,intsize);		
			}
			RegCloseKey(hkeyLocalSetup);
		}
	}
	else iday = today;

								// Open/Create the Setup key
	m_hkeyRegSetup = GetRegKey(HKEY_LOCAL_MACHINE,_T("SOFTWARE\\Purple Planet Software\\Flabbergasted!"));
	if(!m_hkeyRegSetup) return FALSE;

								// Get Setup Options
	rval = RegQueryValueEx(m_hkeyRegSetup,_T("Install Path"),0,NULL,(LPBYTE)szStr,&strsize);
	m_csInstallPath = szStr;
								// Make sure we have an install path
	if(rval != ERROR_SUCCESS) {
		RegCloseKey(m_hkeyRegSetup);
		return FALSE;
	}

	strsize=512;
	RegQueryValueEx(m_hkeyRegSetup,_T("User Name"),0,NULL,(LPBYTE)szStr,&strsize);
	m_csUserName = szStr;


	if(m_iOperation == FLOP_SCREENSAVER || m_iOperation == FLOP_SSCONFIG)
		_tcscpy(szKey,_T("SOFTWARE\\Purple Planet Software\\Flabbergasted!\\ScreenSaver"));

								// Open/Create the Options key
	m_hkeyRegOptions = GetRegKey( HKEY_CURRENT_USER,szKey);
	if(!m_hkeyRegOptions) {
		RegCloseKey(m_hkeyRegSetup);
		return FALSE;
	}


								// Get play options
	RegQueryValueEx(m_hkeyRegOptions,_T("Play SFX"),0,NULL,(LPBYTE)&m_bPlaySFX,&boolsize);
	RegQueryValueEx(m_hkeyRegOptions,_T("Play Music"),0,NULL,(LPBYTE)&m_bPlayMusic,&boolsize);
	RegQueryValueEx(m_hkeyRegOptions,_T("Start With Music"),0,NULL,(LPBYTE)&m_bStartWithMusic,&boolsize);
	RegQueryValueEx(m_hkeyRegOptions,_T("Qq Quit"),0,NULL,(LPBYTE)&m_bQqQuit,&boolsize);
	RegQueryValueEx(m_hkeyRegOptions,_T("Allow Win keys"),0,NULL,(LPBYTE)&m_bAllowWinkeys,&boolsize);
	RegQueryValueEx(m_hkeyRegOptions,_T("Better Sound"),0,NULL,(LPBYTE)&m_bBetterSound,&boolsize);
	RegQueryValueEx(m_hkeyRegOptions,_T("Nice Mouse"),0,NULL,(LPBYTE)&m_bNiceMouse,&boolsize);
	RegQueryValueEx(m_hkeyRegOptions,_T("Music Selection"),0,NULL,(LPBYTE)&m_iMusicSelection,&intsize);



	m_iDaysSinceInstall = today - iday;
	if(m_iDaysSinceInstall < 0) m_iDaysSinceInstall *= -1;

	return TRUE;
	
}

/*===========================================================================
	void CFlDlg::FillMusicCombo() 

	DESCRIPTION:

	      NOTES:

	  REVISIONS:
			7/4/98		Eric Jorgensen		Initial Version

============================================================================*/
int CFlDlg::FillMusicCombo() 
{
	CString csMusicCfgTemplate,csAllMusic;
	WIN32_FIND_DATA fd;
	HANDLE h;
	int numfound = 0;
	FILE *allmusic,*thismusic;

								// Clear the combo list
	while(m_MusicList.GetCount()) {
		m_MusicList.DeleteString(0);
	}

								// Set up path locations
	csMusicCfgTemplate = m_csInstallPath + "\\program\\*.cfg";
	csAllMusic = m_csInstallPath + "\\program\\AllMusic.cfg";

								// Initialize the all music file
	allmusic = fopen(csAllMusic,"w");
	if(allmusic) {
		fprintf(allmusic,"// Music configuration file for Flabbergasted!\n"
						 "// Copyright (c) 1998, Purple Planet Software\n"
						 "//----------------------------------------------\n\n");
	}



	if (h = FindFirstFile(csMusicCfgTemplate,&fd)) {
		do {
			CString csFileBase = fd.cFileName;
	    	if ( csFileBase != ".." && csFileBase != "." && csFileBase != "" ) {
									// Remove ".cfg" suffix
                csFileBase = csFileBase.SpanExcluding(_T("."));
									// Add strFileBase to the Music Lists
				m_MusicList.AddString(csFileBase);
				numfound++;
								// Dump the info in this file to the all music file
				CString csThisMusic = m_csInstallPath + "\\program\\";
				csThisMusic += 	fd.cFileName;
				thismusic = fopen(csThisMusic,"r");
				if(thismusic && allmusic && csFileBase != "AllMusic") {
					fprintf(allmusic,"// Contents of %s: \n",csThisMusic);

					TCHAR str[500];
					while(fgets(str,500,thismusic)) {
						if(allmusic && str[0] != '/' && str[0] > ' ') fprintf(allmusic,"%s",str);
					}
					fprintf(allmusic,"\n\n",csThisMusic);
				}
				fclose(thismusic);
			}
		} while (FindNextFile(h,&fd));

	}

	fclose(allmusic);
	return numfound;
}

/*===========================================================================
	void CFlDlg::OnPaint() 

	DESCRIPTION:
// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.


	      NOTES:

	  REVISIONS:
			7/6/98		Eric Jorgensen		Initial Version

============================================================================*/
void CFlDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

/*===========================================================================
	HCURSOR CFlDlg::OnQueryDragIcon()

	DESCRIPTION:
// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.

	      NOTES:

	  REVISIONS:
			7/6/98		Eric Jorgensen		Initial Version

============================================================================*/
HCURSOR CFlDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

/*===========================================================================
	void CFlDlg::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct) 

	DESCRIPTION:

	      NOTES:

	  REVISIONS:
			7/6/98		Eric Jorgensen		Initial Version

============================================================================*/
void CFlDlg::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
	// TODO: Add your message handler code here and/or call default

	CDC *pdc = CDC::FromHandle(lpDrawItemStruct->hDC);

	switch(nIDCtl) {
	case IDC_BUTTON_SFX:
		m_bmPlaySFX[m_bPlaySFX].Draw(pdc,0,0);
		break;
	case IDC_BUTTON_MUSIC:
		m_bmPlayMusic[m_bPlayMusic].Draw(pdc,0,0);
		break;
	case IDC_BUTTON_STARTMUSIC:
		m_bmStartWithMusic[m_bStartWithMusic].Draw(pdc,0,0);
		break;
	case IDC_BUTTON_QQQUIT:
		m_bmQqQuit[m_bQqQuit].Draw(pdc,0,0);
		break;
	case IDC_BUTTON_WINKEYS:
		m_bmAllowWinkeys[m_bAllowWinkeys].Draw(pdc,0,0);
		break;
	case IDC_BUTTON_HQSOUND:
		m_bmBetterSound[m_bBetterSound].Draw(pdc,0,0);
		break;
	case IDC_BUTTON_NICEMOUSE:
		m_bmNiceMouse[m_bNiceMouse].Draw(pdc,0,0);
		break;
	case IDC_BUTTON_URL:
		m_bmURL.Draw(pdc,0,0);
		break;
	case IDCANCEL:
		m_bmCancel.Draw(pdc,0,0);
		break;
	case IDOK:
		m_bmOK.Draw(pdc,0,0);
		break;
	}
	
	CDialog::OnDrawItem(nIDCtl, lpDrawItemStruct);
}

/*===========================================================================
	void CFlDlg::OnButtonHqsound() 

	DESCRIPTION:

	      NOTES:

	  REVISIONS:
			7/6/98		Eric Jorgensen		Initial Version

============================================================================*/
void CFlDlg::OnButtonHqsound() 
{
//	AfxMessageBox("HQSound");
	m_bBetterSound ^= TRUE;	

	CWnd *lpitem = GetDlgItem(IDC_BUTTON_HQSOUND);
	if(lpitem) lpitem->Invalidate();
}

/*===========================================================================
	void CFlDlg::OnButtonMusic() 

	DESCRIPTION:

	      NOTES:

	  REVISIONS:
			7/6/98		Eric Jorgensen		Initial Version

============================================================================*/
void CFlDlg::OnButtonMusic() 
{
//	AfxMessageBox("OnButtonMusic");
	m_bPlayMusic ^= TRUE;	

	CWnd *lpitem = GetDlgItem(IDC_BUTTON_MUSIC);
	if(lpitem) lpitem->Invalidate();
}

/*===========================================================================
	void CFlDlg::OnButtonQqquit() 

	DESCRIPTION:

	      NOTES:

	  REVISIONS:
			7/6/98		Eric Jorgensen		Initial Version

============================================================================*/
void CFlDlg::OnButtonQqquit() 
{
//	AfxMessageBox("OnButtonQqquit");
	m_bQqQuit ^= TRUE;	

	CWnd *lpitem = GetDlgItem(IDC_BUTTON_QQQUIT);
	if(lpitem) lpitem->Invalidate();
}

/*===========================================================================
	void CFlDlg::OnButtonSfx() 

	DESCRIPTION:

	      NOTES:

	  REVISIONS:
			7/6/98		Eric Jorgensen		Initial Version

============================================================================*/
void CFlDlg::OnButtonSfx() 
{
//	AfxMessageBox("OnButtonSfx");
	m_bPlaySFX ^= TRUE;	

	CWnd *lpitem = GetDlgItem(IDC_BUTTON_SFX);
	if(lpitem) lpitem->Invalidate();
}

/*===========================================================================
	void CFlDlg::OnButtonNicemouse() 

	DESCRIPTION:

	      NOTES:

	  REVISIONS:
			7/6/98		Eric Jorgensen		Initial Version

============================================================================*/
void CFlDlg::OnButtonNicemouse() 
{
	m_bNiceMouse ^= TRUE;	

	CWnd *lpitem = GetDlgItem(IDC_BUTTON_NICEMOUSE);
	if(lpitem) lpitem->Invalidate();
}

/*===========================================================================
	void CFlDlg::OnButtonStartmusic() 

	DESCRIPTION:

	      NOTES:

	  REVISIONS:
			7/6/98		Eric Jorgensen		Initial Version

============================================================================*/
void CFlDlg::OnButtonStartmusic() 
{
	//AfxMessageBox("OnButtonStartmusic");
	m_bStartWithMusic ^= TRUE;

	CWnd *lpitem = GetDlgItem(IDC_BUTTON_STARTMUSIC);
	if(lpitem) lpitem->Invalidate();
}

/*===========================================================================
	void CFlDlg::OnButtonUrl() 

	DESCRIPTION:

	      NOTES:

	  REVISIONS:
			7/6/98		Eric Jorgensen		Initial Version

============================================================================*/
void CFlDlg::OnButtonUrl() 
{
	SHELLEXECUTEINFO ExecInfo;

    ExecInfo.cbSize = sizeof(ExecInfo);
    ExecInfo.fMask = SEE_MASK_NOCLOSEPROCESS;
    ExecInfo.hwnd = m_hWnd;
    ExecInfo.lpVerb = "Open";
    ExecInfo.lpFile = "http://www.purpleplanet.com";
    ExecInfo.lpParameters = "";
    ExecInfo.lpDirectory = "";
    ExecInfo.nShow = 0;
    ExecInfo.hInstApp = 0;

	ShellExecuteEx( &ExecInfo );
	
}

/*===========================================================================
	void CFlDlg::OnButtonWinkeys() 

	DESCRIPTION:

	      NOTES:

	  REVISIONS:
			7/6/98		Eric Jorgensen		Initial Version

============================================================================*/
void CFlDlg::OnButtonWinkeys() 
{
//	AfxMessageBox("OnButtonWinkeys");
	m_bAllowWinkeys ^= TRUE;	

	CWnd *lpitem = GetDlgItem(IDC_BUTTON_WINKEYS);
	if(lpitem) lpitem->Invalidate();
}

/*===========================================================================
	void CFlDlg::OnOK() 

	DESCRIPTION:

	      NOTES:

	  REVISIONS:
			7/6/98		Eric Jorgensen		Initial Version

============================================================================*/
void CFlDlg::OnOK() 
{
	DWORD boolsize = sizeof(BOOL);
	DWORD intsize = sizeof(int);

	m_iMusicSelection = m_MusicList.GetCurSel();

								// Write registry info
	RegSetValueEx(m_hkeyRegOptions,_T("Play SFX"),0,REG_DWORD,(LPBYTE)&m_bPlaySFX,boolsize);
	RegSetValueEx(m_hkeyRegOptions,_T("Play Music"),0,REG_DWORD,(LPBYTE)&m_bPlayMusic,boolsize);
	RegSetValueEx(m_hkeyRegOptions,_T("Start With Music"),0,REG_DWORD,(LPBYTE)&m_bStartWithMusic,boolsize);
	RegSetValueEx(m_hkeyRegOptions,_T("Qq Quit"),0,REG_DWORD,(LPBYTE)&m_bQqQuit,boolsize);
	RegSetValueEx(m_hkeyRegOptions,_T("Allow Win keys"),0,REG_DWORD,(LPBYTE)&m_bAllowWinkeys,boolsize);
	RegSetValueEx(m_hkeyRegOptions,_T("Better Sound"),0,REG_DWORD,(LPBYTE)&m_bBetterSound,boolsize);
	RegSetValueEx(m_hkeyRegOptions,_T("Nice Mouse"),0,REG_DWORD,(LPBYTE)&m_bNiceMouse,boolsize);
	RegSetValueEx(m_hkeyRegOptions,_T("Music Selection"),0,REG_DWORD,(LPBYTE)&m_iMusicSelection,intsize);

	if(m_bDemoExpired) {
		SHELLEXECUTEINFO ExecInfo;

		ExecInfo.cbSize = sizeof(ExecInfo);
		ExecInfo.fMask = SEE_MASK_NOCLOSEPROCESS;
		ExecInfo.hwnd = m_hWnd;
		ExecInfo.lpVerb = "Open";
		ExecInfo.lpFile = "http://www.purpleplanet.com/orders.html";
		ExecInfo.lpParameters = "";
		ExecInfo.lpDirectory = "";
		ExecInfo.nShow = 0;
		ExecInfo.hInstApp = 0;

		ShellExecuteEx( &ExecInfo );

	}
	else if(m_iOperation == FLOP_NORMAL) {
		SpawnFlabber();
	}

	CDialog::OnOK();
}

/*===========================================================================
	int CFlDlg::GetCheckSum( const char* szUserName, int iDaysSinceInstall )

	DESCRIPTION:

	      NOTES:

	  REVISIONS:
			7/7/98		Eric Jorgensen		Initial Version

============================================================================*/
int CFlDlg::GetCheckSum( const char* szUserName, int iDaysSinceInstall )
{
    if ( !szUserName )
        return 0;

    int iSum = strlen( szUserName );
    iSum += iDaysSinceInstall;

    for ( int i = 0; i < (int) strlen(szUserName); i++)
        iSum += szUserName[i];

    return iSum;
}


/*===========================================================================
	void  CFlDlg::MungeParams( char* szParams )

	DESCRIPTION:

	      NOTES:

	  REVISIONS:
			7/7/98		Eric Jorgensen		Initial Version

============================================================================*/
void  CFlDlg::MungeParams( char* szParams )
{
    char szTemp[256] = "",
		 szChar[2] = " ";
    strcpy( szTemp, szParams );

    for ( int i = 0; i < (int) strlen(szTemp); i++)
    	szParams[i] =  158 - szTemp[i];

    // Replace "\" with "\\" in our string
	strcpy(szTemp, "");
	for ( int j = 0; j < (int) strlen(szParams); j++ )
	{
		if ( szParams[j] == '\\' )
		{
			strcat( szTemp, "\\\\" );
		} else {
			szChar[0] = szParams[j];
			strcat( szTemp, szChar );
		}
	}

	strcpy( szParams, szTemp );


	return;
}


/*===========================================================================
	void CFlDlg::SpawnFlabber()

	DESCRIPTION:

	      NOTES:

	  REVISIONS:
			7/6/98		Eric Jorgensen		Initial Version

============================================================================*/
void CFlDlg::SpawnFlabber()
{
	// Set up all parameters and run flabbergasted

	// Change to the flabbergasted directory
	char szOldCurrDir[256] = "",
    	szUserName[256] = "",
        szParams[256] = "",
        szCmdLine[256] = "";

    _getcwd( szOldCurrDir, sizeof(szOldCurrDir) );

								// Get this exe's directory	 
    CString strFilePath = m_csInstallPath + "\\program";

    _chdir( strFilePath );

	CString strOptions;

    if ( m_iOperation == FLOP_SCREENSAVER ) strOptions += "-S ";

    if ( m_bQqQuit ) strOptions += "-H ";
    if ( m_bNiceMouse ) strOptions += "-N ";
    if ( m_bStartWithMusic ) strOptions += "-U ";

	if ( m_bPlaySFX && m_bPlayMusic ) strOptions += "-O 3 ";
	else if ( m_bPlaySFX ) strOptions += "-O 2 ";
	else if ( m_bPlayMusic ) strOptions += "-O 1 ";
	else strOptions += "-O 0 ";

    if ( m_bBetterSound )
    	strOptions += "-4 ";
								// Music Selection
	int msel = m_MusicList.GetCurSel();
	CString strMusic;
	m_MusicList.GetLBText(msel,strMusic);
	strMusic += ".cfg";

	char szShortPath[256];
	GetShortPathName(strMusic,szShortPath,256);

   	strOptions += "-M ";
	strOptions += szShortPath;

//	Application->MessageBox( strOptions.c_str(), "", MB_OK );

	strcpy(szUserName,m_csUserName);
    sprintf( szParams,
    		"FLABBERGASTED^%s^%d^%d",
            m_csUserName,
			m_iDaysSinceInstall,
            GetCheckSum( szUserName,m_iDaysSinceInstall)
    );

    MungeParams( szParams );

    if ( m_bAllowWinkeys ) {
		sprintf( szCmdLine, "Flabberk.%s -@ \"%s\" %s", "pif", szParams, strOptions );
	} else {
		sprintf( szCmdLine, "Flabber.%s -@ \"%s\" %s", "pif", szParams, strOptions );
	}


	int rval = WinExec( szCmdLine, SW_MAXIMIZE );
	if(rval < 32) {
		
//		CString str;
//		str.Format("WinExec Error:  %d",rval);
//		AfxMessageBox(str);
	}
								// This helps us insure tht we don't spawn
								// multiple window when operating as a screensaver
								// with the password turned on.
	HWND hExisting = NULL;	
	Sleep(2000);
	do {
		hExisting = FindWindowEx( NULL, NULL, "tty", "Fl" );
		if(hExisting) ::ShowWindow(hExisting,SW_MAXIMIZE);
		Sleep(1000);
	} while(hExisting);
	

	return;

}




/*===========================================================================
	BOOL CFlDlg::TestPoint(CPoint point, UINT winid)

	DESCRIPTION:

	      NOTES:

	  REVISIONS:
			7/7/98		Eric Jorgensen		Initial Version

============================================================================*/
BOOL CFlDlg::TestPoint(CPoint point, UINT winid)
{
	CWnd *lpitem = GetDlgItem(winid);
	RECT r;

	lpitem->GetWindowRect(&r);

	if(point.x > r.left && point.x < r.right) // &&
	   //point.y < r.top && point.y > r.bottom) 
	   return TRUE;
	return FALSE;
}


/*===========================================================================
	void CFlDlg::DoToolTips(int ID) 

	DESCRIPTION:

	      NOTES:

	  REVISIONS:
			7/7/98		Eric Jorgensen		Initial Version

============================================================================*/
void CFlDlg::DoToolTips(int ID) 
{
	CString csToolText;
	static int lastid = 0;

	if(lastid == ID) return;
	lastid = ID;

	if(ID ==  IDC_BUTTON_SFX) 
		csToolText = "This turns sound effects on or off.";
	else if(ID ==  IDC_BUTTON_MUSIC) 
		csToolText = "This turns music on or off.";
	else if(ID ==  IDC_BUTTON_STARTMUSIC) 
		csToolText = "When this is on, Flabbergasted! will start playing music as soon as the program starts.";
	else if(ID ==  IDC_BUTTON_QQQUIT) 
		csToolText = "This makes it trickier exit Flabbergasted!";
	else if(ID ==  IDC_BUTTON_WINKEYS) 
		csToolText = "Turn this on to allow Windows keystrokes (Alt-Tab, Alt-Enter, ...) to work with Flabbergasted!";
	else if(ID ==  IDC_BUTTON_HQSOUND) 
		csToolText = "Turn this off to make Flabbergasted! run faster on slow computers.";
	else if(ID ==  IDC_BUTTON_NICEMOUSE) 
		csToolText = "Turn this on to disable the Flabbergasted! reverse mouse key.";
	else if(ID ==  IDC_BUTTON_URL) 
		csToolText = "Click here to visit the Purple Planet web site.";
	else if(ID ==  IDOK) {
		if(m_bDemoExpired) 
			csToolText = "Click here to register Flabbergasted!";
		else if(m_iOperation == FLOP_SSCONFIG)
			csToolText = "Click here to save your screensaver settings.";
		else
			csToolText = "Click here to start having fun!";
	}
	else if(ID == IDC_COMBO_MUSICLIST) 
		csToolText = "Choose what music to play with Flabbergasted!";

	CWnd *lpitem = GetDlgItem(IDC_TEXT_KEYHELP);
	if(lpitem) {	
		lpitem->SetWindowText(csToolText);
		lpitem->Invalidate();
	}
}

/*===========================================================================
	LRESULT CFlDlg::WindowProc(UINT message, WPARAM wParam, LPARAM lParam) 

	DESCRIPTION:

	      NOTES:

	  REVISIONS:
			7/7/98		Eric Jorgensen		Initial Version

============================================================================*/
LRESULT CFlDlg::WindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{
	// TODO: Add your specialized code here and/or call the base class
	if(message == WM_IDSELF) {
		DoToolTips(wParam);
	}

	return CDialog::WindowProc(message, wParam, lParam);
}

/*===========================================================================
	void CFlDlg::OnMouseMove(UINT nFlags, CPoint point) 

	DESCRIPTION:

	      NOTES:

	  REVISIONS:
			7/15/98		Eric Jorgensen		Initial Version

============================================================================*/
void CFlDlg::OnMouseMove(UINT nFlags, CPoint point) 
{
	DoToolTips(0);
	
	CDialog::OnMouseMove(nFlags, point);
}

/*===========================================================================
	void CFlDlg::OnTimer(UINT nIDEvent) 

	DESCRIPTION:	Display registration Messages here

	      NOTES:

	  REVISIONS:
			7/16/98		Eric Jorgensen		Initial Version

============================================================================*/
void CFlDlg::OnTimer(UINT nIDEvent) 
{

	KillTimer(1);

	if(m_iOperation != FLOP_SCREENSAVER) {
		if(m_bDemoExpired) {
			MessageBox("This evaluation copy of Flabbergasted! has expired. \n\n" 
						  "You must register Flabbergasted! to continue using it legally. \n\n"
						"The registration fee is only $9.95(US) and with your \n"
						"registered version you will receive almost 100 new\n"
						"songs to listen to while you play Flabbergasted!\n",
						"Flabbergasted!",MB_OK);
		}
		else if(!REGISTERED) {
			CString str;
			str.Format(	"This is an evaluation copy of Flabbergasted!  \n\n"
						"You have %d days left in your evaluation period, \n"
						"but you can register Flabbergasted right now if you \n"
						"want to.\n\n"
						"The registration fee is only $9.95(US) and with your \n"
						"registered version you will receive almost 100 new\n"
						"songs to listen to while you play Flabbergasted! \n\n"
						"Would you like to register Flabbergasted?"
						
						,EVAL_PERIOD_DAYS-m_iDaysSinceInstall);
			int rval = MessageBox(str,"Flabbergasted!",MB_YESNO);
			if(rval == IDYES)  {
				SHELLEXECUTEINFO ExecInfo;

				ExecInfo.cbSize = sizeof(ExecInfo);
				ExecInfo.fMask = SEE_MASK_NOCLOSEPROCESS;
				ExecInfo.hwnd = m_hWnd;
				ExecInfo.lpVerb = "Open";
				ExecInfo.lpFile = "http://www.purpleplanet.com/orders.html";
				ExecInfo.lpParameters = "";
				ExecInfo.lpDirectory = "";
				ExecInfo.nShow = 0;
				ExecInfo.hInstApp = 0;

				ShellExecuteEx( &ExecInfo );
			}

		}
	}


	CDialog::OnTimer(nIDEvent);
}
