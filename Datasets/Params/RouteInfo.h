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
class TRouteInfo {
public:
	__fastcall TRouteInfo ();
	__fastcall TRouteInfo (const TRouteInfo &other);
	TRouteInfo __fastcall operator= (const TRouteInfo &other);
	bool __fastcall operator!= (const TRouteInfo &other) const;
	bool __fastcall operator== (const TRouteInfo &other) const;
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
	__property int RouteID = {read=GetRouteID, write=SetRouteID};
	__property String RouteName = {read=GetRouteName, write=SetRouteName};
	__property int ObjectID = {read=GetObjectID, write=SetObjectID};
// ---------- S t a t i c ----------
	static String Table;
	static String FldRouteID;
	static String FldRouteName;
	static String FldObjectID;
protected:
	void __fastcall AssignAll (const TRouteInfo &other);
private:
	int m_nRouteID;
	String m_strRouteName;
	int m_nObjectID;
//------------------------------------------------------------------------------
	int __fastcall GetRouteID () const;
	String __fastcall GetRouteName () const;
	int __fastcall GetObjectID () const;
//------------------------------------------------------------------------------
	void __fastcall SetRouteID (const int &value);
	void __fastcall SetRouteName (const String &value);
	void __fastcall SetObjectID (const int value);
};
//------------------------------------------------------------------------------
class tRoutes : public TRouteInfoBase {
public:
	__fastcall tRoutes ();
// Vector Database Support
	bool __fastcall LoadFromDB (TADOQuery *query, String &strErr);
	bool __fastcall LoadFromDB (TADOConnection *db, String &strErr);
};
//------------------------------------------------------------------------------
#endif
