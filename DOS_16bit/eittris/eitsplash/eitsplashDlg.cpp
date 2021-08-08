// eitsplashDlg.cpp : implementation file
//

#include "stdafx.h"
#include <afxinet.h>
#include <stdio.h>
#include <stdlib.h>
#include <Wininet.h>

#include "eitsplash.h"
#include "eitsplashDlg.h"

								// Set add timeout to seven days
#define AD_TIMEOUT 604800
//#define AD_TIMEOUT 15

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEitsplashDlg dialog

CEitsplashDlg::CEitsplashDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CEitsplashDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CEitsplashDlg)
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_bDebug = false;
	m_hAdHandle = NULL;
	m_iAdID = 0;
}

void CEitsplashDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEitsplashDlg)
	DDX_Control(pDX, IDC_SPLASHMAP, m_SplashMap);
	DDX_Control(pDX, IDC_AD_FRAME, m_AdFrame);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CEitsplashDlg, CDialog)
	//{{AFX_MSG_MAP(CEitsplashDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_AD_FRAME, OnAdFrame)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_FRAME_HIGHSCORES, OnFrameHighscores)
	ON_BN_CLICKED(IDC_FRAME_SUBMITSCORES, OnFrameSubmitscores)
	ON_BN_CLICKED(IDC_FRAME_CONFIGURE, OnFrameConfigure)
	ON_BN_CLICKED(IDC_SPLASHMAP, OnSplashmap)
	ON_WM_MOUSEMOVE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEitsplashDlg message handlers

BOOL CEitsplashDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here

	SetWindowText("Varmint's EITtris");
	LoadAdFromCache();
	m_hNormalCursor = LoadCursor(NULL,IDC_ARROW);
	m_hActiveCursor = LoadCursor(NULL,IDC_UPARROW);
	CheckInternet();
					
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CEitsplashDlg::OnPaint() 
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

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CEitsplashDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}		

/*===========================================================================
	void  CEitsplashDlg::Bail()

	DESCRIPTION:

	  REVISIONS:
			1/3/00		Eric Jorgensen		Initial Version

============================================================================*/
void  CEitsplashDlg::Bail()
{
	AfxMessageBox("A \"MISSING_DATA\" error has been detected.  Please "
				  "re-install Varmint's EITtris to fix this problem.");	
	EndDialog(0);
}

/*===========================================================================
	unsigned int getchecksum(char *buffer,int seed, int size)
============================================================================*/
unsigned int getchecksum(char *buffer,int seed, int numbytes)
{
	unsigned int checksum = numbytes;
	int i;

	srand(seed);
	checksum = rand();

	for(i = 0; i < numbytes; i++) {
		checksum ^= ((unsigned int)(buffer[i]) << (i%23));
	}
	return checksum;
}

/*===========================================================================
	void  CEitsplashDlg::LoadAdFromCache()

	DESCRIPTION:	Loads an ad from the local cache

	  REVISIONS:
			1/3/00		Eric Jorgensen		Initial Version

============================================================================*/
void  CEitsplashDlg::LoadAdFromCache()
{

	CString AdList[1000];
	char buffer[1000000];
	char name[256];
	FILE *input;
	int numads = 0;
	int id=-1;
	unsigned int checksum1,checksum2;
	char *spot;
	int pick;
	int numbytes;
	WIN32_FIND_DATA fdata;
	HANDLE fhandle;

								// Get an ad list
	fhandle = FindFirstFile("cache\\ad_*.*",&fdata);
	while(fhandle != INVALID_HANDLE_VALUE) {
		AdList[numads] = fdata.cFileName;
		numads++;
		if(!FindNextFile(fhandle,&fdata)) fhandle = INVALID_HANDLE_VALUE;
	}


	if(!numads) {
		Bail();
		return;
	}

							// pick a random ad
	srand(time(NULL));
	pick = rand() % numads;

	strcpy(name,AdList[pick]);
	if(spot = strchr(name,'_')) {
		sscanf(spot+1,"%d",&id);
	}
	if(spot && (spot = strchr(spot+1,'_'))) {
		sscanf(spot+1,"%u",&checksum1);
	}

							// load ad into memory
	sprintf(name,"cache\\%s",AdList[pick]);
	input = fopen(name,"rb");
	if(!input) {
		int err1 = errno;
		int err = GetLastError();
		return;
	}
	numbytes = fread(buffer,1,999999,input);
	fclose(input);

	
							// verify checksum
	checksum2 = getchecksum(buffer,id,numbytes);

	if(checksum1 != checksum2) {
		Bail();
		return;
	}
								// Load the ad

	m_hAdHandle = (HBITMAP)LoadImage(NULL, name, IMAGE_BITMAP, 0,0, LR_LOADFROMFILE|LR_CREATEDIBSECTION);
	m_AdFrame.SetBitmap(m_hAdHandle);
	m_iAdID = id;

}



