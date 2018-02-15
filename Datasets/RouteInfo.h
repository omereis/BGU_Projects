//------------------------------------------------------------------------------
#ifndef	RouteInfoH
#define	RouteInfoH
//------------------------------------------------------------------------------
#include <ADODB.hpp>
#include "DBMisc.h"
#include <vector>
using namespace std;
//------------------------------------------------------------------------------
class TRouteInfo;
typedef vector<TRouteInfo> TRouteInfoBase;
//------------------------------------------------------------------------------
#include "DataPoints.h"
#include "IseTypes.h"
//------------------------------------------------------------------------------
class TRouteInfo {
public:
	__fastcall TRouteInfo ();
	__fastcall TRouteInfo (const TRouteInfo &other);
	TRouteInfo __fastcall operator= (const TRouteInfo &other);
	bool __fastcall operator!= (const TRouteInfo &other) const;
	bool __fastcall operator== (const TRouteInfo &other) const;
	void __fastcall Clear ();
// ---------- Database Methods ----------
	bool __fastcall FindByNameAndObj (TADOQuery *query, String &strErr);
	bool __fastcall InsertAndUpdate (TADOQuery *query, String &strErr);
// ---------- Database Support ----------
	bool __fastcall LoadFromDB (TADOQuery *query);
	bool __fastcall InsertAsNew (TADOConnection *db, String &strErr);
	bool __fastcall InsertAsNew (TADOQuery *query, String &strErr);
	bool __fastcall UpdateInDB (TADOConnection *db, String &strErr);
	bool __fastcall UpdateInDB (TADOQuery *query, String &strErr);
	bool __fastcall DeleteInDB (TADOConnection *db, String &strErr);
	bool __fastcall DeleteInDB (TADOQuery *query, String &strErr);
//----- P r o p e r t i e s -----------------------------------------------
	__property int RouteID = {read=GetRouteID, write=SetRouteID};
	__property String RouteName = {read=GetRouteName, write=SetRouteName};
	__property String RoutePath = {read=GetRoutePath, write=SetRoutePath};
	__property int ObjectID = {read=GetObjectID, write=SetObjectID};
// ---------- S t a t i c ----------
	static String Table;
	static String VPtsInRoute;
	static String FldRouteID;
	static String FldRouteName;
	static String FldObjectID;
	static String FldRoutePath;
protected:
	bool __fastcall ParsePoints (TDataPoints &vPoints);
	void __fastcall AssignAll (const TRouteInfo &other);
private:
	int m_nRouteID;
	String m_strRouteName;
	String m_strPath;
	int m_nObjectID;
//------------------------------------------------------------------------------
	int __fastcall GetRouteID () const;
	String __fastcall GetRouteName () const;
	String __fastcall GetRoutePath () const;
	int __fastcall GetObjectID () const;
//------------------------------------------------------------------------------
	void __fastcall SetRouteID (const int &value);
	void __fastcall SetRouteName (const String &value);
	void __fastcall SetRoutePath (const String &strPath);
	void __fastcall SetObjectID (const int value);
};
//------------------------------------------------------------------------------
class TRoutes : public TRouteInfoBase {
public:
	__fastcall TRoutes ();
// Vector Database Support
	bool __fastcall LoadFromDB (TADOQuery *query, String &strErr);
	bool __fastcall LoadFromDB (TADOConnection *db, String &strErr);
	TRoutes::iterator __fastcall FindRouteByPath (const String &strPathOriginal);
	bool __fastcall LoadPointsCount (TADOQuery *query, TIntVec &vPoints, String &strErr);
};
//------------------------------------------------------------------------------
#endif
