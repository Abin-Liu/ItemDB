// RealmView.cpp : implementation file
//

#include "stdafx.h"
#include "ItemDB.h"
#include "RealmView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRealmView

CRealmView::CRealmView()
{
}

CRealmView::~CRealmView()
{
}


BEGIN_MESSAGE_MAP(CRealmView, CWnd)
	//{{AFX_MSG_MAP(CRealmView)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_NOTIFY(TVN_SELCHANGED, 0, OnSelchanged)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CRealmView message handlers

int CRealmView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	return m_wndTree.Create(WS_CHILD | WS_VISIBLE | TVS_HASLINES | TVS_LINESATROOT | TVS_HASBUTTONS | TVS_SHOWSELALWAYS, CRect(0, 0, 1, 1), this, 0);
}

void CRealmView::OnSize(UINT nType, int cx, int cy) 
{
	ResizeChildToFit(&m_wndTree);
}

void CRealmView::OnSelchanged(NMHDR* pNMHDR, LRESULT* pResult)
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here

	*pResult = 0;
}
