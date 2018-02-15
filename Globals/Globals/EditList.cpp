//---------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "EditList.h"
//---------------------------------------------------------------------
#pragma resource "*.dfm"
TdlgEditList *dlgEditList;
//---------------------------------------------------------------------
__fastcall TdlgEditList::TdlgEditList(TComponent* AOwner)
	: TForm(AOwner)
{
}
//---------------------------------------------------------------------
bool TdlgEditList::Execute (TIDStrings &list, const String &strTitle)
{
	Download (list, strTitle);
	ShowModal ();
	bool f = ModalResult == mrOk;
	if (f)
		Upload (list);
	return (f);
}
//---------------------------------------------------------------------
void TdlgEditList::Download (TIDStrings &list, const String &strTitle)
{
	Download (list);
	Download (strTitle);
}
//---------------------------------------------------------------------
void TdlgEditList::Download (TIDStrings &list)
{
	TIDStrings::iterator item;

	lstItems->Items->Clear ();
	for (item=list.begin() ; item != list.end() ; item++) {
		lstItems->Items->AddObject (item->Name, (TObject*) item->ID);
	}
}
//---------------------------------------------------------------------
void CenterControlsH (TControl *ctrlBase, TControl *ctrl)
{
	ctrl->Left = ctrlBase->Left + (ctrlBase->Width - ctrl->Width) / 2;
}
//---------------------------------------------------------------------
void TdlgEditList::Download (const String &strTitle)
{
	String str = Caption + strTitle;

	Caption = str;
	lblTitle->Caption = strTitle;
	CenterControlsH (lstItems, lblTitle);
}
//---------------------------------------------------------------------
void TdlgEditList::Upload (TIDStrings &list)
{
	int n;
	TIDStr item;

	list.clear ();
	for (n=0 ; n < lstItems->Items->Count ; n++) {
		item.ID = (int) lstItems->Items->Objects[n];
		item.Name = lstItems->Items->Strings[n];
		list.push_back(item); 
	}
}
//---------------------------------------------------------------------
void __fastcall TdlgEditList::bitbtnAddClick(TObject *Sender)
{
	String str;

	if (InputQuery ("Add Item", "", str))
		if (str.Trim().Length() > 0) {
			lstItems->Items->AddObject (str, NULL);
		}
}
//---------------------------------------------------------------------------
void __fastcall TdlgEditList::bitbtnEditClick(TObject *Sender)
{
	String str = lstItems->Items->Strings[lstItems->ItemIndex];

	if (InputQuery ("Edit Item", "", str))
		if (str.Trim().Length() > 0) {
			lstItems->Items->Strings[lstItems->ItemIndex] = str;
		}
}
//---------------------------------------------------------------------------
void __fastcall TdlgEditList::OnIdle(TObject *Sender, bool &Done)
{
	bitbtnEdit->Enabled = lstItems->ItemIndex >= 0;
	bitbtnDel->Enabled = lstItems->ItemIndex >= 0;
}
//---------------------------------------------------------------------------
void __fastcall TdlgEditList::bitbtnDelClick(TObject *Sender)
{
	lstItems->Items->Delete (lstItems->ItemIndex);
}
//---------------------------------------------------------------------------

