// flDlg.h : header file
//

#include "MyButton.h"
#include "MyComboBox.h"

#if !defined(AFX_FLDLG_H__9310A4A7_0FE3_11D2_A5AA_444553540000__INCLUDED_)
#define AFX_FLDLG_H__9310A4A7_0FE3_11D2_A5AA_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#define REGISTERED (0)
#define EVAL_PERIOD_DAYS 7

enum _fl_operations {FLOP_NORMAL, FLOP_SCREENSAVER, FLOP_SSCONFIG, FLOP_PREVIEW, FLOP_CHANGEPASSWORD };

/////////////////////////////////////////////////////////////////////////////
// CFMyBitmap   My convenience Bitmap class

class CMyBitmap : public CBitmap  
{
public:
	CMyBitmap();
	virtual ~CMyBitmap();

	void Draw(CDC *pDC,int x, int y);

};


/////////////////////////////////////////////////////////////////////////////
// CFlDlg dialog

class CFlDlg : public CDialog
{
// Construction
public:
	CFlDlg(CWnd* pParent = NULL);	// standard constructor

	int m_iOperation;

	BOOL m_bPlaySFX;
	BOOL m_bPlayMusic;
	BOOL m_bStartWithMusic;
	BOOL m_bQqQuit;
	BOOL m_bAllowWinkeys;
	BOOL m_bBetterSound;
	BOOL m_bNiceMouse;
	BOOL m_bDemoExpired;

	int  m_iMusicSelection;

	CMyBitmap m_bmPlaySFX[2];
	CMyBitmap m_bmPlayMusic[2];
	CMyBitmap m_bmStartWithMusic[2];
	CMyBitmap m_bmQqQuit[2];
	CMyBitmap m_bmAllowWinkeys[2];
	CMyBitmap m_bmBetterSound[2];
	CMyBitmap m_bmNiceMouse[2];
	CMyBitmap m_bmURL;
	CMyBitmap m_bmOK;
	CMyBitmap m_bmCancel;

	HKEY m_hkeyRegSetup;
	HKEY m_hkeyRegOptions;	

	CString m_csInstallPath;
	CString m_csUserName;
	int		m_iDaysSinceInstall;
	BOOL	m_bRegistered;

// Dialog Data
	//{{AFX_DATA(CFlDlg)
	enum { IDD = IDD_FL_DIALOG };
	CMyButton	m_btnOK;
	CMyButton	m_btnWinKeys;
	CMyButton	m_btnURL;
	CMyButton	m_btnStartMusic;
	CMyButton	m_btnSFX;
	CMyButton	m_btnQQQuit;
	CMyButton	m_btnNiceMouse;
	CMyButton	m_btnMusic;
	CMyButton	m_btnHQSound;
	CMyComboBox	m_MusicList;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFlDlg)
	public:
	virtual BOOL DestroyWindow();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
private:
	BOOL SetupRegistry();
	int FillMusicCombo();
	void SpawnFlabber();
	BOOL TestPoint(CPoint point, UINT winid);
	void DoToolTips(int ID);
	int GetCheckSum( const char* szUserName, int iDaysSinceInstall );
	void MungeParams( char* szParams );

protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CFlDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
	afx_msg void OnButtonHqsound();
	afx_msg void OnButtonMusic();
	afx_msg void OnButtonQqquit();
	afx_msg void OnButtonSfx();
	afx_msg void OnButtonStartmusic();
	afx_msg void OnButtonUrl();
	afx_msg void OnButtonWinkeys();
	virtual void OnOK();
	afx_msg void OnButtonNicemouse();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FLDLG_H__9310A4A7_0FE3_11D2_A5AA_444553540000__INCLUDED_)
