//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "ShowProgress.h"
#include "Misc.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "cgauges"
#pragma resource "*.dfm"
TfrmShowProgress *frmShowProgress;
//---------------------------------------------------------------------------
__fastcall TfrmShowProgress::TfrmShowProgress(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TfrmShowProgress::SetMax (int nFiles)
{
	gauge1->MaxValue = nFiles;
}
//---------------------------------------------------------------------------
void __fastcall TfrmShowProgress::SetProgress (int nProgress)
{
	gauge1->Progress = nProgress;
}
//---------------------------------------------------------------------------
void __fastcall TfrmShowProgress::UpdateGUI ()
{
	InvalidateAll (panelCaption);
	InvalidateAll (btnStop);
	InvalidateAll (gauge1);
}
void __fastcall TfrmShowProgress::UpdateGUI (const String &strCaption)
{
	InvalidateAll (panelCaption);
	InvalidateAll (btnStop);
	InvalidateAll (gauge1);
}
//---------------------------------------------------------------------------
