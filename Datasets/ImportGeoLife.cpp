//---------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "ImportGeoLife.h"
#include "Main.h"
#include <Registry.hpp>
#include "Misc.h"
#include "time.h"
//---------------------------------------------------------------------
#pragma link "cgauges"
#pragma resource "*.dfm"
TdlgImportGeoLife *dlgImportGeoLife;
String TdlgImportGeoLife::GeoConvert ("Geo Life Conversion");
String TdlgImportGeoLife::DatasetPath ("Dataset Path");
//---------------------------------------------------------------------
__fastcall TdlgImportGeoLife::TdlgImportGeoLife(TComponent* AOwner)
	: TForm(AOwner)
{
	m_query = NULL;
	m_LastObj = -1;
	formShowProgress = NULL;
}
//---------------------------------------------------------------------
__fastcall TdlgImportGeoLife::~TdlgImportGeoLife()
{
	if (m_query != NULL) {
		delete m_query;
	}
	if (formShowProgress != NULL) {
		delete formShowProgress;
	}
}
//---------------------------------------------------------------------
bool __fastcall TdlgImportGeoLife::Execute (TADOConnection *db, int nDatasetID)
{
	Download (db, nDatasetID);
	ShowModal ();
	return (ModalResult == mrOk);
}
//---------------------------------------------------------------------
void __fastcall TdlgImportGeoLife::Download (TADOConnection *db, int nDatasetID)
{
	m_db = db;
	m_query = InitQuery (db, this);
	m_nDatasetID = nDatasetID;
	edtRootDir->Text = DirectoryListBox1->Directory;
}
//---------------------------------------------------------------------
void __fastcall TdlgImportGeoLife::DirectoryListBox1Change(TObject *Sender)
{
	edtRootDir->Text = DirectoryListBox1->Directory;
}
//---------------------------------------------------------------------------
void __fastcall TdlgImportGeoLife::OnIdle(TObject *Sender, bool &Done)
{
	bitbtnFind->Enabled = DirectoryExists (edtRootDir->Text.Trim());
	Panel2->Caption = String (FileListBox1->Count);
	Panel3->Caption = String (lboxRoutes->Items->Count);
}
//---------------------------------------------------------------------------
void __fastcall FindFilesFromRoot (const String &strDir, TStringList *lstr)
{
	TSearchRec sr;
	int iAttr;
	static bool fDir;
	String str, strFilter, strExt;

	iAttr = faDirectory | faAnyFile;
	strFilter = strDir + "\\*.*";
	if (FindFirst (strFilter, iAttr, sr) == 0) {
		do {
			if ((sr.Name != ".") && (sr.Name != "..")) {
				str = strDir + "\\" + sr.Name;
				iAttr = sr.Attr;
				if ((sr.Attr & 0x10) != false) {
					FindFilesFromRoot (str, lstr);
				}
				else {
					strExt = ExtractFileExt (str).LowerCase ();
					if (strExt == ".plt")
						lstr->Add (str);
				}
			}
		} while (FindNext (sr) == 0);
		FindClose (sr);
	}
}
//---------------------------------------------------------------------------
void __fastcall TdlgImportGeoLife::bitbtnFindClick(TObject *Sender)
{
	TCursor cr = Screen->Cursor;
	TStringList *lstr;

	try {
		lboxFiles->Items->Clear();
		lstr = new TStringList;
		Screen->Cursor = crHourGlass;
		String strDir = edtRootDir->Text;
		FindFilesFromRoot (strDir, lstr);
		lboxFiles->Items->BeginUpdate();
		lboxFiles->Items->Assign(lstr);
		lboxFiles->Items->EndUpdate();
		ShowMessage (String (lstr->Count) + " items");
		Panel1->Caption = lboxFiles->Items->Count;
	}
	__finally {
		Screen->Cursor = cr;
		delete lstr;
	}
}
//---------------------------------------------------------------------------
String __fastcall ExtractObjName (const String &strRoot, const String &strFile)
{
	int nPos;
	String strObj;

	nPos = strFile.Pos (strRoot);
	strObj = strFile.SubString (strRoot.Length() + 2, strFile.Length());
	nPos = strObj.Pos ("\\");
	strObj = strObj.SubString(1, nPos - 1);
	return (strObj);
}
//---------------------------------------------------------------------------
void __fastcall TdlgImportGeoLife::InsertPoints (const String &strRoot, TStringList *lstr)
{
	int n, idx;
	String strObj;
	TDatasetObj ds_obj;

	m_vRoutes.clear ();
	for (n=0 ; n < lstr->Count ; n++) {
		ds_obj.Clear ();
		strObj = ExtractObjName (strRoot, lstr->Strings[n]);
		ds_obj.ObjName = strObj;
		ds_obj.DatasetID = m_nDatasetID;
		ds_obj.LoadIdByDsAndName (m_query, m_strErr);
		if (ds_obj.ObjID == 0) {
			ds_obj.InsertAndUpdate (m_query, m_strErr);
			idx = lboxObjs->Items->IndexOfObject ((TObject*) ds_obj.ObjID);
			if (idx < 0)
				lboxObjs->Items->AddObject (ds_obj.ObjName, (TObject*) ds_obj.ObjID);
			InsertRoute (ds_obj, lstr->Strings[n]);
		}
	}
}
//---------------------------------------------------------------------------
String __fastcall ExtractRouteName (const String &strFile)
{
	String str;

	str = ExtractFileName (strFile);
	return (str);
}
//---------------------------------------------------------------------------
void __fastcall TdlgImportGeoLife::InsertRoute (const TDatasetObj &ds_obj, const String &strFile)
{
	TRouteInfo route;
	String strRoute = ExtractRouteName (strFile);

	route.RouteName = ds_obj.ObjName + "_" + strRoute;
	route.ObjectID = ds_obj.ObjID;
	route.FindByNameAndObj (m_query, m_strErr);
	if (route.RouteID == 0)
		route.InsertAndUpdate (m_query, m_strErr);
	m_vRoutes.push_back (route);
}
//---------------------------------------------------------------------------
clock_t g_cPoints;
void __fastcall TdlgImportGeoLife::btnInsObjsClick(TObject *Sender)
{
	TCursor cr = Screen->Cursor;
	TDatasetObjects::iterator iObj;
	int n, nFiles;
	String str;
	clock_t cStart, cEnd;

	cStart = clock ();
	timerUpdateGui->Enabled = true;
	Screen->Cursor = crHourGlass;
	lboxObjs->Items->Clear ();
	if (m_vObjs.DeleteFromDB (m_query, m_strErr)) {
		nFiles = ParseObjects (m_vObjs);
		InitShowForm (nFiles);
		for (m_nInsertCounter=0, iObj=m_vObjs.begin() ; iObj != m_vObjs.end() ; iObj++) {
			iObj->DatasetID = m_nDatasetID;
			m_strCurrentObj = iObj->ObjName;
			if (iObj->InsertAndUpdate (m_query, m_strErr)) {
				iObj->InsertRoutes (m_query, m_strErr, this);
			}
		}
		EndFormShow ();
	}
	Screen->Cursor = cr;
	timerUpdateGui->Enabled = false;
	cEnd = clock ();
	double dTotal, dPoints;
	dTotal = (double) (cEnd - cStart) / (double) CLK_TCK;
	dPoints = (double) (g_cPoints) / (double) CLK_TCK;
	Panel6->Caption = "Total Time: " + String (dTotal);
	Panel7->Caption = "Points Time: " + String (dPoints) + ", (" + FormatFloat ("0.##", 100.0 * dPoints / dTotal) + "%)";
}
//---------------------------------------------------------------------------
void __fastcall TdlgImportGeoLife::InitShowForm (int nFiles)
{
	formShowProgress = new TfrmShowProgress (this);
	formShowProgress->Parent = this;
	formShowProgress->Show();
	formShowProgress->SetMax (nFiles);
}
//---------------------------------------------------------------------------
void __fastcall TdlgImportGeoLife::EndFormShow ()
{
	delete formShowProgress;
	formShowProgress = NULL;
}
//---------------------------------------------------------------------------
int __fastcall TdlgImportGeoLife::ParseObjects (TDatasetObjects &vObjs)
{
	TDatasetObjects::iterator iObj;
	TStringList *lstr = new TStringList;
	TDatasetObj d_obj;
	int n, nFiles;
	String str, strRoute;

	vObjs.clear();
	FindFilesFromRoot (edtRootDir->Text, lstr);
	lstr->Sort();
	nFiles = lstr->Count;
	for (n=0 ; n < lstr->Count ; n++) {
		str = d_obj.ParseObjNameFromPath (lstr->Strings[n], strRoute);
		if (str == d_obj.ObjName) {
			d_obj.AddRoute (lstr->Strings[n], strRoute);
		}
		else if (d_obj.ObjName.Length() > 0) {
			vObjs.push_back (d_obj);
			d_obj.Clear ();
			d_obj.ObjName = str;
			d_obj.AddRoute (lstr->Strings[n], strRoute);
		}
		else {
			d_obj.ObjName = str;
			d_obj.AddRoute (lstr->Strings[n], strRoute);
		}
	}
	if (d_obj.ObjName.Length() > 0)
		vObjs.push_back (d_obj);
	for (iObj=vObjs.begin() ; iObj != vObjs.end() ; iObj++) {
		lboxObjs->Items->Add (iObj->ObjName);
	}
	return (nFiles);
}
//---------------------------------------------------------------------------
void __fastcall TdlgImportGeoLife::lboxFilesDblClick(TObject *Sender)
{
	String str;

	str = ExtractObjName (edtRootDir->Text, lboxFiles->Items->Strings[lboxFiles->ItemIndex]) + ", " + String (lboxFiles->ItemIndex);
	Panel1->Caption = str;
}
//---------------------------------------------------------------------------
void __fastcall TdlgImportGeoLife::ShowRoutes ()
{
	int idx, nObj;
	TDatasetObjects::iterator iObj;
	TRoutes::iterator iRoute;
	TRoutes vRoutes;
	String strObjName;

	if (lboxObjs->Items->Count > 0) {
		idx = max (0, lboxObjs->ItemIndex);
		strObjName = lboxObjs->Items->Strings[idx];
		if ((iObj = m_vObjs.FindByName (strObjName)) != NULL) {
			lboxRoutes->Items->Clear ();
			vRoutes = iObj->Routes;
			for (iRoute=vRoutes.begin() ; iRoute != vRoutes.end() ; iRoute++) {
				lboxRoutes->Items->Add (iRoute->RouteName);
			}
		}
	}
}
//---------------------------------------------------------------------------
void __fastcall TdlgImportGeoLife::btnLoadObjectsClick(TObject *Sender)
{
	TDatasetObjects vObjs;
	TDatasetObjects::iterator iObj;

	lboxObjs->Items->Clear ();
	if (vObjs.LoadFromDB (m_query, m_strErr)) {
		for (iObj=vObjs.begin() ; iObj != vObjs.end() ; iObj++) {
			lboxObjs->Items->AddObject (iObj->ObjName, (TObject*) iObj->ObjID);
		}
	}

}
//---------------------------------------------------------------------------
void __fastcall TdlgImportGeoLife::btnShowRoutesClick(TObject *Sender)
{
	ShowRoutes ();
}
//---------------------------------------------------------------------------

