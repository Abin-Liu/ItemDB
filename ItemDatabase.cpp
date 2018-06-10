// ItemDatabase.cpp: implementation of the CItemDatabase class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ItemDatabase.h"
#include "..\\External\\ProgressWnd.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#define RA_SINGLEPLAYER		1

static const LPCSTR FIELDS[] = {
	"[icode] ",
	"[storagenameeng] ",
	"[storagenamechs] ",
	"[qualitynameeng] ",
	"[qualitynamechs] ",
	"[typenameeng] ",
	"[typenamechs] ",
	"[itemtitle] ",
	NULL };

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CItemDatabase::CItemDatabase()
{

}

CItemDatabase::~CItemDatabase()
{
	CloseDatabase();
}

BOOL CItemDatabase::OpenDatabase(LPCSTR lpszPath)
{
	if (lpszPath == NULL || lpszPath[0] == 0)
		return FALSE;

	CloseDatabase();
	CString sConn;
	sConn.Format("Driver={Microsoft Access Driver (*.mdb)}; Dbq=%s;", lpszPath);
	m_db.Open(sConn);

	BOOL bOK = m_db.Open(sConn, "", "");
	m_aModLib.RemoveAll();
	if (bOK)
		LoadModLib();

	return bOK;
}

void CItemDatabase::CloseDatabase()
{
	if (m_db.IsOpen())
		m_db.Close();
}

CItemDatabase::operator CADODatabase*()
{
	return &m_db;
}

BYTE CItemDatabase::GetTypeID(BYTE iTypeID)
{
	if (!m_db.IsOpen())
		return 1;

	CString str;
	str.Format("select tid from [type] where tid=%d", iTypeID);
	CADORecordset rs(&m_db);
	rs.Open((LPCSTR)str);
	return rs.GetRecordCount() ? iTypeID : 1;
}

int CItemDatabase::UpdateGetID1(LPCSTR lpszName, LPCSTR lpszTableName, LPCSTR lpszIDField, LPCSTR lpszNameField, DWORD& rResult)
{
	if (!m_db.IsOpen())
		return RECORD_FAIL;
	
	rResult = 0;
	CString str;
	str.Format("select %s from [%s] where %s='%s'", lpszIDField, lpszTableName, lpszNameField, lpszName);
	
	CADORecordset rs(&m_db);
	rs.Open((LPCSTR)str);

	if (rs.GetRecordCount())
	{
		rs.GetFieldValue(lpszIDField, rResult);
		return RECORD_EXIST;
	}


	DWORD dwID = 0;
	str.Format("select %s from [%s] order by %s desc", lpszIDField, lpszTableName, lpszIDField);
	rs.Open((LPCSTR)str);

	if (rs.GetRecordCount())
		rs.GetFieldValue(lpszIDField, dwID);
	dwID++;

	str.Format("insert into [%s] (%s, %s) values (%d, '%s')", lpszTableName, lpszIDField, lpszNameField, dwID, lpszName);
	m_db.Execute(str);
	rResult = dwID;
	return RECORD_ADDED;
}

int CItemDatabase::UpdateGetID2(LPCSTR lpszName, LPCSTR lpszTableName, LPCSTR lpszIDField, LPCSTR lpszNameField, LPCSTR lpszRelateIDField, DWORD dwRelateID, DWORD& rResult)
{
	if (!m_db.IsOpen())
		return RECORD_FAIL;

	rResult = 0;
	CString str;
	str.Format("select %s from [%s] where %s='%s' and %s=%d", lpszIDField, lpszTableName, lpszNameField, lpszName, lpszRelateIDField, dwRelateID);

	CADORecordset rs(&m_db);
	rs.Open((LPCSTR)str);

	if (rs.GetRecordCount())
	{
		rs.GetFieldValue(lpszIDField, rResult);
		return RECORD_EXIST;
	}

	DWORD dwID = 0;
	str.Format("select %s from [%s] order by %s desc", lpszIDField, lpszTableName, lpszIDField);
	rs.Open((LPCSTR)str);

	if (rs.GetRecordCount())
		rs.GetFieldValue(lpszIDField, dwID);
	dwID++;

	str.Format("insert into [%s] (%s, %s, %s) values (%d, '%s', %d)", lpszTableName, lpszIDField, lpszNameField, lpszRelateIDField, dwID, lpszName, dwRelateID);
	m_db.Execute(str);
	rResult = dwID;
	return RECORD_ADDED;
}

