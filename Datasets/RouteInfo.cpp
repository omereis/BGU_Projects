//------------------------------------------------------------------------------
#include<vcl.h>
#pragma hdrstop
#include "RouteInfo.h"
#include "Misc.h"
//------------------------------------------------------------------------------
#pragma package(smart_init)

//------------------------------------------------------------------------------
String TRouteInfo::Table       ("T_ROUTES");
String TRouteInfo::VPtsInRoute ("V_POINTS_IN_ROUTE");
String TRouteInfo::FldRouteID  ("ROUTE_ID");
String TRouteInfo::FldRouteName("ROUTE_NAME");
String TRouteInfo::FldObjectID ("OBJECT_ID");
String TRouteInfo::FldRoutePath("ROUTE_PATH");
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
	RoutePath = other.RoutePath;
	ObjectID  = other.ObjectID;
}
//------------------------------------------------------------------------------
void __fastcall TRouteInfo::Clear ()
{
	RouteID   = 0;
	RouteName = "";
	RoutePath = "";
	ObjectID  = 0;
}
//------------------------------------------------------------------------------
bool __fastcall TRouteInfo::operator== (const TRouteInfo &other) const
{
	if (RouteID   != other.RouteID)
		return (false);
	if (RouteName != other.RouteName)
		return (false);
	if (RoutePath != other.RoutePath)
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
void __fastcall TRouteInfo::SetRoutePath (const String &strPath)
{
	m_strPath = strPath;
}
//------------------------------------------------------------------------------
String __fastcall TRouteInfo::GetRoutePath () const
{
	return (m_strPath);
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
		RoutePath = query->Fields->FieldByName (FldRoutePath)->AsString;
		ObjectID =  query->Fields->FieldByName (FldObjectID)->AsInteger;
	}
	catch (...) {
		f = false;
	}
	return (f);;
}
//------------------------------------------------------------------------------
bool __fastcall TRouteInfo::InsertAsNew (TADOQuery *query, String &strErr)
{
	int idNew;
	String strSql;
	bool f;

	if ((f = GetFieldMax (query, Table, FldRouteID, idNew)) == true) {
		++idNew;
		strSql = "insert into " + Table + " (" + FldRouteID + ") values ("
				+ String (idNew) + ");";
		if ((f = RunQuery (query, strSql, QueryExec, strErr)) == true) {
			RouteID = idNew;
		}
	}
	return (f);
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
bool __fastcall TRouteInfo::UpdateInDB (TADOQuery *query, String &strErr)
{
	bool f;
	String strSql;

	strSql = "update " + Table + " set " +
			ModifyForUpdate (FldRouteName, RouteName) + "," +
			ModifyForUpdate (FldRoutePath, RoutePath) + "," +
			ModifyForUpdate (FldObjectID, ObjectID, true) +
			" where " + FldRouteID + "=" + String (RouteID) + ";";
	f = RunQuery (query, strSql, QueryExec, strErr);
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
bool __fastcall TRouteInfo::FindByNameAndObj (TADOQuery *query, String &strErr)
{
	bool f;
	String strSql;

	strSql = "select * from " + Table + " where " +
			FldRouteName + "=" + ModifyForInsert (RouteName) + " and " +
			FldObjectID + "=" + String (ObjectID) + ";";
	if ((f = RunQuery (query, strSql, QueryOpen, strErr)) == true) {
		query->First ();
		if (!query->Eof) {
			LoadFromDB (query);
		}
	}
	return (f);
}
//------------------------------------------------------------------------------
bool __fastcall TRouteInfo::InsertAndUpdate (TADOQuery *query, String &strErr)
{
	bool f;
	TDataPoints vPoints;
	int id;

	if ((f = InsertAsNew(query, strErr)) == true) {
		id = RouteID;
		if ((f = UpdateInDB (query, strErr)) == true) {
        	vPoints.clear();
			if (ParsePoints (vPoints))
				f = vPoints.InsertAll (query, strErr);
		}
	}
	return (f);
}
//------------------------------------------------------------------------------
bool __fastcall TRouteInfo::ParsePoints (TDataPoints &vPoints)
{
	TDataPoint d_point;
	TStringList *lstr = new TStringList, *lstrTokens = new TStringList, *lstrDateTokens = new TStringList;
	int n;
	bool f;

	try {
		try {
			d_point.RouteID = RouteID;
			lstr->LoadFromFile (RoutePath);
			for (n=6 ; n < lstr->Count ; n++) {
				Tokenize (lstr->Strings[n], lstrTokens);
				d_point.Lat = atof (lstrTokens->Strings[0].c_str());
				d_point.Long = atof (lstrTokens->Strings[1].c_str());
				d_point.Alt  = atof (lstrTokens->Strings[3].c_str());
				d_point.SetPointGeoTime (lstrTokens->Strings[5],lstrTokens->Strings[6], lstrDateTokens);
				f = true;
				vPoints.push_back (d_point);
			}
		}
		catch (Exception &e) {
			f = false;
			ShowMessage ("Error while converting GeoLife File\n" + RoutePath +
						"\nLine # " + String (n) + ":\n" +
						e.Message);
		}
	}
	__finally  {
		delete lstr;
		delete lstrTokens;
		delete lstrDateTokens;
		return (f);
	}
}
//------------------------------------------------------------------------------
//	TRoutes
//------------------------------------------------------------------------------
__fastcall TRoutes::TRoutes () : TRouteInfoBase ()
{
}
//------------------------------------------------------------------------------
bool __fastcall TRoutes::LoadFromDB (TADOQuery *query, String &strErr)
{
	bool f;
	String strSql;
	TRouteInfo route;

	clear ();
	strSql = "select * from " + TRouteInfo::Table + ";";
	if ((f = RunQuery (query, strSql, QueryOpen, strErr)) == true) {
		query->First ();
		while (!query->Eof) {
			if (route.LoadFromDB (query)) {
				push_back (route);
			}
			query->Next ();
		}
	}
	return (f);
}
//------------------------------------------------------------------------------
bool __fastcall TRoutes::LoadFromDB (TADOConnection *db, String &strErr)
{
	TADOQuery *query = InitQuery (db, NULL);
	bool f = LoadFromDB (query, strErr);
	delete query;
	return (f);
}
//------------------------------------------------------------------------------
TRoutes::iterator __fastcall TRoutes::FindRouteByPath (const String &strPathOriginal)
{
	TRoutes::iterator iRoute, iFound = NULL;
	String strRoute, strPath;

	strPath = strPathOriginal.LowerCase ();
	for (iRoute=begin() ; (iRoute != end()) && (iFound == NULL) ; iRoute++) {
		strRoute = iRoute->RouteName.LowerCase();
		if (strPath == strRoute) {
			iFound = iRoute;
		}
	}
	return (iFound);
}
//------------------------------------------------------------------------------
bool __fastcall TRoutes::LoadPointsCount (TADOQuery *query, TIntVec &vPoints, String &strErr)
{
	String strSql;
	bool f;
	int nCount, n;
	TRouteInfo route;

	TCursor cr = Screen->Cursor;
	Screen->Cursor = crHourGlass;
	strSql = "select * from " + TRouteInfo::VPtsInRoute + "," + TRouteInfo::Table +
			" WHERE " + TRouteInfo::Table + "." + TRouteInfo::FldRouteID + "=" +
			TRouteInfo::VPtsInRoute + "." + TRouteInfo::FldRouteID +
			";";
	vPoints.clear ();
	clear ();
	if ((f = RunQuery (query, strSql, QueryOpen, strErr)) == true) {
		query->First ();
		n = 1;
		while (!query->Eof) {
			route.LoadFromDB (query);
			push_back (route);
			nCount = query->Fields->FieldByName ("POINTS")->AsInteger;
			vPoints.push_back (nCount);
			query->Next ();
			n++;
		}
	}
	Screen->Cursor = cr;
	return (f);
}
//------------------------------------------------------------------------------

