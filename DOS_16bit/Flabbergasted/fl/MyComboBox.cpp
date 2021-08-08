// MyComboBox.cpp : implementation file
//

#include "stdafx.h"
#include "fl.h"
#include "MyComboBox.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyComboBox

CMyComboBox::CMyComboBox()
{
}

CMyComboBox::~CMyComboBox()
{
}


BEGIN_MESSAGE_MAP(CMyComboBox, CComboBox)
	//{{AFX_MSG_MAP(CMyComboBox)
	ON_WM_MOUSEMOVE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyComboBox message handlers

/*===========================================================================
	void CMyComboBox::OnMouseMove(UINT nFlags, CPoint point) 

	DESCRIPTION:

	      NOTES:

	  REVISIONS:
			7/15/98		Eric Jorgensen		Initial Version

============================================================================*/
void CMyComboBox::OnMouseMove(UINT nFlags, CPoint point) 
{
	CWnd *pwnd;

	pwnd = GetParent();
	if(pwnd) {
		::PostMessage(pwnd->m_hWnd,WM_IDSELF,m_ID,0);	
	}
	
	CComboBox::OnMouseMove(nFlags, point);
}