int CItemDatabase::GetRealmID(LPCSTR lpszRealmName, DWORD& rResult)
{
	if (lpszRealmName == NULL || lpszRealmName[0] == 0)
	{
		rResult = RA_SINGLEPLAYER;
		return RECORD_EXIST;
	}

	return UpdateGetID1(lpszRealmName, "realm", "rid", "rname", rResult);
}

int CItemDatabase::GetAccountID(LPCSTR lpszAccountName, DWORD dwRealmID, DWORD& rResult)
{
	if (lpszAccountName == NULL || lpszAccountName[0] == 0)
	{
		rResult = RA_SINGLEPLAYER;
		return RECORD_EXIST;
	}

	return UpdateGetID2(lpszAccountName, "account", "aid", "aname", "realmid", dwRealmID, rResult);
}

DWORD CItemDatabase::CreatePlayer(LPCCHARINFO lpChar, DWORD dwAccountID)
{
	if (!m_db.IsOpen() || lpChar == NULL || lpChar->szCharName == NULL || lpChar->szCharName[0] == 0)
		return RA_SINGLEPLAYER;

	DWORD dwID = 0;
	CString str;
	str.Format("select * from [player] where accountid=%d and pname='%s'", dwAccountID, lpChar->szCharName);
	CADORecordset rs(&m_db);
	rs.Open((LPCSTR)str);

	if (rs.GetRecordCount())
	{
		rs.GetFieldValue("pid", dwID);	
		str.Format("update [player] set classid=%d, phardcore=%d, pmercclass=%d, pmercname='%s', pinvgold=%d, pstashgold=%d, pgoldlimit=%d, pweaponswitch=%d where pid=%d",
			lpChar->iCharClass, !!lpChar->iHardcore, lpChar->wMercClass, lpChar->szMercName, lpChar->dwInvGold, lpChar->dwStashGold, lpChar->dwGoldLimit, lpChar->iActiveSwitch, dwID);
		m_db.Execute(str);
	}
	else
	{
		// add		
		rs.Open("select pid from [player] order by pid desc");
		if (rs.GetRecordCount())
			rs.GetFieldValue("pid", dwID);
		dwID++;

		str.Format("insert into [player] (pid, pname, accountid, classid, phardcore, pmercclass, pmercname, pinvgold, pstashgold, pgoldlimit, pweaponswitch) values (%d, '%s', %d, %d, %d, %d, '%s', %d, %d, %d, %d)",
			dwID, lpChar->szCharName, dwAccountID, lpChar->iCharClass, !!lpChar->iHardcore, lpChar->wMercClass, lpChar->szMercName, lpChar->dwInvGold, lpChar->dwStashGold, lpChar->dwGoldLimit, lpChar->iActiveSwitch);
		m_db.Execute(str);		
	}
	return dwID;
}

void CItemDatabase::CheckItemBase(LPCITEMINFO p)
{
	if (p == NULL || !m_db.IsOpen())
		return;

	CString str;
	str.Format("select bcode from [base] where bcode='%s'", p->szCode);
	CADORecordset rs(&m_db);
	rs.Open((LPCSTR)str);

	if (rs.GetRecordCount())
		return;

	str.Format("insert into [base] (bcode, typeid, bcx, bcy, btwohand) values \
		 ('%s', %d, %d, %d, %d)",
		 p->szCode, p->iType, p->cx, p->cy, !!p->i2Hand);
	m_db.Execute(str);
}

int CItemDatabase::LoadModLib()
{
	m_aModLib.RemoveAll();

	if (!m_db.IsOpen())
		return 0;

	MODDETAIL md;
	CString sFmt;
	CADORecordset rs(&m_db);
	rs.Open("select * from [mod]");

	while (!rs.IsEof())
	{
		::memset(&md, 0, sizeof(md));
		rs.GetFieldValue("mid", md.dwModID);
		rs.GetFieldValue("mvaluecount", md.nValueCount);
		rs.GetFieldValue("mfloat", md.bFloat);
		rs.GetFieldValue("mbool", md.bBoolean);
		rs.GetFieldValue(g_bLanguage ? "chsname" : "engname", sFmt);
		::strncpy(md.szFmt, sFmt, 255);	
		m_aModLib.Add(md);
		rs.MoveNext();
	}	

	m_aModLib.Sort();
	return m_aModLib.GetSize();
}

const CModLib* CItemDatabase::GetModLib() const
{
	return &m_aModLib;
}

BOOL CItemDatabase::Execute(LPCSTR lpszCommand)
{
	if (lpszCommand == NULL || lpszCommand[0] == 0 || !m_db.IsOpen())
		return FALSE;

	return m_db.Execute(lpszCommand);
}

