#if !defined(AFX_GENERICVIEW_H__345331B1_D7E1_40F0_AB1F_652DEC53D5A1__INCLUDED_)
#define AFX_GENERICVIEW_H__345331B1_D7E1_40F0_AB1F_652DEC53D5A1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GenericView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CGenericView window

class CGenericView : public CWnd
{
// Construction
public:
	CGenericView();
	virtual ~CGenericView();

	void ResizeChildToFit(CWnd* pChildWnd) const;

protected:

	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGenericView)
	//}}AFX_VIRTUAL

protected:
	//{{AFX_MSG(CGenericView)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GENERICVIEW_H__345331B1_D7E1_40F0_AB1F_652DEC53D5A1__INCLUDED_)
