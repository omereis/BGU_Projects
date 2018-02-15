//------------------------------------------------------------------------------
#include<vcl.h>
#pragma hdrstop
#include "DatasetObj.h"
#include "Misc.h"
#include "ImportGeoLife.h"
//------------------------------------------------------------------------------
#pragma package(smart_init)

//------------------------------------------------------------------------------
String TDatasetObj::Table       ("T_OBJECTS");
String TDatasetObj::FldObjID    ("OBJECT_ID");
String TDatasetObj::FldDatasetID("DATASET_ID");
String TDatasetObj::FldObjName  ("OBJ_NAME");
String TDatasetObj::FldObjType  ("OBJ_TYPE");
//------------------------------------------------------------------------------
__fastcall TDatasetObj::TDatasetObj ()
{
	Clear();
}
//------------------------------------------------------------------------------
__fastcall TDatasetObj::TDatasetObj (const TDatasetObj &other)
{
	AssignAll (other);
}
//------------------------------------------------------------------------------
__fastcall TDatasetObj::TDatasetObj (const String &strName)
{
	Clear ();
	ObjName = strName;
}
//------------------------------------------------------------------------------
TDatasetObj __fastcall TDatasetObj::operator= (const TDatasetObj &other)
{
	AssignAll (other);
	return (*this);
}
//------------------------------------------------------------------------------
void __fastcall TDatasetObj::AssignAll (const TDatasetObj &other)
{
	ObjID     = other.ObjID;
	DatasetID = other.DatasetID;
	ObjName   = other.ObjName;
	ObjType   = other.ObjType;
	m_vRoutes = other.m_vRoutes;
}
//------------------------------------------------------------------------------
void __fastcall TDatasetObj::Clear ()
{
	ObjID     = 0;
	DatasetID = 0;
	ObjName   = "";
	ObjType   = "";
	m_vRoutes.clear ();
}
//------------------------------------------------------------------------------
bool __fastcall TDatasetObj::operator== (const TDatasetObj &other) const
{
	if (ObjID     != other.ObjID)
		return (false);
	if (DatasetID != other.DatasetID)
		return (false);
	if (ObjName   != other.ObjName)
		return (false);
	if (ObjType   != other.ObjType)
		return (false);
	if (m_vRoutes   != other.m_vRoutes)
		return (false);
	return (true);
}
//------------------------------------------------------------------------------
void __fastcall TDatasetObj::SetObjID (const int value)
{
	m_nObjID = value;
}
//------------------------------------------------------------------------------
int __fastcall TDatasetObj::GetObjID () const
{
	return (m_nObjID);
}
//------------------------------------------------------------------------------
void __fastcall TDatasetObj::SetDatasetID (const int value)
{
	m_nDatasetID = value;
}
//------------------------------------------------------------------------------
int __fastcall TDatasetObj::GetDatasetID () const
{
	return (m_nDatasetID);
}
//------------------------------------------------------------------------------
void __fastcall TDatasetObj::SetObjName (const String &value)
{
	m_strObjName = value;
}
//------------------------------------------------------------------------------
String __fastcall TDatasetObj::GetObjName () const
{
	return (m_strObjName);
}
//------------------------------------------------------------------------------
void __fastcall TDatasetObj::SetObjType (const String &value)
{
	m_strObjType = value;
}
//------------------------------------------------------------------------------
String __fastcall TDatasetObj::GetObjType () const
{
	return (m_strObjType);
}
//------------------------------------------------------------------------------
void __fastcall TDatasetObj::SetRoutes (TRoutes &vRoutes)
{
	m_vRoutes = vRoutes;
}
//------------------------------------------------------------------------------
TRoutes __fastcall TDatasetObj::GetRoutes () const
{
	return (m_vRoutes);
}
//------------------------------------------------------------------------------
bool __fastcall TDatasetObj::LoadFromDB (TADOQuery *query)
{
	bool f = true;
	
	try {
		ObjID =     query->Fields->FieldByName (FldObjID)->AsInteger;
		DatasetID = query->Fields->FieldByName (FldDatasetID)->AsInteger;
		ObjName =   query->Fields->FieldByName (FldObjName)->AsString;
		ObjType =   query->Fields->FieldByName (FldObjType)->AsString;
	}
	catch (...) {
		f = false;
	}
	return (f);;
}
//------------------------------------------------------------------------------
bool __fastcall TDatasetObj::InsertAsNew (TADOQuery *query, String &strErr)
{
	int id, idNew;
	bool f;
	String strSql;

	f = GetFieldMax (query, Table, FldObjID, id);
	idNew = id + 1;
	if (f) {
		strSql = "insert into " + Table + "(" + FldObjID + ") values (" + String (idNew) + ");";
		if ((f = RunQuery (query, strSql, QueryExec, strErr)) == true)
			ObjID = idNew;;
	}
	return (f);
}
//------------------------------------------------------------------------------
bool __fastcall TDatasetObj::InsertAsNew (TADOConnection *db, String &strErr)
{
	bool f;
	TADOQuery *query = InitQuery (db, NULL);
	
	f = InsertAsNew(query, strErr);
	delete query;
	return (f);
}
//------------------------------------------------------------------------------
bool __fastcall TDatasetObj::UpdateInDB (TADOQuery *query, String &strErr)
{
	String strSql;
	bool f;

	strSql = "update " + Table + " set "  + ModifyForUpdate(FldObjID, ObjID) + ", " +
				ModifyForUpdate(FldDatasetID, DatasetID) + ", " +
				ModifyForUpdate(FldObjName, ObjName) + ", " +
				ModifyForUpdate(FldObjType, ObjType) +
			" where " + FldObjID + " = " + String(ObjID);
	f = RunQuery(query, strSql, QueryExec, strErr);
	return (f);
}
//------------------------------------------------------------------------------
bool __fastcall TDatasetObj::UpdateInDB (TADOConnection *db, String &strErr)
{
	bool f;
	TADOQuery *query = InitQuery (db, NULL);

	f = UpdateInDB(query, strErr);
	delete query;
	return (f);
}
//------------------------------------------------------------------------------
bool __fastcall TDatasetObj::LoadIdByDsAndName (TADOQuery *query, String &strErr)
{
	bool f;
	String strSql;

	strSql = "select * from " + Table + " where " +
			FldDatasetID + "=" + String (DatasetID) + " and " +
			FldObjName + "=" + ModifyForInsert (ObjName);
	if ((f = RunQuery (query, strSql, QueryOpen, strErr)) == true) {
		query->First();
		if (!query->Eof) {
			LoadFromDB (query);
		}
	}
	return (f);
}
//------------------------------------------------------------------------------
bool __fastcall TDatasetObj::InsertAndUpdate (TADOQuery *query, String &strErr)
{
	bool f;

	if (InsertAsNew (query, strErr))
		f = UpdateInDB (query, strErr);
	return (f);
}
//------------------------------------------------------------------------------
String __fastcall TDatasetObj::ParseObjNameFromPath (const String &strLine, String &strRoute)
{
	TStringList *lstrTokens = new TStringList;
	int n;
	String strName;

	Tokenize (strLine, lstrTokens, "\\");
	strName = lstrTokens->Strings[lstrTokens->Count - 3];
	strRoute = lstrTokens->Strings[lstrTokens->Count - 1];
	delete lstrTokens;
	return (strName);
}
//------------------------------------------------------------------------------
void __fastcall TDatasetObj::ParseDir (const String &strLine)
{
	TStringList *lstrTokens = new TStringList;
	int n;
	String str;

	Tokenize (strLine, lstrTokens, "\\");
	ObjName = lstrTokens->Strings[lstrTokens->Count - 3];
	delete lstrTokens;
}
//------------------------------------------------------------------------------
void __fastcall TDatasetObj::AddRoute (const String &strPath, const String &strRoute)
{
	TRoutes::iterator iRoute;

	if ((iRoute = m_vRoutes.FindRouteByPath (strPath)) == NULL) {
		TRouteInfo route;
		route.RoutePath = strPath;
		route.RouteName = strRoute;
		m_vRoutes.push_back (route);
	}
}
//------------------------------------------------------------------------------
bool __fastcall TDatasetObj::InsertRoutes (TADOQuery *query, String &strErr, TForm *parent)
{
	TRoutes::iterator iRoute;
	TdlgImportGeoLife *dlgParent;
	bool f;
	TdlgImportGeoLife *dlg;

	dlgParent = (TdlgImportGeoLife *) parent;
	for (iRoute=m_vRoutes.begin() ; iRoute != m_vRoutes.end() ; iRoute++) {
		iRoute->ObjectID = ObjID;
		f = iRoute->InsertAndUpdate (query, strErr);
		if (dlgParent != NULL)
			dlgParent->UpdateGUI ();
	}
	return (f);
}
//------------------------------------------------------------------------------
//	TDatasetObjects
//------------------------------------------------------------------------------
__fastcall TDatasetObjects::TDatasetObjects ()
	: TDatasetObjBase ()
{
}
//------------------------------------------------------------------------------
bool __fastcall TDatasetObjects::LoadFromDB (TADOQuery *query, String &strErr)
{
	bool f;
	String strSql;
	TDatasetObj d_obj;

	clear ();
	strSql = "select * from " + TDatasetObj::Table + ";";
	if ((f = RunQuery (query, strSql, QueryOpen, strErr)) == true) {
		query->First ();
		while (!query->Eof) {
			if (d_obj.LoadFromDB (query)) {
				push_back (d_obj);
			}
			query->Next ();
		}
	}
	return (f);
}
//------------------------------------------------------------------------------
bool __fastcall TDatasetObjects::LoadFromDB (TADOConnection *db, String &strErr)
{
	TADOQuery *query = InitQuery (db, NULL);
	bool f = LoadFromDB (query, strErr);
	delete query;
	return (f);
}
//------------------------------------------------------------------------------
bool __fastcall TDatasetObjects::DeleteFromDB (TADOQuery *query, String &strErr)
{
	bool f;
	String strSql;

	strSql = "delete from " + TDatasetObj::Table + ";";
	f = RunQuery (query, strSql, QueryExec, strErr);
	return (f);
}
//------------------------------------------------------------------------------
TDatasetObjects::iterator __fastcall TDatasetObjects::FindByName (const String &strObjName)
{
	TDatasetObjects::iterator iObj, iFound = NULL;

	for (iObj=begin() ; iObj != end() ; iObj++) {
		if (iObj->ObjName.LowerCase() == strObjName.LowerCase()) {
			iFound = iObj;
		}
	}
	return (iFound);
}
//------------------------------------------------------------------------------
bool __fastcall TDatasetObjects::LoadDatasetsObjects (TADOQuery *query, int idDataset, String &strErr)
{
	String strSql;
	bool f;
	TDatasetObj dso;

	clear ();
	strSql = "select * from " + TDatasetObj::Table + " where " + TDatasetObj::FldDatasetID + "=" + String (idDataset) + ";";
	if ((f = RunQuery (query, strSql, QueryOpen, strErr)) == true) {
		query->First ();
		while (!query->Eof) {
			dso.LoadFromDB (query);
			push_back (dso);
			query->Next ();
		}
	}
	return (f);
}
//------------------------------------------------------------------------------

