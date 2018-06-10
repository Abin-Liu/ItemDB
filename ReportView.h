#if !defined(AFX_REPORTVIEW_H__43351E7A_D511_4126_BB6A_FD67F6E66621__INCLUDED_)
#define AFX_REPORTVIEW_H__43351E7A_D511_4126_BB6A_FD67F6E66621__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ReportView.h : header file
//

#include "GenericView.h"
#include "External\\ReportCtrl.h"

/////////////////////////////////////////////////////////////////////////////
// CReportView window

class CReportView : public CGenericView
{
// Construction
public:
	CReportView();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CReportView)
	protected:
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CReportView();

	// Generated message map functions
protected:
	//{{AFX_MSG(CReportView)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

protected:
	CReportCtrl m_wndChar;
	CReportCtrl m_wndSQL;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_REPORTVIEW_H__43351E7A_D511_4126_BB6A_FD67F6E66621__INCLUDED_)
