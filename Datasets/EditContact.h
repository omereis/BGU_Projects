//----------------------------------------------------------------------------
#ifndef EditContactH
#define EditContactH
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
#include "ContactInfo.h"
//----------------------------------------------------------------------------
class TdlgContact : public TForm
{
__published:
	TLabel *Label8;
	TLabel *Label9;
	TLabel *Label10;
	TLabel *Label1;
	TEdit *edtName;
	TEdit *edtPhone;
	TEdit *edtEmail;
	TEdit *edtComments;
	TBitBtn *bitbtnOK;
	TBitBtn *bitbtnCancel;
	TPanel *panelID;
private:
protected:
	void __fastcall Upload (TContactInfo &contact);
	void __fastcall Download (const TContactInfo &contact);
public:
	bool __fastcall Execute (TContactInfo &contact);
	virtual __fastcall TdlgContact(TComponent* AOwner);
};
//----------------------------------------------------------------------------
extern PACKAGE TdlgContact *dlgContact;
//----------------------------------------------------------------------------
#endif    
