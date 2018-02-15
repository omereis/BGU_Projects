//----------------------------------------------------------------------------
#ifndef EditDatasetH
#define EditDatasetH
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
//----------------------------------------------------------------------------
#include "DatasetInfo.h"
#include <AppEvnts.hpp>
//----------------------------------------------------------------------------
class TdlgEditDataset : public TForm
{
__published:
	TBitBtn *bitbtnOK;
	TBitBtn *bitbtnCancel;
	TLabel *Label1;
	TLabel *Label2;
	TLabel *Label3;
	TLabel *Label4;
	TLabel *Label5;
	TLabel *Label6;
	TEdit *edtName;
	TEdit *edtURL;
	TEdit *edtUsername;
	TEdit *edtPasswors;
	TMemo *memoStructure;
	TEdit *edtDescription;
	TGroupBox *GroupBox1;
	TListBox *lboxContacts;
	TBitBtn *bitbtnAdd;
	TBitBtn *bitbtnEdit;
	TBitBtn *bitbtnDel;
	TPanel *panelID;
	TEdit *edtOrg;
	TLabel *Label7;
	TButton *btnURLTest;
	TPanel *panelChars;
	TApplicationEvents *ApplicationEvents1;
	TLabel *Label8;
	TComboBox *comboType;
	void __fastcall btnURLTestClick(TObject *Sender);
	void __fastcall OnIdle(TObject *Sender, bool &Done);
	void __fastcall FormCreate(TObject *Sender);
private:
protected:
	void __fastcall DownloadType (TDatasetInfo &dataset);
	void __fastcall Download (TDatasetInfo &dataset);
	void __fastcall Upload (TDatasetInfo &dataset);
public:
	virtual __fastcall TdlgEditDataset(TComponent* AOwner);
	bool __fastcall Execute (TDatasetInfo &dataset);
};
//----------------------------------------------------------------------------
extern PACKAGE TdlgEditDataset *dlgEditDataset;
//----------------------------------------------------------------------------
#endif    