/*===========================================================================
	void  CEitsplashDlg::GetAdFromInternet()

	DESCRIPTION:

	  REVISIONS:
			1/3/00		Eric Jorgensen		Initial Version

============================================================================*/
void  CEitsplashDlg::GetAdFromInternet()
{
	char buffer[1000000];
	char buf[100] = {""},ext[100] = {""};
	int id;
	int numbytes = 0,bytesread;
	char *spot,*dataspot;
	unsigned int checksum,size;
	CString outfile = "cache\\";
	FILE *output,*input;	
	CString adfile = "cache\\ar32.b";
	char adname[256];
	time_t t_lastad;
	time_t t_now;
	int reads = 0;
	
	time(&t_now);
								// see if it is time for a new check
	if(input = fopen(adfile,"r")) {
		if(fgets(adname,255,input) && (spot = strchr(adname,'\n'))) *spot = 0;
		fgets(buf,100,input);
		t_lastad = atoi(buf);
		fclose(input);
		if(t_now - t_lastad < AD_TIMEOUT) return;
	}



	try {
								// See if there is an active connection.
								// (This code does not seem to work)
//		if(!InternetCheckConnection("http://www.purpleplanet.com",0,0)) {
//			int err = GetLastError();
//			CString msg;
//
//			msg.Format("E: %d",err);
//			AfxMessageBox(msg);
//			return;
//		}
//		AfxMessageBox("Connected!");
								// Connect to Internet
		CInternetSession isession;
		CHttpFile *input = (CHttpFile *)isession.OpenURL("http://www.purpleplanet.com/cgi-bin/ads/ct?g",1,INTERNET_FLAG_TRANSFER_BINARY | INTERNET_FLAG_RELOAD);
		
		numbytes = 0;
		do {
			reads++;
			Sleep(100);
			bytesread = input->Read(buffer+numbytes,999999-numbytes);
			numbytes += bytesread;
		} while(bytesread && reads < 100);

		input->Close();

	}
	catch(CInternetException &err) {
		char errstring[1000];
		err.GetErrorMessage(errstring,999);
	}
								// Get ID
	spot = buffer;
	sscanf(buffer,"%d",&id);
								// skip ID
	if(spot && (spot = strchr(spot,'\n'))) spot++;
								// Get filename
	if(spot) sscanf(spot,"%s",buf);
	if(spot && (spot = strchr(spot,'\n'))) spot++;
								// Get size
	if(spot) sscanf(spot,"%u",&size);
	if(spot && (spot = strchr(spot,'\n'))) spot++;
	
	if(!spot) return;
	dataspot = spot;

								// Construct a filename for the local cache
	if(spot = strchr(buf,'.')) {
		strcpy(ext,spot);
		*spot = 0;
	}

	numbytes -= (dataspot-buffer);
								// skip this ad if we didn't get it all
	if(numbytes < size * .95) {
		return;
	}

								// Clean up old ad
	DeleteFile(adname);

								// Build a filename
	checksum = getchecksum(dataspot,id,numbytes);

	strcat(buf,"_");
	sprintf(buf+strlen(buf),"%u",checksum);
	strcat(buf,ext);

	outfile += buf;
								// remember the new ad
	if(output = fopen(adfile,"w")) {
		fprintf(output,"%s\n%u\n",outfile,t_now);
		fclose(output);
	}
								// Write the file
	output = fopen(outfile,"wb");
	if(output) {
		fwrite(dataspot,1,numbytes,output);
		fclose(output);
	}
}


/*===========================================================================
	void CEitsplashDlg::OnButtonAdhere() 

	DESCRIPTION:

	  REVISIONS:
			12/31/99		Eric Jorgensen		Initial Version

============================================================================*/
void CEitsplashDlg::OnButtonAdhere() 
{
	OpenWebPage("http://www.purpleplanet.com/advertising");
}

/*===========================================================================
	void CEitsplashDlg::OnButtonEyeball() 

	DESCRIPTION:

	  REVISIONS:
			12/31/99		Eric Jorgensen		Initial Version

============================================================================*/
void CEitsplashDlg::OnButtonEyeball() 
{
	m_bDebug = true;
}

/*===========================================================================
	void CEitsplashDlg::OnButtonPlay() 

	DESCRIPTION:

	  REVISIONS:
			12/31/99		Eric Jorgensen		Initial Version

============================================================================*/
void CEitsplashDlg::OnButtonPlay() 
{
	SHELLEXECUTEINFO ExecInfo;

    ExecInfo.cbSize = sizeof(ExecInfo);
    ExecInfo.fMask = SEE_MASK_NOCLOSEPROCESS;
    ExecInfo.hwnd = m_hWnd;
    ExecInfo.lpVerb = "Open";
    ExecInfo.lpFile = "eitprog.exe";
    if(m_bDebug) ExecInfo.lpParameters = "dhonig";
	else  ExecInfo.lpParameters = "honig";
    ExecInfo.lpDirectory = "";
    ExecInfo.nShow = SW_HIDE;
    ExecInfo.hInstApp = 0;

	ShellExecuteEx( &ExecInfo );	 

	EndDialog(0);
}

