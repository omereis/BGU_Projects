//------------------------------------------------------------------------------
#include<vcl.h>
#pragma hdrstop
#include "IDStr.h"
//------------------------------------------------------------------------------
#pragma package(smart_init)

//------------------------------------------------------------------------------
/*
String TIDStr::Table  ("");
String TIDStr::FldID  ("");
String TIDStr::FldName("");
String TIDStr::Table  ("");
String TIDStr::FldID  ("");
String TIDStr::FldStr ("");
*/
//------------------------------------------------------------------------------
__fastcall TIDStr::TIDStr ()
{
	Clear();
}
//------------------------------------------------------------------------------
__fastcall TIDStr::TIDStr (const TIDStr &other)
{
	AssignAll (other);
}
//------------------------------------------------------------------------------
TIDStr __fastcall TIDStr::operator= (const TIDStr &other)
{
	AssignAll (other);
	return (*this);
}
//------------------------------------------------------------------------------
void __fastcall TIDStr::AssignAll (const TIDStr &other)
{
	ID     = other.ID;
	Name   = other.Name;
}
//------------------------------------------------------------------------------
void __fastcall TIDStr::Clear ()
{
	ID     = 0;
	Name   = "";
}
//------------------------------------------------------------------------------
bool __fastcall TIDStr::operator== (const TIDStr &other) const
{
	if (ID     != other.ID)
		return (false);
	if (Name   != other.Name)
		return (false);
	return (true);
}
//------------------------------------------------------------------------------
void __fastcall TIDStr::SetID (const int value)
{
	m_nID = value;
}
//------------------------------------------------------------------------------
int __fastcall TIDStr::GetID () const
{
	return (m_nID);
}
//------------------------------------------------------------------------------
void __fastcall TIDStr::SetName (const String &value)
{
	m_strName = value;
}
//------------------------------------------------------------------------------
String __fastcall TIDStr::GetName () const
{
	return (m_strName);
}
//------------------------------------------------------------------------------
bool __fastcall TIDStr::LoadFromDB (TADOQuery *query, const String strTable, const String strFldID, const String &strFldStr)
{
	bool f = true;

	try {
		ID   = query->Fields->FieldByName (strFldID)->AsInteger;
		Name = query->Fields->FieldByName (strFldStr)->AsString;
	}
	catch (...) {
		f = false;
	}
	return (f);;
}
//------------------------------------------------------------------------------
bool __fastcall TIDStr::InsertAsNew (TADOQuery *query, const String &strTable, const String &strFldID, String &strErr)
{
	int id;
	bool f;
	String strSql;

	f = GetFieldMax (query, strTable, strFldID, id);
	if (f) {
		strSql = "insert into " + strTable + "(" + strFldID + ") values (" +
				String (id + 1) + ");";
		f = RunQuery (query, strSql, QueryExec, strErr);
	}
	return (f);
}
//------------------------------------------------------------------------------
bool __fastcall TIDStr::InsertAsNew (TADOConnection *db, const String &strTable, const String &strFldID, String &strErr)
{
	bool f;
	TADOQuery *query = InitQuery (db, NULL);
	
	f = InsertAsNew(query, strTable, strFldID, strErr);
	delete query;
	return (f);
}
//------------------------------------------------------------------------------
bool __fastcall TIDStr::UpdateInDB (TADOQuery *query, const String &strTable, const String &strFldID, const String &strFldStr, String &strErr)
{
	String strSql;
	bool f;

	strSql = "update " + strTable + "set "  + ModifyForUpdate(strFldID, ID) + ", " +
/*
				ModifyForUpdate(FldName, Name) + ", " +
				ModifyForUpdate(Table, Table) + ", " +
				ModifyForUpdate(FldID, FldID) + ", " +
*/
				ModifyForUpdate(strFldStr, Name) +
			"where " + strFldID + " = " + String(ID);
	f = RunQuery(query, strSql, QueryExec, strErr);
	return (f);
}
//------------------------------------------------------------------------------
bool __fastcall TIDStr::UpdateInDB (TADOConnection *db, const String &strTable, const String &strFldID, const String &strFldStr, String &strErr)
{
	bool f;
	TADOQuery *query = InitQuery (db, NULL);

	f = UpdateInDB(query, strTable, strFldID, strFldStr, strErr);
	delete query;
	return (f);
}
//------------------------------------------------------------------------------
bool __fastcall TIDStr::DeleteInDB (TADOConnection *db, const String &strTable, const String &strFldID, const String &strFldStr, String &strErr)
{
	bool f;
	TADOQuery *query = InitQuery (db, NULL);

	f = DeleteInDB(query, strTable, strFldID, strFldStr, strErr);
	delete query;
	return (f);
}
//------------------------------------------------------------------------------
bool __fastcall TIDStr::DeleteInDB (TADOQuery *query, const String &strTable, const String &strFldID, const String &strFldStr, String &strErr)
{
	bool f;
	String strSql;
	
	strSql = "delete from " + strTable + " where " + strFldID + " = " + String(ID);
	f = RunQuery(query, strSql, QueryExec, strErr);
	delete query;
	return (f);
}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//	TIDStrings
//------------------------------------------------------------------------------
TIDStrings::TIDStrings(const String &strTable, const String &strFldID, const String &strFldStr)
	:	TIDStrBase()
{
	m_strTable = strTable;
	m_strFldID = strFldID;
	m_strFldStr = strFldStr;
	m_db = NULL;
	m_query = NULL;
}
//------------------------------------------------------------------------------
TIDStrings::TIDStrings(TADOConnection *db, const String &strTable, const String &strFldID, const String &strFldStr)
	:	TIDStrBase()
{
	m_strTable = strTable;
	m_strFldID = strFldID;
	m_strFldStr = strFldStr;
	m_db = db;
	m_query = InitQuery (db, NULL);
}
//------------------------------------------------------------------------------
TIDStrings::~TIDStrings ()
{
	if (m_query != NULL)
		delete m_query;
}
//------------------------------------------------------------------------------
bool __fastcall TIDStrings::LoadFromDB (TADOConnection *db, String &strErr)
{
	TADOQuery * query = InitQuery (db, NULL);
	bool f;
	
	f = LoadFromDB(query, strErr);
	delete query;
	return (f);
}
//------------------------------------------------------------------------------
bool __fastcall TIDStrings::LoadFromDB (TADOQuery *query, String &strErr)
{
	String strSql;
	bool f;
	TIDStr Item;

	clear ();
	strSql = "select * from " + m_strTable + ";";
	f = RunQuery(query, strSql, QueryOpen, strErr);
	if (f) {
		query->First();
		while (!query->Eof) {
			if (Item.LoadFromDB(query, m_strTable, m_strFldID, m_strFldStr))
				push_back (Item);
			query->Next();
		}
	}
	delete query;
	return (f);
}
//------------------------------------------------------------------------------
TIDStrings::iterator __fastcall TIDStrings::FindByID (int id)
{
	TIDStrings::iterator i, iFound=NULL;

	for (i=begin() ; (i != end()) && (iFound == NULL); i++)
		if (i->ID == id)
			iFound = i;
	return (iFound);
}
//------------------------------------------------------------------------------
bool __fastcall TIDStrings::UpdateItems (String &strErr)
{
	TIDStrings::iterator i;
	bool f= false;

	for (i=begin() ; i != end() ; i++) {
		f = i->UpdateInDB (m_query, m_strTable, m_strFldID, m_strFldStr, strErr);
	}
	return (f);
}
//------------------------------------------------------------------------------
bool __fastcall TIDStrings::InsertItems (String &strErr)
{
	TIDStrings::iterator i;
	bool f= false;

	for (i=begin() ; i != end() ; i++) {
		if (i->InsertAsNew (m_query, m_strTable, m_strFldID, strErr))
			f = i->UpdateInDB (m_query, m_strTable, m_strFldID, m_strFldStr, strErr);
	}
	return (f);
}
//------------------------------------------------------------------------------
bool __fastcall TIDStrings::DeleteItems (String &strErr)
{
	TIDStrings::iterator i;
	bool f= false;

	for (i=begin() ; i != end() ; i++) {
		f = i->DeleteInDB (m_query, m_strTable, m_strFldID, m_strFldStr, strErr);
	}
	return (f);
}
//------------------------------------------------------------------------------

