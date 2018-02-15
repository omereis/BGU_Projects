//---------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "EditContent.h"
#include "DBMisc.h"
#include "DatasetInfo.h"
#include "DatasetObj.h"
#include "RouteInfo.h"
#include "Misc.h"
//---------------------------------------------------------------------
#pragma resource "*.dfm"
TdlgContent *dlgContent;
//---------------------------------------------------------------------
__fastcall TdlgContent::TdlgContent(TComponent* AOwner)
	: TForm(AOwner)
{
}
//---------------------------------------------------------------------
bool __fastcall TdlgContent::Execute (TADOConnection *db, int idDataset)
{
	m_query = InitQuery (db, this);
	if (Download (db, idDataset))
		ShowModal ();
	delete m_query;
	return (true);
}
//---------------------------------------------------------------------
bool __fastcall TdlgContent::Download (TADOConnection *db, int idDataset)
{
	TDatasetInfo ds;
	bool f;
	TDatases vds;

	vds.LoadFromDB (m_query, m_strErr);
	if ((f = ds.LoadByID (m_query, idDataset, m_strErr)) == true) {
		edtName->Text = ds.Name;
		edtDesc->Text = ds.Description;
		edtName->Tag = ds.DatasetID;
	}
	return (f);
}
//---------------------------------------------------------------------
void __fastcall TdlgContent::btnObjectsClick(TObject *Sender)
{
	TDatasetObjects vDOs;
	TDatasetObjects::iterator iObj;

	lboxObjects->Items->Clear ();
	if (vDOs.LoadDatasetsObjects (m_query, edtName->Tag, m_strErr))
		for (iObj=vDOs.begin() ; iObj != vDOs.end() ; iObj++) {
            lboxObjects->Items->AddObject (iObj->ObjName, (TObject*) iObj->ObjID);
		}
}
//---------------------------------------------------------------------------
void __fastcall TdlgContent::FormCreate(TObject *Sender)
{
	InitRoutesGrid ();
	InitPointsGrid ();
}
//---------------------------------------------------------------------------
void __fastcall TdlgContent::InitRoutesGrid ()
{
	gridRoutePoints->Cells[0][0] = "Route";
	gridRoutePoints->Cells[1][0] = "# of Points";
}
//---------------------------------------------------------------------------
void __fastcall TdlgContent::InitPointsGrid ()
{
	gridPoints->Cells[0][0] = "Latitude";
	gridPoints->Cells[1][0] = "Longitude";
	gridPoints->Cells[2][0] = "Altitude";
	gridPoints->Cells[3][0] = "Date & Time";
}
//---------------------------------------------------------------------------
void __fastcall TdlgContent::btnShowRoutesClick(TObject *Sender)
{
	TRoutes vRoutes;
	TIntVec vPoints;
	TRoutes::iterator iRoute;
	TIntVec::iterator i;
	int r, nTotal;

	PurgeGrid (gridRoutePoints);
	nTotal = 0;
	if (vRoutes.LoadPointsCount (m_query, vPoints, m_strErr)) {
		gridRoutePoints->RowCount = max (2, (int) (1 + vRoutes.size()));
		for (iRoute=vRoutes.begin(), i=vPoints.begin(), r=1 ; iRoute != vRoutes.end() ; iRoute++, i++, r++) {
			gridRoutePoints->Cells[0][r] = iRoute->RouteName;
			gridRoutePoints->Cells[1][r] = *i;
			nTotal += *i;
			gridRoutePoints->Objects[0][r] = (TObject*) iRoute->RouteID;
		}
	}
	panelCount->Caption = String (nTotal);
}
//---------------------------------------------------------------------------
int __fastcall TdlgContent::UploadRouteID ()
{
	int id = -1;

	if (gridRoutePoints->Row >= 1)
		id = (int) gridRoutePoints->Objects[0][gridRoutePoints->Row];
	return (id);
}
//---------------------------------------------------------------------------
void __fastcall TdlgContent::brnShowPointsClick(TObject *Sender)
{
	int idRoute = UploadRouteID ();
	TDataPoints vPoints;
	TDataPoints::iterator iPoint;
	int r;

	PurgeGrid (gridPoints);
	if (vPoints.LoadRoutePoints (idRoute, m_query, m_strErr)) {
		gridPoints->RowCount = max (2, (int) (1 + vPoints.size() + 1 ));
		for (iPoint=vPoints.begin(), r=1 ; iPoint != vPoints.end() ; iPoint++, r++) {
			SetGridPoint (*iPoint, r);
		}
	}

}
//---------------------------------------------------------------------------
void __fastcall TdlgContent::SetGridPoint (const TDataPoint &dpt, int row)
{
	gridPoints->Cells[0][row] = FormatFloat ("#,###0.0", dpt.Lat);
	gridPoints->Cells[1][row] = FormatFloat ("#,###0.0", dpt.Long);//Longitude
	gridPoints->Cells[2][row] = FormatFloat ("#,###0.0", dpt.Alt);//Altitude";
	gridPoints->Cells[3][row] = dpt.GetDateTimeString();//GetSqlInsertString ();//Alt"Date & Time";
}
//---------------------------------------------------------------------------
void __fastcall TdlgContent::OnIdle(TObject *Sender, bool &Done)
{
	brnShowPoints->Enabled = UploadRouteID () > 0;
}
//---------------------------------------------------------------------------

