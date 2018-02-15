//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Main.h"
#include "EditDataset.h"
#include "Misc.h"
#include "ImportGeoLife.h"
#include <FileCtrl.hpp>
#include "EditContent.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfrmMain *frmMain;
static String DBFileName ("FILE NAME=");
//---------------------------------------------------------------------------
__fastcall TfrmMain::TfrmMain(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
String __fastcall ExtractUDL (const String &strConnectionString)
{
	int nPos;
	String strSub, strUDL;

	nPos = strConnectionString.Pos (DBFileName);
	if (nPos > 0) {
		strSub = strConnectionString.SubString (nPos + DBFileName.Length(), strConnectionString.Length());
		strUDL = ExtractFileName (strSub);
	}
	return (strUDL);
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::FormCreate(TObject *Sender)
{
	m_strUDL = ExtractUDL (dbMain->ConnectionString);
	m_strCaption = Caption;
	InitRegRoot ();
	InitDatasetsGrid ();
	ConnectToDB ();
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::actExitExecute(TObject *Sender)
{
	Close ();
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::ConnectToDB ()
{
	TCursor cr = Screen->Cursor;
	Screen->Cursor = crHourGlass;
	try {
		try {
			dbMain->Connected = true;
			DownloadDatasete ();
		} catch (Exception &e) {
			ShowMessage ("Error connecting to database:\n" + e.Message);
		}
	}
	__finally {
		Screen->Cursor = cr;
	}
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::actConnectExecute(TObject *Sender)
{
	ConnectToDB ();
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::actDisconnectExecute(TObject *Sender)
{
	Disconect ();
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::OnIdle(TObject *Sender, bool &Done)
{
	UpdateActions ();
	UpdateStatusBar ();
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::UpdateActions ()
{
	bool fConnected = dbMain->Connected;

	actConnect->Enabled = fConnected == false;
	actDisconnect->Enabled = fConnected == true;
	actDSAdd->Enabled = fConnected;
	actDSEdit->Enabled = fConnected;
	actDSDel->Enabled = fConnected;
	actChangeUDL->Enabled = !fConnected;
	miShowContent->Enabled = fConnected;
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::Disconect ()
{
	dbMain->Connected = false;
	PurgeGrid (gridDatasets);
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::FormClose(TObject *Sender, TCloseAction &Action)
{
	if (dbMain->Connected)
		Disconect ();
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::UpdateStatusBar ()
{
	String str;

	str = dbMain->Connected ? "Conected" : "Disconnected";
	StatusBar1->Panels[0].Items[0]->Text = str;
	StatusBar1->Panels[0].Items[1]->Text = m_strUDL;
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::InitDatasetsGrid ()
{
	gridDatasets->Cells[0][0] = "Name";
	gridDatasets->Cells[1][0] = "Description";
	gridDatasets->Cells[2][0] = "URL";
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::actDSAddExecute(TObject *Sender)
{
	TDatasetInfo dataset;
	bool fNew = false;

	if (dataset.InsertAsNew (dbMain, m_strErr)) {
		if (EditDataset (dataset)) {
			if (dataset.UpdateInDB (dbMain, m_strErr)) {
				fNew = true;
			}
		}
	}
	if (fNew) {
		DownloadNewDataset (dataset);
	}
	else
		dataset.DeleteInDB (dbMain, m_strErr);
	if (m_strErr.Length() > 0) {
		ShowMessage (m_strErr);
	}
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::actDSEditExecute(TObject *Sender)
{
	TDatasetInfo dataset;

	dataset.DatasetID = UploadDatasetID ();
	if (dataset.LoadByID (dbMain, m_strErr))
		if (EditDataset (dataset))
			if (dataset.UpdateInDB (dbMain, m_strErr))
				Download (dataset, gridDatasets->Row);
}
//---------------------------------------------------------------------------
int __fastcall TfrmMain::UploadDatasetID ()
{
	int id;

	id = (int) gridDatasets->Objects[0][gridDatasets->Row];
	return (id);
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::actDSDelExecute(TObject *Sender)
{
	TDatasetInfo dataset;

	dataset.DatasetID = UploadDatasetID ();
	if (dataset.LoadByID (dbMain, m_strErr))
		if (dataset.ConfirmDeletion ()) {
			if (dataset.DeleteInDB (dbMain, m_strErr))
				DeleteLine (gridDatasets, gridDatasets->Row);
		}
}
//---------------------------------------------------------------------------
int __fastcall GetNextEmptyRow (TStringGrid *grid)
{
	bool fNew = true;

	if (grid->RowCount == 2) {
		if (grid->Objects[0][1] == NULL) {
			fNew = false;
		}
	}
	if (fNew) {
		grid->RowCount++;
	}
	return (grid->RowCount - 1);
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::DownloadNewDataset (TDatasetInfo &dataset)
{
	int nRow;

	nRow = GetNextEmptyRow (gridDatasets);
	Download (dataset, nRow);
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::Download (TDatasetInfo &dataset, int nRow)
{
	gridDatasets->Cells[0][nRow] = dataset.Name;
	gridDatasets->Cells[1][nRow] = dataset.Description;
	gridDatasets->Cells[2][nRow] = dataset.URL;
	gridDatasets->Objects[0][nRow] = (TObject*) dataset.DatasetID;
}
//---------------------------------------------------------------------------
bool __fastcall TfrmMain::EditDataset (TDatasetInfo &dataset)
{
	TdlgEditDataset *dlg = new TdlgEditDataset (this);
	bool f;

	f = dlg->Execute (dataset);
	delete dlg;
	return (f);
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::DownloadDatasete ()
{
	TDatases vSet;

	if (vSet.LoadFromDB (dbMain, m_strErr))
		DownloadDatasets (vSet);
	else
		ShowMessage ("Error loading datasets:\n" + m_strErr);
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::DownloadDatasets (TDatases &vSet)
{
	TDatases::iterator iSet;
	int nRow;

	PurgeGrid (gridDatasets);
	if (vSet.size() > 0) {
		gridDatasets->RowCount = vSet.size() + 1;
		for (iSet=vSet.begin(), nRow=1 ; iSet != vSet.end() ; iSet++, nRow++) {
			Download (*iSet, nRow);
		}

	}

}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::gridDatasetsDblClick(TObject *Sender)
{
	if (actDSEdit->Enabled) {
        actDSEdit->OnExecute (Sender);
	}
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::bitbtnImportClick(TObject *Sender)
{
	TdlgImportGeoLife *dlg = new TdlgImportGeoLife (this);
#ifndef	_DEBUG
	dbMain->BeginTrans ();
#endif
	bool f = dlg->Execute (dbMain, UploadDatasetID ());
	delete dlg;
#ifndef	_DEBUG
	if (f) {
		ShowMessage ("Commited");
		dbMain->CommitTrans ();
	}
	else
		dbMain->RollbackTrans ();
#endif
/*	String strDir;

	if (SelectDirectory("Select Dataset Source", ".", strDir, TSelectDirExtOpts () << sdShowEdit))
		ShowMessage ("Selected folder:\n" + strDir);
*/
}
//---------------------------------------------------------------------------
String __fastcall TfrmMain::GetAppRegRoot () const
{
	return (m_strAppRegRoot);
}
//---------------------------------------------------------------------------
String __fastcall TfrmMain::InitRegRoot ()
{
	m_strAppRegRoot = "Software\\BGU Lab #8\\Data Mining Dataset";
	return (m_strAppRegRoot);
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::actChangeUDLExecute(TObject *Sender)
{
	if (dlgSelectUDL->Execute()) {
		dbMain->ConnectionString = DBFileName + dlgSelectUDL->FileName;
		m_strUDL = ExtractFileName (dlgSelectUDL->FileName);
	}
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::miShowContentClick(TObject *Sender)
{
	TdlgContent *dlg = new TdlgContent (this);
	dlg->Execute (dbMain, UploadDatasetID ());
	delete dlg;
}
//---------------------------------------------------------------------------

