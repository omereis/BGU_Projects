//------------------------------------------------------------------------------
#include<vcl.h>
#pragma hdrstop
#include "UserInfo.h"
//------------------------------------------------------------------------------
#pragma package(smart_init)

//------------------------------------------------------------------------------
String TUserInfo::Table      ("T_USERS");
String TUserInfo::FldID      ("USER_ID");
String TUserInfo::FldUsername("USERNAME");
String TUserInfo::FldPassword("PASSWD");
String TUserInfo::FldFirst   ("FIRST");
String TUserInfo::FldLast    ("LAST");
//------------------------------------------------------------------------------
__fastcall TUserInfo::TUserInfo ()
{
	Clear();
}
//------------------------------------------------------------------------------
__fastcall TUserInfo::TUserInfo (const TUserInfo &other)
{
	AssignAll (other);
}
//------------------------------------------------------------------------------
TUserInfo __fastcall TUserInfo::operator= (const TUserInfo &other)
{
	AssignAll (other);
	return (*this);
}
//------------------------------------------------------------------------------
void __fastcall TUserInfo::AssignAll (const TUserInfo &other)
{
	UserID   = other.UserID;
	Username = other.Username;
	Password = other.Password;
	First    = other.First;
	Last     = other.Last;
}
//------------------------------------------------------------------------------
void __fastcall TUserInfo::Clear ()
{
	UserID   = 0;
	Username = "";
	Password = "";
	First    = "";
	Last     = "";
}
//------------------------------------------------------------------------------
bool __fastcall TUserInfo::operator== (const TUserInfo &other) const
{
	if (UserID   != other.UserID)
		return (false);
	if (Username != other.Username)
		return (false);
	if (Password != other.Password)
		return (false);
	if (First    != other.First)
		return (false);
	if (Last     != other.Last)
		return (false);
	return (true);
}
//------------------------------------------------------------------------------
void __fastcall TUserInfo::SetUserID (const int value)
{
	m_nUserID = value;
}
//------------------------------------------------------------------------------
int __fastcall TUserInfo::GetUserID () const
{
	return (m_nUserID);
}
//------------------------------------------------------------------------------
void __fastcall TUserInfo::SetUsername (const String &value)
{
	m_strUsername = value;
}
//------------------------------------------------------------------------------
String __fastcall TUserInfo::GetUsername () const
{
	return (m_strUsername);
}
//------------------------------------------------------------------------------
void __fastcall TUserInfo::SetPassword (const String &value)
{
	m_strPasswd = value;
}
//------------------------------------------------------------------------------
String __fastcall TUserInfo::GetPassword () const
{
	return (m_strPasswd);
}
//------------------------------------------------------------------------------
void __fastcall TUserInfo::SetFirst (const String &value)
{
	m_strFirst = value;
}
//------------------------------------------------------------------------------
String __fastcall TUserInfo::GetFirst () const
{
	return (m_strFirst);
}
//------------------------------------------------------------------------------
void __fastcall TUserInfo::SetLast (const String &value)
{
	m_strLast = value;
}
//------------------------------------------------------------------------------
String __fastcall TUserInfo::GetLast () const
{
	return (m_strLast);
}
//------------------------------------------------------------------------------
bool __fastcall TUserInfo::LoadFromDB (TADOQuery *query)
{
	bool f = true;
	
	try {
		UserID =   query->Fields->FieldByName (FldID)->AsInteger;
		Username = query->Fields->FieldByName (FldUsername)->AsString;
		Password = query->Fields->FieldByName (FldPassword)->AsString;
		First =    query->Fields->FieldByName (FldFirst)->AsString;
		Last =     query->Fields->FieldByName (FldLast)->AsString;
	}
	catch (...) {
		f = false;
	}
	return (f);;
}
//------------------------------------------------------------------------------
bool __fastcall TUserInfo::InsertAsNew (TADOQuery *query, String &strErr)
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
bool __fastcall TUserInfo::InsertAsNew (TADOConnection *db, String &strErr)
{
	bool f;
	TADOQuery *query = InitQuery (db, NULL);
	
	f = InsertAsNew(query, strErr);
	delete query;
	return (f);
}
//------------------------------------------------------------------------------
bool __fastcall TUserInfo::UpdateInDB (TADOQuery *query, String &strErr)
{
	String strSql;
	bool f;
	
	strSql = "update " + Table + "set "  + ModifyForUpdate(FldID, UserID) + ", " + 
				ModifyForUpdate(FldUsername, Username) + ", " + 
				ModifyForUpdate(FldPassword, Password) + ", " + 
				ModifyForUpdate(FldFirst, First) + ", " + 
				ModifyForUpdate(FldLast, Last) + 
			"where " + FldID + " = " + String(UserID);
	f = RunQuery(query, strSql, QueryExec, strErr);
	return (f);
}
//------------------------------------------------------------------------------
bool __fastcall TUserInfo::UpdateInDB (TADOConnection *db, String &strErr)
{
	bool f;
	TADOQuery *query = InitQuery (db, NULL);
	
	f = UpdateInDB(query, strErr);
	delete query;
	return (f);
}
//------------------------------------------------------------------------------
