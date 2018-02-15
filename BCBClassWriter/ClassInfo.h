//---------------------------------------------------------------------------

#ifndef ClassInfoH
#define ClassInfoH
//---- I n c l u d e s ------------------------------------------------------
#include "ClassMemberInfo.h"
enum EMethodClass {EMC_Class, EMC_Vector, EMC_None};
//---------------------------------------------------------------------------
class TClassInfo {
public:
	__fastcall TClassInfo ();
	__fastcall TClassInfo (const TClassInfo &other);

	void __fastcall Generate ();
	void __fastcall Generate (const String &strSrcPath);

	String __fastcall GetCtorH (bool fSource);
	String __fastcall GetCopyCtorH (bool fSource);
	String __fastcall GetAssignH (bool fSource);
	String __fastcall GetInEqH (bool fSource);
	String __fastcall GetEqH (bool fSource);
	String __fastcall GetClearH (bool fSource);

	String __fastcall GetDefaultCtorH () const;
	String __fastcall GetDefaultCtorSrc () const;
	void __fastcall WriteProperties (TStringList *lstr);
	String __fastcall GetAssignAllH (bool fSource);
	void __fastcall WriteMembersH (TStringList *lstr);
	void __fastcall WriteClearSrc (TStringList *lstrSrc);
	void __fastcall WriteOperatorEq (TStringList *lstrSrc);
	void __fastcall WritePropertiesSrc (TStringList *lstrSrc);

	void __fastcall WriteInsertItem (TStringList *lstrSrc);
	void __fastcall WriteInsertItemToDB (TStringList *lstrSrc);
	void __fastcall WriteUpdateItemToDB (TStringList *lstrSrc);
	void __fastcall WriteUpdateItem (TStringList *lstrSrc);

	bool __fastcall LoadFromFile (const String &strFile);
	bool __fastcall SaveToFile (const String &strFile);

	void __fastcall WriteCtorSrc (TStringList *lstrSrc);
	void __fastcall WriteCopyCtorSrc (TStringList *lstrSrc);
	void __fastcall WriteAssignSrc (TStringList *lstrSrc);
	void __fastcall WriteAssignAllSrc (TStringList *lstrSrc);
	void __fastcall WriteSetter (TStringList *lstrSrc, TClassMemberInfo &member);
	void __fastcall WriteGetter (TStringList *lstrSrc, TClassMemberInfo &member);

	TClassInfo __fastcall operator= (const TClassInfo &other);
	bool __fastcall operator== (const TClassInfo &other) const;
	bool __fastcall operator!= (const TClassInfo &other) const;
	void __fastcall ClearClass ();
//----- P r o p e r t i e s -----------------------------------------------
	__property String Name  = { read=GetName, write=SetName };
	__property TMembers Members  = { read=GetMembers, write=SetMembers };
	__property String VectorName  = { read=GetVectorName, write=SetVectorName };
	__property String SourceFile  = { read=GetSourceFile, write=SetSourceFile };
	__property String Include  = { read=GetInclude, write=SetInclude };
	__property String FileDir  = { read=GetFileDir, write=SetFileDir };
	__property String IfDef  = { read=GetIfDef, write=SetIfDef };
	__property bool DefCtor  = { read=GetDefCtor, write=SetDefCtor };
	__property bool CopyCtor  = { read=GetCopyCtor, write=SetCopyCtor };
	__property bool Dtor  = { read=GetDtor, write=SetDtor };
	__property bool DoClear  = { read=GetDoClear, write=SetDoClear };
	__property bool DoAssignAll  = { read=GetDoAssignAll, write=SetDoAssignAll };
	__property bool Eq  = { read=GetEq, write=SetEq };
	__property bool Uneq  = { read=GetUneq, write=SetUneq };
	__property bool Assign  = { read=GetAssign, write=SetAssign };
	__property bool Vector  = { read=GetVector, write=SetVector };
	__property bool Database  = { read=GetDatabase, write=SetDatabase };
	__property String SqlTable  = { read=GetSqlTable, write=SetSqlTable };
	__property String MemberTable  = { read=GetMemberTable, write=SetMemberTable };
protected:
	void __fastcall PerformInDB (TStringList *lstrSrc, const String &strMethd);

