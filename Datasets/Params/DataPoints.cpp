//------------------------------------------------------------------------------
#include<vcl.h>
#pragma hdrstop
#include "DataPoints.h"
//------------------------------------------------------------------------------
#pragma package(smart_init)

//------------------------------------------------------------------------------
String TDataPoint::Table       ("DATASETS_POINTS");
String TDataPoint::FldPointID  ("POINT_ID");
String TDataPoint::FldObjectID ("OBJECT_ID");
String TDataPoint::FldDatasetID("FATASET_ID");
String TDataPoint::FldLong     ("LONG");
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
	ObjectID  = other.ObjectID;
	DatasetID = other.DatasetID;
	Long      = other.Long;
	Lat       = other.Lat;
	Alt       = other.Alt;
	PointTime = other.PointTime;
}
//------------------------------------------------------------------------------
void __fastcall TDataPoint::Clear ()
{
	PointID   = 0;
	ObjectID  = 0;
	DatasetID = 0;
	Long      = 0.0;
	Lat       = 0.0;
	Alt       = 0.0;
	PointTime = ;
}
//------------------------------------------------------------------------------
bool __fastcall TDataPoint::operator== (const TDataPoint &other) const
{
	if (PointID   != other.PointID)
		return (false);
	if (ObjectID  != other.ObjectID)
		return (false);
	if (DatasetID != other.DatasetID)
		return (false);
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
void __fastcall TDataPoint::SetObjectID (const int value)
{
	m_nObjectID = value;
}
//------------------------------------------------------------------------------
int __fastcall TDataPoint::GetObjectID () const
{
	return (m_nObjectID);
}
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
		ObjectID =  query->Fields->FieldByName (FldObjectID)->AsInteger;
		DatasetID = query->Fields->FieldByName (FldDatasetID)->AsInteger;
		Long =      query->Fields->FieldByName (FldLong)->AsFloat;
		Lat =       query->Fields->FieldByName (FldLat)->AsFloat;
		Alt =       query->Fields->FieldByName (FldAlt)->AsFloat;
		PointTime = query->Fields->FieldByName (FldPointTime)->Ass;
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
				ModifyForUpdate(FldObjectID, ObjectID) + ", " + 
				ModifyForUpdate(FldDatasetID, DatasetID) + ", " + 
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
