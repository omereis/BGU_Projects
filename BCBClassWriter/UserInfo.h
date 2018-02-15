//------------------------------------------------------------------------------
#ifndef	ClassTUserInfoH
#define	ClassTUserInfoH
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
	bool __fastcall operator!= (const TUserInfo &other);
	bool __fastcall operator== (const TUserInfo &other);
	void __fastcall Clear ();

//----- P r o p e r t i e s -----------------------------------------------
	__property int UserID = {read=GetUserID, write=SetUserID};
	__property String UserName = {read=GetUserName, write=SetUserName};
	__property String Last = {read=GetLast, write=SetLast};
	__property String Password = {read=GetPassword, write=SetPassword};
	__property String First = {read=GetFirst, write=SetFirst};
protected:
	void __fastcall AssignAll (const TUserInfo &other);
private:
	int m_nUserID;
	String m_strUserName;
	String m_strLast;
	String m_strPassword;
	String m_strFirst;
//------------------------------------------------------------------------------
	int __fastcall GetUserID () const;
	String __fastcall GetUserName () const;
	String __fastcall GetLast () const;
	String __fastcall GetPassword () const;
	String __fastcall GetFirst () const;
//------------------------------------------------------------------------------
	void __fastcall SetUserID (const int value);
	void __fastcall SetUserName (const String &value);
	void __fastcall SetLast (const String &value);
	void __fastcall SetPassword (const String &value);
	void __fastcall SetFirst (const String &value);
};
//------------------------------------------------------------------------------
class TUsers : public TUserInfoBase {
public:
	__fastcall TUsers ();
};
//------------------------------------------------------------------------------
#endif