DWORD CItemDatabase::AddItem(DWORD dwPlayerID, LPITEMINFO p)
{
	if (p == NULL || !m_db.IsOpen())
		return 0;	

	// add to database
	DWORD dwTitleID = GetTitleID(p);
	
	CString str;
	str.Format("insert into [item] (playerid, icode, storageid, ix, iy, qualityid, isockets, iflags, istrreq, idexreq, ilvlreq, ilevel, imindmg, imaxdmg, idefense, titleid, imindura, imaxdura, iquantity, iartwork, ivalue) values (%d, '%s', %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d)",
		dwPlayerID,
		p->szCode,
		p->iStorageType,
		p->x,
		p->y,
		p->iQuality,
		p->iSockets,
		p->dwFlags,
		p->wStrReq,
		p->wDexReq,
		p->iLevelreq,
		p->iLevel,
		p->wMinDamage,
		p->wMaxDamage,
		p->wdefense,
		dwTitleID,
		p->wMinDura,
		p->wMaxDura,
		p->wQuantity,
		p->iArtwork,
		p->dwValue);

	m_db.Execute(str);	

	CADORecordset rs(&m_db);

	DWORD dwMaxItem = 0;
	rs.Open("select max (iid) as id from [item]");
	rs.GetFieldValue("id", dwMaxItem);
	
	// add mods
	static MODDETAIL md;
	for (BYTE n = 0; n < p->iModCount; n++)
	{
		md.dwModID = p->aMods[n].dwModID;
		if (m_aModLib.Find(md) != -1)
		{
			str.Format("insert into [attr] (itemid, modid, val1, val2, val3, val4) values (%d, %d, %d, %d, %d, %d)",
			dwMaxItem, p->aMods[n].dwModID, p->aMods[n].aValues[0], p->aMods[n].aValues[1], p->aMods[n].aValues[2], p->aMods[n].aValues[3]);
			m_db.Execute(str);
		}
	}

	return dwMaxItem;
}

DWORD CItemDatabase::GetTitleID(LPCITEMINFO p)
{
	if (p == NULL || p->szName[0] == 0 || !m_db.IsOpen())
		return 0;

	DWORD dwResult = 0;
	UpdateGetID1(p->szName, "title", "tid", "tname", dwResult);
	return dwResult;
}

int CItemDatabase::SearchItem(LPCSTR lpsz, CArrayEx<DWORD, DWORD>& aFound, BOOL bLike)
{
	if (lpsz == NULL || lpsz[0] == 0 || !m_db.IsOpen())
		return 0;

	CString str = GetItemQueryString(lpsz, bLike);

	CADORecordset rs(&m_db);
	rs.Open((LPCSTR)str);

	if (rs.GetRecordCount() == 0)
		return 0;

	DWORD dwID;
	int nCount = 0;

	rs.MoveFirst();
	while (!rs.IsEof())
	{
		rs.GetFieldValue("iid", dwID);
		if (aFound.Find(dwID) == -1)
		{
			aFound.Add(dwID);
			nCount++;
		}

		rs.MoveNext();
	}

	return nCount;
}

CString CItemDatabase::GetItemQueryString(LPCSTR lpsz, BOOL bLike)
{
	if (lpsz == NULL || lpsz[0] == 0)
		return "";

	CString str = "select iid from [listitem] where (";
	for (int i = 0; FIELDS[i]; i++)
	{
		str += FIELDS[i];
		if (bLike)
		{
			str += "like '%";
			str += lpsz;
			str += "%' or ";
		}
		else
		{
			str += "='";
			str += lpsz;
			str += "' or ";
		}
	}

	str.TrimRight();
	if (str.Right(2) == "or")
		str.Delete(str.GetLength() - 2, 2);
	str += ") ";

	return str;
}