/*===========================================================================
	void CEitsplashDlg::OnButtonPurpleplanet() 

	DESCRIPTION:

	  REVISIONS:
			12/31/99		Eric Jorgensen		Initial Version

============================================================================*/
void CEitsplashDlg::OnButtonPurpleplanet() 
{
	OpenWebPage("http://www.purpleplanet.com");
}

/*===========================================================================
	void CEitsplashDlg::OnAdFrame() 

	DESCRIPTION:

	  REVISIONS:
			1/3/00		Eric Jorgensen		Initial Version

============================================================================*/
void CEitsplashDlg::OnAdFrame() 
{
	char url[1000];

	sprintf(url,"http://www.purpleplanet.com/cgi-bin/ads/ct?l+%d",m_iAdID);

	OpenWebPage(url);
}

/*===========================================================================
	void CEitsplashDlg::SlpashHitTest(int itemid) 

	DESCRIPTION:

	  REVISIONS:
			12/31/99		Eric Jorgensen		Initial Version

============================================================================*/
bool CEitsplashDlg::SplashHitTest(int itemid) 
{
	POINT mousepoint;
	RECT winrect;
	CWnd *dlgitem;

	GetCursorPos(&mousepoint);
	dlgitem = GetDlgItem(itemid);
	dlgitem->GetClientRect(&winrect);
	dlgitem->ClientToScreen((POINT*) &winrect);
	dlgitem->ClientToScreen((POINT*) &winrect.right);

	if(mousepoint.x >= winrect.left	&& mousepoint.x <= winrect.right &&
		mousepoint.y >= winrect.top  && mousepoint.y <= winrect.bottom) return true;
	else return false;
}




/*===========================================================================
	void CEitsplashDlg::OnDestroy() 

	DESCRIPTION:

	  REVISIONS:
			1/3/00		Eric Jorgensen		Initial Version

============================================================================*/
void CEitsplashDlg::OnDestroy() 
{
	CDialog::OnDestroy();
	
	if(m_hAdHandle)  DeleteObject(m_hAdHandle);
	
}

/*===========================================================================
	void CEitsplashDlg::OpenWebPage(char *szURL)

	DESCRIPTION:

	  REVISIONS:
			1/4/00		Eric Jorgensen		Initial Version

============================================================================*/
void CEitsplashDlg::OpenWebPage(char *szURL)
{
								// Since the user wants to connect to the 
								// internet at this point, we will go ahead
								// and try to load an ad.
	GetAdFromInternet();

	SHELLEXECUTEINFO ExecInfo;

    ExecInfo.cbSize = sizeof(ExecInfo);
    ExecInfo.fMask = SEE_MASK_NOCLOSEPROCESS;
    ExecInfo.hwnd = m_hWnd;
    ExecInfo.lpVerb = "Open";
    ExecInfo.lpFile = szURL;
    ExecInfo.lpParameters = "";
    ExecInfo.lpDirectory = "";
    ExecInfo.nShow = 0;
    ExecInfo.hInstApp = 0;

	ShellExecuteEx( &ExecInfo );

}



/*===========================================================================
	void CEitsplashDlg::OnFrameHighscores() 

	DESCRIPTION:

	  REVISIONS:
			1/5/00		Eric Jorgensen		Initial Version

============================================================================*/
void CEitsplashDlg::OnFrameHighscores() 
{
	OpenWebPage("http://www.ericjorgensen.com/eittris/hiscores.htm");
	
}

