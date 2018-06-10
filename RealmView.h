#if !defined(AFX_REALMVIEW_H__7A341E7D_E122_4552_91CA_B08C051974B6__INCLUDED_)
#define AFX_REALMVIEW_H__7A341E7D_E122_4552_91CA_B08C051974B6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RealmView.h : header file
//

#include "GenericView.h"

/////////////////////////////////////////////////////////////////////////////
// CRealmView window

class CRealmView : public CGenericView
{
// Construction
public:
	CRealmView();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRealmView)
	protected:
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CRealmView();

	// Generated message map functions
protected:
	//{{AFX_MSG(CRealmView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnSelchanged(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

protected:
	CTreeCtrl m_wndTree;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_REALMVIEW_H__7A341E7D_E122_4552_91CA_B08C051974B6__INCLUDED_)
