//---------------------------------------------------------------------------

#include "Generic.h"
#pragma hdrstop

//---------------------------------------------------------------------------

USEFORM("R128MakerUnit.cpp", Form1);
USEFORM("SettingsUnit.cpp", SettingsForm);

//---------------------------------------------------------------------------

WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	try
	{
		Application->Initialize();
		Application->Title = "R128 maker";
		Application->CreateForm(__classid(TForm1), &Form1);
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
