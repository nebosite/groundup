// eitsplashDlg.h : header file
//

#if !defined(AFX_EITSPLASHDLG_H__89F8EAF9_C5B0_4B68_B061_F88EEA952912__INCLUDED_)
#define AFX_EITSPLASHDLG_H__89F8EAF9_C5B0_4B68_B061_F88EEA952912__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "mystatic.h"

/////////////////////////////////////////////////////////////////////////////
// CEitsplashDlg dialog

class CEitsplashDlg : public CDialog
{
// Construction
public:
	void CheckInternet();
	CEitsplashDlg(CWnd* pParent = NULL);	// standard constructor
	CBitmap m_bmAd;
	void LoadAdFromCache();
	void  GetAdFromInternet();
	void OpenWebPage(char *szURL);
	int m_iAdID;
	HBITMAP m_hAdHandle;
	void Bail();
	HCURSOR m_hNormalCursor,m_hActiveCursor;


// Dialog Data
	//{{AFX_DATA(CEitsplashDlg)
	enum { IDD = IDD_EITSPLASH_DIALOG };
	CMyStatic	m_SplashMap;
	CStatic	m_AdFrame;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEitsplashDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;
	bool m_bDebug;
	bool SplashHitTest(int itemid);
	void OnButtonEyeball();
	void OnButtonPlay();
	void OnButtonAdhere();
	void OnButtonPurpleplanet();



	// Generated message map functions
	//{{AFX_MSG(CEitsplashDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnAdFrame();
	afx_msg void OnDestroy();
	afx_msg void OnFrameHighscores();
	afx_msg void OnFrameSubmitscores();
	afx_msg void OnFrameConfigure();
	afx_msg void OnSplashmap();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EITSPLASHDLG_H__89F8EAF9_C5B0_4B68_B061_F88EEA952912__INCLUDED_)
