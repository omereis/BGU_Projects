//---------------------------------------------------------------------------

#ifndef DBMiscH
#define DBMiscH
//---------------------------------------------------------------------------
#include <dbtables.hpp>
#include <ADODB.hpp>
enum QueryOp {QueryOpen, QueryExec};
//---------------------------------------------------------------------------
TQuery *__fastcall InitQuery (TDatabase *db, Classes::TComponent* owner);
TADOQuery *__fastcall InitQuery (TADOConnection *db, Classes::TComponent* owner);
bool __fastcall RunQuery (TQuery *query, const String &strSql, QueryOp op, String &strErr);
bool __fastcall RunQuery (TADOQuery *query, const String &strSql, QueryOp op, String &strErr);
String __fastcall ModifyForInsert (const String &strValue);
String ModifyForUpdate (const String &strField, const String &strValue);
String ModifyForUpdate (const String &strField, int nValue, bool fZeroIsNull=false);
String ModifyForUpdate (const String &strField, double dValue);
String ModifyForUpdate (const String &strField, bool fValue, bool fZeroIsNull=false);
bool __fastcall GetFieldMax (TADOQuery *query, const String &strTable, const String &strField, int &nValue);
#endif

