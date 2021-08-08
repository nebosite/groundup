#if !defined(AFX_MYCOMBOBOX_H__AB25BDC1_1BDF_11D2_A5AA_444553540000__INCLUDED_)
#define AFX_MYCOMBOBOX_H__AB25BDC1_1BDF_11D2_A5AA_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// MyComboBox.h : header file
//
#define WM_IDSELF 0x7FFE 

/////////////////////////////////////////////////////////////////////////////
// CMyComboBox window

class CMyComboBox : public CComboBox
{
// Construction
public:
	CMyComboBox();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyComboBox)
	//}}AFX_VIRTUAL

// Implementation
public:
	int m_ID;
	virtual ~CMyComboBox();

	// Generated message map functions
protected:
	//{{AFX_MSG(CMyComboBox)
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYCOMBOBOX_H__AB25BDC1_1BDF_11D2_A5AA_444553540000__INCLUDED_)
