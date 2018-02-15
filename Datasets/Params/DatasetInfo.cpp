//------------------------------------------------------------------------------
#include<vcl.h>
#pragma hdrstop
#include "DatasetInfo.h"
//------------------------------------------------------------------------------
#pragma package(smart_init)

//------------------------------------------------------------------------------
String TDatasetInfo::Table         ("DATASETS");
String TDatasetInfo::FldDatasetID  ("DATASET_ID");
String TDatasetInfo::FldName       ("NAME");
String TDatasetInfo::FldURL        ("URL");
String TDatasetInfo::FldStructure  ("STRUCTURE");
String TDatasetInfo::              ("");
String TDatasetInfo::              ("");
String TDatasetInfo::FldUsername   ("USERNAME");
String TDatasetInfo::FldPassword   ("PASSWD");
String TDatasetInfo::FldDescription("DESCRIPTION");
//------------------------------------------------------------------------------
__fastcall TDatasetInfo::TDatasetInfo ()
{
	Clear();
}
//------------------------------------------------------------------------------
__fastcall TDatasetInfo::TDatasetInfo (const TDatasetInfo &other)
{
	AssignAll (other);
}
//------------------------------------------------------------------------------
TDatasetInfo __fastcall TDatasetInfo::operator= (const TDatasetInfo &other)
{
	AssignAll (other);
	return (*this);
}
//------------------------------------------------------------------------------
void __fastcall TDatasetInfo::AssignAll (const TDatasetInfo &other)
{
	DatasetID   = other.DatasetID;
	Name        = other.Name;
	URL         = other.URL;
	Structure   = other.Structure;
	Contacts    = other.Contacts;
	Points      = other.Points;
	Username    = other.Username;
	Password    = other.Password;
	Description = other.Description;
}
//------------------------------------------------------------------------------
void __fastcall TDatasetInfo::Clear ()
{
	DatasetID   = 0;
	Name        = "";
	URL         = "";
	Structure   = "";
	Contacts    = ;
	Points      = ;
	Username    = "";
	Password    = "";
	Description = "";
}
//------------------------------------------------------------------------------
bool __fastcall TDatasetInfo::operator== (const TDatasetInfo &other) const
{
	if (DatasetID   != other.DatasetID)
		return (false);
	if (Name        != other.Name)
		return (false);
	if (URL         != other.URL)
		return (false);
	if (Structure   != other.Structure)
		return (false);
	if (Contacts    != other.Contacts)
		return (false);
	if (Points      != other.Points)
		return (false);
	if (Username    != other.Username)
		return (false);
	if (Password    != other.Password)
		return (false);
	if (Description != other.Description)
		return (false);
	return (true);
}
//------------------------------------------------------------------------------
void __fastcall TDatasetInfo::SetDatasetID (const int value)
{
	m_nDatasetID = value;
}
//------------------------------------------------------------------------------
int __fastcall TDatasetInfo::GetDatasetID () const
{
	return (m_nDatasetID);
}
//------------------------------------------------------------------------------
void __fastcall TDatasetInfo::SetName (const String &value)
{
	m_strName = value;
}
//------------------------------------------------------------------------------
String __fastcall TDatasetInfo::GetName () const
{
	return (m_strName);
}
//------------------------------------------------------------------------------
void __fastcall TDatasetInfo::SetURL (const String &value)
{
	m_strURL = value;
}
//------------------------------------------------------------------------------
String __fastcall TDatasetInfo::GetURL () const
{
	return (m_strURL);
}
//------------------------------------------------------------------------------
void __fastcall TDatasetInfo::SetStructure (const String &value)
{
	m_strStructure = value;
}
//------------------------------------------------------------------------------
String __fastcall TDatasetInfo::GetStructure () const
{
	return (m_strStructure);
}
//------------------------------------------------------------------------------
void __fastcall TDatasetInfo::SetContacts (const TContacts value)
{
	m_vContacts = value;
}
//------------------------------------------------------------------------------
TContacts __fastcall TDatasetInfo::GetContacts () const
{
	return (m_vContacts);
}
//------------------------------------------------------------------------------
void __fastcall TDatasetInfo::SetPoints (const TDataPoints value)
{
	m_vPoints = value;
}
//------------------------------------------------------------------------------
TDataPoints __fastcall TDatasetInfo::GetPoints () const
{
	return (m_vPoints);
}
//------------------------------------------------------------------------------
void __fastcall TDatasetInfo::SetUsername (const String &value)
{
	m_strString = value;
}
//------------------------------------------------------------------------------
String __fastcall TDatasetInfo::GetUsername () const
{
	return (m_strString);
}
//------------------------------------------------------------------------------
void __fastcall TDatasetInfo::SetPassword (const String &value)
{
	m_strPassword = value;
}
//------------------------------------------------------------------------------
String __fastcall TDatasetInfo::GetPassword () const
{
	return (m_strPassword);
}
//------------------------------------------------------------------------------
void __fastcall TDatasetInfo::SetDescription (const String &value)
{
	m_strDescription = value;
}
//------------------------------------------------------------------------------
String __fastcall TDatasetInfo::GetDescription () const
{
	return (m_strDescription);
}
//------------------------------------------------------------------------------
bool __fastcall TDatasetInfo::LoadFromDB (TADOQuery *query)
{
	bool f = true;
	
	try {
		DatasetID =   query->Fields->FieldByName (FldDatasetID)->AsInteger;
		Name =        query->Fields->FieldByName (FldName)->AsString;
		URL =         query->Fields->FieldByName (FldURL)->AsString;
		Structure =   query->Fields->FieldByName (FldStructure)->AsString;
		Contacts =    query->Fields->FieldByName ()->Ass;
		Points =      query->Fields->FieldByName ()->Ass;
		Username =    query->Fields->FieldByName (FldUsername)->AsString;
		Password =    query->Fields->FieldByName (FldPassword)->AsString;
		Description = query->Fields->FieldByName (FldDescription)->AsString;
	}
	catch (...) {
		f = false;
	}
	return (f);;
}
//------------------------------------------------------------------------------
bool __fastcall TDatasetInfo::InsertAsNew (TADOQuery *query, String &strErr)
{
	int id;
	bool f;
	String strSql;
	
	f = GetFieldMax (query, Table, FldDatasetID, id);
	if (f) {
		strSql = "insert into " + Table + "(" + FldDatasetID + ") values (" + String (id + 1) + ");";
		f = RunQuery (query, strSql, QueryExec, strErr);
	}
	return (f);
}
//------------------------------------------------------------------------------
bool __fastcall TDatasetInfo::InsertAsNew (TADOConnection *db, String &strErr)
{
	bool f;
	TADOQuery *query = InitQuery (db, NULL);
	
	f = InsertAsNew(query, strErr);
	delete query;
	return (f);
}
//------------------------------------------------------------------------------
bool __fastcall TDatasetInfo::UpdateInDB (TADOQuery *query, String &strErr)
{
	String strSql;
	bool f;
	
	strSql = "update " + Table + "set "  + 
				ModifyForUpdate(FldDatasetID, DatasetID) + ", " + 
				ModifyForUpdate(FldName, Name) + ", " + 
				ModifyForUpdate(FldURL, URL) + ", " + 
				ModifyForUpdate(FldStructure, Structure) + ", " + 
				ModifyForUpdate(, Contacts) + ", " + 
				ModifyForUpdate(, Points) + ", " + 
				ModifyForUpdate(FldUsername, Username) + ", " + 
				ModifyForUpdate(FldPassword, Password) + ", " + 
				ModifyForUpdate(FldDescription, Description) + 
			"where " + FldDatasetID + " = " + String(DatasetID);
	f = RunQuery(query, strSql, QueryExec, strErr);
	return (f);
}
//------------------------------------------------------------------------------
bool __fastcall TDatasetInfo::UpdateInDB (TADOConnection *db, String &strErr)
{
	bool f;
	TADOQuery *query = InitQuery (db, NULL);
	
	f = UpdateInDB(query, strErr);
	delete query;
	return (f);
}
//------------------------------------------------------------------------------
