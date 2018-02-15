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
void __fastcall SetComboText (TComboBox *combo, const String &str)
{
	int idx;

	idx = combo->Items->IndexOf(str);
	if (idx>= 0) {
		combo->ItemIndex = idx;
	}
}
//---------------------------------------------------------------------------
void __fastcall DeleteLine (TStringGrid *grid, int nRow)
{
	if ((grid->RowCount == 2) && (nRow == 1)) {
		ClearGridRow (grid, 1);
	}
	else if ((grid->RowCount - 1) == nRow) { // last row
		ClearGridRow (grid, nRow);
	}
	else {
		for (int r = nRow; r < grid->RowCount - 1 ; r++) {
			for (int c=grid->FixedCols ; c < grid->ColCount ; c++) {
				String s, s1;
				s = grid->Cells[c][r]; s1 = grid->Cells[c][r + 1];
				grid->Cells[c][r] = grid->Cells[c][r + 1];
				grid->Objects[c][r] = grid->Objects[c][r + 1];
			}
		}
		ClearGridRow (grid, grid->RowCount - 1);
		grid->RowCount--;
	}
}
//---------------------------------------------------------------------------
void __fastcall ClearGridRow (TStringGrid *grid, int nRow)
{
	for (int c=0 ; c < grid->ColCount ; c++) {
		grid->Cells[c][nRow] = "";
		grid->Objects[c][nRow] = NULL;
	}
}
//------------------------------------------------------------------------------
int __fastcall Tokenize (const String &strLine, TStringList *lstrTokens, const String &strSep)
{
	int nNext;
	String str (strLine), strSub;

	lstrTokens->Clear ();
	for (nNext = 1 ; nNext > 0 ; ) {
		nNext = str.Pos (strSep);
		if (nNext > 0) {
			strSub = str.SubString (1, nNext - strSep.Length());
			lstrTokens->Add (strSub);
			str = str.SubString (nNext + strSep.Length(), str.Length());
		}
	}
	if (str.Length() > 0) {
		lstrTokens->Add (str);
	}
	return (lstrTokens->Count);
}
//------------------------------------------------------------------------------
int __fastcall Tokenize (const String &strLine, TStringList *lstrTokens, char c)
{
	return (Tokenize (strLine, lstrTokens, String (c)));
}
//---------------------------------------------------------------------------
void __fastcall InvalidateAll (TControl *ctrl)
{
	ctrl->Invalidate ();
	if (ctrl->Parent != NULL) {
		InvalidateAll ((TControl *)ctrl->Parent);
	}
}
//---------------------------------------------------------------------------