/*===========================================================================
	void CEitsplashDlg::OnFrameSubmitscores() 

	DESCRIPTION:

	  REVISIONS:
			1/5/00		Eric Jorgensen		Initial Version

============================================================================*/
void CEitsplashDlg::OnFrameSubmitscores() 
{
	FILE *input;
	FILE *output;
	CString outname = "cache\\submit.htm";
	char score[100]={""};
	char rows[100]={""};
	char vcode[100] = {""};
	char buffer[1000];

								// Load last high score information
	if(input = fopen("webscore.txt","r")) {
		while(fgets(buffer,999,input)) {
			if(strstr(buffer,"Score:")) sscanf(buffer+7,"%s",score);
			if(strstr(buffer,"Rows:")) sscanf(buffer+6,"%s",rows);
			if(strstr(buffer,"code:")) sscanf(buffer+17,"%s",vcode);
		}
		fclose(input);
	}

	output = fopen(outname,"w");
	if(!output) return;

	fprintf(output,
		"<TITLE>Varmint's EITtris: High Score Entry Form</TITLE>"
		"<TITLE>Varmint's EITtris: High Score Entry Form</TITLE>"

		"<CENTER>"
		"<h2>Enter your EITtris high score to attain fame and glory.</h2>"
		"<FORM METHOD=\"POST\" ACTION=\"http://www.ericjorgensen.com/bin/eit/eitscore\">"
		"<TABLE BORDER>"
		"<TD>"
		"<TABLE>"
		"<TD ALIGN=right><B>Name:</B></TD><TD Align=left><INPUT TYPE=TEXT NAME=\"NAME\" SIZE=20></TD>"
		"<TR>"
		"<TD ALIGN=right><B>Words for the press?"
		"<br>Email Address?</B>"
		"</TD>"
		"<TD><INPUT TYPE=TEXT NAME=\"EMAIL\" SIZE=40>"
		"</TD>"
		"<TR>"
		"<TD ALIGN=right><B>Score:</B></TD><TD><INPUT "
		"TYPE=TEXT NAME=\"SCORE\" SIZE=8 VALUE=\"%s\">  (No commas, no spaces)</TD>"
		"<TR>"
		"<TD ALIGN=right><B>Rows:</B></TD><TD><INPUT TYPE=TEXT NAME=\"ROWS\" "
		"SIZE=4 VALUE=\"%s\"></TD>"
		"<TR>"
		"<TD ALIGN=right><B>Authentication Code:</B></TD><TD><INPUT TYPE=TEXT NAME=\"CODE\" SIZE=16 VALUE=\"%s\"></TD>"
		"<TR></TABLE></TD></TABLE>"
		"<P><CENTER><INPUT TYPE=SUBMIT Value=\"Submit Score\"></CENTER></FORM></CENTER></BODY>",
		score,rows,vcode);
	fclose(output);

	OpenWebPage((char *)(LPCTSTR)outname);
}

/*===========================================================================
	void CEitsplashDlg::OnFrameConfigure() 

	DESCRIPTION:

	  REVISIONS:
			1/5/00		Eric Jorgensen		Initial Version

============================================================================*/
void CEitsplashDlg::OnFrameConfigure() 
{

	WinExec("notepad eittris.cfg",SW_SHOW);	
}


/*===========================================================================
	void CEitsplashDlg::OnSplashmap() 

	DESCRIPTION:

	  REVISIONS:
			1/5/00		Eric Jorgensen		Initial Version

============================================================================*/
void CEitsplashDlg::OnSplashmap() 
{

	if(SplashHitTest(IDC_FRAME_EYEBALL)) OnButtonEyeball();
	else if(SplashHitTest(IDC_FRAME_PLAY)) OnButtonPlay();
	else if(SplashHitTest(IDC_FRAME_ADHERE)) OnButtonAdhere();
	else if(SplashHitTest(IDC_FRAME_PURPLEPLANET)) OnButtonPurpleplanet();
	else if(SplashHitTest(IDC_AD_FRAME)) OnAdFrame();
	else if(SplashHitTest(IDC_FRAME_HIGHSCORES)) OnFrameHighscores();
	else if(SplashHitTest(IDC_FRAME_SUBMITSCORES)) OnFrameSubmitscores();
	else if(SplashHitTest(IDC_FRAME_CONFIGURE)) OnFrameConfigure();
	
}


/*===========================================================================
	void CEitsplashDlg::OnMouseMove(UINT nFlags, CPoint point) 

	DESCRIPTION:

	  REVISIONS:
			1/5/00		Eric Jorgensen		Initial Version

============================================================================*/
void CEitsplashDlg::OnMouseMove(UINT nFlags, CPoint point) 
{
	if(	SplashHitTest(IDC_FRAME_PLAY) ||
		SplashHitTest(IDC_FRAME_ADHERE)	||
		SplashHitTest(IDC_FRAME_PURPLEPLANET)||
		SplashHitTest(IDC_AD_FRAME) ||
		SplashHitTest(IDC_FRAME_HIGHSCORES)||
		SplashHitTest(IDC_FRAME_SUBMITSCORES)||
		SplashHitTest(IDC_FRAME_CONFIGURE)) {

		SetCursor(m_hActiveCursor);
	}
	else SetCursor(m_hNormalCursor);
	
	CDialog::OnMouseMove(nFlags, point);
}

/*===========================================================================
	void CEitsplashDlg::CheckInternet()

	DESCRIPTION:

	  REVISIONS:
			2/9/00		Eric Jorgensen		Initial Version

============================================================================*/
void CEitsplashDlg::CheckInternet()
{
	DWORD dwflags = 0;
	if(InternetGetConnectedState(&dwflags,0)) {
		if(dwflags & INTERNET_FLAG_OFFLINE) return;

		GetAdFromInternet();
	}
	else {
		// no internet connection
	}

}
