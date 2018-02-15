//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
USERES("BCBClassWriter.res");
USEFORM("main.cpp", formMain);
USEUNIT("..\Globals\Misc.cpp");
USEFORM("EditMember.cpp", dlgEditMember);
USEUNIT("ClassInfo.cpp");
USEUNIT("ClassMemberInfo.cpp");
USEUNIT("ProjMisc.cpp");
USEUNIT("CommonStrings.cpp");
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	try
	{
		Application->Initialize();
		Application->CreateForm(__classid(TformMain), &formMain);
		Application->Run();
	}
	catch (Exception &exception)
	{
		Application->ShowException(&exception);
	}
	return 0;
}
//---------------------------------------------------------------------------
