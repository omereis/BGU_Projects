//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "ClassInfo.h"
#include "Misc.h"
#include "ProjMisc.h"
#include "CommonStrings.h"
//---------------------------------------------------------------------------

#pragma package(smart_init)

//---------------------------------------------------------------------------
__fastcall TClassInfo::TClassInfo ()
{
	ClearClass ();
}
//---------------------------------------------------------------------------
__fastcall TClassInfo::TClassInfo (const TClassInfo &other)
{
	AssignAll (other);
}
//---------------------------------------------------------------------------
TClassInfo __fastcall TClassInfo::operator= (const TClassInfo &other)
{
	AssignAll (other);
	return(*this);
}
//---------------------------------------------------------------------------
bool __fastcall TClassInfo::operator== (const TClassInfo &other) const
{
	if (Name        != other.Name)
		return (false);
	if (Members     != other.Members)
		return (false);
	if (VectorName  != other.VectorName)
		return (false);
	if (SourceFile  != other.SourceFile)
		return (false);
	if (Include     != other.Include)
		return (false);
	if (FileDir     != other.FileDir)
		return (false);
	if (IfDef       != other.IfDef)
		return (false);
	if (DefCtor     != other.DefCtor)
		return (false);
	if (CopyCtor    != other.CopyCtor)
		return (false);
	if (Dtor        != other.Dtor)
		return (false);
	if (DoClear     != other.DoClear)
		return (false);
	if (DoAssignAll != other.DoAssignAll)
		return (false);
	if (Eq          != other.Eq)
		return (false);
	if (Uneq        != other.Uneq)
		return (false);
	if (Assign      != other.Assign)
		return (false);
	if (Vector      != other.Vector)
		return (false);
	if (Database    != other.Database)
		return (false);
	if (SqlTable    != other.SqlTable)
		return (false);
	if (MemberTable != other.MemberTable)
		return (false);
	return (true);
}
//---------------------------------------------------------------------------
bool __fastcall TClassInfo::operator!= (const TClassInfo &other) const
{
	return (!(*this == other));
}
//---------------------------------------------------------------------------
void __fastcall TClassInfo::ClearClass ()
{
	Name        = "";
	m_Members.clear();
	VectorName  = "";
	SourceFile  = "";
	Include     = "";
	FileDir     = "";
	IfDef       = "";
	SqlTable    = "";
	MemberTable = "";
	DefCtor     = true;
	CopyCtor    = true;
	Dtor        = false;
	DoClear     = true;
	DoAssignAll = true;
	Eq          = true;
	Uneq        = true;
	Assign      = true;
	Vector      = true;
	Database    = true;
}
//---------------------------------------------------------------------------
void __fastcall TClassInfo::AssignAll (const TClassInfo &other)
{
	Name        = other.Name;
	Members     = other.Members;
	VectorName  = other.VectorName;
	SourceFile  = other.SourceFile;
	Include     = other.Include;
	FileDir     = other.FileDir;
	IfDef       = other.IfDef;
	SqlTable    = other.SqlTable;
	MemberTable = other.MemberTable;
	DefCtor     = other.DefCtor;
	CopyCtor    = other.CopyCtor;
	Dtor        = other.Dtor;
	DoClear     = other.DoClear;
	DoAssignAll = other.DoAssignAll;
	Eq          = other.Eq;
	Uneq        = other.Uneq;
	Assign      = other.Assign;
	Vector      = other.Vector;
	Database    = other.Database;
}
//---------------------------------------------------------------------------
void __fastcall TClassInfo::SetName(const String &value)
{
	if(m_strName != value) {
		m_strName = value;
		IfDef = "Class" + m_strName + "H";
	}
}
//---------------------------------------------------------------------------
String __fastcall TClassInfo::GetName() const
{
	return m_strName;
}
//---------------------------------------------------------------------------
void __fastcall TClassInfo::SetMembers(const TMembers &value)
{
	if(m_Members != value) {
		m_Members = value;
	}
}
//---------------------------------------------------------------------------
TMembers __fastcall TClassInfo::GetMembers() const
{
	return m_Members;
}
//---------------------------------------------------------------------------
void __fastcall TClassInfo::SetVectorName(const String &value)
{
	if(m_strVectorName != value) {
		m_strVectorName = value;
	}
}
//---------------------------------------------------------------------------
String __fastcall TClassInfo::GetVectorName() const
{
	return m_strVectorName;
}
//---------------------------------------------------------------------------
void __fastcall TClassInfo::SetSourceFile(const String &value)
{
	if(m_strSrc != value) {
		m_strSrc = value;
	}
}
//---------------------------------------------------------------------------
String __fastcall TClassInfo::GetSourceFile() const
{
	return m_strSrc;
}
//---------------------------------------------------------------------------
void __fastcall TClassInfo::SetInclude(const String &value)
{
	if(m_strInclude != value) {
		m_strInclude = value;
	}
}
//---------------------------------------------------------------------------
String __fastcall TClassInfo::GetInclude() const
{
	return m_strInclude;
}
//---------------------------------------------------------------------------
void __fastcall TClassInfo::SetFileDir(const String &value)
{
	if(m_strFileDir != value) {
		m_strFileDir = value;
	}
}
//---------------------------------------------------------------------------
String __fastcall TClassInfo::GetFileDir() const
{
	return m_strFileDir;
}
//---------------------------------------------------------------------------
void __fastcall TClassInfo::SetIfDef(const String &value)
{
	m_strIfDef = value;
}
//---------------------------------------------------------------------------
String __fastcall TClassInfo::GetIfDef() const
{
	return (m_strIfDef);
}
//---------------------------------------------------------------------------
void __fastcall TClassInfo::Generate ()
{
	Generate (SourceFile);
}
//---------------------------------------------------------------------------
void __fastcall TClassInfo::Generate (const String &strSrcPath)
{
	TStringList *lstrInclude = new TStringList, *lstrSource = new TStringList;
	SourceFile  = strSrcPath;
	FileDir  = ExtractFileDir (strSrcPath);
	Include = HeaderFromSrc (SourceFile);
	GenerateInclude (lstrInclude);
	GenerateSource (lstrSource);
	lstrInclude->SaveToFile (Include);
	lstrSource->SaveToFile (SourceFile);
	delete lstrInclude;
	delete lstrSource;
}
//---------------------------------------------------------------------------
String __fastcall TClassInfo::GetDefaultCtorH () const
{
	String str;

	str = FastCall + Name + "::" + Name + "();";
	return (str);
}
//---------------------------------------------------------------------------
String __fastcall TClassInfo::GetDefaultCtorSrc () const
{
	String str;

	str = FastCall + Name + "::" + Name + "()\n{\n\tClear();\n}\n";
	return (str);
}
//---------------------------------------------------------------------------
String __fastcall TClassInfo::GetClassHeader (EMethodClass emc, const String &type, const String &proc_name, const String &params, bool fSource, bool fConst)
{
	String strName;

	if (emc == EMC_Class)
		strName = Name;
	else if (emc == EMC_Vector)
		strName = VectorName;
	return (GetMethodHeader (strName, type, proc_name, params, fSource, fConst));
}
//---------------------------------------------------------------------------
String __fastcall TClassInfo::GetCtorH (bool fSource)
{
	String str;

	str = GetClassHeader (EMC_Class, "", Name, "", fSource, false);
	return (str);;
}
//---------------------------------------------------------------------------
String __fastcall TClassInfo::GetOtherParam ()
{
	return ("const " + Name + " &" + Other);
}
//---------------------------------------------------------------------------
String __fastcall TClassInfo::GetCopyCtorH (bool fSource)
{
	String str;

	str = GetClassHeader (EMC_Class, "", Name, GetOtherParam (), fSource, false);
	return (str);;
}
//---------------------------------------------------------------------------
String __fastcall TClassInfo::GetClearH (bool fSource)
{
	String str;

	str = GetClassHeader (EMC_Class, Void, "Clear", "", fSource, false);
	return (str);
}
//---------------------------------------------------------------------------
String __fastcall TClassInfo::GetAssignH (bool fSource)
{
	String str;

	str = GetClassHeader (EMC_Class, Name, "operator=", GetOtherParam (), fSource, false);
	return (str);
}
//---------------------------------------------------------------------------
String __fastcall TClassInfo::GetEqH (bool fSource)
{
	String str;

	str = GetClassHeader (EMC_Class, Bool, "operator==", GetOtherParam (), fSource, true);
	return (str);
}
//---------------------------------------------------------------------------
String __fastcall TClassInfo::GetInEqH (bool fSource)
{
	String str;

	str = GetClassHeader (EMC_Class, Bool, "operator!=", GetOtherParam (), fSource, true);
	return (str);
}
//---------------------------------------------------------------------------
String __fastcall TClassInfo::FormatProperty (TClassMemberInfo &member)
{
	String str;

	str = "\t" + Property + Space + member.Type + Space + member.PropertyName;
	str += " = {read=" + member.GetterName() + ", write=" + member.SetterName () + "};";
	return (str);
}
//---------------------------------------------------------------------------
void __fastcall TClassInfo::WriteProperties (TStringList *lstr)
{
	TMembers::iterator iMember;
	String str;

	for (iMember=m_Members.begin() ; iMember != m_Members.end() ; iMember++) {
		str = FormatProperty (*iMember);
		lstr->Add (str);
	}
}
//---------------------------------------------------------------------------
String __fastcall TClassInfo::GetAssignAllH (bool fSource)
{
	String str;

	str = GetClassHeader (EMC_Class, Void, "AssignAll", GetOtherParam (), fSource, false);
	return (str);
}
//---------------------------------------------------------------------------
void __fastcall TClassInfo::WriteMembersH (TStringList *lstr)
{
	String str, strParam;
	TMembers::iterator iMember;

	for (iMember=m_Members.begin() ; iMember < m_Members.end() ; iMember++) {
		str = "\t" + iMember->Type + Space + iMember->MemberName + ";";
		lstr->Add (str);
	}
	lstr->Add (GetSepLine ());
	for (iMember=m_Members.begin() ; iMember < m_Members.end() ; iMember++) {
		str = GetClassHeader (EMC_Class, iMember->Type, iMember->GetterName(), "", false, true);
		lstr->Add (str);
	}
	lstr->Add (GetSepLine ());
	for (iMember=m_Members.begin() ; iMember < m_Members.end() ; iMember++) {
		strParam = GetMemberSetterParam (*iMember);
		str = GetClassHeader (EMC_Class, Void, iMember->SetterName(), strParam, false, false);
		lstr->Add (str);
	}
}
//---------------------------------------------------------------------------
void __fastcall TClassInfo::WriteCtorSrc (TStringList *lstrSrc)
{
	String strHeader, strBody;

	strHeader = GetClassHeader (EMC_Class, "", Name, "", true, false);
	strBody = "Clear();";
	AddProc (lstrSrc, strHeader, strBody);
}
//---------------------------------------------------------------------------
void __fastcall TClassInfo::WriteCopyCtorSrc (TStringList *lstrSrc)
{
	String strHeader, strBody;

	if (m_strOtherParam.IsEmpty())
		m_strOtherParam = MakeOtherParam ();
	strHeader = GetClassHeader (EMC_Class, "", Name, m_strOtherParam, true, false);
	strBody = "AssignAll (" + Other + ");";
	AddProc (lstrSrc, strHeader, strBody);
}
//---------------------------------------------------------------------------
String __fastcall TClassInfo::MakeOtherParam ()
{
	String str;

	str = Const + Space + Name + " &" + Other;
	return (str);
}
//---------------------------------------------------------------------------
void __fastcall TClassInfo::WriteAssignSrc (TStringList *lstrSrc)
{
	String str, strHeader;
	TStringList *lstrBody = new TStringList;
	TMembers::iterator iMember;
	int n;

	if (m_strOtherParam.IsEmpty())
		m_strOtherParam = MakeOtherParam ();
	strHeader = GetClassHeader (EMC_Class, Name, "operator=", m_strOtherParam, true, false);
	lstrBody->Add ("AssignAll (" + Other + ");");
	lstrBody->Add ("return (*this);");
	AddProc (lstrSrc, strHeader, lstrBody);
	delete lstrBody;
}
//---------------------------------------------------------------------------
void __fastcall TClassInfo::WriteAssignAllSrc (TStringList *lstrSrc)
{
	String str, strHeader;
	TStringList *lstrBody = new TStringList;
	TMembers::iterator iMember;
	int n;

	if (m_strOtherParam.IsEmpty())
		m_strOtherParam = MakeOtherParam ();
//	strHeader = GetHeader (Name, "AssignAll", m_strOtherParam, true, false);
	strHeader = GetAssignAllH (true);
	for (iMember=m_Members.begin() ; iMember != m_Members.end() ; iMember++)
		lstrBody->Add (iMember->PropertyName);
	AlignList (lstrBody);
	for (iMember=m_Members.begin(), n=0 ; iMember != m_Members.end() ; iMember++, n++) {
		str = lstrBody->Strings[n];
		str += String (EQ + Other + ".") + iMember->PropertyName + ";";
		lstrBody->Strings[n] = str;
	}
	AddProc (lstrSrc, strHeader, lstrBody);
	delete lstrBody;
}
//---------------------------------------------------------------------------
void __fastcall TClassInfo::WriteClearSrc (TStringList *lstrSrc)
{
	String str, strHeader;
	TStringList *lstrBody = new TStringList;
	TMembers::iterator iMember;
	int n;

	strHeader = GetClassHeader (EMC_Class, Void, "Clear", "", true, false);
	for (iMember=m_Members.begin() ; iMember != m_Members.end() ; iMember++) {
		lstrBody->Add (iMember->PropertyName);
	}
	AlignList (lstrBody);
	for (iMember=m_Members.begin(), n=0 ; iMember != m_Members.end() ; iMember++, n++) {
		str = lstrBody->Strings[n];
		str += " = " + iMember->ClearValue + ";";
		lstrBody->Strings[n] = str;
	}
	AddProc (lstrSrc, strHeader, lstrBody);
	delete lstrBody;
}
//---------------------------------------------------------------------------
void __fastcall TClassInfo::WriteOperatorEq (TStringList *lstrSrc)
{
	String str, strHeader;
	TStringList *lstrBody = new TStringList;
	TMembers::iterator iMember;
	int n;

	if (m_strOtherParam.IsEmpty())
		m_strOtherParam = MakeOtherParam ();
	strHeader = GetEqH (true);
	for (iMember=m_Members.begin() ; iMember != m_Members.end() ; iMember++)
		lstrBody->Add ("if (" + iMember->PropertyName);
	AlignList (lstrBody);
	for (iMember=m_Members.begin(), n=0 ; iMember != m_Members.end() ; iMember++, n++) {
		str = lstrBody->Strings[n];
		str += String (" != other.") + iMember->PropertyName + ")\n\t\treturn (false);";
		lstrBody->Strings[n] = str;
	}
	lstrBody->Add ("return (true);");
	AddProc (lstrSrc, strHeader, lstrBody);
	delete lstrBody;
}
//---------------------------------------------------------------------------
void __fastcall TClassInfo::WritePropertiesSrc (TStringList *lstrSrc)
{
	TMembers::iterator iMember;

	for (iMember=m_Members.begin() ; iMember != m_Members.end() ; iMember++) {
		WriteSetter (lstrSrc, *iMember);
		WriteGetter (lstrSrc, *iMember);
	}
}
//---------------------------------------------------------------------------
String __fastcall TClassInfo::GetMemberSetterParam (TClassMemberInfo &member)
{
	String strParam;

	strParam = Const + Space + member.Type + Space;
	if (member.UseReference)
		strParam += "&";
	strParam += Value;
	return (strParam);
}
//---------------------------------------------------------------------------
void __fastcall TClassInfo::WriteSetter (TStringList *lstrSrc, TClassMemberInfo &member)
{
	String strBody, strHeader, strParam;

//	strParam = Const + Space + member.Type + Space;
//	if (member.UseReference)
//		strParam += "&";
//	strParam += Value;
	strParam = GetMemberSetterParam (member);
	strHeader = GetClassHeader (EMC_Class, Void, member.SetterName(), strParam, true, false);
	strBody = member.MemberName + " = value;";
	AddProc (lstrSrc, strHeader, strBody);
}
//---------------------------------------------------------------------------
void __fastcall TClassInfo::WriteGetter (TStringList *lstrSrc, TClassMemberInfo &member)
{
	String strBody, strHeader;

	strHeader = member.Type + " " + FastCall + " " + Name + "::" + member.GetterName() + "() const\n";
	strHeader = GetClassHeader (EMC_Class, member.Type, member.GetterName(), "", true, true);
	strBody = "return (" + member.MemberName + ");";
	AddProc (lstrSrc, strHeader, strBody);
}
//---------------------------------------------------------------------------
static const char *s_szSecMain = "Main Parameters";
static const char *s_szIdentClass = "Class Name";
static const char *s_szVecClass = "Vector Name";
static const char *s_szClassFile = "Class File";
static const char *s_szDefCtor = "Default Constructor";
static const char *s_szDtor = "Destructor";
static const char *s_szCopyCtor = "Copy Constructor";
static const char *s_szClear = "Clear Method";
static const char *s_szAssignAll = "Assign All Method";
static const char *s_szEq = "equation (=) operator";
static const char *s_szUnEq = "inequation (!=) operator";
static const char *s_szAssign = "Assignment (=) Operator";
static const char *s_szVector = "Create Vector";
static const char *s_szDB = "Database Support";
static const char *s_szMembersCount = "Members Count";
static const char *s_szSqlTable = "Database Table Name";
static const char *s_szMemberTable = "Member Table";
//---------------------------------------------------------------------------
bool __fastcall TClassInfo::SaveToFile (const String &strFile)
{
	TIniFile *ini = NULL;
	bool f;

	try {
		try {
			ini = new TIniFile (strFile);
			f = SaveToFile (ini);
		}
		catch (...) {
			f = false;
		}
	}
	__finally {
		if (ini != NULL)
			delete ini;
	}
	return (f);
}
//---------------------------------------------------------------------------
bool __fastcall TClassInfo::SaveToFile (TIniFile *ini)
{
	bool f = true;
	int n;
	TMembers::iterator iMember;

	try {
		ini->WriteString (s_szSecMain, s_szIdentClass, Name);
		ini->WriteString (s_szSecMain, s_szVecClass, VectorName);
		ini->WriteString (s_szSecMain, s_szClassFile, SourceFile);
		ini->WriteString (s_szSecMain, s_szSqlTable, SqlTable);
		ini->WriteString (s_szSecMain, s_szMemberTable, MemberTable);
		ini->WriteBool (s_szSecMain, s_szDefCtor, DefCtor);
		ini->WriteBool (s_szSecMain, s_szDtor, Dtor);
		ini->WriteBool (s_szSecMain, s_szCopyCtor, CopyCtor);
		ini->WriteBool (s_szSecMain, s_szClear, DoClear);
		ini->ReadBool (s_szSecMain, s_szAssignAll, DoAssignAll);
		ini->WriteBool (s_szSecMain, s_szAssignAll, DoAssignAll);
		ini->WriteBool (s_szSecMain, s_szEq, Eq);
		ini->WriteBool (s_szSecMain, s_szUnEq, Uneq);
		ini->WriteBool (s_szSecMain, s_szAssign, Assign);
		ini->WriteBool (s_szSecMain, s_szVector, Vector);
		ini->WriteBool (s_szSecMain, s_szDB, Database);
		ini->WriteInteger (s_szSecMain, s_szMembersCount, (int) m_Members.size());
		for (iMember=m_Members.begin(), n=1 ; iMember != m_Members.end() ; iMember++) {
			iMember->WriteToIni (ini, n++);
		}

	}
	catch (...) {
		f = false;
	}
	return (f);
}
//---------------------------------------------------------------------------
bool __fastcall TClassInfo::LoadFromFile (const String &strFile)
{
	TIniFile *ini = NULL;
	bool f;

	try {
		try {
			ini = new TIniFile (strFile);
			f = LoadFromFile (ini);
		}
		catch (...) {
			f = false;
		}
	}
	__finally {
		if (ini != NULL)
			delete ini;
	}
	return (f);
}
//---------------------------------------------------------------------------
bool __fastcall TClassInfo::LoadFromFile (TIniFile *ini)
{
	bool f = true;
	int n, nMembers;
	TClassMemberInfo member;

	try {
		Name        = ini->ReadString (s_szSecMain, s_szIdentClass, "");
		VectorName  = ini->ReadString (s_szSecMain, s_szVecClass, "");
		SourceFile  = ini->ReadString (s_szSecMain, s_szClassFile, "");
		SqlTable    = ini->ReadString (s_szSecMain, s_szSqlTable, "");
		MemberTable = ini->ReadString (s_szSecMain, s_szMemberTable, "");
		DefCtor     = ini->ReadBool (s_szSecMain, s_szDefCtor, true);
		Dtor        = ini->ReadBool (s_szSecMain, s_szDtor, false);
		CopyCtor    = ini->ReadBool (s_szSecMain, s_szCopyCtor, true);
		DoClear     = ini->ReadBool (s_szSecMain, s_szClear, true);
		DoAssignAll = ini->ReadBool (s_szSecMain, s_szAssignAll, true);
		Eq          = ini->ReadBool (s_szSecMain, s_szEq, true);
		Uneq        = ini->ReadBool (s_szSecMain, s_szUnEq, true);
		Assign      = ini->ReadBool (s_szSecMain, s_szAssign, true);
		Vector      = ini->ReadBool (s_szSecMain, s_szVector, true);
		Database    = ini->ReadBool (s_szSecMain, s_szDB, true);
		nMembers    = ini->ReadInteger (s_szSecMain, s_szMembersCount, 0);
		for (n=0 ; n < nMembers ; n++) 
			if (member.ReadFromIni (ini, n + 1))
				m_Members.push_back (member);
	}
	catch (...) {
		f = false;
	}
	return (f);
}
//---------------------------------------------------------------------------
void __fastcall TClassInfo::SetDefCtor(bool value)
{
	if(m_fDefCtor != value) {
		m_fDefCtor = value;
	}
}
//---------------------------------------------------------------------------
bool __fastcall TClassInfo::GetDefCtor() const
{
	return m_fDefCtor;
}
//---------------------------------------------------------------------------
void __fastcall TClassInfo::SetCopyCtor(bool value)
{
	if(m_fCopyCtor != value) {
		m_fCopyCtor = value;
	}
}
//---------------------------------------------------------------------------
bool __fastcall TClassInfo::GetCopyCtor() const
{
	return m_fCopyCtor;
}
//---------------------------------------------------------------------------
void __fastcall TClassInfo::SetDtor(bool value)
{
	if(m_fDtor != value) {
		m_fDtor = value;
	}
}
//---------------------------------------------------------------------------
bool __fastcall TClassInfo::GetDtor() const
{
	return m_fDtor;
}
//---------------------------------------------------------------------------
void __fastcall TClassInfo::SetDoClear(bool value)
{
	if(m_fClear != value) {
		m_fClear = value;
	}
}
//---------------------------------------------------------------------------
bool __fastcall TClassInfo::GetDoClear() const
{
	return m_fClear;
}
//---------------------------------------------------------------------------
void __fastcall TClassInfo::SetDoAssignAll(bool value)
{
	if(m_fAssignAll != value) {
		m_fAssignAll = value;
	}
}
//---------------------------------------------------------------------------
bool __fastcall TClassInfo::GetDoAssignAll() const
{
	return m_fAssignAll;
}
//---------------------------------------------------------------------------
void __fastcall TClassInfo::SetEq(bool value)
{
	if(m_fEq != value) {
		m_fEq = value;
	}
}
//---------------------------------------------------------------------------
bool __fastcall TClassInfo::GetEq() const
{
	return m_fEq;
}
//---------------------------------------------------------------------------
void __fastcall TClassInfo::SetUneq(bool value)
{
	if(m_fUneq != value) {
		m_fUneq = value;
	}
}
//---------------------------------------------------------------------------
bool __fastcall TClassInfo::GetUneq() const
{
	return m_fUneq;
}
//---------------------------------------------------------------------------
void __fastcall TClassInfo::SetAssign(bool value)
{
	if(m_fAssign != value) {
		m_fAssign = value;
	}
}
//---------------------------------------------------------------------------
bool __fastcall TClassInfo::GetAssign() const
{
	return m_fAssign;
}
//---------------------------------------------------------------------------
void __fastcall TClassInfo::SetVector(bool value)
{
	if(m_fVector != value) {
		m_fVector = value;
	}
}
//---------------------------------------------------------------------------
bool __fastcall TClassInfo::GetVector() const
{
	return m_fVector;
}
//---------------------------------------------------------------------------
void __fastcall TClassInfo::SetDatabase(bool value)
{
	if(m_fDatabase != value) {
		m_fDatabase = value;
	}
}
//---------------------------------------------------------------------------
bool __fastcall TClassInfo::GetDatabase() const
{
	return m_fDatabase;
}
//---------------------------------------------------------------------------
void __fastcall TClassInfo::GenerateInclude (TStringList *lstr)
{
	WriteHeaderStart (lstr);
	lstr->Add ("class " + Name + " {");
	lstr->Add ("public:");

	GenerateBasicProcsHeaders (lstr);
	lstr->Add ("//----- P r o p e r t i e s -----------------------------------------------");
	WriteProperties (lstr);
	if (Database)
		WriteStaticVars (lstr);
	lstr->Add ("protected:");
	lstr->Add (GetAssignAllH (false));
	lstr->Add ("private:");
	WriteMembersH (lstr);
	lstr->Add ("};");
	if (Vector)
		GenerateVectorHeader (lstr);
	lstr->Add (GetSepLine ());
	lstr->Add ("#endif");
}
//---------------------------------------------------------------------------
void __fastcall TClassInfo::WriteStaticVars (TStringList *lstr)
{
	TMembers::iterator iMember;

	lstr->Add ("// ---------- S t a t i c ----------");
	lstr->Add (Tab + Static + Space + StrName + Space + StrTable + SC);
	for (iMember=m_Members.begin() ; iMember != m_Members.end() ; iMember++) {
		lstr->Add (Tab + Static + Space + StrName + Space + iMember->MemberField + SC);
	}
}
//---------------------------------------------------------------------------
void __fastcall TClassInfo::GenerateBasicProcsHeaders (TStringList *lstr)
{
	lstr->Add (GetCtorH(false));
	lstr->Add (GetCopyCtorH (false));
	lstr->Add (GetAssignH (false));
	lstr->Add (GetInEqH (false));
	lstr->Add (GetEqH (false));
	lstr->Add (GetClearH (false));
	if (Database)
		WriteDBHeaders (lstr);
}
//---------------------------------------------------------------------------
void __fastcall TClassInfo::WriteHeaderStart (TStringList *lstr)
{
	String strDefine;

	lstr->Add (GetSepLine ());
	strDefine = GetIncludeDef ();
	lstr->Add (IfNotDef + Tab + strDefine);
	lstr->Add (Define + Tab + strDefine);
	lstr->Add (GetSepLine ());
	if (Database) {
		lstr->Add (DirInclude + Space + "<ADODB.hpp>");
		lstr->Add (DirInclude + Space + DQuote + "DBMisc.h" + DQuote);
	}
	if (Vector) {
		lstr->Add (DirInclude + " <vector>");
		lstr->Add ("using namespace std;");
		lstr->Add (GetSepLine ());
		lstr->Add ("class " + Name + ";");
		lstr->Add ("typedef vector<" + Name + "> " + Name + "Base;");
		lstr->Add (GetSepLine ());
	}
}
//---------------------------------------------------------------------------
void __fastcall TClassInfo::GenerateSource (TStringList *lstr)
{
	lstr->Add (GetSepLine ());
	lstr->Add (DirInclude + "<vcl.h>");
	lstr->Add ("#pragma hdrstop");
	lstr->Add (DirInclude + " \"" + ExtractFileName (Include) + "\"");//\"%s\"\n\n", ExtractFileName (Include));
	lstr->Add (GetSepLine ());
	lstr->Add ("#pragma package(smart_init)\n");
	lstr->Add (GetSepLine ());
	if (Database)
		WriteConstVars (lstr);
	WriteBasicMethods (lstr);
	if (Database)
		WriteItemDBMethods (lstr);
}
//---------------------------------------------------------------------------
void __fastcall TClassInfo::WriteConstVars (TStringList *lstr)
{
	TMembers::iterator iMember;
	TStringList *lstrMembers = new TStringList;
	int n;
	String str, strPre;

	strPre = StrName + Space + Name + "::";
	lstrMembers->Add (strPre + StrTable);
	for (iMember=m_Members.begin() ; iMember != m_Members.end() ; iMember++)
		lstrMembers->Add (StrName + Space + Name + "::" + iMember->MemberField);
	AlignList (lstrMembers);
	str = lstrMembers->Strings[0];
	str += "(" + DQuote + SqlTable + DQuote + ")" + SC;
	lstr->Add (str);
	for (iMember=m_Members.begin(), n=1 ; iMember != m_Members.end() ; iMember++, n++) {
		lstrMembers->Strings[n] = lstrMembers->Strings[n] + "(" + DQuote + iMember->SqlField + DQuote + ")" + SC;
		lstr->Add (lstrMembers->Strings[n]);
	}
	delete lstrMembers;
	lstr->Add (GetSepLine());
}
//---------------------------------------------------------------------------
void __fastcall TClassInfo::WriteBasicMethods (TStringList *lstr)
{
	WriteCtorSrc (lstr);
	WriteCopyCtorSrc (lstr);
	WriteAssignSrc (lstr);
	WriteAssignAllSrc (lstr);
	WriteClearSrc (lstr);
	WriteOperatorEq (lstr);
	WritePropertiesSrc (lstr);
}
//---------------------------------------------------------------------------
String __fastcall TClassInfo::GetIncludeDef ()
{
	String strDefine, strFile;
	int nDot;

	strFile = ExtractFileName (SourceFile);
	nDot = strFile.Pos (".");
	if (nDot > 0)
		strDefine = strFile.SubString (1, nDot - 1);
	strDefine += "H";
	return (strDefine);
}
//---------------------------------------------------------------------------
void __fastcall TClassInfo::SetSqlTable(const String &value)
{
	if(m_strSqlTable != value) {
		m_strSqlTable = value;
	}
}
//---------------------------------------------------------------------------
String __fastcall TClassInfo::GetSqlTable() const
{
	return m_strSqlTable;
}
//---------------------------------------------------------------------------
void __fastcall TClassInfo::SetMemberTable(const String &value)
{
	if(m_strMemberTable != value) {
		m_strMemberTable = value;
	}
}
//---------------------------------------------------------------------------
String __fastcall TClassInfo::GetMemberTable() const
{
	return m_strMemberTable;
}
//---------------------------------------------------------------------------
String __fastcall GetDBParams (bool fQuery, bool fStrErr)
{
	String str;

	if (fQuery)
		str = AdoQuery + Query;
	else
		str = AdoDB + DBVar;
	if (fStrErr)
		str += ", " + StrName + " &" + StrErrName;
	return (str);
}
//---------------------------------------------------------------------------
String __fastcall TClassInfo::GetDBHeader (const String &strProcName, bool fSource, bool fQuery, bool fStrErr)
{
	String str;

	str = GetClassHeader (EMC_Class, Bool, strProcName, GetDBParams (fQuery, fStrErr), fSource, false);
	return (str);
}
//---------------------------------------------------------------------------
String __fastcall TClassInfo::GetLoadItemHeader (bool fVector, bool fQuery, bool fSoure)
{
	String str;
	bool fStrErr = fVector;

	str = GetClassHeader (EMC_Class, Bool, LoadFromDBStr, GetDBParams (fQuery, fStrErr), fSoure, false);
	return (str);
}
//---------------------------------------------------------------------------
String __fastcall TClassInfo::GetLoadItemHeader ()
{
	String str;

	str = GetClassHeader (EMC_Class, Bool, LoadFromDBStr, GetDBParams (true, false), false, false);
	return (str);
}
//---------------------------------------------------------------------------
void __fastcall TClassInfo::WriteDBHeaders (TStringList *lstrSrc)
{

	lstrSrc->Add ("// ---------- Database Support ----------");
	lstrSrc->Add (GetLoadItemHeader ());
	lstrSrc->Add (GetDPMethodHeader (InsertMethod, false, false, true));
	lstrSrc->Add (GetDPMethodHeader (InsertMethod, false, true, true));

	lstrSrc->Add (GetDPMethodHeader (UpdateMethod, false, false, true));
	lstrSrc->Add (GetDPMethodHeader (UpdateMethod, false, true, true));

	lstrSrc->Add (GetDPMethodHeader (DeleteMethod, false, false, true));
	lstrSrc->Add (GetDPMethodHeader (DeleteMethod, false, true, true));
}
//---------------------------------------------------------------------------
String __fastcall TClassInfo::GetDPMethodHeader (const String &strMethod, bool fSource, bool fQuery, bool fStrErr)
{
//	bool fStrErr = !fQuery;
	String str;

	str = GetDBHeader (strMethod, fSource, fQuery, fStrErr);
	return (str);
}
//---------------------------------------------------------------------------
void __fastcall TClassInfo::GenerateVectorHeader (TStringList *lstrSrc)
{
	lstrSrc->Add (GetSepLine ());
	lstrSrc->Add ("class " + VectorName + " : public " + Name + "Base" + " {");
	lstrSrc->Add ("public:");
	lstrSrc->Add (GetClassHeader (EMC_Vector, "", VectorName, "", false, false));
	if (Database)
		GenerateVectorDBHeader (lstrSrc);
	lstrSrc->Add ("};");
}
//---------------------------------------------------------------------------
void __fastcall TClassInfo::GenerateVectorDBHeader (TStringList *lstrSrc)
{
	lstrSrc->Add ("// Vector Database Support");
	lstrSrc->Add (GetLoadItemHeader (true, true, false));
	lstrSrc->Add (GetLoadItemHeader (true, false, false));
}
//---------------------------------------------------------------------------
void __fastcall TClassInfo::WriteItemDBMethods (TStringList *lstrSrc)
{
	WriteLoadItemSrc (lstrSrc);
	WriteInsertItem (lstrSrc);
	WriteInsertItemToDB (lstrSrc);
	WriteUpdateItem (lstrSrc);
	WriteUpdateItemToDB (lstrSrc);
//		lstrSrc->Add (GetDPMethodHeader (InsertMethod, false, false));

}
//---------------------------------------------------------------------------
void __fastcall TClassInfo::WriteLoadItemSrc (TStringList *lstrSrc)
{
	TMembers::iterator iMember;
	String strHeader, str;
	TStringList *lstrBody = new TStringList, *lstrMembers = new TStringList;
	int n;

	strHeader = GetLoadItemHeader (false, true, true);
	lstrBody->Add (Bool + Space + F_Var + EQ + TrueStr + SC);
//	lstrBody->Add (AdoQuery + Space + Query + EQ + InitQueryCall + SC);
	lstrBody->Add ("");
//	lstrBody->Add (F_Var + EQ + LoadFromDBStr + " (" + Query + ", " + StrErrName + ");");
	lstrBody->Add (TryStart);
	for (iMember=m_Members.begin() ; iMember != m_Members.end() ; iMember++)
		lstrMembers->Add (iMember->PropertyName + EQ);
	AlignList (lstrMembers);
	for (iMember=m_Members.begin(), n=0 ; iMember != m_Members.end() ; iMember++, n++) {
		str = lstrMembers->Strings[n] + Query + "->Fields->FieldByName (" + iMember->MemberField + ")->" + iMember->GetSqlAs () + SC;
		lstrMembers->Strings[n] = str;
	}
	for (n=0 ; n < lstrMembers->Count ; n++)
		lstrBody->Add (Tab + lstrMembers->Strings[n]);
	lstrBody->Add ("}");
	lstrBody->Add (CatchStart);
	lstrBody->Add (Tab + F_Var + EQ + FalseStr + SC);
	lstrBody->Add ("}");
	lstrBody->Add (ReturnF + SC);
	AddProc (lstrSrc, strHeader, lstrBody);
	delete lstrBody;
	delete lstrMembers;
}
//---------------------------------------------------------------------------
void __fastcall TClassInfo::WriteInsertItem (TStringList *lstrSrc)
{
	String strHeader;
	TStringList *lstrBody = new TStringList;
	TMembers::iterator iKeyMember;

	iKeyMember = m_Members.GetIDMemberName ();
	if (iKeyMember != NULL) {
		lstrBody->Add (IntStr + Space + IdName + SC);
		lstrBody->Add (Bool + Space + F_Var + SC);
		lstrBody->Add (StrName + Space + SqlStr + SC);
		lstrBody->Add ("");
		lstrBody->Add (F_Var + EQ + "GetFieldMax (" + Query + Comma + MemberTable + Comma + iKeyMember->MemberField + Comma + IdName + ");");
//		kstrBody->Add ("if (" + FName + ") {";
		lstrBody->Add (IfF);
		lstrBody->Add (Tab + SqlStr + EQ + DQuote + SqlInsert + Space + SqlInto + Space + DQuote +
						Plus + MemberTable + Plus + DQuote + "(" + DQuote + Plus +
						iKeyMember->MemberField + Plus + DQuote + ") values (" + DQuote +
						Plus + StrName + " (" + IdName + Plus + "1)" +
						Plus + DQuote + ");" + DQuote + SC);
		lstrBody->Add (Tab + F_Var + EQ + "RunQuery (" + Query + Comma + SqlStr + Comma +
						StrQueryExec + Comma + StrErrName + ");");
		lstrBody->Add ("}");
		lstrBody->Add (ReturnF);
		strHeader = GetDPMethodHeader (InsertMethod, true, true, true);
		AddProc (lstrSrc, strHeader, lstrBody);
	}
	delete lstrBody;
}
//---------------------------------------------------------------------------
void __fastcall TClassInfo::PerformInDB (TStringList *lstrSrc, const String &strMethd)
{
	String strHeader;
	TStringList *lstrBody = new TStringList;

	strHeader = GetDPMethodHeader (strMethd, true, false, true);
	lstrBody->Add (Bool + Space + F_Var + SC);
	lstrBody->Add (AdoQuery + Query + EQ + InitQueryCall + SC);
	lstrBody->Add ("");
	lstrBody->Add (F_Var + EQ + strMethd + "(" + Query + Comma + StrErrName + ");");
	lstrBody->Add (Delete + Space + Query + SC);
	lstrBody->Add (ReturnF);
	AddProc (lstrSrc, strHeader, lstrBody);
	delete lstrBody;
}
//---------------------------------------------------------------------------
void __fastcall TClassInfo::WriteInsertItemToDB (TStringList *lstrSrc)
{
	PerformInDB (lstrSrc, InsertMethod);
}
//---------------------------------------------------------------------------
void __fastcall TClassInfo::WriteUpdateItemToDB (TStringList *lstrSrc)
{
	PerformInDB (lstrSrc, UpdateMethod);
}
//---------------------------------------------------------------------------
void __fastcall TClassInfo::WriteUpdateItem (TStringList *lstrSrc)
{
	String strHeader, strSet, strUpdate, strWhere, strUpdateTerm;
	TStringList *lstrBody = new TStringList;
	TMembers::iterator iKeyMember, iMember;
	size_t n;

	strHeader = GetDPMethodHeader (UpdateMethod, true, true, true);
	iKeyMember = m_Members.GetIDMemberName ();
	if (iKeyMember != NULL) {
		lstrBody->Add (StrName + Space + SqlStr + SC);
		lstrBody->Add (Bool + Space + F_Var + SC);
		lstrBody->Add ("");
		strSet = SqlStr + EQ + DQuote + SqlUpdate + Space + DQuote + Plus + MemberTable
						 + Plus + DQuote + SqlSet + DQuote + Space + Plus;
		strWhere = DQuote + SqlWhere + Space + DQuote + Plus +
				iKeyMember->MemberField + Plus + DQuote + EQ + DQuote + Plus + StrName +
				"(" + iKeyMember->PropertyName + ")";
		for (iMember=m_Members.begin(), n=0 ; iMember != m_Members.end() ; iMember++, n++) {
			strUpdateTerm = iMember->GetSqlUpdate ();
			if (strSet.Length() + strUpdate.Length() + strUpdateTerm.Length() > 75)
				strUpdateTerm = StrNewLine + Tab + Tab + Tab + Tab + strUpdateTerm;
			strUpdate += strUpdateTerm;
			if (n < m_Members.size() - 1)
				strUpdate += Plus + DQuote + Comma + DQuote;
			strUpdate +=  Plus;
		}
		lstrBody->Add (strSet + strUpdate);
		lstrBody->Add (Tab2 + strWhere + SC);
		lstrBody->Add (F_Var + EQ + StrRunQuery + "(" + Query + Comma + SqlStr + Comma + StrQueryExec + Comma + StrErrName + ");");
		lstrBody->Add (ReturnF);
		AddProc (lstrSrc, strHeader, lstrBody);
	}
	delete lstrBody;
}
//---------------------------------------------------------------------------

