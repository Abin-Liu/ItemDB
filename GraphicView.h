#if !defined(AFX_GRAPHICVIEW_H__1F0962CD_AB04_4934_9CFC_20762A676FD9__INCLUDED_)
#define AFX_GRAPHICVIEW_H__1F0962CD_AB04_4934_9CFC_20762A676FD9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GraphicView.h : header file
//
#include "GenericView.h"
#include "External\\ReportCtrl.h"
#include "D2View.h"

/////////////////////////////////////////////////////////////////////////////
// CGraphicView window

class CGraphicView : public CGenericView
{
// Construction
public:
	CGraphicView();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGraphicView)
	protected:
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CGraphicView();

	// Generated message map functions
protected:
	//{{AFX_MSG(CGraphicView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

protected:

	CD2View m_wndD2;
	CReportCtrl m_wndChar;
	CReportCtrl m_wndSQL;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GRAPHICVIEW_H__1F0962CD_AB04_4934_9CFC_20762A676FD9__INCLUDED_)
