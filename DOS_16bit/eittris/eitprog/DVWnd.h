// Direct Varmint Wnd class.  
// This class will encapsulate all the DirectX Data and functionality of the application.

#include <DVinput.h>
#include <DVsound.h>
#include <DVdraw.h>
#include <math.h>
#include <time.h>

#if !defined(AFX_DVWND_H__CB95819E_8DB2_413D_AE54_BE2B674F4AD7__INCLUDED_)
#define AFX_DVWND_H__CB95819E_8DB2_413D_AE54_BE2B674F4AD7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DVWnd.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDVWnd window

class CDVWnd : public CWnd
{
// Construction
public:
	CDVWnd();

// Attributes
private:
	DWORD				m_dwTicksPerFrame;	// Frame Rate Control

public:
	HICON				m_hIcon;
	BOOL                m_bActive;			// Used to exit the message loop
	CDVDraw				m_dvdrawobject;		// Handle To DrectDraw stuff
	CDVInput			m_dvinputobject;	// Handle to DirectInput Stuff
	CDVSound			m_dvsoundobject;	// Handle to DirectSound Stuff
	double				m_dFPS;				// Frames per second  (calculated)
	double				m_dFrameRate;		// Target Frame Rate
	int					m_iFrame;			// Current Frame

	int					m_iResX;			// Graphics parameters
	int					m_iResY;
	int					m_iResBitDepth;

// Operations
public:
	BOOL CreateFullScreenWindow(char *WindowName,CWnd *parentwnd = NULL);
	void Initialize();
	void DoFrame();
	void Execute();
	BOOL CheckNextFrame();
	void Cleanup();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDVWnd)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CDVWnd();

	// Generated message map functions
protected:
	//{{AFX_MSG(CDVWnd)
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DVWND_H__CB95819E_8DB2_413D_AE54_BE2B674F4AD7__INCLUDED_)
