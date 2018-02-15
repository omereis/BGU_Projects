//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "ClassMemberInfo.h"
#include "CommonStrings.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

//---------------------------------------------------------------------------
__fastcall TClassMemberInfo::TClassMemberInfo ()
{
	Clear ();
}
//---------------------------------------------------------------------------
__fastcall TClassMemberInfo::TClassMemberInfo (const TClassMemberInfo &other)
{
	AssignAll (other);
}
//---------------------------------------------------------------------------
TClassMemberInfo __fastcall TClassMemberInfo::operator= (const TClassMemberInfo &other)
{
	AssignAll (other);
	return(*this);
}
//---------------------------------------------------------------------------
bool __fastcall TClassMemberInfo::operator== (const TClassMemberInfo &other) const
{
	if (MemberID     != other.MemberID)
		return (false);
	if (Type         != other.Type)
		return (false);
	if (MemberName   != other.MemberName)
		return (false);
	if (PropertyName != other.PropertyName)
		return (false);
	if (UseReference != other.UseReference)
		return (false);
	if (ClearValue   != other.ClearValue)
		return (false);
	if (SqlField     != other.SqlField)
		return (false);
	if (IsKey        != other.IsKey)
		return (false);
	if (MemberField  != other.MemberField)
		return (false);
	return (true);
}
//---------------------------------------------------------------------------
bool __fastcall TClassMemberInfo::operator!= (const TClassMemberInfo &other) const
{
	return (!(*this == other));
}
//---------------------------------------------------------------------------
void __fastcall TClassMemberInfo::Clear ()
{
	MemberID     = 0;
	Type         = "";
	MemberName   = "";
	PropertyName = "";
	UseReference = false;
	ClearValue   = "";
	SqlField     = "";
	IsKey        = false;
	MemberField  = "";
}
//---------------------------------------------------------------------------
void __fastcall TClassMemberInfo::AssignAll (const TClassMemberInfo &other)
{
	MemberID     = other.MemberID;
	Type         = other.Type;
	MemberName   = other.MemberName;
	PropertyName = other.PropertyName;
	UseReference = other.UseReference;
	ClearValue   = other.ClearValue;
	SqlField     = other.SqlField;
	IsKey        = other.IsKey;
	MemberField  = other.MemberField;
}
//---------------------------------------------------------------------------

void __fastcall TClassMemberInfo::SetType(const String &value)
{
	if(m_strType != value) {
		m_strType = value;
	}
}
//---------------------------------------------------------------------------
String __fastcall TClassMemberInfo::GetType() const
{
	return m_strType;
}
//---------------------------------------------------------------------------
void __fastcall TClassMemberInfo::SetMemberName(const String &value)
{
	if(m_strMemberName != value) {
		m_strMemberName = value;
	}
}
//---------------------------------------------------------------------------
String __fastcall TClassMemberInfo::GetMemberName() const
{
	return m_strMemberName;
}
//---------------------------------------------------------------------------
void __fastcall TClassMemberInfo::SetPropertyName(const String &value)
{
	if(m_strPropertyName != value) {
		m_strPropertyName = value;
	}
}
//---------------------------------------------------------------------------
String __fastcall TClassMemberInfo::GetPropertyName() const
{
	return m_strPropertyName;
}
//---------------------------------------------------------------------------
void __fastcall TClassMemberInfo::SetUseReference(bool value)
{
	if(m_fUseRef != value) {
		m_fUseRef = value;
	}
}