BOOL CItemDatabase::LoadItemInfo(DWORD dwItemID, LPSERVERITEM lpBuffer)
{
	if (dwItemID == 0 || lpBuffer == NULL || !m_db.IsOpen())
		return FALSE;

	::memset(lpBuffer, 0, sizeof(SERVERITEM));
	CString str;
	DWORD dwVal;
	
	CADORecordset rs(&m_db);
	str.Format("select * from [listitemsimple] where iid=%d", dwItemID);
	rs.Open((LPCSTR)str);

	if (rs.GetRecordCount() == 0)
		return FALSE;

	rs.GetFieldValue("qualityid", dwVal);
	lpBuffer->iQuality = (BYTE)dwVal;

	rs.GetFieldValue("isockets", dwVal);
	lpBuffer->iSockets = (BYTE)dwVal;

	rs.GetFieldValue("iflags", lpBuffer->dwFlags);

	rs.GetFieldValue("istrreq", dwVal);
	lpBuffer->wStrReq = (WORD)dwVal;

	rs.GetFieldValue("idexreq", dwVal);
	lpBuffer->wDexReq = (WORD)dwVal;

	rs.GetFieldValue("ilvlreq", dwVal);
	lpBuffer->iLevelreq = (BYTE)dwVal;

	rs.GetFieldValue("ilevel", dwVal);
	lpBuffer->iLevel = (BYTE)dwVal;

	rs.GetFieldValue("imindmg", dwVal);
	lpBuffer->wMinDamage = (WORD)dwVal;

	rs.GetFieldValue("imaxdmg", dwVal);
	lpBuffer->wMaxDamage = (WORD)dwVal;

	rs.GetFieldValue("idefense", dwVal);
	lpBuffer->wdefense = (WORD)dwVal;

	rs.GetFieldValue("imindura", dwVal);
	lpBuffer->wMinDura = (WORD)dwVal;

	rs.GetFieldValue("imaxdura", dwVal);
	lpBuffer->wMaxDura = (WORD)dwVal;

	rs.GetFieldValue("iquantity", dwVal);
	lpBuffer->wQuantity = (WORD)dwVal;

	rs.GetFieldValue("typeid", dwVal);
	lpBuffer->iType = (BYTE)dwVal;

	rs.GetFieldValue("ivalue", lpBuffer->dwValue);

	rs.GetFieldValue("bcx", dwVal);
	lpBuffer->cx = (BYTE)dwVal;

	rs.GetFieldValue("bcy", dwVal);
	lpBuffer->cy = (BYTE)dwVal;

	rs.GetFieldValue("btwohand", dwVal);
	lpBuffer->i2Hand = (BYTE)dwVal;

	
	// load mods	
	str.Format("select * from attr where itemid=%d", dwItemID);
	MODDETAIL md;
	rs.Open((LPCSTR)str);

	for (int i = 0; i < 16 && !rs.IsEof(); i++)
	{
		rs.GetFieldValue("modid", md.dwModID);
		int nIdx = m_aModLib.Find(md);
		if (nIdx == -1)
			continue;

		const MODDETAIL& lib = m_aModLib.GetAt(nIdx);
		lpBuffer->aMods[i].dwModID = lib.dwModID;
		lpBuffer->aMods[i].dwOriginalID = lib.dwModID;
		lpBuffer->aMods[i].bBoolean = lib.bBoolean;
		lpBuffer->aMods[i].bFloat = lib.bFloat;
		lpBuffer->aMods[i].nValueCount = lib.nValueCount;

		rs.GetFieldValue("val1", lpBuffer->aMods[i].aValues[0]);
		rs.GetFieldValue("val2", lpBuffer->aMods[i].aValues[1]);
		rs.GetFieldValue("val3", lpBuffer->aMods[i].aValues[2]);
		rs.GetFieldValue("val4", lpBuffer->aMods[i].aValues[3]);

		lpBuffer->iModCount++;
		rs.MoveNext();
	}
	
	return TRUE;
}

DWORD CItemDatabase::GetItemCount()
{
	if (!m_db.IsOpen())
		return 0;

	CADORecordset rs(&m_db);
	rs.Open("select count(iid) as itemcount from [item]");
	if (rs.GetRecordCount() == 0)
		return 0;

	DWORD dwVal;
	rs.GetFieldValue("itemcount", dwVal);
	return dwVal;
}

int CItemDatabase::GetItemIDs(CArrayEx<DWORD, DWORD> &aList)
{
	if (!m_db.IsOpen())
		return 0;

	aList.RemoveAll();
	CADORecordset rs(&m_db);
	rs.Open("select iid from [item]");
	DWORD dwVal;
	while (!rs.IsEof())
	{
		rs.GetFieldValue("iid", dwVal);
		aList.Add(dwVal);
		rs.MoveNext();
	}

	return aList.GetSize();
}

int CItemDatabase::LoadInputHistory(CStringArray &aList, int nLimit)
{
	aList.RemoveAll();

	if (!m_db.IsOpen())
		return 0;

	CADORecordset rs(&m_db);
	rs.Open("select str from [inputs] order by sid desc");
	CString str;

	while (!rs.IsEof() && aList.GetSize() < nLimit)
	{
		rs.GetFieldValue("str", str);
		str.TrimLeft();
		str.TrimRight();
		if (str.IsEmpty())
			continue;

		str.Replace('^', '\'');
		aList.InsertAt(0, str);
		rs.MoveNext();
	}
	

	return aList.GetSize();
}

