// GenericView.cpp : implementation file
//

#include "stdafx.h"
#include "ItemDB.h"
#include "GenericView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGenericView

CGenericView::CGenericView()
{
}

CGenericView::~CGenericView()
{
}


BEGIN_MESSAGE_MAP(CGenericView, CWnd)
	//{{AFX_MSG_MAP(CGenericView)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CGenericView message handlers

BOOL CGenericView::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		::LoadCursor(NULL, IDC_ARROW), HBRUSH(COLOR_WINDOW+1), NULL);

	return TRUE;
}

void CGenericView::ResizeChildToFit(CWnd *pChildWnd) const
{
	if (!::IsWindow(m_hWnd) || pChildWnd == NULL || !::IsWindow(pChildWnd->m_hWnd) || pChildWnd->GetParent() != (CWnd*)this)
	{
		ASSERT(FALSE);
		return;
	}

	CRect rect;
	GetClientRect(&rect);
	pChildWnd->MoveWindow(&rect);
}
