//---------------------------------------------------------------------------

#ifndef MainH
#define MainH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ActnCtrls.hpp>
#include <ActnList.hpp>
#include <ActnMan.hpp>
#include <Buttons.hpp>
#include <ImgList.hpp>
#include <Menus.hpp>
#include <ToolWin.hpp>
#include <XPStyleActnCtrls.hpp>
#include <ADODB.hpp>
#include <AppEvnts.hpp>
#include <DB.hpp>
#include <ComCtrls.hpp>
#include <Grids.hpp>
//---------------------------------------------------------------------------
#include "DatasetInfo.h"
#include <Dialogs.hpp>
//---------------------------------------------------------------------------
class TfrmMain : public TForm
{
__published:	// IDE-managed Components
	TMainMenu *MainMenu1;
	TImageList *ImageList1;
	TMenuItem *miFile;
	TMenuItem *miExit;
	TMenuItem *miFileSep1;
	TMenuItem *miConnect;
	TMenuItem *miDisconnect;
	TADOConnection *dbMain;
	TApplicationEvents *ApplicationEvents1;
	TStatusBar *StatusBar1;
	TToolBar *ToolBar1;
	TToolButton *tbtnConnetct;
	TToolButton *tbtnDisconnetct;
	TToolButton *ToolButton1;
	TToolButton *tbtnExit;
	TActionList *ActionList1;
	TAction *actConnect;
	TAction *actDisconnect;
	TAction *actExit;
	TStringGrid *gridDatasets;
	TAction *actDSAdd;
	TAction *actDSEdit;
	TAction *actDSDel;
	TMenuItem *miDatasets;
	TMenuItem *miDSAdd;
	TMenuItem *miDSEdit;
	TMenuItem *miDSDel;
	TMenuItem *miDSSep1;
	TToolButton *ToolButton2;
	TToolButton *ToolButton3;
	TToolButton *ToolButton4;
	TToolButton *ToolButton5;
	TTreeView *TreeView1;
	TBitBtn *bitbtnImport;
	TAction *actChangeUDL;
	TMenuItem *miChangeUDL;
	TMenuItem *miFileSep2;
	TToolButton *tbtnChangeUDL;
	TOpenDialog *dlgSelectUDL;
	TToolButton *ToolButton6;
	TMenuItem *miShowContent;
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall actExitExecute(TObject *Sender);
	void __fastcall actConnectExecute(TObject *Sender);
	void __fastcall OnIdle(TObject *Sender, bool &Done);
	void __fastcall actDisconnectExecute(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall actDSAddExecute(TObject *Sender);
	void __fastcall actDSEditExecute(TObject *Sender);
	void __fastcall actDSDelExecute(TObject *Sender);
	void __fastcall gridDatasetsDblClick(TObject *Sender);
	void __fastcall bitbtnImportClick(TObject *Sender);
	void __fastcall actChangeUDLExecute(TObject *Sender);
	void __fastcall miShowContentClick(TObject *Sender);
private:	// User declarations
	String m_strCaption;
	String m_strErr;
	String m_strAppRegRoot;
	String m_strUDL;
protected:	// User declarations
	String __fastcall InitRegRoot ();
	String __fastcall GetAppRegRoot () const;
	int __fastcall UploadDatasetID ();
	void __fastcall DownloadDatasete ();
	void __fastcall ConnectToDB ();
	void __fastcall DownloadDatasets (TDatases &vSet);
	bool __fastcall EditDataset (TDatasetInfo &dataset);
	void __fastcall DownloadNewDataset (TDatasetInfo &dataset);
	void __fastcall Download (TDatasetInfo &dataset, int nRow);
	void __fastcall InitDatasetsGrid ();
	void __fastcall Disconect ();
	void __fastcall UpdateActions ();
	void __fastcall UpdateStatusBar ();
public:		// User declarations
	__fastcall TfrmMain(TComponent* Owner);
	__property String AppRegRoot = {read=GetAppRegRoot};
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmMain *frmMain;
//---------------------------------------------------------------------------
#endif
