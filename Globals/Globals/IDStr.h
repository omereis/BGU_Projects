//------------------------------------------------------------------------------
#ifndef	IDStrH
#define	IDStrH
//------------------------------------------------------------------------------
#include <ADODB.hpp>
#include "DBMisc.h"
#include <vector>
using namespace std;
#include <Dialogs.hpp>
//------------------------------------------------------------------------------
class TIDStr;
typedef vector<TIDStr> TIDStrBase;
//------------------------------------------------------------------------------
class TIDStr {
public:
	__fastcall TIDStr ();
	__fastcall TIDStr (const TIDStr &other);
	TIDStr __fastcall operator= (const TIDStr &other);
	bool __fastcall operator!= (const TIDStr &other) const;
	bool __fastcall operator== (const TIDStr &other) const;
	void __fastcall Clear ();
// ---------- Database Support ----------
	bool __fastcall LoadFromDB (TADOQuery *query, const String strTable, const String strFldID, const String &strFldStr);
	bool __fastcall InsertAsNew (TADOConnection *db, const String &strTable, const String &strFldID, String &strErr);
	bool __fastcall InsertAsNew (TADOQuery *query, const String &strTable, const String &strFldID, String &strErr);
	bool __fastcall UpdateInDB (TADOConnection *db, const String &strTable, const String &strFldID, const String &strFldStr, String &strErr);
	bool __fastcall UpdateInDB (TADOQuery *query, const String &strTable, const String &strFldID, const String &strFldStr, String &strErr);
	bool __fastcall DeleteInDB (TADOConnection *db, const String &strTable, const String &strFldID, const String &strFldStr, String &strErr);
	bool __fastcall DeleteInDB (TADOQuery *query, const String &strTable, const String &strFldID, const String &strFldStr, String &strErr);
//----- P r o p e r t i e s -----------------------------------------------
	__property int ID      = {read=GetID, write=SetID};
	__property String Name = {read=GetName, write=SetName};
/*
// ---------- S t a t i c ----------
	static String Table;
	static String FldID;
	static String FldName;
	static String Table;
	static String FldID;
	static String FldStr;
*/
protected:
	void __fastcall AssignAll (const TIDStr &other);
private:
	int m_nID;
	String m_strName;
//------------------------------------------------------------------------------
	int __fastcall GetID () const;
	String __fastcall GetName () const;
//------------------------------------------------------------------------------
	void __fastcall SetID (const int value);
	void __fastcall SetName (const String &value);
};
//------------------------------------------------------------------------------
class TIDStrings : public TIDStrBase {
public:
	TIDStrings (const String &strTable, const String &strFldID, const String &strFldStr);
	TIDStrings (TADOConnection *db, const String &strTable, const String &strFldID, const String &strFldStr);
	~TIDStrings ();
// Vector Database Support
	bool __fastcall LoadFromDB (TADOQuery *query, String &strErr);
	bool __fastcall LoadFromDB (TADOConnection *db, String &strErr);

	TIDStrings::iterator __fastcall FindByID (int id);

	bool __fastcall UpdateItems (String &strErr);
	bool __fastcall InsertItems (String &strErr);
	bool __fastcall DeleteItems (String &strErr);
protected:
	TADOConnection *m_db;
	TADOQuery *m_query;
	String m_strTable;
	String m_strFldID;
	String m_strFldStr;
};
//------------------------------------------------------------------------------
#endif
