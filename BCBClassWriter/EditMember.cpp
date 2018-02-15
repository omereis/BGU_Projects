//---------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "EditMember.h"
#include "Misc.h"
#include "main.h"
//---------------------------------------------------------------------
#pragma resource "*.dfm"
TdlgEditMember *dlgEditMember;
//---------------------------------------------------------------------
__fastcall TdlgEditMember::TdlgEditMember(TComponent* AOwner)
	: TForm(AOwner)
{
}
//---------------------------------------------------------------------
String __fastcall HungarianVarName (const String &strType, bool fIsMember = false)
{
	String str;

	if (strType == "String")
		str = "str";
	else if (strType == "int")
		str = "n";
	else if (strType == "double")
		str = "d";
	else if (strType == "bool")
		str = "f";
	if (str.Length() &&  (fIsMember))
		str = "m_" + str;
	return (str);
}
//---------------------------------------------------------------------
void __fastcall TdlgEditMember::comboTypeChange(TObject *Sender)
{
	if (comboType->Text == "String")
		cboxUseReference->Checked = true;
	if (edtMemberName->Text.Trim().IsEmpty()) {
		edtMemberName->Text = HungarianVarName (comboType->Text, true);
	}
}
//---------------------------------------------------------------------
bool __fastcall TdlgEditMember::Execute (TForm *parent, TClassMemberInfo &class_info, bool fDatabase, bool fNew)
{
	bool f;

	m_parent = parent;
	panelDBParams->Visible = fDatabase;
	bitbtnApplyAndNew->Visible = fNew;
	Download (class_info);
	ShowModal ();
	if ((f = (ModalResult == mrOk)) == true)
		Upload (class_info);
	else
		f = false;
	return (f);
}
//---------------------------------------------------------------------
void __fastcall SetComboText (TComboBox *combo, String &str)
{
	int idx = combo->Items->IndexOf (str);
	if (idx < 0)
		idx = combo->Items->Add (str);
	combo->ItemIndex = idx;
}
//---------------------------------------------------------------------
void __fastcall TdlgEditMember::Download (TClassMemberInfo &class_info)
{
	panelID->Caption          = String (class_info.MemberID);
	edtPropName->Text         = class_info.PropertyName;
	edtMemberName->Text       = class_info.MemberName;
	cboxUseReference->Checked = class_info.UseReference;
	edtClear->Text            = class_info.ClearValue;
	edtSqlField->Text         = class_info.SqlField;
	edtMemberField->Text      = class_info.MemberField;
	cboxIsKey->Checked        = class_info.IsKey;
	SetComboText (comboType, class_info.Type);
}
//---------------------------------------------------------------------
void __fastcall TdlgEditMember::Upload (TClassMemberInfo &class_info)
{
	class_info.MemberID     = panelID->Caption.ToIntDef (0);
	class_info.MemberName   = edtMemberName->Text.Trim();
	class_info.PropertyName = edtPropName->Text.Trim();
	class_info.Type         = comboType->Text.Trim();
	class_info.UseReference = cboxUseReference->Checked;
	class_info.ClearValue   = edtClear->Text;
	class_info.SqlField     = edtSqlField->Text;
	class_info.MemberField  = edtMemberField->Text;
	class_info.IsKey        = cboxIsKey->Checked;
}
//---------------------------------------------------------------------------
//	edtMemberName->Text = HungarianVarName (comboType->Text, true) + edtPropName->Text;
//---------------------------------------------------------------------------
void __fastcall TdlgEditMember::bitbtnApplyAndNewClick(TObject *Sender)
{
	TClassMemberInfo class_info;
	TformMain *pMain = (TformMain *) m_parent;

	Upload (class_info);
	pMain->AddAndNew (class_info);
	Download (class_info);
	comboType->SetFocus ();
}
//---------------------------------------------------------------------------

