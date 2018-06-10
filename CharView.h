#if !defined(AFX_CHARVIEW_H__1B7EB922_6C6A_40DC_AE08_CC5F11F0AD1F__INCLUDED_)
#define AFX_CHARVIEW_H__1B7EB922_6C6A_40DC_AE08_CC5F11F0AD1F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CharView.h : header file
//

#include "GenericView.h"
#include "CharList.h"

/////////////////////////////////////////////////////////////////////////////
// CCharView window

class CCharView : public CGenericView
{
// Construction
public:
	CCharView();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCharView)
	protected:
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CCharView();

	// Generated message map functions
protected:
	//{{AFX_MSG(CCharView)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

protected:

	CCharList m_wndList;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHARVIEW_H__1B7EB922_6C6A_40DC_AE08_CC5F11F0AD1F__INCLUDED_)
