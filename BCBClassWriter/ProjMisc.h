//---------------------------------------------------------------------------

#ifndef ProjMiscH
#define ProjMiscH
//---------------------------------------------------------------------------
#include <dstring.h>
//---------------------------------------------------------------------------
String GetSepLine ();
String __fastcall HeaderFromSrc (const String &strSrc);
String __fastcall GetMethodHeader (const String &strClassName, const String &type, const String &proc_name, const String &params, bool fSource, bool fConst);
void __fastcall AddProc (TStringList *lstrSrc, String &strHeader, TStringList *lstrBody);
void __fastcall AddProc (TStringList *lstrSrc, String &strHeader, String &strBody);
int __fastcall GetLongest (TStringList *lstr, int &len);
void __fastcall AlignList (TStringList *lstr);
//---------------------------------------------------------------------------
#endif

