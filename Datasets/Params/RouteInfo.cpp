//------------------------------------------------------------------------------
#include<vcl.h>
#pragma hdrstop
#include "RouteInfo.h"
//------------------------------------------------------------------------------
#pragma package(smart_init)

//------------------------------------------------------------------------------
String TRouteInfo::Table       ("T_ROUTES");
String TRouteInfo::FldRouteID  ("ROUTE_ID");
String TRouteInfo::FldRouteName("ROUTE_NAME");
String TRouteInfo::FldObjectID ("OBJECT_ID");
//------------------------------------------------------------------------------
__fastcall TRouteInfo::TRouteInfo ()
{
	Clear();
}
//------------------------------------------------------------------------------
__fastcall TRouteInfo::TRouteInfo (const TRouteInfo &other)
{
	AssignAll (other);
}
//------------------------------------------------------------------------------
TRouteInfo __fastcall TRouteInfo::operator= (const TRouteInfo &other)
{
	AssignAll (other);
	return (*this);
}
//------------------------------------------------------------------------------
void __fastcall TRouteInfo::AssignAll (const TRouteInfo &other)
{
	RouteID   = other.RouteID;
	RouteName = other.RouteName;
	ObjectID  = other.ObjectID;
}
//------------------------------------------------------------------------------
void __fastcall TRouteInfo::Clear ()
{
	RouteID   = 0;
	RouteName = "";
	ObjectID  = 0;
}
//------------------------------------------------------------------------------
bool __fastcall TRouteInfo::operator== (const TRouteInfo &other) const
{
	if (RouteID   != other.RouteID)
		return (false);
	if (RouteName != other.RouteName)
		return (false);
	if (ObjectID  != other.ObjectID)
		return (false);
	return (true);
}
//------------------------------------------------------------------------------
void __fastcall TRouteInfo::SetRouteID (const int &value)
{
	m_nRouteID = value;
}
//------------------------------------------------------------------------------
int __fastcall TRouteInfo::GetRouteID () const
{
	return (m_nRouteID);
}
//------------------------------------------------------------------------------
void __fastcall TRouteInfo::SetRouteName (const String &value)
{
	m_strRouteName = value;
}
//------------------------------------------------------------------------------
String __fastcall TRouteInfo::GetRouteName () const
{
	return (m_strRouteName);
}
//------------------------------------------------------------------------------
void __fastcall TRouteInfo::SetObjectID (const int value)
{
	m_nObjectID = value;
}
//------------------------------------------------------------------------------
int __fastcall TRouteInfo::GetObjectID () const
{
	return (m_nObjectID);
}
//------------------------------------------------------------------------------
bool __fastcall TRouteInfo::LoadFromDB (TADOQuery *query)
{
	bool f = true;
	
	try {
		RouteID =   query->Fields->FieldByName (FldRouteID)->AsInteger;
		RouteName = query->Fields->FieldByName (FldRouteName)->AsString;
		ObjectID =  query->Fields->FieldByName (FldObjectID)->AsInteger;
	}
	catch (...) {
		f = false;
	}
	return (f);;
}
//------------------------------------------------------------------------------
bool __fastcall TRouteInfo::InsertAsNew (TADOConnection *db, String &strErr)
{
	bool f;
	TADOQuery *query = InitQuery (db, NULL);
	
	f = InsertAsNew(query, strErr);
	delete query;
	return (f);
}
//------------------------------------------------------------------------------
bool __fastcall TRouteInfo::UpdateInDB (TADOConnection *db, String &strErr)
{
	bool f;
	TADOQuery *query = InitQuery (db, NULL);
	
	f = UpdateInDB(query, strErr);
	delete query;
	return (f);
}
//------------------------------------------------------------------------------
