//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Misc.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
void __fastcall EnableEdit  (TEdit *edt, bool fEnabled)
{
	edt->Enabled = fEnabled;
	edt->Color = fEnabled ? clWindow : clBtnFace;
}
//---------------------------------------------------------------------------
void __fastcall ClearGrid (TStringGrid *grid)
{
	int r, c;

	for (r=grid->FixedRows ; r < grid->RowCount ; r++)
		for (c=grid->FixedCols ; c < grid->ColCount ; c++) {
			grid->Cells[c][r] = "";
			grid->Objects[c][r] = NULL;
		}
}
//---------------------------------------------------------------------------
void __fastcall PurgeGrid (TStringGrid *grid)
{
	ClearGrid (grid);
	grid->RowCount = grid->FixedRows + 1;
}
//---------------------------------------------------------------------------
String __fastcall Reverse (const String &strSrc)
{
	int len = strSrc.Length() + 1;
	char *sz = new char [len];
	strcpy (sz, strSrc.c_str());
	strrev (sz);
	String strRev = String (sz);
	delete[] sz;
	return (strRev);
}
//---------------------------------------------------------------------------
void __fastcall WriteH (FILE *fileInclude, const String &strPrototype)
{
	fprintf (fileInclude, "\t%s;\n", strPrototype.c_str());
}
//---------------------------------------------------------------------------
void __fastcall WriteSepLine (FILE *file)
{
	static String str ("//");

	if (str.Length() == 2)
	for (int n=0 ; n < 76 ; n++)
		str += "-";
	fprintf (file, "%s\n", str.c_str());
}
//---------------------------------------------------------------------------
void __fastcall SaveIni (const String &strFile, const String &strSec, const String &Ident, const String &strValue)
{
	TIniFile *ini = NULL;

	try {
		ini = new TIniFile (strFile);
		ini->WriteString (strSec, Ident, strValue);
	}
	__finally {
		if (ini != NULL)
			delete ini;
	}
}
//---------------------------------------------------------------------------
String __fastcall LoadIniString  (const String &strFile, const String &strSec, const String &Ident)
{
	TIniFile *ini = NULL;
	String strValue;

	try {
		ini = new TIniFile (strFile);
		strValue = ini->ReadString (strSec, Ident, strValue);
	}
	__finally {
		if (ini != NULL)
			delete ini;
	}
	return (strValue);
}
//---------------------------------------------------------------------------

