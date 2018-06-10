// CharList.cpp : implementation file
//

#include "stdafx.h"
#include "ItemDB.h"
#include "CharList.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCharList

CCharList::CCharList()
{
}

CCharList::~CCharList()
{
}

BEGIN_MESSAGE_MAP(CCharList, CListCtrl)
	//{{AFX_MSG_MAP(CCharList)
	ON_NOTIFY_REFLECT(NM_CUSTOMDRAW, OnCustomDraw)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCharList message handlers
void CCharList::OnCustomDraw(NMHDR* pNMHDR, LRESULT* pResult) 
{
	LPNMLVCUSTOMDRAW lplvcd = (LPNMLVCUSTOMDRAW)pNMHDR;

	switch(lplvcd->nmcd.dwDrawStage)
	{
	case CDDS_PREPAINT:
		*pResult = CDRF_NOTIFYITEMDRAW;          // ask for item notifications.
		break;

	case CDDS_ITEMPREPAINT:
		*pResult = CDRF_DODEFAULT;
		if (GetItemData(lplvcd->nmcd.dwItemSpec) & HC_FLAG)
			lplvcd->clrText = RGB(212, 32, 32);//(181, 69, 49);
		break;

	default:
		*pResult = CDRF_DODEFAULT;
		break;
	}
}
