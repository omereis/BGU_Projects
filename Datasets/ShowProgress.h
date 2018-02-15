//---------------------------------------------------------------------------

#ifndef ShowProgressH
#define ShowProgressH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "cgauges.h"
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TfrmShowProgress : public TForm
{
__published:	// IDE-managed Components
	TPanel *Panel4;
	TCGauge *gauge1;
	TPanel *panelCaption;
	TButton *btnStop;
private:	// User declarations
public:		// User declarations
	__fastcall TfrmShowProgress(TComponent* Owner);
	void __fastcall SetMax (int nFiles);
	void __fastcall SetProgress (int nProgress);
	void __fastcall UpdateGUI ();
	void __fastcall UpdateGUI (const String &strCaption);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmShowProgress *frmShowProgress;
//---------------------------------------------------------------------------
#endif
