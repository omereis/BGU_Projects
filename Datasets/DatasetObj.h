//------------------------------------------------------------------------------
#ifndef	DatasetObjH
#define	DatasetObjH
//------------------------------------------------------------------------------
#include <ADODB.hpp>
#include "DBMisc.h"
#include <vector>
using namespace std;
#include "RouteInfo.h"
//------------------------------------------------------------------------------
class TDatasetObj;
typedef vector<TDatasetObj> TDatasetObjBase;
//------------------------------------------------------------------------------
class TDatasetObj {
public:
	__fastcall TDatasetObj ();
	__fastcall TDatasetObj (const TDatasetObj &other);
	__fastcall TDatasetObj (const String &strName);
	TDatasetObj __fastcall operator= (const TDatasetObj &other);
	bool __fastcall operator!= (const TDatasetObj &other) const;
	bool __fastcall operator== (const TDatasetObj &other) const;
	void __fastcall Clear ();
// ---------- Database Support ----------
	bool __fastcall LoadDatasetsObjects (TADOQuery *query, int idDataset, String &strErr);
	bool __fastcall InsertRoutes (TADOQuery *query, String &strErr, TForm *parent=NULL);
	void __fastcall AddRoute (const String &strPath, const String &strRoute);
	String __fastcall ParseObjNameFromPath (const String &strLine, String &strRoute);
	void __fastcall ParseDir (const String &strLine);
	bool __fastcall LoadIdByDsAndName (TADOQuery *query, String &strErr);
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
	__property int ObjID = {read=GetObjID, write=SetObjID};
	__property int DatasetID = {read=GetDatasetID, write=SetDatasetID};
	__property String ObjName = {read=GetObjName, write=SetObjName};
	__property String ObjType = {read=GetObjType, write=SetObjType};
	__property TRoutes Routes = {read=GetRoutes, write=SetRoutes};
// ---------- S t a t i c ----------
	static String Table;
	static String FldObjID;
	static String FldDatasetID;
	static String FldObjName;
	static String FldObjType;
protected:
	void __fastcall AssignAll (const TDatasetObj &other);
private:
	int m_nObjID;
	int m_nDatasetID;
	String m_strObjName;
	String m_strObjType;
	TRoutes m_vRoutes;
//------------------------------------------------------------------------------
	int __fastcall GetObjID () const;
	int __fastcall GetDatasetID () const;
	String __fastcall GetObjName () const;
	String __fastcall GetObjType () const;
	TRoutes __fastcall GetRoutes () const;
//------------------------------------------------------------------------------
	void __fastcall SetObjID (const int value);
	void __fastcall SetDatasetID (const int value);
	void __fastcall SetObjName (const String &value);
	void __fastcall SetObjType (const String &value);
	void __fastcall SetRoutes (TRoutes &vRoutes);
};
//------------------------------------------------------------------------------
class TDatasetObjects : public TDatasetObjBase {
public:
	__fastcall TDatasetObjects ();
// Vector Database Support
	bool __fastcall LoadFromDB (TADOQuery *query, String &strErr);
	bool __fastcall LoadFromDB (TADOConnection *db, String &strErr);
	bool __fastcall DeleteFromDB (TADOQuery *query, String &strErr);
	TDatasetObjects::iterator __fastcall FindByName (const String &strObjName);
	bool __fastcall LoadDatasetsObjects (TADOQuery *query, int idDataset, String &strErr);
};
//------------------------------------------------------------------------------
#endif
