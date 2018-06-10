// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINFRM_H__DECFCF3D_F20D_4F3A_A9EE_ABF27DF277E9__INCLUDED_)
#define AFX_MAINFRM_H__DECFCF3D_F20D_4F3A_A9EE_ABF27DF277E9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "External\\SimpleSplitter.h"
#include "RealmView.h"
#include "CharView.h"
#include "GraphicView.h"
#include "ReportView.h"

class CMainFrame : public CFrameWnd
{
	
public:
	CMainFrame();
protected: 
	DECLARE_DYNAMIC(CMainFrame)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // control bar embedded members

	CStatusBar  m_wndStatusBar;
	CToolBar    m_wndToolBar;
	CSimpleSplitter m_wndSplitterL;
	CSimpleSplitter m_wndSplitterR;
	CRealmView m_wndRealm;
	CCharView m_wndChar;
	CGraphicView m_wndGraphic;
	CReportView m_wndList;

// Generated message map functions
protected:
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__DECFCF3D_F20D_4F3A_A9EE_ABF27DF277E9__INCLUDED_)