//---------------------------------------------------------------------------
bool __fastcall TClassMemberInfo::GetUseReference() const
{
	return m_fUseRef;
}
//---------------------------------------------------------------------------
void __fastcall TClassMemberInfo::SetMemberID(int value)
{
	if(m_id != value) {
		m_id = value;
	}
}
//---------------------------------------------------------------------------
int __fastcall TClassMemberInfo::GetMemberID() const
{
	return m_id;
}
static const char *s_szMemberNo     = "Member Number";
static const char *s_szType         = "Member Type";
static const char *s_szMemberName   = "Member Name";
static const char *s_szPropertyName = "Property Name";
static const char *s_szUseReference = "Use Reference";
static const char *s_szClearValue   = "Clear Value";
static const char *s_szMember       = "Member";
static const char *s_szSqlField     = "Database Field";
static const char *s_szMemberField  = "Member Field";
static const char *s_szIsKey  = "Is Database Key";
//---------------------------------------------------------------------------
void __fastcall TClassMemberInfo::WriteToIni (TIniFile *ini, int n)
{
	String strMember = String (s_szMember) + String (n);

	ini->WriteInteger (strMember, s_szMemberNo,   n);
	ini->WriteString (strMember, s_szType        , Type);
	ini->WriteString (strMember, s_szMemberName  , MemberName);
	ini->WriteString (strMember, s_szPropertyName, PropertyName);
	ini->WriteBool   (strMember, s_szUseReference, UseReference);
	ini->WriteString (strMember, s_szClearValue  , ClearValue);
	ini->WriteString (strMember, s_szSqlField    , SqlField);
	ini->WriteString (strMember, s_szMemberField , MemberField);
	ini->WriteBool   (strMember, s_szIsKey       , IsKey);
}
//---------------------------------------------------------------------------
bool __fastcall TClassMemberInfo::ReadFromIni (TIniFile *ini, int n)
{
	bool f;
	String strMember = String (s_szMember) + String (n);

	try {
		MemberID = ini->ReadInteger (strMember, s_szMemberNo,   1);
		Type = ini->ReadString (strMember, s_szType        , "");
		MemberName = ini->ReadString (strMember, s_szMemberName  , "");
		PropertyName = ini->ReadString (strMember, s_szPropertyName, "");
		UseReference = ini->ReadBool   (strMember, s_szUseReference, false);
		ClearValue   = ini->ReadString (strMember, s_szClearValue  ,  "");
		SqlField     = ini->ReadString (strMember, s_szSqlField    , "");
		MemberField  = ini->ReadString (strMember, s_szMemberField , "");
		IsKey        = ini->ReadBool   (strMember, s_szIsKey       , false);
		if (ClearValue.IsEmpty() && Type == "String")
			ClearValue = "\"\"";
		f = true;
	}
	catch (Exception &e) {
		f = false;
	}
	return (f);
}
//---------------------------------------------------------------------------
String __fastcall TClassMemberInfo::GetGetterH ()
{
	String str;

	str = Type + " __fastcall Get" + PropertyName + "(); const";
	return (str);
}
//---------------------------------------------------------------------------
String __fastcall TClassMemberInfo::GetSetterH ()
{
	String str;

	str = "void __fastcall Set" + PropertyName + "(" + Type + " ";
	if (UseReference)
		str += "&";
	str += ");";
	return (str);
}
//---------------------------------------------------------------------------
String __fastcall TClassMemberInfo::GetGetterSrc (const String &strClass)
{
	String str;

	str = Type + " __fastcall " + strClass + "::Get" + PropertyName + "() const\n{";
	str += "\treturn (" + PropertyName + ");\n}";
	return (str);
}
//---------------------------------------------------------------------------
String __fastcall TClassMemberInfo::GetSetterSrc (const String &strClass)
{
	String str;

	str = "void __fastcall " + strClass + "::Set" + PropertyName + "(" + Type + " ";
	if (UseReference)
		str += "&";
	str += ")\n{";
	return (str);
}
//---------------------------------------------------------------------------
void __fastcall TClassMemberInfo::SetClearValue(const String &value)
{
	if(m_strClearValue != value) {
		m_strClearValue = value;
	}
}
//---------------------------------------------------------------------------
String __fastcall TClassMemberInfo::GetClearValue() const
{
	return m_strClearValue;
}
//---------------------------------------------------------------------------
void __fastcall TClassMemberInfo::WritePropertyH (FILE *fileInclude)
{
}
//---------------------------------------------------------------------------
String __fastcall TClassMemberInfo::GetterName ()
{
	return ("Get" + PropertyName);
}
//---------------------------------------------------------------------------
String __fastcall TClassMemberInfo::SetterName ()
{
	return ("Set" + PropertyName);
}
//---------------------------------------------------------------------------
String __fastcall TClassMemberInfo::GetSqlField() const
{
	return m_strSqlField;
}
//---------------------------------------------------------------------------
void __fastcall TClassMemberInfo::SetMemberField(const String &value)
{
	if(m_strMemberField != value) {
		m_strMemberField = value;
	}
}
//---------------------------------------------------------------------------
String __fastcall TClassMemberInfo::GetMemberField() const
{
	return m_strMemberField;
}
//---------------------------------------------------------------------------
void __fastcall TClassMemberInfo::SetIsKey(bool value)
{
	if(m_fIsKey != value) {
		m_fIsKey = value;
	}
}
//---------------------------------------------------------------------------
bool __fastcall TClassMemberInfo::GetIsKey() const
{
	return m_fIsKey;
}
//---------------------------------------------------------------------------
String __fastcall TClassMemberInfo::GetSqlAs () const
{
	String strAs;

	if (Type == "int")
		strAs = "Integer";
	else if (Type == "String")
		strAs = "String";
	else if (Type == Bool)
		strAs = "Boolean";
	else if ((Type == Float) || (Type == DoubleStr))
		strAs = "Float";
	else
		strAs = "s";
	return ("As" + strAs);
}
//---------------------------------------------------------------------------
String __fastcall TClassMemberInfo::GetSqlUpdate () const
{
	String str;

	str = ModifyProc + "(" + MemberField + Comma + PropertyName + ")";
	return (str);
}
//---------------------------------------------------------------------------
// TMembers class
//---------------------------------------------------------------------------
TMembers::TMembers ()
	: TMembersBase ()
{
}
//---------------------------------------------------------------------------
int __fastcall TMembers::GetNextID () const
{
	return ((int) size() + 1);
}
//---------------------------------------------------------------------------
void __fastcall TClassMemberInfo::SetSqlField(const String &value)
{
	if(m_strSqlField != value) {
		m_strSqlField = value;
	}
}
//---------------------------------------------------------------------------
TMembers::iterator __fastcall TMembers::GetIDMemberName ()
{
	TMembers::iterator iMember, iFound = NULL;

	for (iMember=begin() ; (iMember != end()) && (iFound == NULL) ; iMember++)
		if (iMember->IsKey)
			iFound = iMember;
	return (iFound);
}
//---------------------------------------------------------------------------

