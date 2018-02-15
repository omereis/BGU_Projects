//------------------------------------------------------------------------------
#ifndef	UserInfoH
#define	UserInfoH
//------------------------------------------------------------------------------
#include <ADODB.hpp>
#include "DBMisc.h"
#include <vector>
using namespace std;
//------------------------------------------------------------------------------
class TUserInfo;
typedef vector<TUserInfo> TUserInfoBase;
//------------------------------------------------------------------------------
class TUserInfo {
public:
	__fastcall TUserInfo ();
	__fastcall TUserInfo (const TUserInfo &other);
	TUserInfo __fastcall operator= (const TUserInfo &other);
	bool __fastcall operator!= (const TUserInfo &other) const;
	bool __fastcall operator== (const TUserInfo &other) const;
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
	__property int UserID = {read=GetUserID, write=SetUserID};
	__property String Username = {read=GetUsername, write=SetUsername};
	__property String Password = {read=GetPassword, write=SetPassword};
	__property String First = {read=GetFirst, write=SetFirst};
	__property String Last = {read=GetLast, write=SetLast};
// ---------- S t a t i c ----------
	static String Table;
	static String FldID;
	static String FldUsername;
	static String FldPassword;
	static String FldFirst;
	static String FldLast;
protected:
	void __fastcall AssignAll (const TUserInfo &other);
private:
	int m_nUserID;
	String m_strUsername;
	String m_strPasswd;
	String m_strFirst;
	String m_strLast;
//------------------------------------------------------------------------------
	int __fastcall GetUserID () const;
	String __fastcall GetUsername () const;
	String __fastcall GetPassword () const;
	String __fastcall GetFirst () const;
	String __fastcall GetLast () const;
//------------------------------------------------------------------------------
	void __fastcall SetUserID (const int value);
	void __fastcall SetUsername (const String &value);
	void __fastcall SetPassword (const String &value);
	void __fastcall SetFirst (const String &value);
	void __fastcall SetLast (const String &value);
};
//------------------------------------------------------------------------------
class TUsers : public TUserInfoBase {
public:
	__fastcall TUsers ();
// Vector Database Support
	bool __fastcall LoadFromDB (TADOQuery *query, String &strErr);
	bool __fastcall LoadFromDB (TADOConnection *db, String &strErr);
};
//------------------------------------------------------------------------------
#endif
