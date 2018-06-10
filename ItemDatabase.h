// ItemDatabase.h: interface for the CItemDatabase class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ITEMDATABASE_H__20560D30_3F99_4BAC_9A95_90925352A7B7__INCLUDED_)
#define AFX_ITEMDATABASE_H__20560D30_3F99_4BAC_9A95_90925352A7B7__INCLUDED_

#include "..\\external\\ado.h"
#include "D2ItemDesc.h"
#include "..\\regexp\\ServerItem.h"

enum { RECORD_FAIL = 0, RECORD_EXIST, RECORD_ADDED, RECORD_CHANGED };

typedef BOOL (CALLBACK *LISTPROC)(const CD2ItemDesc* pItem, WPARAM wParam, LPARAM lParam);

class CItemDatabase : public CSyncObj
{
public:		

	CItemDatabase();
	virtual ~CItemDatabase();

	BOOL OpenDatabase(LPCSTR lpszPath);
	void CloseDatabase();
	BOOL Execute(LPCSTR lpszCommand);
	BOOL Query(CADORecordset* pRS, LPCSTR lpszFmt, ...);

	int SearchItem(LPCSTR lpsz, CArrayEx<DWORD, DWORD>& aFound, BOOL bLike);
	BOOL LoadItemInfo(DWORD dwItemID, LPSERVERITEM lpBuffer);
	DWORD GetItemCount();
	int GetItemIDs(CArrayEx<DWORD, DWORD>& aList);
	BOOL ListItems(LISTPROC lpfn, const CArrayEx<DWORD, DWORD>& aIDs, int nStart = 0, int nCount = -1, WPARAM wParam = 0, LPARAM lParam = 0, CWnd* pProgDlg = NULL);

	int GetRealmID(LPCSTR lpszRealmName, DWORD& rResult);
	int GetAccountID(LPCSTR lpszAccountName, DWORD dwRealmID, DWORD& rResult);
	DWORD CreatePlayer(LPCCHARINFO lpChar, DWORD dwAccountID);
	DWORD GetTitleID(LPCITEMINFO p);
	BYTE GetTypeID(BYTE iTypeID);
	void CheckItemBase(LPCITEMINFO p);
	const CModLib* GetModLib() const;	
	DWORD AddItem(DWORD dwPlayerID, LPITEMINFO p);
	operator CADODatabase*();

	BOOL GetAccountPlayerFromItem(DWORD dwItemID, DWORD& rRealmID, DWORD& rAccountID, DWORD& rPlayerID);
	BOOL DeletePlayer(DWORD dwID);
	BOOL DeleteAccount(DWORD dwID);
	BOOL DeleteRealm(DWORD dwID);
	void SaveInputHistory(const CStringArray &aList, int nLimit);
	int LoadInputHistory(CStringArray& aList, int nLimit);

private:
	static CString GetItemQueryString(LPCSTR lpsz, BOOL bLike);

	int LoadModLib();
	int UpdateGetID1(LPCSTR lpszName, LPCSTR lpszTableName, LPCSTR lpszIDField, LPCSTR lpszNameField, DWORD& rResult);
	int UpdateGetID2(LPCSTR lpszName, LPCSTR lpszTableName, LPCSTR lpszIDField, LPCSTR lpszNameField, LPCSTR lpszRelateIDField, DWORD dwRelateID, DWORD& rResult);

	CADODatabase m_db;
	CModLib m_aModLib;
};

#endif // !defined(AFX_ITEMDATABASE_H__20560D30_3F99_4BAC_9A95_90925352A7B7__INCLUDED_)
