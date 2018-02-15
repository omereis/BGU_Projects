//---------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "EditContact.h"
//---------------------------------------------------------------------
#pragma resource "*.dfm"
TdlgContact *dlgContact;
//---------------------------------------------------------------------
__fastcall TdlgContact::TdlgContact(TComponent* AOwner)
	: TForm(AOwner)
{
}
//---------------------------------------------------------------------
bool __fastcall TdlgContact::Execute (TContactInfo &contact)
{
	bool f;

	Download (contact);
	ShowModal ();
	if ((f = (ModalResult == mrOk)) == true)
		Upload (contact);
	return (f);
}
//---------------------------------------------------------------------
void __fastcall TdlgContact::Download (const TContactInfo &contact)
{
	edtName->Text     = contact.Name;
	edtPhone->Text    = contact.Phone;
	edtEmail->Text    = contact.Email;
	edtComments->Text = contact.Comments;
	Tag = contact.ID;
	panelID->Caption = String (contact.ID);
}
//---------------------------------------------------------------------
void __fastcall TdlgContact::Upload (TContactInfo &contact)
{
	contact.Name = edtName->Text.Trim();
	contact.Phone = edtPhone->Text.Trim();
	contact.Email = edtEmail->Text.Trim();
	contact.Comments = edtComments->Text.Trim();
	contact.ID = Tag;
}
//---------------------------------------------------------------------