	void __fastcall WriteConstVars (TStringList *lstr);
	void __fastcall WriteStaticVars (TStringList *lstr);
	void __fastcall WriteLoadItemSrc (TStringList *lstrSrc);
	void __fastcall WriteItemDBMethods (TStringList *lstrSrc);
	void __fastcall WriteBasicMethods (TStringList *lstr);
	String __fastcall GetOtherParam ();
	void __fastcall GenerateVectorDBHeader (TStringList *lstrSrc);
	void __fastcall GenerateVectorHeader (TStringList *lstrSrc);
	String __fastcall GetDPMethodHeader (const String &strMethod, bool fSource, bool fQuery, bool fStrErr);
	String __fastcall GetDBHeader (const String &strProcName, bool fSource, bool fQuery, bool fStrErr);
	String __fastcall GetLoadItemHeader (bool fVector, bool fQuery, bool fSoure);
	String __fastcall GetLoadItemHeader ();
	void __fastcall WriteDBHeaders (TStringList *lstrSrc);
	String __fastcall GetMemberSetterParam (TClassMemberInfo &member);
	void __fastcall GenerateBasicProcsHeaders (TStringList *lstr);
	String __fastcall MakeOtherParam ();
	String __fastcall FormatProperty (TClassMemberInfo &member);
	String __fastcall GetClassHeader (EMethodClass emc, const String &type, const String &proc_name, const String &params, bool fSource, bool fConst);
	void __fastcall WriteHeaderStart (TStringList *lstr);
	String __fastcall GetIncludeDef ();
	void __fastcall GenerateInclude (TStringList *lstr);
	void __fastcall GenerateSource (TStringList *lstr);
	bool __fastcall LoadFromFile (TIniFile *ini);
	bool __fastcall SaveToFile (TIniFile *ini);
	void __fastcall AssignAll (const TClassInfo &other);
	void __fastcall WriteSetter (FILE *fileSrc, TClassMemberInfo &member);
	void __fastcall WriteGetter (FILE *fileSrc, TClassMemberInfo &member);
private: // members
	String m_strName;
	TMembers m_Members;
	String m_strVectorName;
	String m_strSrc;
	String m_strInclude;
	String m_strFileDir;
	String m_strIfDef;
	String m_strSqlTable;
	String m_strMemberTable;
	bool m_fDefCtor;
	bool m_fCopyCtor;
	bool m_fDtor;
	bool m_fClear;
	bool m_fAssignAll;
	bool m_fEq;
	bool m_fUneq;
	bool m_fAssign;
	bool m_fVector;
	bool m_fDatabase;
	String m_strOtherParam;
private: // methods
	void __fastcall SetName(const String &value);
	String __fastcall GetName() const;
	void __fastcall SetMembers(const TMembers &value);
	TMembers __fastcall GetMembers() const;
	void __fastcall SetVectorName(const String &value);
	String __fastcall GetVectorName() const;
	void __fastcall SetSourceFile(const String &value);
	String __fastcall GetSourceFile() const;
	void __fastcall SetInclude(const String &value);
	String __fastcall GetInclude() const;
	void __fastcall SetFileDir(const String &value);
	String __fastcall GetFileDir() const;
	void __fastcall SetIfDef(const String &value);
	String __fastcall GetIfDef() const;
	void __fastcall SetDefCtor(bool value);
	bool __fastcall GetDefCtor() const;
	void __fastcall SetCopyCtor(bool value);
	bool __fastcall GetCopyCtor() const;
	void __fastcall SetDtor(bool value);
	bool __fastcall GetDtor() const;
	void __fastcall SetDoClear(bool value);
	bool __fastcall GetDoClear() const;
	void __fastcall SetDoAssignAll(bool value);
	bool __fastcall GetDoAssignAll() const;
	void __fastcall SetEq(bool value);
	bool __fastcall GetEq() const;
	void __fastcall SetUneq(bool value);
	bool __fastcall GetUneq() const;
	void __fastcall SetAssign(bool value);
	bool __fastcall GetAssign() const;
	void __fastcall SetVector(bool value);
	bool __fastcall GetVector() const;
	void __fastcall SetDatabase(bool value);
	bool __fastcall GetDatabase() const;
	void __fastcall SetSqlTable(const String &value);
	String __fastcall GetSqlTable() const;
	void __fastcall SetMemberTable(const String &value);
	String __fastcall GetMemberTable() const;
};
#endif
