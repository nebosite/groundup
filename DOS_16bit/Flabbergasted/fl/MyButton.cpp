// MyButton.cpp : implementation file
//

#include "stdafx.h"
#include "fl.h"
#include "MyButton.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyButton

CMyButton::CMyButton()
{
}

CMyButton::~CMyButton()
{
}


BEGIN_MESSAGE_MAP(CMyButton, CButton)
	//{{AFX_MSG_MAP(CMyButton)
	ON_WM_MOUSEMOVE()
	ON_WM_DRAWITEM()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyButton message handlers

void CMyButton::OnMouseMove(UINT nFlags, CPoint point) 
{
	CWnd *pwnd;

	pwnd = GetParent();
	if(pwnd) {
		::PostMessage(pwnd->m_hWnd,WM_IDSELF,m_ID,0);	
	}
	
	CButton::OnMouseMove(nFlags, point);
}

void CMyButton::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
	// TODO: Add your code to draw the specified item
	
}

void CMyButton::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
	// TODO: Add your message handler code here and/or call default
	
//	CButton::OnDrawItem(nIDCtl, lpDrawItemStruct);
}
