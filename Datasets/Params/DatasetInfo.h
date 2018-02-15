//------------------------------------------------------------------------------
#ifndef	DatasetInfoH
#define	DatasetInfoH
//------------------------------------------------------------------------------
#include <ADODB.hpp>
#include "DBMisc.h"
#include <vector>
using namespace std;
//------------------------------------------------------------------------------
class TDatasetInfo;
typedef vector<TDatasetInfo> TDatasetInfoBase;
//------------------------------------------------------------------------------
class TDatasetInfo {
public:
	__fastcall TDatasetInfo ();
	__fastcall TDatasetInfo (const TDatasetInfo &other);
	TDatasetInfo __fastcall operator= (const TDatasetInfo &other);
	bool __fastcall operator!= (const TDatasetInfo &other) const;
	bool __fastcall operator== (const TDatasetInfo &other) const;
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
	__property int DatasetID = {read=GetDatasetID, write=SetDatasetID};
	__property String Name = {read=GetName, write=SetName};
	__property String URL = {read=GetURL, write=SetURL};
	__property String Structure = {read=GetStructure, write=SetStructure};
	__property TContacts Contacts = {read=GetContacts, write=SetContacts};
	__property TDataPoints Points = {read=GetPoints, write=SetPoints};
	__property String Username = {read=GetUsername, write=SetUsername};
	__property String Password = {read=GetPassword, write=SetPassword};
	__property String Description = {read=GetDescription, write=SetDescription};
// ---------- S t a t i c ----------
	static String Table;
	static String FldDatasetID;
	static String FldName;
	static String FldURL;
	static String FldStructure;
	static String ;
	static String ;
	static String FldUsername;
	static String FldPassword;
	static String FldDescription;
protected:
	void __fastcall AssignAll (const TDatasetInfo &other);
private:
	int m_nDatasetID;
	String m_strName;
	String m_strURL;
	String m_strStructure;
	TContacts m_vContacts;
	TDataPoints m_vPoints;
	String m_strString;
	String m_strPassword;
	String m_strDescription;
//------------------------------------------------------------------------------
	int __fastcall GetDatasetID () const;
	String __fastcall GetName () const;
	String __fastcall GetURL () const;
	String __fastcall GetStructure () const;
	TContacts __fastcall GetContacts () const;
	TDataPoints __fastcall GetPoints () const;
	String __fastcall GetUsername () const;
	String __fastcall GetPassword () const;
	String __fastcall GetDescription () const;
//------------------------------------------------------------------------------
	void __fastcall SetDatasetID (const int value);
	void __fastcall SetName (const String &value);
	void __fastcall SetURL (const String &value);
	void __fastcall SetStructure (const String &value);
	void __fastcall SetContacts (const TContacts value);
	void __fastcall SetPoints (const TDataPoints value);
	void __fastcall SetUsername (const String &value);
	void __fastcall SetPassword (const String &value);
	void __fastcall SetDescription (const String &value);
};
//------------------------------------------------------------------------------
class TDatases : public TDatasetInfoBase {
public:
	__fastcall TDatases ();
// Vector Database Support
	bool __fastcall LoadFromDB (TADOQuery *query, String &strErr);
	bool __fastcall LoadFromDB (TADOConnection *db, String &strErr);
};
//------------------------------------------------------------------------------
#endif
