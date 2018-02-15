//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "ProjMisc.h"
#include "Misc.h"
#include "CommonStrings.h"
//---------------------------------------------------------------------------

#pragma package(smart_init)
//---------------------------------------------------------------------------
String GetSepLine ()
{
	String str;

	str = "//" + str.StringOfChar ('-', 78);
	return (str);
}
//---------------------------------------------------------------------------
String __fastcall HeaderFromSrc (const String &strSrc)
{
	String strHeader, strRev, strFile, strDir;
	int nDot;

	strFile = ExtractFileName (strSrc);
	strDir = ExtractFileDir   (strSrc);
	nDot = strFile.Pos (".");
	if (nDot > 0)
		strHeader = strFile.SubString (1, nDot);
	else
		strHeader = strFile + ".";
	strHeader += "h";
	return (strDir + "\\" + strHeader);
}
//---------------------------------------------------------------------------
String __fastcall GetMethodHeader (const String &strClassName, const String &type, const String &proc_name, const String &params, bool fSource, bool fConst)
{
	String str;

	if (!fSource)
		str = "\t";
	str += type;
	if (type.Length() > 0)
		str += Space;
	str += FastCall + Space;
	if (fSource)
		str += strClassName + "::";
	str += proc_name + " (" + params + ")";
	if (fConst)
		str += " const";
	if (!fSource)
		str += ";";
	return (str);;
}
//---------------------------------------------------------------------------
void __fastcall AddProc (TStringList *lstrSrc, String &strHeader, TStringList *lstrBody)
{
	int n;

	lstrSrc->Add (strHeader);
	lstrSrc->Add ("{");
	for (n=0 ; n < lstrBody->Count ; n++)
		lstrSrc->Add ("\t" + lstrBody->Strings[n]);
	lstrSrc->Add ("}");
	lstrSrc->Add (GetSepLine ());
}
//---------------------------------------------------------------------------
void __fastcall AddProc (TStringList *lstrSrc, String &strHeader, String &strBody)
{
	TStringList *lstrBody = new TStringList;

	lstrBody->Add (strBody);
	AddProc (lstrSrc, strHeader, lstrBody);
	delete lstrBody;
}
//---------------------------------------------------------------------------
int __fastcall GetLongest (TStringList *lstr, int &len)
{
	int n, iLong, lNew;

	len = 0;
	for (n=0 ; n < lstr->Count ; n++) {
		lNew = lstr->Strings[n].Length();
		if (lNew > len) {
			len = lNew;
			iLong ; n;
		}
	}
	return (iLong);
}
//---------------------------------------------------------------------------
void __fastcall AlignList (TStringList *lstr)
{
	int n, iLong, len;
	String str;

	GetLongest (lstr, len);
	for (n=0 ; n < lstr->Count ; n++) {
		str = lstr->Strings[n];
		while (str.Length () < len)
			str += " ";
		lstr->Strings[n] = str;
	}
}
//---------------------------------------------------------------------------

