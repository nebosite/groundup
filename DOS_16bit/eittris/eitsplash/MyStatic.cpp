// MyStatic.cpp : implementation file
//

#include "stdafx.h"
#include "eitsplash.h"
#include "MyStatic.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyStatic

CMyStatic::CMyStatic()
{
}

CMyStatic::~CMyStatic()
{
}


BEGIN_MESSAGE_MAP(CMyStatic, CStatic)
	//{{AFX_MSG_MAP(CMyStatic)
	ON_WM_MOUSEMOVE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyStatic message handlers

void CMyStatic::OnMouseMove(UINT nFlags, CPoint point) 
{
	CWnd *parent = GetParent();
	DWORD *value = (DWORD *)&point;

	if(parent) parent->PostMessage(WM_MOUSEMOVE,nFlags,*value);
	
	CStatic::OnMouseMove(nFlags, point);
}