void CItemDatabase::SaveInputHistory(const CStringArray &aList, int nLimit)
{
	if (!m_db.IsOpen())
		return;
	
	m_db.Execute("delete from [inputs]");
	CString sQry, str;
	for (int i = 0; i < nLimit && i < aList.GetSize(); i++)
	{
		str = aList[i];
		str.Replace('\'', '^');
		sQry.Format("insert into [inputs] (str) values ('%s')", str);
		m_db.Execute(sQry);
	}
}

BOOL CItemDatabase::DeleteRealm(DWORD dwID)
{
	if (!m_db.IsOpen() || dwID < 2)
		return FALSE;

	CString str;
	str.Format("delete from realm where rid=%d", dwID);
	m_db.Execute(str);
	return TRUE;
}

BOOL CItemDatabase::DeleteAccount(DWORD dwID)
{
	if (!m_db.IsOpen() || dwID < 2)
		return FALSE;

	CString str;
	str.Format("delete from account where aid=%d", dwID);
	m_db.Execute(str);
	return TRUE;
}

BOOL CItemDatabase::DeletePlayer(DWORD dwID)
{
	if (!m_db.IsOpen())
		return FALSE;
	
	CString str;
	str.Format("delete from player where pid=%d", dwID);
	m_db.Execute(str);
	return TRUE;
}

BOOL CItemDatabase::GetAccountPlayerFromItem(DWORD dwItemID, DWORD& rRealmID, DWORD& rAccountID, DWORD& rPlayerID)
{
	if (!m_db.IsOpen())
		return FALSE;

	rRealmID = 0;
	rAccountID = 0;
	rPlayerID = 0;
	CString str;

	CADORecordset rs(&m_db);
	str.Format("select playerid, accountid, realmid from [listitem] where iid=%d", dwItemID);
	rs.Open((LPCSTR)str);
	if (rs.GetRecordCount() == 0)
		return FALSE;

	rs.GetFieldValue("realmid", rRealmID);
	rs.GetFieldValue("accountid", rAccountID);
	rs.GetFieldValue("playerid", rPlayerID);

	return TRUE;
}

BOOL CItemDatabase::ListItems(LISTPROC lpfn, const CArrayEx<DWORD, DWORD> &aIDs, int nStart, int nCount, WPARAM wParam, LPARAM lParam, CWnd* pProgDlg)
{
	if (!m_db.IsOpen())
		return FALSE;

	nStart = max(0, nStart);
	if (lpfn == NULL || nCount == 0 || nStart >= aIDs.GetSize())
		return 0;

	if (nCount < 0)
		nCount = INT_MAX;

	CString sNum;
	CString str = "select * from [listitem] where iid in (";
	aIDs.Lock();
	for (int i = nStart; i < nStart + nCount && i < aIDs.GetSize(); i++)
	{
		sNum.Format("%d, ", aIDs[i]);
		str += sNum;
	}
	aIDs.Unlock();

	str.Delete(str.GetLength() - 2, 2);
	str += ")";
	
	Lock();
	CADORecordset rs(&m_db);
	rs.Open((LPCSTR)str);
	while (!rs.IsEof())
	{
		CD2ItemDesc ds;
		BOOL bOK  = ds.FromDatabase(&rs);

		CProgressWnd* pDlg = (CProgressWnd*)pProgDlg;
		if (pDlg && ::IsWindow(pDlg->m_hWnd))
		{
			pDlg->SetText(ds.sName);
			pDlg->StepIt();
		}

		if (bOK)
		{
			if (!lpfn(&ds, wParam, lParam))
			{
				Unlock();
				return FALSE;
			}
		}
		
		rs.MoveNext();
	}

	Unlock();
	return TRUE;
}

BOOL CItemDatabase::Query(CADORecordset* pRS, LPCSTR lpszFmt, ...)
{
	if (pRS == NULL || lpszFmt == NULL || lpszFmt[0] == 0)
		return FALSE;

	va_list args;
	va_start(args, lpszFmt);
	CString str;
	str.FormatV(lpszFmt, args);
	va_end(args);

	if (str.IsEmpty())
		return FALSE;

	pRS->Open((LPCSTR)str);
	return pRS->GetRecordCount();
}