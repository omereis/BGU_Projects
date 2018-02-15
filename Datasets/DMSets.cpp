//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
//---------------------------------------------------------------------------
USEFORM("Main.cpp", frmMain);
USEFORM("EditDataset.cpp", dlgEditDataset);
USEFORM("EditContact.cpp", dlgContact);
USEFORM("ImportGeoLife.cpp", dlgImportGeoLife);
USEFORM("ShowProgress.cpp", frmShowProgress);
USEFORM("EditContent.cpp", dlgContent);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	try
	{
		Application->Initialize();
		SetApplicationMainFormOnTaskBar(Application, true);
		Application->Title = "Datasets for Data Mining";
		Application->CreateForm(__classid(TfrmMain), &frmMain);
		Application->CreateForm(__classid(TdlgContent), &dlgContent);
		Application->Run();
	}
	catch (Exception &exception)
	{
		Application->ShowException(&exception);
	}
	catch (...)
	{
		try
		{
			throw Exception("");
		}
		catch (Exception &exception)
		{
			Application->ShowException(&exception);
		}
	}
	return 0;
}
//---------------------------------------------------------------------------
