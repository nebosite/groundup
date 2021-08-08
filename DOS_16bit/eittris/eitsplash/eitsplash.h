// eitsplash.h : main header file for the EITSPLASH application
//

#if !defined(AFX_EITSPLASH_H__32CC2597_0585_4302_B4FD_C1A4C6AB63D1__INCLUDED_)
#define AFX_EITSPLASH_H__32CC2597_0585_4302_B4FD_C1A4C6AB63D1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CEitsplashApp:
// See eitsplash.cpp for the implementation of this class
//

class CEitsplashApp : public CWinApp
{
public:
	CEitsplashApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEitsplashApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CEitsplashApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EITSPLASH_H__32CC2597_0585_4302_B4FD_C1A4C6AB63D1__INCLUDED_)
