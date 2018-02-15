//------------------------------------------------------------------------------
#include<vcl.h>
#pragma hdrstop
#include "UserInfo.h"
//------------------------------------------------------------------------------
#pragma package(smart_init)

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
	UserName = other.UserName;
	Last     = other.Last;
	Password = other.Password;
	First    = other.First;
}
//------------------------------------------------------------------------------
void __fastcall TUserInfo::Clear ()
{
	UserID   = 0;
	UserName = "";
	Last     = "";
	Password = "";
	First    = "";
}
//------------------------------------------------------------------------------
bool __fastcall TUserInfo::operator== (const TUserInfo &other)
{
	if (UserID   != other.UserID)
		return (false);
	if (UserName != other.UserName)
		return (false);
	if (Last     != other.Last)
		return (false);
	if (Password != other.Password)
		return (false);
	if (First    != other.First)
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
void __fastcall TUserInfo::SetUserName (const String &value)
{
	m_strUserName = value;
}
//------------------------------------------------------------------------------
String __fastcall TUserInfo::GetUserName () const
{
	return (m_strUserName);
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
void __fastcall TUserInfo::SetPassword (const String &value)
{
	m_strPassword = value;
}
//------------------------------------------------------------------------------
String __fastcall TUserInfo::GetPassword () const
{
	return (m_strPassword);
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