void __fastcall TdlgImportGeoLife::Panel2Click(TObject *Sender)
{
//DriveComboBox1->Drive
//DirectoryListBox1->Path
}
//---------------------------------------------------------------------------
void __fastcall TdlgImportGeoLife::SaveDatasetPath ()
{
	TfrmMain *frmMain;
	String strKey, strPath, strSection, strIdent;
	TRegistry *reg = new TRegistry;

	try {
		reg->RootKey = HKEY_CURRENT_USER;
		frmMain = (TfrmMain *) Application->MainForm;
		strKey = frmMain->AppRegRoot + "\\" + GeoConvert;
		strPath = edtRootDir->Text;
//		strPath = DirectoryListBox1->Directory;
//		if (!reg->KeyExists (strKey)) {
			if (reg->OpenKey (strKey, true)) {
				reg->WriteString (DatasetPath, strPath);
				reg->CloseKey ();
			}
//		}
	}
	__finally {
		delete reg;
	}
}
//---------------------------------------------------------------------------
void __fastcall TdlgImportGeoLife::LoadDatasetPath ()
{
	TfrmMain *frmMain;
	String strKey, strPath, str;
	TRegistry *reg = new TRegistry;
	char cDrive;

	try {
		reg->RootKey = HKEY_CURRENT_USER;
		frmMain = (TfrmMain *) Application->MainForm;
		strKey = frmMain->AppRegRoot + "\\" + GeoConvert;
		if (reg->KeyExists (strKey)) {
			if (reg->OpenKey (strKey, true)) {
				strPath = reg->ReadString (DatasetPath);
				DirectoryListBox1->Directory =  strPath;
			reg->CloseKey ();
			}
		}
	}
	__finally {
		delete reg;
	}
}
//---------------------------------------------------------------------------
void __fastcall TdlgImportGeoLife::FormCreate(TObject *Sender)
{
	LoadDatasetPath ();
}
//---------------------------------------------------------------------------
void __fastcall TdlgImportGeoLife::FormClose(TObject *Sender,
	  TCloseAction &Action)
{
	if (ModalResult == mrOk) {
		SaveDatasetPath ();
	}
}
//---------------------------------------------------------------------------
void __fastcall TdlgImportGeoLife::UpdateGUI()
{
	formShowProgress->SetProgress (m_nInsertCounter++);
	if ((m_nInsertCounter % 10) == 0) {
		formShowProgress->UpdateGUI ("Inserting " + m_strCurrentObj);
	}
}
//---------------------------------------------------------------------------
void __fastcall TdlgImportGeoLife::timerUpdateGuiTimer(TObject *Sender)
{
	static bool fBusy = false;

	if (fBusy != false) {
		fBusy = true;
		if (formShowProgress != NULL)
        	formShowProgress->UpdateGUI ();
		fBusy = false;
	}
}
//---------------------------------------------------------------------------

