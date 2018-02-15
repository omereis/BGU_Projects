//------------------------------------------------------------------------------
#ifndef	FileInfoH
#define	FileInfoH
//------------------------------------------------------------------------------
#include <ADODB.hpp>
#include "DBMisc.h"
#include <vector>
using namespace std;
//------------------------------------------------------------------------------
class TFileInfo;
typedef vector<TFileInfo> TFileInfoBase;
//------------------------------------------------------------------------------
class TFileInfo {
public:
	__fastcall TFileInfo ();
	__fastcall TFileInfo (const TFileInfo &other);
	TFileInfo __fastcall operator= (const TFileInfo &other);
	bool __fastcall operator!= (const TFileInfo &other) const;
	bool __fastcall operator== (const TFileInfo &other) const;
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
	__property int FileID = {read=GetFileID, write=SetFileID};
	__property int DatasetID = {read=GetDatasetID, write=SetDatasetID};
	__property int Size = {read=GetSize, write=SetSize};
	__property String FileName = {read=GetFileName, write=SetFileName};
	__property String Comment = {read=GetComment, write=SetComment};
// ---------- S t a t i c ----------
	static String Table;
	static String FldID;
	static String FldDatasetID;
	static String FldSize;
	static String FldFileName;
	static String FldComment;
protected:
	void __fastcall AssignAll (const TFileInfo &other);
private:
	int m_nFileID;
	int m_nDatasetID;
	int m_nSize;
	String m_strFileName;
	String m_strComment;
//------------------------------------------------------------------------------
	int __fastcall GetFileID () const;
	int __fastcall GetDatasetID () const;
	int __fastcall GetSize () const;
	String __fastcall GetFileName () const;
	String __fastcall GetComment () const;
//------------------------------------------------------------------------------
	void __fastcall SetFileID (const int value);
	void __fastcall SetDatasetID (const int value);
	void __fastcall SetSize (const int value);
	void __fastcall SetFileName (const String &value);
	void __fastcall SetComment (const String &value);
};
//------------------------------------------------------------------------------
class TFiles : public TFileInfoBase {
public:
	__fastcall TFiles ();
// Vector Database Support
	bool __fastcall LoadFromDB (TADOQuery *query, String &strErr);
	bool __fastcall LoadFromDB (TADOConnection *db, String &strErr);
};
//------------------------------------------------------------------------------
#endif
