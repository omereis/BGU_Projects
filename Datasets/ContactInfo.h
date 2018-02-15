//------------------------------------------------------------------------------
#ifndef	ContactInfoH
#define	ContactInfoH
//------------------------------------------------------------------------------
#include <ADODB.hpp>
#include "DBMisc.h"
#include <vector>
using namespace std;
//------------------------------------------------------------------------------
class TContactInfo;
typedef vector<TContactInfo> TContactInfoBase;
//------------------------------------------------------------------------------
class TContactInfo {
public:
	__fastcall TContactInfo ();
	__fastcall TContactInfo (const TContactInfo &other);
	TContactInfo __fastcall operator= (const TContactInfo &other);
	bool __fastcall operator!= (const TContactInfo &other) const;
	bool __fastcall operator== (const TContactInfo &other) const;
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
	__property int ID = {read=GetID, write=SetID};
	__property int DatasetID = {read=GetDatasetID, write=SetDatasetID};
	__property String Name = {read=GetName, write=SetName};
	__property String Email = {read=GetEmail, write=SetEmail};
	__property String Phone = {read=GetPhone, write=SetPhone};
	__property String Comments = {read=GetComments, write=SetComments};
// ---------- S t a t i c ----------
	static String Table;
	static String FldID;
	static String FldDatasetID;
	static String FldName;
	static String FldEmail;
	static String FldPhone;
	static String FldComments;
protected:
	void __fastcall AssignAll (const TContactInfo &other);
private:
	int m_nID;
	int m_nDatasetID;
	String m_strName;
	String m_strEmail;
	String m_strPhone;
	String m_strComments;
//------------------------------------------------------------------------------
	int __fastcall GetID () const;
	int __fastcall GetDatasetID () const;
	String __fastcall GetName () const;
	String __fastcall GetEmail () const;
	String __fastcall GetPhone () const;
	String __fastcall GetComments () const;
//------------------------------------------------------------------------------
	void __fastcall SetID (const int value);
	void __fastcall SetDatasetID (const int value);
	void __fastcall SetName (const String &value);
	void __fastcall SetEmail (const String &value);
	void __fastcall SetPhone (const String &value);
	void __fastcall SetComments (const String &value);
};
//------------------------------------------------------------------------------
class TContacts : public TContactInfoBase {
public:
	TContacts ();
// Vector Database Support
	bool __fastcall LoadFromDB (TADOQuery *query, String &strErr);
	bool __fastcall LoadFromDB (TADOConnection *db, String &strErr);
};
//------------------------------------------------------------------------------
#endif
