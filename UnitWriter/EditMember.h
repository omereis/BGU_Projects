//----------------------------------------------------------------------------
#ifndef EditMemberH
#define EditMemberH
//----------------------------------------------------------------------------
#include <vcl\System.hpp>
#include <vcl\Windows.hpp>
#include <vcl\SysUtils.hpp>
#include <vcl\Classes.hpp>
#include <vcl\Graphics.hpp>
#include <vcl\StdCtrls.hpp>
#include <vcl\Forms.hpp>
#include <vcl\Controls.hpp>
#include <vcl\Buttons.hpp>
#include <vcl\ExtCtrls.hpp>
//----------------------------------------------------------------------------
#include "ClassMemberInfo.h"
//----------------------------------------------------------------------------
class TdlgEditMember : public TForm
{
__published:
	TLabel *Label1;
	TLabel *Label2;
	TCheckBox *cboxUseReference;
	TEdit *edtMemberName;
	TComboBox *comboType;
	TBitBtn *bitbtnOK;
	TBitBtn *bitbtnCancel;
	TBitBtn *bitbtnApplyAndNew;
	TEdit *edtPropName;
	TLabel *Label3;
	TPanel *panelID;
	TEdit *edtClear;
	TLabel *Label4;
	TPanel *panelDBParams;
	TLabel *Label5;
	TLabel *Label6;
	TEdit *edtSqlField;
	TEdit *edtMemberField;
	TCheckBox *cboxIsKey;
	void __fastcall comboTypeChange(TObject *Sender);
	void __fastcall bitbtnApplyAndNewClick(TObject *Sender);
private:
	TForm *m_parent; 
protected:
	void __fastcall Download (TClassMemberInfo &class_info);
	void __fastcall Upload (TClassMemberInfo &class_info);
public:
	virtual __fastcall TdlgEditMember(TComponent* AOwner);
	bool __fastcall Execute (TForm *parent, TClassMemberInfo &class_info, bool fDatabase, bool fNew);
};
//----------------------------------------------------------------------------
extern PACKAGE TdlgEditMember *dlgEditMember;
//----------------------------------------------------------------------------
#endif
