//------------------------------------------------------------------------------
#include<vcl.h>
#pragma hdrstop
#include "DatasetObj.h"
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
}
//------------------------------------------------------------------------------
void __fastcall TDatasetObj::Clear ()
{
	ObjID     = 0;
	DatasetID = 0;
	ObjName   = "";
	ObjType   = "";
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
	int id;
	bool f;
	String strSql;
	
	f = GetFieldMax (query, Table, FldObjID, id);
	if (f) {
		strSql = "insert into " + Table + "(" + FldObjID + ") values (" + String (id + 1) + ");";
		f = RunQuery (query, strSql, QueryExec, strErr);
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
	
	strSql = "update " + Table + "set "  + ModifyForUpdate(FldObjID, ObjID) + ", " + 
				ModifyForUpdate(FldDatasetID, DatasetID) + ", " + 
				ModifyForUpdate(FldObjName, ObjName) + ", " + 
				ModifyForUpdate(FldObjType, ObjType) + 
			"where " + FldObjID + " = " + String(ObjID);
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
