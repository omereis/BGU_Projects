//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "DBMisc.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)
static const String MaxValueField ("MaxValue");
//---------------------------------------------------------------------------
TQuery *__fastcall InitQuery (TDatabase *db, Classes::TComponent* owner)
{
	TQuery *query = new TQuery (owner);
	query->DatabaseName = db->DatabaseName;
	return (query);
}
//---------------------------------------------------------------------------
TADOQuery *__fastcall InitQuery (TADOConnection *db, Classes::TComponent* owner)
{
	TADOQuery *query = new TADOQuery (owner);
	query->Connection = db;
	return (query);
}
//---------------------------------------------------------------------------
bool __fastcall RunQuery (TQuery *query, const String &strSql, QueryOp op, String &strErr)
{
	bool f = true;

	query->SQL->Clear ();
	query->SQL->Add (strSql);
	try {
		if (op == QueryOpen)
			query->Open ();
		else if (op == QueryExec)
			query->ExecSQL ();
		else
			f = false;
	}
	catch (Exception &e) {
			f = false;
			strErr = e.Message;
	};
	return (f);
}
//---------------------------------------------------------------------------
#include <stdio.h>
void __fastcall AddSqlLog (const String &strSql)
{
	FILE *file;
	String strFile;

	strFile = ExtractFileDir (Application->ExeName) + "\\sql.txt";

	if ((file = fopen (strFile.c_str(), "a+")) != NULL) {
		fprintf (file, "%s\n", strSql.c_str());
		fclose (file);
//		file = fopen ("sql.txt", "r");
//		fclose (file);
    }
}
//---------------------------------------------------------------------------
bool __fastcall RunQuery (TADOQuery *query, const String &strSql, QueryOp op, String &strErr)
{
	bool f = true;

	strErr = "";
	query->SQL->Clear ();
	query->SQL->Add (strSql);
/*
#ifdef	_DEBUG
	AddSqlLog (strSql);
#endif
*/
	try {
		if (op == QueryOpen)
			query->Open ();
		else if (op == QueryExec)
			query->ExecSQL ();
		else
			f = false;
	}
	catch (Exception &e) {
			f = false;
			strErr = e.Message;
	};
	return (f);
}
//---------------------------------------------------------------------------
String FixQuotes (const String &strValue)
{
	char *sz;
	int n;
	String strFixed;
	static char cQuote ('\'');

	sz = strValue.c_str();
	for (n=0 ; n < strValue.Length() ; n++) {
		if (sz[n] == cQuote)
			strFixed += cQuote;
		strFixed += sz[n];
	}
	return (strFixed);
}
#include "IseTypes.h"
//---------------------------------------------------------------------------
String ModifyForUpdate(const String &strField, const TDateTime &dt)
{
	ushort usYear, usMonth, usDay, usHour, usMin, usSec, usMsec;
	String str, strDateTime;

	dt.DecodeDate(&usYear, &usMonth, &usDay);
	dt.DecodeTime(&usHour, &usMin, &usSec, &usMsec);
	strDateTime.sprintf ("%4d-%02d-%2 %02d:%02d:%2d", usYear, usMonth, usDay, usHour, usMin, usSec);
	str = strField + "='" + strDateTime + "'";
	return (str);
}
//---------------------------------------------------------------------------
String ModifyForUpdate (const String &strField, double dValue)
{
	String strValue;

	strValue = FormatFloat ("#.00000000000000#", dValue);
	return (ModifyForUpdate (strField, strValue));
}
//---------------------------------------------------------------------------
String ModifyForUpdate (const String &strField, bool fValue)
{
	return (ModifyForUpdate (strField, (int) fValue, false ));
}
//---------------------------------------------------------------------------
String ModifyForUpdate (const String &strField, int nValue, bool fZeroIsNull)
{
	String str, strFieldValue, strMisQuote;

	if ((nValue == 0) && (fZeroIsNull))
		strFieldValue = "NULL";
	else
		strFieldValue = String (nValue);
	str = strField + "=" + strFieldValue;
	return (str);
}
//---------------------------------------------------------------------------
String ModifyForUpdate (const String &strField, const String &strValue)
{
	String str, strFieldValue, strMisQuote;

	if (strValue.IsEmpty()) {
		strFieldValue = "NULL";
	}
	else {
		strFieldValue = "'" + FixQuotes (strValue) + "'";
	}
	str = strField + "=" + strFieldValue;
	return (str);
}
//---------------------------------------------------------------------------
bool __fastcall GetFieldMax (TADOQuery *query, const String &strTable, const String &strField, int &nValue)
{
	String strSql, strErr;
	bool f;

	nValue = 0;
	strSql = "select max(" + strField + ") as '" + MaxValueField + "' from " + strTable + ";";
	f = RunQuery (query, strSql, QueryOpen, strErr);
	if (f) {
		query->First ();
		if (!query->Eof) {
			nValue = query->Fields->FieldByName (MaxValueField)->AsInteger;
		}
	}
	return (f);
}
//---------------------------------------------------------------------------
String __fastcall ModifyForInsert (const String &strValue)
{
	String strFieldValue = "'" + FixQuotes (strValue) + "'";
	return (strFieldValue);
}
//---------------------------------------------------------------------------


