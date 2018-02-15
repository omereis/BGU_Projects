//---------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "EditDataset.h"
//---------------------------------------------------------------------
#pragma resource "*.dfm"
TdlgEditDataset *dlgEditDataset;
//---------------------------------------------------------------------
__fastcall TdlgEditDataset::TdlgEditDataset(TComponent* AOwner)
	: TForm(AOwner)
{
}
//---------------------------------------------------------------------
bool __fastcall TdlgEditDataset::Execute (TDatasetInfo &dataset)
{
	bool f;

	Download (dataset);
	ShowModal ();
	f = ModalResult == mrOk;
	if (f)
		Upload (dataset);
	return (f);
}
//---------------------------------------------------------------------
void  __fastcall TdlgEditDataset::Download (TDatasetInfo &dataset)
{
	Tag = dataset.DatasetID;
	panelID->Caption = String (Tag);
	edtName->Text = dataset.Name;
	edtURL->Text = dataset.URL;
	edtOrg->Text = dataset.Organization;
	memoStructure->Lines->Text = dataset.Structure;
//	dataset.Contacts = ;
//	dataset.Points = ;
	edtUsername->Text = dataset.Username;
	edtPasswors->Text = dataset.Password;
	edtDescription->Text = dataset.Description;
	DownloadType (dataset);
}
//---------------------------------------------------------------------
void __fastcall TdlgEditDataset::DownloadType (TDatasetInfo &dataset)
{
	String strType;
	int idx;

	strType = TDatasetInfo::GetTypeName (dataset.Type);
	if ((idx = comboType->Items->IndexOf (strType)) > 0)
    	comboType->ItemIndex = idx;

}
//---------------------------------------------------------------------
void __fastcall TdlgEditDataset::Upload (TDatasetInfo &dataset)
{
//	dataset.Contacts = ;
//	dataset.Points;
	dataset.DatasetID = Tag;
    dataset.Type = (EDatasetType) comboType->ItemIndex;
	dataset.Name = edtName->Text;
	dataset.URL = edtURL->Text;
	dataset.Structure = memoStructure->Lines->Text;
	dataset.Username = edtUsername->Text;
	dataset.Password = edtPasswors->Text;
	dataset.Description = edtDescription->Text;
	dataset.Organization = edtOrg->Text;
}
//---------------------------------------------------------------------
void __fastcall TdlgEditDataset::btnURLTestClick(TObject *Sender)
{
	String str = edtURL->Text.Trim();

	if (str.Length() > 0) {
		ShellExecute(Handle, "open", str.c_str(), NULL, NULL,SW_SHOWNORMAL);
	}
}
//---------------------------------------------------------------------------
void __fastcall TdlgEditDataset::OnIdle(TObject *Sender, bool &Done)
{
	panelChars->Caption = String (memoStructure->Lines->Text.Length());	
}
//---------------------------------------------------------------------------
void __fastcall TdlgEditDataset::FormCreate(TObject *Sender)
{
	int n;
	TStringList *lstr = new TStringList;

	comboType->Items->Clear();
	if (TDatasetInfo::GetTypeNames (lstr) > 0) {
		for (n=0 ; n < lstr->Count ; n++)
			comboType->Items->Add (lstr->Strings[n]);
	}
	delete lstr;
}
//---------------------------------------------------------------------------

