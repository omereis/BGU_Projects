//------------------------------------------------------------------------------
#include<vcl.h>
#pragma hdrstop
#include "ContactInfo.h"
//------------------------------------------------------------------------------
#pragma package(smart_init)

//------------------------------------------------------------------------------
String TContactInfo::Table       ("T_CONTACTS");
String TContactInfo::FldID       ("CONTACT_ID");
String TContactInfo::FldDatasetID("DATASET_ID");
String TContactInfo::FldName     ("NAME");
String TContactInfo::FldEmail    ("EMAIL");
String TContactInfo::FldPhone    ("PHONE");
String TContactInfo::FldComments ("COMMENTS");
//------------------------------------------------------------------------------
__fastcall TContactInfo::TContactInfo ()
{
	Clear();
}
//------------------------------------------------------------------------------
__fastcall TContactInfo::TContactInfo (const TContactInfo &other)
{
	AssignAll (other);
}
//------------------------------------------------------------------------------
TContactInfo __fastcall TContactInfo::operator= (const TContactInfo &other)
{
	AssignAll (other);
	return (*this);
}
//------------------------------------------------------------------------------
void __fastcall TContactInfo::AssignAll (const TContactInfo &other)
{
	ID        = other.ID;
	DatasetID = other.DatasetID;
	Name      = other.Name;
	Email     = other.Email;
	Phone     = other.Phone;
	Comments  = other.Comments;
}
//------------------------------------------------------------------------------
void __fastcall TContactInfo::Clear ()
{
	ID        = 0;
	DatasetID = 0;
	Name      = "";
	Email     = "";
	Phone     = "";
	Comments  = "";
}
//------------------------------------------------------------------------------
bool __fastcall TContactInfo::operator== (const TContactInfo &other) const
{
	if (ID        != other.ID)
		return (false);
	if (DatasetID != other.DatasetID)
		return (false);
	if (Name      != other.Name)
		return (false);
	if (Email     != other.Email)
		return (false);
	if (Phone     != other.Phone)
		return (false);
	if (Comments  != other.Comments)
		return (false);
	return (true);
}
//------------------------------------------------------------------------------
void __fastcall TContactInfo::SetID (const int value)
{
	m_nID = value;
}
//------------------------------------------------------------------------------
int __fastcall TContactInfo::GetID () const
{
	return (m_nID);
}
//------------------------------------------------------------------------------
void __fastcall TContactInfo::SetDatasetID (const int value)
{
	m_nDatasetID = value;
}
//------------------------------------------------------------------------------
int __fastcall TContactInfo::GetDatasetID () const
{
	return (m_nDatasetID);
}
//------------------------------------------------------------------------------
void __fastcall TContactInfo::SetName (const String &value)
{
	m_strName = value;
}
//------------------------------------------------------------------------------
String __fastcall TContactInfo::GetName () const
{
	return (m_strName);
}
//------------------------------------------------------------------------------
void __fastcall TContactInfo::SetEmail (const String &value)
{
	m_strEmail = value;
}
//------------------------------------------------------------------------------
String __fastcall TContactInfo::GetEmail () const
{
	return (m_strEmail);
}
//------------------------------------------------------------------------------
void __fastcall TContactInfo::SetPhone (const String &value)
{
	m_strPhone = value;
}
//------------------------------------------------------------------------------
String __fastcall TContactInfo::GetPhone () const
{
	return (m_strPhone);
}
//------------------------------------------------------------------------------
void __fastcall TContactInfo::SetComments (const String &value)
{
	m_strComments = value;
}
//------------------------------------------------------------------------------
String __fastcall TContactInfo::GetComments () const
{
	return (m_strComments);
}
//------------------------------------------------------------------------------
bool __fastcall TContactInfo::LoadFromDB (TADOQuery *query)
{
	bool f = true;
	
	try {
		ID =        query->Fields->FieldByName (FldID)->AsInteger;
		DatasetID = query->Fields->FieldByName (FldDatasetID)->AsInteger;
		Name =      query->Fields->FieldByName (FldName)->AsString;
		Email =     query->Fields->FieldByName (FldEmail)->AsString;
		Phone =     query->Fields->FieldByName (FldPhone)->AsString;
		Comments =  query->Fields->FieldByName (FldComments)->AsString;
	}
	catch (...) {
		f = false;
	}
	return (f);;
}
//------------------------------------------------------------------------------
bool __fastcall TContactInfo::InsertAsNew (TADOQuery *query, String &strErr)
{
	int id;
	bool f;
	String strSql;
	
	f = GetFieldMax (query, Table, FldID, id);
	if (f) {
		strSql = "insert into " + Table + "(" + FldID + ") values (" + String (id + 1) + ");";
		f = RunQuery (query, strSql, QueryExec, strErr);
	}
	return (f);
}
//------------------------------------------------------------------------------
bool __fastcall TContactInfo::InsertAsNew (TADOConnection *db, String &strErr)
{
	bool f;
	TADOQuery *query = InitQuery (db, NULL);
	
	f = InsertAsNew(query, strErr);
	delete query;
	return (f);
}
//------------------------------------------------------------------------------
bool __fastcall TContactInfo::UpdateInDB (TADOQuery *query, String &strErr)
{
	String strSql;
	bool f;
	
	strSql = "update " + Table + "set "  + ModifyForUpdate(FldID, ID) + ", " + 
				ModifyForUpdate(FldDatasetID, DatasetID) + ", " + 
				ModifyForUpdate(FldName, Name) + ", " + 
				ModifyForUpdate(FldEmail, Email) + ", " + 
				ModifyForUpdate(FldPhone, Phone) + ", " + 
				ModifyForUpdate(FldComments, Comments) + 
			"where " + FldID + " = " + String(ID);
	f = RunQuery(query, strSql, QueryExec, strErr);
	return (f);
}
//------------------------------------------------------------------------------
bool __fastcall TContactInfo::UpdateInDB (TADOConnection *db, String &strErr)
{
	bool f;
	TADOQuery *query = InitQuery (db, NULL);
	
	f = UpdateInDB(query, strErr);
	delete query;
	return (f);
}
//------------------------------------------------------------------------------
