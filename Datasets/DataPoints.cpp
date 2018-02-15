//------------------------------------------------------------------------------
#include<vcl.h>
#pragma hdrstop
#include "DataPoints.h"
#include "Misc.h"
//------------------------------------------------------------------------------
#pragma package(smart_init)

//------------------------------------------------------------------------------
String TDataPoint::Table       ("T_POINTS");
String TDataPoint::FldPointID  ("POINT_ID");
String TDataPoint::FldRouteID  ("ROUTE_ID");
//String TDataPoint::FldDatasetID("FATASET_ID");
String TDataPoint::FldLong     ("LNG");
String TDataPoint::FldLat      ("LAT");
String TDataPoint::FldAlt      ("ALT");
String TDataPoint::FldPointTime("PT_TIME");
//------------------------------------------------------------------------------
__fastcall TDataPoint::TDataPoint ()
{
	Clear();
}
//------------------------------------------------------------------------------
__fastcall TDataPoint::TDataPoint (const TDataPoint &other)
{
	AssignAll (other);
}
//------------------------------------------------------------------------------
TDataPoint __fastcall TDataPoint::operator= (const TDataPoint &other)
{
	AssignAll (other);
	return (*this);
}
//------------------------------------------------------------------------------
void __fastcall TDataPoint::AssignAll (const TDataPoint &other)
{
	PointID   = other.PointID;
	RouteID  = other.RouteID;
//	DatasetID = other.DatasetID;
	Long      = other.Long;
	Lat       = other.Lat;
	Alt       = other.Alt;
	PointTime = other.PointTime;
}
//------------------------------------------------------------------------------
void __fastcall TDataPoint::Clear ()
{
	PointID   = 0;
	RouteID  = 0;
//	DatasetID = 0;
	Long      = 0.0;
	Lat       = 0.0;
	Alt       = 0.0;
//	PointTime = ;
}
//------------------------------------------------------------------------------
bool __fastcall TDataPoint::operator== (const TDataPoint &other) const
{
	if (PointID   != other.PointID)
		return (false);
	if (RouteID  != other.RouteID)
		return (false);
//	if (DatasetID != other.DatasetID)
//		return (false);
	if (Long      != other.Long)
		return (false);
	if (Lat       != other.Lat)
		return (false);
	if (Alt       != other.Alt)
		return (false);
	if (PointTime != other.PointTime)
		return (false);
	return (true);
}
//------------------------------------------------------------------------------
void __fastcall TDataPoint::SetPointID (const int value)
{
	m_nPointID = value;
}
//------------------------------------------------------------------------------
int __fastcall TDataPoint::GetPointID () const
{
	return (m_nPointID);
}
//------------------------------------------------------------------------------
void __fastcall TDataPoint::SetRouteID (const int value)
{
	m_nRouteID = value;
}
//------------------------------------------------------------------------------
int __fastcall TDataPoint::GetRouteID () const
{
	return (m_nRouteID);
}
/*
//------------------------------------------------------------------------------
void __fastcall TDataPoint::SetDatasetID (const int value)
{
	m_nDatasetID = value;
}
//------------------------------------------------------------------------------
int __fastcall TDataPoint::GetDatasetID () const
{
	return (m_nDatasetID);
}
*/
//------------------------------------------------------------------------------
void __fastcall TDataPoint::SetLong (const double value)
{
	m_dLong = value;
}
//------------------------------------------------------------------------------
double __fastcall TDataPoint::GetLong () const
{
	return (m_dLong);
}
//------------------------------------------------------------------------------
void __fastcall TDataPoint::SetLat (const double value)
{
	m_dLat = value;
}
//------------------------------------------------------------------------------
double __fastcall TDataPoint::GetLat () const
{
	return (m_dLat);
}
//------------------------------------------------------------------------------
void __fastcall TDataPoint::SetAlt (const double value)
{
	m_d = value;
}
//------------------------------------------------------------------------------
double __fastcall TDataPoint::GetAlt () const
{
	return (m_d);
}
//------------------------------------------------------------------------------
void __fastcall TDataPoint::SetPointTime (const TDateTime &value)
{
	m_dtPointTime = value;
}
//------------------------------------------------------------------------------
TDateTime __fastcall TDataPoint::GetPointTime () const
{
	return (m_dtPointTime);
}
//------------------------------------------------------------------------------
bool __fastcall TDataPoint::LoadFromDB (TADOQuery *query)
{
	bool f = true;
	
	try {
		PointID =   query->Fields->FieldByName (FldPointID)->AsInteger;
		RouteID =  query->Fields->FieldByName (FldRouteID)->AsInteger;
//		DatasetID = query->Fields->FieldByName (FldDatasetID)->AsInteger;
		Long =      query->Fields->FieldByName (FldLong)->AsFloat;
		Lat =       query->Fields->FieldByName (FldLat)->AsFloat;
		Alt =       query->Fields->FieldByName (FldAlt)->AsFloat;
		PointTime = query->Fields->FieldByName (FldPointTime)->AsDateTime;
	}
	catch (...) {
		f = false;
	}
	return (f);;
}
//------------------------------------------------------------------------------
bool __fastcall TDataPoint::InsertAsNew (TADOQuery *query, String &strErr)
{
	int id;
	bool f;
	String strSql;
	
	f = GetFieldMax (query, Table, FldPointID, id);
	if (f) {
		strSql = "insert into " + Table + "(" + FldPointID + ") values (" + String (id + 1) + ");";
		f = RunQuery (query, strSql, QueryExec, strErr);
	}
	return (f);
}
//------------------------------------------------------------------------------
bool __fastcall TDataPoint::InsertAsNew (TADOConnection *db, String &strErr)
{
	bool f;
	TADOQuery *query = InitQuery (db, NULL);
	
	f = InsertAsNew(query, strErr);
	delete query;
	return (f);
}
//------------------------------------------------------------------------------
bool __fastcall TDataPoint::UpdateInDB (TADOQuery *query, String &strErr)
{
	String strSql;
	bool f;
	
	strSql = "update " + Table + "set "  + ModifyForUpdate(FldPointID, PointID) + ", " + 
				ModifyForUpdate(FldRouteID, RouteID) + ", " +
//				ModifyForUpdate(FldDatasetID, DatasetID) + ", " + 
				ModifyForUpdate(FldLong, Long) + ", " + 
				ModifyForUpdate(FldLat, Lat) + ", " + 
				ModifyForUpdate(FldAlt, Alt) + ", " + 
				ModifyForUpdate(FldPointTime, PointTime) +
			"where " + FldPointID + " = " + String(PointID);
	f = RunQuery(query, strSql, QueryExec, strErr);
	return (f);
}
//------------------------------------------------------------------------------
bool __fastcall TDataPoint::UpdateInDB (TADOConnection *db, String &strErr)
{
	bool f;
	TADOQuery *query = InitQuery (db, NULL);

	f = UpdateInDB(query, strErr);
	delete query;
	return (f);
}
//------------------------------------------------------------------------------
Word __fastcall StringToWord (const String &str)
{
	Word w;

	w = (Word) str.ToIntDef(0);
	return (w);
}
//------------------------------------------------------------------------------
bool __fastcall TDataPoint::SetPointGeoTime (const String &strDate, const String &strTime, TStringList *lstrTokens)
{
	bool f = true;
	TDateTime dtDate, dtTime, dt;
//	String str;
//	TStringList *lstrTokens = new TStringList;
	Word wYear, wMonth, wDay, wHour, wMin, wSec, wMSec = 0;

	try {
		try {
			Tokenize (strDate, lstrTokens, "-");
			if (lstrTokens->Count >= 2) {
				wYear  = StringToWord (lstrTokens->Strings[0]);
				wMonth = StringToWord (lstrTokens->Strings[1]);
				wDay   = StringToWord (lstrTokens->Strings[2]);
				dtDate = EncodeDate (wYear, wMonth, wDay);
//				str = dtDate.DateString();
			}
			Tokenize (strTime, lstrTokens, ":");
			if (lstrTokens->Count >= 2) {
				wHour = StringToWord (lstrTokens->Strings[0]);
				wMin  = StringToWord (lstrTokens->Strings[1]);
				wSec  = StringToWord (lstrTokens->Strings[2]);
				dtTime = EncodeTime (wHour, wMin, wSec, wMSec);
//				str = dtTime.TimeString();
			}
			dt = dtDate + dtTime;
			PointTime = dt;
		} catch (...) {
			f = false;
		}
	}
	__finally {
//		delete lstrTokens;
		return (f);
	}
//	str = dt.DateString() + ", " + dt.TimeString();
}
//------------------------------------------------------------------------------
String __fastcall GetMySQLDateTimeString (const TDateTime dt)
{
	Word wYear, wMonth, wDay, wHour, wMin, wSec, wMSec;
	String str;

	dt.DecodeDate(&wYear, &wMonth, &wDay);
	dt.DecodeTime (&wHour, &wMin, &wSec, &wMSec);
	str.sprintf ("'%d-%02d-%d %02d:%02d:%02d'", wYear, wMonth, wDay, wHour, wMin, wSec);
	return (str);
}
//------------------------------------------------------------------------------
String __fastcall TDataPoint::GetSqlInsertString () const
{
	String str;

	str = 	String (PointID) + "," +
			String(RouteID) + "," +
			FormatFloat ("#.######", Long) + "," +
			FormatFloat ("#.######", Lat) + "," +
			FormatFloat ("#0.0######", Alt) + "," +
			GetMySQLDateTimeString (PointTime);
	return ("(" + str + ")");
}
//------------------------------------------------------------------------------
String __fastcall TDataPoint::GetDateTimeString () const
{
	Word wYear, wMonth, wDay, wHour, wMin, wSec, wMSec;
	String str;

	PointTime.DecodeDate(&wYear, &wMonth, &wDay);
	PointTime.DecodeTime (&wHour, &wMin, &wSec, &wMSec);
	str.sprintf ("%d-%02d-%d %02d:%02d:%02d", wDay, wYear, wMonth, wHour, wMin, wSec);
	return (str);
//	return (GetMySQLDateTimeString (PointTime));
}
//------------------------------------------------------------------------------
//	TDataPoints
//------------------------------------------------------------------------------
TDataPoints::TDataPoints () : TDataPointBase ()
{
}
//------------------------------------------------------------------------------
bool __fastcall TDataPoints::LoadFromDB (TADOQuery *query, String &strErr, int idRoute)
{
	bool f;
	String strSql;
	TDataPoint dpt;

	clear ();
	strSql = "select * from " + TDataPoint::Table;
	if (idRoute > 0)
		strSql += " where " + TDataPoint::FldRouteID + "=" + String (idRoute);
	strSql += ";";
	if ((f = RunQuery (query, strSql, QueryOpen, strErr)) == true) {
		query->First ();
		while (!query->Eof) {
			if (dpt.LoadFromDB (query)) {
				push_back (dpt);
			}
			query->Next ();
		}
	}
	return (f);
}
//------------------------------------------------------------------------------
bool __fastcall TDataPoints::LoadFromDB (TADOConnection *db, String &strErr, int idRoute)
{
	TADOQuery *query = InitQuery (db, NULL);
	bool f;

	f = LoadFromDB (query, strErr, idRoute);
	delete query;
	return (f);
}
#include <time.h>
extern clock_t g_cPoints;
//------------------------------------------------------------------------------
bool __fastcall TDataPoints::InsertAll (TADOQuery *query, String &strErr)
{
	bool f;
	String strSql, strConst, strValues, str;
	TDataPoints::iterator iPoint;
	size_t n;
	int id;
	clock_t cStart, cEnd;

	cStart = clock ();
/*
	strConst = "insert into " + TDataPoint::Table + "(" + TDataPoint::FldPointID + ") values ";
*/
	strConst = "insert into " + TDataPoint::Table + "(" + TDataPoint::FldPointID + "," +
													TDataPoint::FldRouteID + "," +
													TDataPoint::FldLong + "," +
													TDataPoint::FldLat + "," +
													TDataPoint::FldAlt + "," +
													TDataPoint::FldPointTime + ") values ";
	if ((f = GetFieldMax (query, TDataPoint::Table, TDataPoint::FldPointID, id)) == true) {
		id++;
		for (iPoint=begin(), n=0 ; iPoint != end() ; iPoint++, n++) {
			iPoint->PointID = id++;
			str = iPoint->GetSqlInsertString () + ",";
//			str = "(" + String (iPoint->PointID) + "),";
			if ((n > 0) && (n % 1000) == 0) {
				strValues[strValues.Length()] = ';';
				strSql = strConst + strValues;
				f = RunQuery (query, strSql, QueryExec, strErr);
				strValues = "";
			}
			else
				strValues += str;// + ",";
		}
		if (strValues.Length() > 0) {
			strValues[strValues.Length()] = ';';
			strSql = strConst + strValues;
			f = RunQuery (query, strSql, QueryExec, strErr);
		}
	}
	cEnd = clock ();
	g_cPoints += (cEnd - cStart);
	return (f);
}
//------------------------------------------------------------------------------
bool __fastcall TDataPoints::LoadRoutePoints (int idRoute, TADOQuery *query, String &strErr)
{
	return (LoadFromDB (query, strErr, idRoute));
}
//------------------------------------------------------------------------------

