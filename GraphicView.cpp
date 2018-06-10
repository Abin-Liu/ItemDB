// GraphicView.cpp : implementation file
//

#include "stdafx.h"
#include "ItemDB.h"
#include "GraphicView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGraphicView

CGraphicView::CGraphicView()
{
}

CGraphicView::~CGraphicView()
{
}


BEGIN_MESSAGE_MAP(CGraphicView, CWnd)
	//{{AFX_MSG_MAP(CGraphicView)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CGraphicView message handlers


int CGraphicView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	return m_wndD2.Create("", WS_VISIBLE | WS_CHILD, CRect(0, 0, 1, 1), this, 0);
}
