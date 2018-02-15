//---------------------------------------------------------------------------

#ifndef ClassMemberInfoH
#define ClassMemberInfoH
//---------------------------------------------------------------------------
#include <inifiles.hpp>
//---------------------------------------------------------------------------
#include <vector>;
using namespace std;
//---------------------------------------------------------------------------
class TClassMemberInfo;
typedef vector <TClassMemberInfo> TMembersBase;
//---------------------------------------------------------------------------
class TClassMemberInfo {
public:
	__fastcall TClassMemberInfo ();
	__fastcall TClassMemberInfo (const TClassMemberInfo &other);

	TClassMemberInfo __fastcall operator= (const TClassMemberInfo &other);
	bool __fastcall operator== (const TClassMemberInfo &other) const;
	bool __fastcall operator!= (const TClassMemberInfo &other) const;
	void __fastcall Clear ();

	String __fastcall GetterName ();
	String __fastcall SetterName ();
	
	void __fastcall WritePropertyH (FILE *fileInclude);
	String __fastcall GetGetterH ();
	String __fastcall GetSetterH ();
	String __fastcall GetGetterSrc (const String &strClass);
	String __fastcall GetSetterSrc (const String &strClass);

	String __fastcall GetSqlAs () const;
	String __fastcall GetSqlUpdate () const;

	void __fastcall WriteToIni (TIniFile *ini, int n);
	bool __fastcall ReadFromIni (TIniFile *ini, int n);
//----- P r o p e r t i e s-----------------------------------------------
	__property int MemberID  = { read=GetMemberID, write=SetMemberID };
	__property String Type  = { read=GetType, write=SetType };
	__property String MemberName  = { read=GetMemberName, write=SetMemberName };
	__property String PropertyName  = { read=GetPropertyName, write=SetPropertyName };
	__property bool UseReference  = { read=GetUseReference, write=SetUseReference };
	__property String ClearValue  = { read=GetClearValue, write=SetClearValue };
	__property String SqlField  = { read=GetSqlField, write=SetSqlField };
	__property String MemberField  = { read=GetMemberField, write=SetMemberField };
	__property bool IsKey  = { read=GetIsKey, write=SetIsKey };
protected:
	void __fastcall AssignAll (const TClassMemberInfo &other);
private:
	int m_id;
	String m_strType;
	String m_strMemberName;
	String m_strPropertyName;
	String m_strClearValue;
	String m_strSqlField;
	String m_strMemberField;
	bool m_fUseRef;
	bool m_fIsKey;
	void __fastcall SetType(const String &value);
	String __fastcall GetType() const;
	void __fastcall SetMemberName(const String &value);
	String __fastcall GetMemberName() const;
	void __fastcall SetPropertyName(const String &value);
	String __fastcall GetPropertyName() const;
	void __fastcall SetUseReference(bool value);
	bool __fastcall GetUseReference() const;
	void __fastcall SetMemberID(int value);
	int __fastcall GetMemberID() const;
	void __fastcall SetClearValue(const String &value);
	String __fastcall GetClearValue() const;
	void __fastcall SetSqlField(const String &value);
	String __fastcall GetSqlField() const;
	void __fastcall SetMemberField(const String &value);
	String __fastcall GetMemberField() const;
	void __fastcall SetIsKey(bool value);
	bool __fastcall GetIsKey() const;
};
//---------------------------------------------------------------------------
class TMembers : public TMembersBase {
public:
	TMembers ();
	int __fastcall GetNextID () const;
	TMembers::iterator __fastcall GetIDMemberName ();
};
//---------------------------------------------------------------------------
#endif
