//------------------------------------------------------------------------------
#ifndef	DataPointsH
#define	DataPointsH
//------------------------------------------------------------------------------
#include <ADODB.hpp>
#include "DBMisc.h"
#include <vector>
using namespace std;
//------------------------------------------------------------------------------
class TDataPoint;
typedef vector<TDataPoint> TDataPointBase;
//------------------------------------------------------------------------------
class TDataPoint {
public:
	__fastcall TDataPoint ();
	__fastcall TDataPoint (const TDataPoint &other);
	TDataPoint __fastcall operator= (const TDataPoint &other);
	bool __fastcall operator!= (const TDataPoint &other) const;
	bool __fastcall operator== (const TDataPoint &other) const;
	void __fastcall Clear ();
// ---------- Database Support ----------
	bool __fastcall LoadFromDB (TADOQuery *query);
	bool __fastcall InsertAsNew (TADOConnection *db, String &strErr);
	bool __fastcall InsertAsNew (TADOQuery *query, String &strErr);
	bool __fastcall UpdateInDB (TADOConnection *db, String &strErr);
	bool __fastcall UpdateInDB (TADOQuery *query, String &strErr);
	bool __fastcall DeleteInDB (TADOConnection *db, String &strErr);
	bool __fastcall DeleteInDB (TADOQuery *query, String &strErr);
//----- P r o p e r t i e s -----------------------------------------------
	__property int PointID = {read=GetPointID, write=SetPointID};
	__property int ObjectID = {read=GetObjectID, write=SetObjectID};
	__property int DatasetID = {read=GetDatasetID, write=SetDatasetID};
	__property double Long = {read=GetLong, write=SetLong};
	__property double Lat = {read=GetLat, write=SetLat};
	__property double Alt = {read=GetAlt, write=SetAlt};
	__property TDateTime PointTime = {read=GetPointTime, write=SetPointTime};
// ---------- S t a t i c ----------
	static String Table;
	static String FldPointID;
	static String FldObjectID;
	static String FldDatasetID;
	static String FldLong;
	static String FldLat;
	static String FldAlt;
	static String FldPointTime;
protected:
	void __fastcall AssignAll (const TDataPoint &other);
private:
	int m_nPointID;
	int m_nObjectID;
	int m_nDatasetID;
	double m_dLong;
	double m_dLat;
	double m_d;
	TDateTime m_dtPointTime;
//------------------------------------------------------------------------------
	int __fastcall GetPointID () const;
	int __fastcall GetObjectID () const;
	int __fastcall GetDatasetID () const;
	double __fastcall GetLong () const;
	double __fastcall GetLat () const;
	double __fastcall GetAlt () const;
	TDateTime __fastcall GetPointTime () const;
//------------------------------------------------------------------------------
	void __fastcall SetPointID (const int value);
	void __fastcall SetObjectID (const int value);
	void __fastcall SetDatasetID (const int value);
	void __fastcall SetLong (const double value);
	void __fastcall SetLat (const double value);
	void __fastcall SetAlt (const double value);
	void __fastcall SetPointTime (const TDateTime &value);
};
//------------------------------------------------------------------------------
class TDataPoints : public TDataPointBase {
public:
	__fastcall TDataPoints ();
// Vector Database Support
	bool __fastcall LoadFromDB (TADOQuery *query, String &strErr);
	bool __fastcall LoadFromDB (TADOConnection *db, String &strErr);
};
//------------------------------------------------------------------------------
#endif
