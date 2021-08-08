// fl.h : main header file for the FL application
//

#if !defined(AFX_FL_H__9310A4A5_0FE3_11D2_A5AA_444553540000__INCLUDED_)
#define AFX_FL_H__9310A4A5_0FE3_11D2_A5AA_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CFlApp:
// See fl.cpp for the implementation of this class
//

class CFlApp : public CWinApp
{
public:
	CFlApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFlApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CFlApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FL_H__9310A4A5_0FE3_11D2_A5AA_444553540000__INCLUDED_)
