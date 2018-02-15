//----------------------------------------------------------------------------
#ifndef EditListH
#define EditListH
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
#include "IDStr.h"
#include <AppEvnts.hpp>
//----------------------------------------------------------------------------
class TdlgEditList : public TForm
{
__published:
	TBitBtn *bitbtnOK;
	TBitBtn *bitbtnCancel;
	TListBox *lstItems;
	TBitBtn *bitbtnAdd;
	TBitBtn *bitbtnEdit;
	TBitBtn *bitbtnDel;
	TLabel *lblTitle;
	TApplicationEvents *ApplicationEvents1;
	void __fastcall bitbtnAddClick(TObject *Sender);
	void __fastcall bitbtnEditClick(TObject *Sender);
	void __fastcall OnIdle(TObject *Sender, bool &Done);
	void __fastcall bitbtnDelClick(TObject *Sender);
private:
	void Download (TIDStrings &list, const String &strTitle);
	void Download (TIDStrings &list);
	void Download (const String &strTitle);
	void Upload (TIDStrings &list);
public:
	virtual __fastcall TdlgEditList(TComponent* AOwner);
	bool Execute (TIDStrings &list, const String &strTitle);
};
//----------------------------------------------------------------------------
extern PACKAGE TdlgEditList *dlgEditList;
//----------------------------------------------------------------------------
#endif
