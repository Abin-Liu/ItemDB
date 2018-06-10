// CharView.cpp : implementation file
//

#include "stdafx.h"
#include "ItemDB.h"
#include "CharView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCharView

CCharView::CCharView()
{
}

CCharView::~CCharView()
{
}


BEGIN_MESSAGE_MAP(CCharView, CWnd)
	//{{AFX_MSG_MAP(CCharView)
	ON_WM_SIZE()
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CCharView message handlers


void CCharView::OnSize(UINT nType, int cx, int cy) 
{
	CGenericView::OnSize(nType, cx, cy);
}

int CCharView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	return m_wndList.Create(WS_CHILD | WS_VISIBLE | LVS_AUTOARRANGE | LVS_ICON | LVS_SINGLESEL, CRect(0, 0, 1, 1), this, 0);
}
