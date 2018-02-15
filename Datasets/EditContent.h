//----------------------------------------------------------------------------
#ifndef EditContentH
#define EditContentH
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
#include "DBMisc.h"
#include <Grids.hpp>
#include "IseTypes.h"
#include <AppEvnts.hpp>
#include "DataPoints.h"
//----------------------------------------------------------------------------
class TdlgContent : public TForm
{
__published:
	TBitBtn *bitbtnOK;
	TBitBtn *bitbtnCancel;
	TListBox *lboxObjects;
	TButton *btnObjects;
	TEdit *edtName;
	TLabel *Label3;
	TLabel *Label4;
	TEdit *edtDesc;
	TButton *btnShowRoutes;
	TStringGrid *gridRoutePoints;
	TPanel *panelCount;
	TStringGrid *gridPoints;
	TButton *brnShowPoints;
	TApplicationEvents *ApplicationEvents1;
	void __fastcall btnObjectsClick(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall btnShowRoutesClick(TObject *Sender);
	void __fastcall brnShowPointsClick(TObject *Sender);
	void __fastcall OnIdle(TObject *Sender, bool &Done);
private:
	TADOQuery *m_query;
	String m_strErr;
protected:
	void __fastcall SetGridPoint (const TDataPoint &dpt, int row);
	int __fastcall UploadRouteID ();
	void __fastcall InitPointsGrid ();
	void __fastcall InitRoutesGrid ();
	bool __fastcall Download (TADOConnection *db, int idDataset);
public:
	virtual __fastcall TdlgContent(TComponent* AOwner);
	bool __fastcall Execute (TADOConnection *db, int idDataset);
};
//----------------------------------------------------------------------------
extern PACKAGE TdlgContent *dlgContent;
//----------------------------------------------------------------------------
#endif
