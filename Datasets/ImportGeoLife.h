//----------------------------------------------------------------------------
#ifndef ImportGeoLifeH
#define ImportGeoLifeH
//----------------------------------------------------------------------------
#include <vcl\ExtCtrls.hpp>
#include <vcl\Buttons.hpp>
#include <vcl\StdCtrls.hpp>
#include <vcl\Controls.hpp>
#include <vcl\Forms.hpp>
#include <vcl\Graphics.hpp>
#include <vcl\Classes.hpp>
#include <vcl\SysUtils.hpp>
#include <vcl\Windows.hpp>
#include <vcl\System.hpp>
#include <FileCtrl.hpp>
#include "DBMisc.h"
#include "DatasetInfo.h"
#include <AppEvnts.hpp>
//----------------------------------------------------------------------------
#include "DatasetObj.h"
#include "RouteInfo.h"
#include "cgauges.h"
#include "ShowProgress.h"
//----------------------------------------------------------------------------
class TdlgImportGeoLife : public TForm
{
__published:
	TBitBtn *bitbtnOK;
	TBitBtn *bitbtnCancel;
	TDriveComboBox *DriveComboBox1;
	TDirectoryListBox *DirectoryListBox1;
	TBitBtn *bitbtnSelDir;
	TEdit *edtRootDir;
	TBitBtn *bitbtnFind;
	TApplicationEvents *ApplicationEvents1;
	TFileListBox *FileListBox1;
	TListBox *lboxFiles;
	TPanel *Panel1;
	TButton *btnInsObjs;
	TListBox *lboxObjs;
	TListBox *lboxRoutes;
	TLabel *Label1;
	TLabel *Label2;
	TButton *btnLoadObjects;
	TButton *btnShowRoutes;
	TPanel *Panel2;
	TPanel *Panel3;
	TPanel *Panel6;
	TPanel *Panel7;
	TTimer *timerUpdateGui;
	void __fastcall DirectoryListBox1Change(TObject *Sender);
	void __fastcall OnIdle(TObject *Sender, bool &Done);
	void __fastcall bitbtnFindClick(TObject *Sender);
	void __fastcall btnInsObjsClick(TObject *Sender);
	void __fastcall lboxFilesDblClick(TObject *Sender);
	void __fastcall btnLoadObjectsClick(TObject *Sender);
	void __fastcall btnShowRoutesClick(TObject *Sender);
	void __fastcall Panel2Click(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall timerUpdateGuiTimer(TObject *Sender);
private:
	TADOConnection *m_db;
	TADOQuery *m_query;
	String m_strErr;
	int m_nDatasetID;
	TRoutes m_vRoutes;
	int m_LastObj;
	int m_nInsertCounter;
	TDatasetObjects m_vObjs;
	TfrmShowProgress *formShowProgress;
	String m_strCurrentObj;
protected:
	void __fastcall InitShowForm (int nFiles);
	void __fastcall EndFormShow ();
	int __fastcall ParseObjects (TDatasetObjects &vObjs);
	void __fastcall ShowRoutes ();
	void __fastcall InsertRoute (const TDatasetObj &ds_obj, const String &strFile);
	void __fastcall InsertPoints (const String &strRoot, TStringList *lstr);
	void __fastcall Download (TADOConnection *db, int nDatasetID);
	void __fastcall LoadDatasetPath ();
	void __fastcall SaveDatasetPath ();
public:
	static String GeoConvert;
	static String DatasetPath;
	virtual __fastcall ~TdlgImportGeoLife();
	virtual __fastcall TdlgImportGeoLife(TComponent* AOwner);
	bool __fastcall Execute (TADOConnection *db, int nDatasetID);
	void __fastcall UpdateGUI();
};
//----------------------------------------------------------------------------
extern PACKAGE TdlgImportGeoLife *dlgImportGeoLife;
//----------------------------------------------------------------------------
#endif
