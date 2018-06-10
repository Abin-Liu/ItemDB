// ReportView.cpp : implementation file
//

#include "stdafx.h"
#include "ItemDB.h"
#include "ReportView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CReportView

CReportView::CReportView()
{
}

CReportView::~CReportView()
{
}


BEGIN_MESSAGE_MAP(CReportView, CWnd)
	//{{AFX_MSG_MAP(CReportView)
	ON_WM_SIZE()
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CReportView message handlers


void CReportView::OnSize(UINT nType, int cx, int cy) 
{
	ResizeChildToFit(&m_wndChar);
	ResizeChildToFit(&m_wndSQL);
}

int CReportView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	return m_wndChar.Create(this, 0) && m_wndSQL.Create(this, 1);
}
