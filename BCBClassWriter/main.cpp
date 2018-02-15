//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "main.h"
#include "Misc.h"
#include "ClassMemberInfo.h"
#include "EditMember.h"
#include <stdio.h>
#include <string.h>
#include "ProjMisc.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TformMain *formMain;
//---------------------------------------------------------------------------
int TformMain::ColMemberID     = 0;
int TformMain::ColName         = 1;
int TformMain::ColPropertyName = 2;
int TformMain::ColType         = 3;
int TformMain::ColClear        = 4;
int TformMain::ColSqlTable     = 5;
int TformMain::ColVarTable     = 6;
String TformMain::SecParams          = "Parameters";
String TformMain::IdentParamFile = "Parameters Directory";
//---------------------------------------------------------------------------
__fastcall TformMain::TformMain(TComponent* Owner)
	: TForm(Owner)
{
	m_fChange = false;
}
//---------------------------------------------------------------------------
void __fastcall TformMain::OnIdle(TObject */*Sender*/, bool &/*Done*/)
{
	EnableEdit  (edtVector, cboxVector->Checked);
	actSave->Enabled = !m_strParamsFile.Trim().IsEmpty();
	actMemberEdit->Enabled = gridMembers->Cells[0][gridMembers->Row].ToIntDef(0) > 0;
	actMembersDel->Enabled = gridMembers->Cells[0][gridMembers->Row].ToIntDef(0) > 0;
	actGenerate->Enabled = edtClassFile->Text.Trim().Length() > 0;
	panelDBParams->Visible = cboxDatabase->Checked;
	actGenerate->Enabled = (edtClassFile->Text.Trim().Length() > 0) && (edtClassName->Text.Trim().Length() > 0);
}
//---------------------------------------------------------------------------
void __fastcall TformMain::actOpenExecute(TObject */*Sender*/)
{
	TClassInfo class_info;
	String strDir;

	strDir = LoadIniString  (m_strIni, SecParams, IdentParamFile);
	dlgOpenParams->InitialDir = strDir;
	if (dlgOpenParams->Execute()) {
		if (class_info.LoadFromFile (dlgOpenParams->FileName))
			Download (class_info);
			m_strParamsFile = dlgOpenParams->FileName;
			SetCaption (class_info);
			m_fChange = false;
			SaveParamsFile ();
	}
}
//---------------------------------------------------------------------------
void __fastcall TformMain::FormCreate(TObject */*Sender*/)
{
	m_strCaptionBase = Caption;
	gridMembers->Anchors << akRight << akBottom;
	InitMembersGrid ();
	m_fChange = false;
	AssembleIniFileName ();
}
//---------------------------------------------------------------------------
void __fastcall TformMain::AssembleIniFileName ()
{
	String strDir = ExtractFileDir (Application->ExeName);

	m_strIni = strDir + "\\UnitWriter.ini";
}
//---------------------------------------------------------------------------
void __fastcall TformMain::InitMembersGrid ()
{
	gridMembers->Cells[ColMemberID][0]     = "Member ID";
	gridMembers->Cells[ColName][0]         = "Name";
	gridMembers->Cells[ColPropertyName][0] = "Property Name";
	gridMembers->Cells[ColType][0]         = "Type";
	gridMembers->Cells[ColClear][0]        = "Clear";
	gridMembers->Cells[ColSqlTable][0]     = "DB Field";
	gridMembers->Cells[ColVarTable][0]     = "Field Member";
}
//---------------------------------------------------------------------------
void __fastcall TformMain::SetMemberRow (int nRow, const TClassMemberInfo &member)
{
	TObject *obj;

	gridMembers->Cells[0][nRow] = String (member.MemberID);
	gridMembers->Cells[1][nRow] = member.MemberName;
	gridMembers->Cells[2][nRow] = member.PropertyName;
	gridMembers->Cells[3][nRow] = member.Type;
	gridMembers->Cells[ColSqlTable][nRow]     = member.SqlField;
	gridMembers->Objects[ColSqlTable][nRow] = (TObject*) member.IsKey;
	gridMembers->Cells[ColVarTable][nRow]     = member.MemberField;
	obj = (member.UseReference ? (TObject *) 0x1 : NULL);
	gridMembers->Objects[3][nRow] = obj;
	gridMembers->Cells[4][nRow] = member.ClearValue;
}
//---------------------------------------------------------------------------
bool __fastcall TformMain::UploadMemberRow (int nRow, TClassMemberInfo &member)
{
	member.MemberID     = gridMembers->Cells[0][nRow].ToIntDef (0);
	member.MemberName   = gridMembers->Cells[1][nRow];
	member.PropertyName = gridMembers->Cells[2][nRow];
	member.Type         = gridMembers->Cells[3][nRow];
	member.UseReference = (gridMembers->Objects[3][nRow] == NULL ? false : true);
	member.ClearValue = gridMembers->Cells[4][nRow];
	member.SqlField     = gridMembers->Cells[ColSqlTable][nRow];
	member.IsKey    = (int) gridMembers->Objects[ColSqlTable][nRow];
	member.MemberField  = gridMembers->Cells[ColVarTable][nRow];
	String str = member.MemberName.Trim();
	return (str.Length() > 0);
}
//---------------------------------------------------------------------------
bool __fastcall TformMain::EditMember (TClassMemberInfo &member, bool fNew)
{
	TdlgEditMember *dlg = new TdlgEditMember (this);

	bool f = dlg->Execute (this, member, cboxDatabase->Checked, fNew);
	delete dlg;
	return (f);
}
//---------------------------------------------------------------------------
void __fastcall TformMain::AddAndNew (TClassMemberInfo &class_info)
{
	m_vMembers.push_back (class_info);
	if (gridMembers->RowCount > 2 || !gridMembers->Cells[0][1].IsEmpty())
		gridMembers->RowCount++;
	SetMemberRow (gridMembers->RowCount - 1, class_info);
	class_info.Clear ();
	class_info.MemberID = m_vMembers.GetNextID ();
}
//---------------------------------------------------------------------------
void __fastcall TformMain::actSaveAsExecute(TObject */*Sender*/)
{
	if (dlgSaveParams->Execute ()) {
		SaveToFile (dlgSaveParams->FileName);
	}
}
//---------------------------------------------------------------------------
void __fastcall TformMain::SaveToFile (const String &strFile)
{
	TClassInfo class_info;

	Upload (class_info);
	try {
		if (class_info.SaveToFile (strFile)) {
			m_strParamsFile = strFile;
			SetCaption (strFile);
			SaveParamsFile ();
		}
	}
	catch (Exception &e) {
		ShowMessage ("Error savnig paremeters file '" + strFile + "'\n" + e.Message);
	}
}
//---------------------------------------------------------------------------
void __fastcall TformMain::btnBrowseClick(TObject */*Sender*/)
{
	if (dlgSaveClass->Execute())
		edtClassFile->Text = dlgSaveClass->FileName;
}
//---------------------------------------------------------------------------
void __fastcall TformMain::miClearClick(TObject */*Sender*/)
{
//	Download (TClassInfo ());
	Clear();
}
//---------------------------------------------------------------------------
void __fastcall TformMain::Clear()
{
	Download (TClassInfo ());
	m_strParamsFile = "";
/*
	edtClassFile->Text = "";
	edtVector->Text = "";
	edtClassName->Text = "";
	PurgeGrid (gridMembers);
	cboxDefCtor->Checked   = true;
	cboxCopyCtor->Checked  = true;
	cboxDtor->Checked      = false;
	cboxClear->Checked     = true;
	cboxAssignAll->Checked = true;
	cboxEq->Checked        = true;
	cboxUneq->Checked      = true;
	cboxAssign->Checked    = true;
	cboxVector->Checked    = true;
	cboxDatabase->Checked  = true;
*/
}
//---------------------------------------------------------------------------
void __fastcall TformMain::actSaveExecute(TObject *Sender)
{
	if (m_strParamsFile.Trim().IsEmpty())
		actSaveAs->OnExecute (Sender);
	else
		SaveToFile (m_strParamsFile);
}
//---------------------------------------------------------------------------
void __fastcall TformMain::Download (TClassInfo &class_info)
{
	edtClassFile->Text     = class_info.SourceFile;
	edtClassName->Text     = class_info.Name;
	edtVector->Text        = class_info.VectorName;
	edtSqlTable->Text      = class_info.SqlTable;
	edtMemberTable->Text   = class_info.MemberTable;
	cboxDefCtor->Checked   = class_info.DefCtor;
	cboxDtor->Checked      = class_info.Dtor;
	cboxCopyCtor->Checked  = class_info.CopyCtor;
	cboxClear->Checked     = class_info.DoClear;
	cboxAssignAll->Checked = class_info.DoAssignAll;
	cboxEq->Checked        = class_info.Eq;
	cboxUneq->Checked      = class_info.Uneq;
	cboxAssign->Checked    = class_info.Assign;
	cboxVector->Checked    = class_info.Vector;
	cboxDatabase->Checked  = class_info.Database;
	DownloadMembers (class_info.Members);
}
//---------------------------------------------------------------------------
void __fastcall TformMain::DownloadMembers (const TMembers &vMembers)
{
	TMembers::const_iterator iMember;
	int nRow;

	PurgeGrid (gridMembers);
	gridMembers->RowCount = max (2, (int) vMembers.size() + 1);
	for (iMember=vMembers.begin(), nRow=1 ; iMember != vMembers.end() ; iMember++, nRow++)
		SetMemberRow (nRow, *iMember);
}
//---------------------------------------------------------------------------
void __fastcall TformMain::gridMembersDblClick(TObject *Sender)
{
	if (actMemberEdit->Enabled)
		actMemberEditExecute(Sender);
}
/*
fprintf (fileUser, "VO39232"
fprintf (fileUser, "ID"
fprintf (fileUser, "2009ABC"
*/
//---------------------------------------------------------------------------
void __fastcall TformMain::Upload (TClassInfo &class_info)
{
	class_info.SourceFile = edtClassFile->Text.Trim();
	class_info.Name = edtClassName->Text;
	class_info.VectorName = edtVector->Text;
	class_info.SqlTable  = edtSqlTable->Text.Trim();
	class_info.MemberTable  = edtMemberTable->Text.Trim();
	UpoadMembers (class_info);
//	strInclude = HeaderFromSrc (strSrc);
}
//---------------------------------------------------------------------------
void __fastcall TformMain::UpoadMembers (TClassInfo &class_info)
{
	int nRow;
	TClassMemberInfo member;
	TMembers vMembers;

	for (nRow=1 ; nRow < gridMembers->RowCount ; nRow++) {
		UploadMemberRow (nRow, member);
		vMembers.push_back (member);
		member.Clear ();
	}
	if (vMembers.size())
		class_info.Members = vMembers;
}
//---------------------------------------------------------------------------
void __fastcall TformMain::UpoadMembers (TMembers &vMembers)
{
	int nRow;
	TClassMemberInfo member;

	vMembers.clear ();
	for (nRow=1 ; nRow < gridMembers->RowCount ; nRow++) {
		if (UploadMemberRow (nRow, member))
			vMembers.push_back (member);
		member.Clear ();
	}
}
//---------------------------------------------------------------------------
void __fastcall TformMain::actMembersAddExecute(TObject */*Sender*/)
{
	TClassMemberInfo class_info;

	class_info.MemberID = GetNextMemberID ();
	if (EditMember (class_info, true)) {
		m_vMembers.push_back (class_info);
		if (gridMembers->RowCount > 2 || !gridMembers->Cells[0][1].IsEmpty())
			gridMembers->RowCount++;
		SetMemberRow (gridMembers->RowCount - 1, class_info);
		m_fChange = true;
	}
}
//---------------------------------------------------------------------------
void __fastcall TformMain::actMemberEditExecute(TObject */*Sender*/)
{
	TClassMemberInfo member;
	int nRow = gridMembers->Row;

	UploadMemberRow (nRow, member);
	if (EditMember (member, false)) {
		SetMemberRow (nRow, member);
		m_fChange = true;
	}
}
//---------------------------------------------------------------------------
void __fastcall DeleteRow (TStringGrid *grid, int nRow)
{
	int r, c;

	for (r=nRow ; r < grid->RowCount-1 ; r++)
		for (c=0 ; c < grid->ColCount ; c++) {
			grid->Cells[c][r] = grid->Cells[c][r+1];
			grid->Objects[c][r] = grid->Objects[c][r+1];
		}
	r = grid->RowCount - 1;
	for (c=0 ; c < grid->ColCount ; c++) {
		grid->Cells[c][r] = "";
		grid->Objects[c][r] = NULL;
	}
	if (grid->RowCount > 2)
		grid->RowCount--;
}
//---------------------------------------------------------------------------
void __fastcall TformMain::actMembersDelExecute(TObject */*Sender*/)
{
	TClassMemberInfo member;
	int nRow = gridMembers->Row;
	String strMsg;

	UploadMemberRow (nRow, member);
	strMsg = "Delete " + member.MemberName + "?";
	if (MessageBox (Handle, strMsg.c_str(), "Confirm Deletion", MB_YESNO | MB_ICONQUESTION | MB_DEFBUTTON2) == IDYES) {
		DeleteRow (gridMembers, gridMembers->Row);
		m_fChange = true;
	}
}
//---------------------------------------------------------------------------
void __fastcall TformMain::SetCaption (TClassInfo &class_info)
{
	String strName;

	strName = class_info.Name;
	if (strName.IsEmpty())
		strName = "no class";
	SetCaption (strName);
}
//---------------------------------------------------------------------------
void __fastcall TformMain::SetCaption (const String &strClassName)
{
	String strCaption, strFile (m_strParamsFile);

	strCaption = m_strCaptionBase + " - " + strClassName + " - " + m_strParamsFile;
	Caption = strCaption;
}
//---------------------------------------------------------------------------
void __fastcall TformMain::edtClassFileChange(TObject */*Sender*/)
{
	m_fChange = true;
}
//---------------------------------------------------------------------------
void __fastcall TformMain::edtClassNameChange(TObject */*Sender*/)
{
	m_fChange = true;
}
//---------------------------------------------------------------------------
void __fastcall TformMain::edtVectorChange(TObject */*Sender*/)
{
	m_fChange = true;
}
//---------------------------------------------------------------------------
void __fastcall TformMain::OnParamClick(TObject */*Sender*/)
{
	m_fChange = true;
}
//---------------------------------------------------------------------------
void __fastcall TformMain::FormCloseQuery(TObject */*Sender*/, bool &CanClose)
{
	int mb;

	CanClose = true;
	if (m_fChange) {
		mb = MessageDlg ("Parameters Changed.\nDiscard changes?", mtConfirmation,
				TMsgDlgButtons() << mbYes << mbNo, 0);
		CanClose = (mb == mrYes);
	}
}
//---------------------------------------------------------------------------
int __fastcall TformMain::GetNextMemberID ()
{
	TClassInfo ci;

	Upload (ci);
	return ((int) (ci.Members.size() + 1));
}
//---------------------------------------------------------------------------
void __fastcall TformMain::actExitExecute(TObject */*Sender*/)
{
	Close ();
}
//---------------------------------------------------------------------------
void __fastcall TformMain::actGenerateExecute(TObject */*Sender*/)
{
	String strSrc, strInclude;
	TClassInfo class_info;

	Upload (class_info);
	class_info.Generate ();
	MessageBeep (MB_OK);
	ShowMessage ("Class Cerated\nYeah!");
}
//---------------------------------------------------------------------------
void __fastcall TformMain::FormClose(TObject */*Sender*/, TCloseAction &/*Action*/)
{
	SaveParamsFile ();
}
//---------------------------------------------------------------------------
void __fastcall TformMain::SaveParamsFile ()
{
	SaveIni (m_strIni, SecParams, IdentParamFile, ExtractFileDir (m_strParamsFile));
}
//---------------------------------------------------------------------------

