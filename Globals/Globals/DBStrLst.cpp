//---------------------------------------------------------------------------


#pragma hdrstop

#include "DBStrLst.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
__fastcall TDBStringList::TDBStringList (TADOConnection *db, const String &strTable, const String &strID, const String &strName)
	: TStringList ()
{
	m_db = db;
	m_query = InitQuery (m_db, NULL);
	m_strTable = strTable;
	m_strID    = m_strID;
	m_strName  = strName;
}
//---------------------------------------------------------------------------
__fastcall TDBStringList::~TDBStringList ()
{
	if (m_query != NULL) {
		m_query->Close ();
		delete m_query;
	}
}
//---------------------------------------------------------------------------
bool __fastcall TDBStringList::Load (String &strErr)
{
	String str, strSql;
	bool f;
	int id;

	Clear ();
	f = false;
	strSql = "select * from " + m_strTable + ";";
	if ((f = RunQuery (m_query, strSql, QueryOpen, strErr)) == true) {
		m_query->First ();
		while (!m_query->Eof) {
			str = m_query->Fields->FieldByName (m_strName)->AsString;
			id  = m_query->Fields->FieldByName (m_strID)->AsInteger;
			AddObject (str, (TObject*) id);
			m_query->Next();
		}
		f = true;
	}
	return (f);
}
//---------------------------------------------------------------------------
bool __fastcall TDBStringList::DeleteAllFromDB (String &strErr)
{
	String strSql;
	bool f;

	strSql = "delete from " + m_strTable + ";";
	f = RunQuery (m_query, strSql, QueryExec, strErr);
	return (f);
}
//---------------------------------------------------------------------------
bool __fastcall TDBStringList::DeleteFromDB (int id, String &strErr)
{
	String strSql;
	bool f;

	strSql = "delete from " + m_strTable + " where " + m_strID + "=" + String (id) + ";";
	f = RunQuery (m_query, strSql, QueryExec, strErr);
	return (f);
}
//---------------------------------------------------------------------------
bool __fastcall TDBStringList::DeleteContentFromDB (String &strErr)
{
	String strSql, strWhere;
	bool f;
	int n;

	if (Count) {
		strSql = "delete from " + m_strTable + " where ";
		for (n=0 ; n < Count ; n++) {
			strWhere += "(" + m_strID + "=" + String ((int) Objects[n]) + ")";
			if (n < Count - 1) {
				strWhere += " or ";
			}
		}
		strSql += strWhere + ";";
		f = RunQuery (m_query, strSql, QueryExec, strErr);
	}
	return (f);
}
//---------------------------------------------------------------------------
bool __fastcall TDBStringList::InsertToDB (String &strErr)
{
	String strSql;
	bool f;
	int n, id;

	if (Count > 0) {
		if ((f = GetFieldMax (m_query, m_strTable, m_strID, id)) == true) {
			for (n=0; (n < Count) && (f) ; n++) {
				f = InsertItemToDB (Strings[n], ++id, strErr);
			}
		}
	}
	return (f);
}
//---------------------------------------------------------------------------
bool __fastcall TDBStringList::InsertItemToDB (const String &str, int id, String &strErr)
{
	String strSql = "insert into " + m_strTable + "(" + m_strID + "," + m_strID +
			") values (" + String (id) + "," + ModifyForInsert (str) + ");";
	bool f = RunQuery (m_query, strSql, QueryExec, strErr);
	return (f);
}
//---------------------------------------------------------------------------
bool __fastcall TDBStringList::UpdateInDB (TDBStringList *dblstrOld, const String &strErr)
{
//	TDBStringList *lstrInsert, *lstrUpdate, *lstrDelete;

//	lstrInsert = new TDBStringList; lstrDelete = new TDBStringList; lstrUpdate = new TDBStringList;
//	delete lstrInsert; delete lstrUpdate; delete lstrDelete;
}
//---------------------------------------------------------------------------

