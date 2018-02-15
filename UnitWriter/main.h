//---------------------------------------------------------------------------

#ifndef mainH
#define mainH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Menus.hpp>
#include <Dialogs.hpp>
#include <ExtCtrls.hpp>
#include <AppEvnts.hpp>
#include <ActnList.hpp>
#include <ComCtrls.hpp>
#include <Grids.hpp>
#include <ToolWin.hpp>
//---------------------------------------------------------------------------
#include "ClassMemberInfo.h"
#include <ImgList.hpp>
#include <inifiles.hpp>
#include "ClassInfo.h"
#include <Buttons.hpp>
//---------------------------------------------------------------------------
class TformMain : public TForm
{
__published:	// IDE-managed Components
	TMainMenu *MainMenu1;
	TMenuItem *miFile;
	TMenuItem *miExit;
	TMenuItem *miOpen;
	TMenuItem *miFilesSep1;
	TMenuItem *miSave;
	TMenuItem *miSaveAs;
	TMenuItem *miClass;
	TMenuItem *miAddMember;
	TMenuItem *miEditMember;
	TMenuItem *miClassSep1;
	TMenuItem *miDelMember;
	TMenuItem *miMembers;
	TLabel *Label1;
	TEdit *edtClassName;
	TLabel *Label2;
	TEdit *edtClassFile;
	TButton *btnBrowse;
	TSaveDialog *dlgSaveClass;
	TGroupBox *GroupBox1;
	TCheckBox *cboxDefCtor;
	TCheckBox *cboxCopyCtor;
	TCheckBox *cboxDtor;
	TCheckBox *cboxClear;
	TCheckBox *cboxAssignAll;
	TCheckBox *cboxEq;
	TCheckBox *cboxUneq;
	TCheckBox *cboxAssign;
	TCheckBox *cboxVector;
	TCheckBox *cboxDatabase;
	TEdit *edtVector;
	TLabel *Label3;
	TApplicationEvents *ApplicationEvents1;
	TButton *btnOptsDefs;
	TStringGrid *gridMembers;
	TToolBar *ToolBar1;
	TActionList *ActionList1;
	TOpenDialog *dlgOpenParams;
	TAction *actOpen;
	TImageList *ImageList1;
	TAction *actSave;
	TToolButton *ToolButton1;
	TToolButton *ToolButton2;
	TToolButton *ToolButton3;
	TAction *actSaveAs;
	TStatusBar *StatusBar1;
	TSaveDialog *dlgSaveParams;
	TMenuItem *miClear;
	TToolButton *ToolButton4;
	TToolButton *ToolButton5;
	TAction *actGenerate;
	TAction *actMembersAdd;
	TToolButton *ToolButton6;
	TToolButton *ToolButton7;
	TAction *actMemberEdit;
	TToolButton *ToolButton8;
	TAction *actMembersDel;
	TToolButton *ToolButton9;
	TBitBtn *bitbtnGenerate;
	TPanel *panelDBParams;
	TEdit *edtSqlTable;
	TEdit *edtMemberTable;
	TLabel *Label4;
	TLabel *Label5;
	TAction *actExit;
	TToolButton *ToolButton10;
	TToolButton *ToolButton11;
	TAction *actNew;
	TMenuItem *miNew;
	TMenuItem *miFileSep2;
	TToolButton *tbtnNew;
	TToolButton *ToolButton12;
	void __fastcall OnIdle(TObject *Sender, bool &Done);
	void __fastcall actOpenExecute(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall actSaveAsExecute(TObject *Sender);
	void __fastcall btnBrowseClick(TObject *Sender);
	void __fastcall miClearClick(TObject *Sender);
	void __fastcall actSaveExecute(TObject *Sender);
	void __fastcall gridMembersDblClick(TObject *Sender);
	void __fastcall actMembersAddExecute(TObject *Sender);
	void __fastcall actMemberEditExecute(TObject *Sender);
	void __fastcall actMembersDelExecute(TObject *Sender);
	void __fastcall edtClassFileChange(TObject *Sender);
	void __fastcall edtClassNameChange(TObject *Sender);
	void __fastcall edtVectorChange(TObject *Sender);
	void __fastcall OnParamClick(TObject *Sender);
	void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
	void __fastcall actExitExecute(TObject *Sender);
	void __fastcall actGenerateExecute(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall actNewExecute(TObject *Sender);
private:	// User declarations
	TMembers m_vMembers;
	String m_strParamsFile;
	bool m_fChange;
	String m_strCaptionBase;
	String m_strIni;
protected:	// User declarations
	void __fastcall SaveParamsFile ();
	void __fastcall AssembleIniFileName ();
	int __fastcall GetNextMemberID ();
	void __fastcall SetCaption (const String &strClassName);
	void __fastcall SetCaption (TClassInfo &class_info);
	void __fastcall Download (TClassInfo &class_info);
	void __fastcall UpoadMembers (TMembers &vMembers);
	void __fastcall UpoadMembers (TClassInfo &class_info);
	void __fastcall Upload (TClassInfo &class_info);
	void __fastcall DownloadMembers (const TMembers &vMembers);
	void __fastcall Clear();
	void __fastcall SaveToFile (const String &strFile);
	void __fastcall InitMembersGrid ();
	bool __fastcall UploadMemberRow (int nRow, TClassMemberInfo &member);
	void __fastcall SetMemberRow (int nRow, const TClassMemberInfo &class_info);
	bool __fastcall EditMember (TClassMemberInfo &member, bool fNew);

	static int ColMemberID;
	static int ColName;
	static int ColPropertyName;
	static int ColType;
	static int ColClear;
	static int ColSqlTable;
	static int ColVarTable;
public:		// User declarations
	__fastcall TformMain(TComponent* Owner);
	void __fastcall AddAndNew (TClassMemberInfo &class_info);

	static String SecParams;
	static String IdentParamFile;
};
//---------------------------------------------------------------------------
extern PACKAGE TformMain *formMain;
//---------------------------------------------------------------------------
#endif
