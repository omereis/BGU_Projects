//------------------------------------------------------------------------------
#include<vcl.h>
#pragma hdrstop
#include "DatasetInfo.h"
//------------------------------------------------------------------------------
#pragma package(smart_init)

//------------------------------------------------------------------------------
String TDatasetInfo::Table         ("T_DATASETS");
String TDatasetInfo::FldDatasetID  ("DATASET_ID");
String TDatasetInfo::FldDatasetType("DS_TYPE");
String TDatasetInfo::FldName       ("DATASET_NAME");
String TDatasetInfo::FldURL        ("URL");
String TDatasetInfo::FldStructure  ("STRUCTURE");
String TDatasetInfo::FldUsername   ("USERNAME");
String TDatasetInfo::FldPassword   ("PASSWD");
String TDatasetInfo::FldDescription("DESCRIPTION");
String TDatasetInfo::FldOrganization("ORGANIZATION");
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
	Type        = other.Type;
	Name        = other.Name;
	URL         = other.URL;
	Structure   = other.Structure;
	Contacts    = other.Contacts;
	Points      = other.Points;
	Username    = other.Username;
	Password    = other.Password;
	Description = other.Description;
	Organization= other.Organization;
}
//------------------------------------------------------------------------------
void __fastcall TDatasetInfo::Clear ()
{
	DatasetID   = 0;
	Type        = EDT_UNKNOWN;
	Name        = "";
	URL         = "";
	Structure   = "";
	Contacts.clear();
	Points.clear();
	Username    = "";
	Password    = "";
	Description = "";
	Organization= "";
}
//------------------------------------------------------------------------------
bool __fastcall TDatasetInfo::operator== (const TDatasetInfo &other) const
{
	if (DatasetID   != other.DatasetID)
		return (false);
	if (Type        != other.Type) 
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
	if (Organization != other.Organization)
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
void __fastcall TDatasetInfo::SetType (EDatasetType type)
{
	m_type = type;
}
//------------------------------------------------------------------------------
EDatasetType __fastcall TDatasetInfo::GetType () const
{
	return (m_type);
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
String __fastcall TDatasetInfo::GetOrganization () const
{
	return (m_strOrganization);
}
//------------------------------------------------------------------------------
void __fastcall TDatasetInfo::SetOrganization (const String &value)
{
	m_strOrganization = value;
}
//------------------------------------------------------------------------------
bool __fastcall TDatasetInfo::LoadFromDB (TADOQuery *query)
{
	bool f = true;
	
	try {
		DatasetID =   query->Fields->FieldByName (FldDatasetID)->AsInteger;
		Type         = (EDatasetType) query->Fields->FieldByName (FldDatasetType)->AsInteger;
		Name =        query->Fields->FieldByName (FldName)->AsString;
		URL =         query->Fields->FieldByName (FldURL)->AsString;
		Structure =   query->Fields->FieldByName (FldStructure)->AsString;
//		Contacts =    query->Fields->FieldByName ()->Ass;
//		Points =      query->Fields->FieldByName ()->Ass;
		Username =    query->Fields->FieldByName (FldUsername)->AsString;
		Password =    query->Fields->FieldByName (FldPassword)->AsString;
		Description = query->Fields->FieldByName (FldDescription)->AsString;
		Organization = query->Fields->FieldByName (FldOrganization)->AsString;
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
		if ((f = RunQuery (query, strSql, QueryExec, strErr)) == true)
			DatasetID = id + 1;
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
	
	strSql = "update " + Table + " set "  +
				ModifyForUpdate(FldDatasetID, DatasetID) + ", " +
				ModifyForUpdate(FldDatasetType, Type) + ", " +
				ModifyForUpdate(FldName, Name) + ", " + 
				ModifyForUpdate(FldURL, URL) + ", " + 
				ModifyForUpdate(FldStructure, Structure) + ", " + 
//				ModifyForUpdate(, Contacts) + ", " +
//				ModifyForUpdate(, Points) + ", " + 
				ModifyForUpdate(FldUsername, Username) + ", " + 
				ModifyForUpdate(FldPassword, Password) + ", " +
				ModifyForUpdate(FldDescription, Description) + ", " +
				ModifyForUpdate(FldOrganization, Organization) +
			" where " + FldDatasetID + " = " + String(DatasetID);
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
bool __fastcall TDatasetInfo::DeleteInDB (TADOConnection *db, String &strErr)
{
	TADOQuery *query = InitQuery (db, NULL);
	bool f;

	f = DeleteInDB (query, strErr);
	delete query;
	return (f);
}
//------------------------------------------------------------------------------
bool __fastcall TDatasetInfo::DeleteInDB (TADOQuery *query, String &strErr)
{
	String strSql;

	strSql = "delete from " + Table + " where " + FldDatasetID + "=" + String (DatasetID) + ";";
	return (RunQuery (query, strSql, QueryExec, strErr));
}
//------------------------------------------------------------------------------
bool __fastcall TDatasetInfo::LoadByID (TADOConnection *db, String &strErr)
{
	String strSql;
	bool f;
	TADOQuery *query = InitQuery (db, NULL);

	try {
		strSql = "select * from " + Table + " where " + FldDatasetID + "=" + String (DatasetID) + ";";
		if ((f = RunQuery (query, strSql, QueryOpen, strErr)) == true) {
			query->First ();
			if (!query->Eof) {
				LoadFromDB (query);
			}
		}
	} __finally {
		delete query;
		return (f);
	}
}
//------------------------------------------------------------------------------
bool __fastcall TDatasetInfo::ConfirmDeletion ()
{
	String strName, str;

	if (Name.Length() > 0)
		strName = Name;
	else
		strName = "Dataset ID #" + String (DatasetID);
	str = "Delete Dataset '" + strName + "'?";
//	MessageDlg (str, mtConfirmation, TMsgDlgButtons () << mbYes, 0);
	int mb = MessageDlg (str, mtConfirmation, TMsgDlgButtons () << mbYes << mbNo, 0, mbNo);
	return (mb == mrYes);
}
//------------------------------------------------------------------------------
EDatasetType __fastcall TDatasetInfo::TypeFromInt (int n)
{
	EDatasetType type = EDT_UNKNOWN;

	if (n == 1)
		type = EDT_GEO_LIFE;
	return (type);

}
//------------------------------------------------------------------------------
int __fastcall TDatasetInfo::IntFromType (EDatasetType type)
{
	int idx;

	idx = max ((int) type, (int) EDT_NEW);
	return (idx);
}
//------------------------------------------------------------------------------
String __fastcall TDatasetInfo::GetTypeName (EDatasetType type)
{
	String str;

	if (type == EDT_UNKNOWN)
		str = "Unknown";
	else if (type == EDT_GEO_LIFE)
		str = "Geo Life";
	return (str);
}
//------------------------------------------------------------------------------
int __fastcall TDatasetInfo::GetTypeNames (TStringList *lstr)
{
	int n;
	lstr->Clear ();

	for (n=0 ; n < (int) EDT_NEW ; n++)
		lstr->Add (GetTypeName ((EDatasetType) n));
	return (lstr->Count);
}
//------------------------------------------------------------------------------
bool __fastcall TDatasetInfo::LoadByID (TADOQuery *query, int idDataset, String &strErr)
{
	String strSql;
	bool f;

	Clear ();
	strSql = "select * from " + Table + " where " + FldDatasetID + "=" + String (idDataset) + ";";
	if ((f = RunQuery (query, strSql, QueryOpen, strErr)) == true) {
		query->First ();
		if (!query->Eof) {
			LoadFromDB (query);
		}
	}
	return (f);
}
//------------------------------------------------------------------------------
//	TDatases
//------------------------------------------------------------------------------
__fastcall TDatases::TDatases () : TDatasetInfoBase ()
{
}
//------------------------------------------------------------------------------
bool __fastcall TDatases::LoadFromDB (TADOQuery *query, String &strErr)
{
	bool f;
	String strSql;
	TDatasetInfo data_set;

	clear ();
	strSql = "select * from " + TDatasetInfo::Table + ";";
	if ((f = RunQuery (query, strSql, QueryOpen, strErr)) == true) {
		query->First ();
		while (!query->Eof) {
			if (data_set.LoadFromDB (query)) {
				push_back (data_set);
			}
			query->Next ();
		}
	}
	return (f);
}
//------------------------------------------------------------------------------
bool __fastcall TDatases::LoadFromDB (TADOConnection *db, String &strErr)
{
	TADOQuery *query = InitQuery (db, NULL);
	bool f;

	f = LoadFromDB (query, strErr);
	delete query;
	return (f);
}
//------------------------------------------------------------------------------
/*
The whole data is stored in a directory. Each object, a person in that case, is stored in a different sub directory.
That directory contains just one sub directory called Trajectories.
Each Trajectories directory contains 1 or more PLT files, each of which contains a route/trajectory.
PLT file format is as follows:
Line 1…6 are useless in this dataset, and can be ignored. Points are described in following lines, one for each line.
Field 1: Latitude in decimal degrees.
Field 2: Longitude in decimal degrees.
Field 3: All set to 0 for this dataset.
Field 4: Altitude in feet (-777 if not valid).
Field 5: Date - number of days (with fractional part) that have passed since 12/30/1899.
Field 6: Date as a string.
Field 7: Time as a string.
*/
