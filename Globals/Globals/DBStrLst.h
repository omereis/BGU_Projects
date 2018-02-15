//---------------------------------------------------------------------------

#ifndef DBStrLstH
#define DBStrLstH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include "DBMisc.h"
//#include <ADODB.hpp>
//#include <DB.hpp>
//---------------------------------------------------------------------------
class TDBStringList : public TStringList {
public:
	__fastcall TDBStringList (TADOConnection *db, const String &strTable, const String &strID, const String &strName);
	virtual __fastcall ~TDBStringList ();

	bool __fastcall Load (String &strErr);
	bool __fastcall DeleteAllFromDB (String &strErr);
	bool __fastcall DeleteFromDB (int id, String &strErr);
	bool __fastcall DeleteContentFromDB (String &strErr);

	bool __fastcall InsertToDB (String &strErr);
	bool __fastcall InsertItemToDB (const String &str, int id, String &strErr);
	bool __fastcall UpdateInDB (TDBStringList *dblstrOld, const String &strErr);
protected:
private:
	TADOQuery *m_query;
	TADOConnection *m_db;
	String m_strTable;
	String m_strID;
	String m_strName;
	String m_strErr;
};
#endif
