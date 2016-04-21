// GvimLauncher.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "GvimLauncher.h"
#include <shellapi.h>
#include <iostream>


int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hInstance);
	UNREFERENCED_PARAMETER(hPrevInstance);

	LPTSTR arguments = new TCHAR[wcslen(lpCmdLine)+2];
	arguments[0] = L'\0';
	


	bool argumentsPassed = false;
	for( int i=1; i < __argc; i++)
	{
		if (wcscmp(__wargv[i], L"-z") == 0)
		{
			// -z specificed - skip the next parameter
			i++;
		}
		else
		{
			if (argumentsPassed == false)
				wcscat(arguments, L"--remote-tab-silent \"");
			else
				wcscat(arguments, L" ");

			argumentsPassed = true;
			wcscat(arguments, __wargv[i]);
		}
	}

	if (argumentsPassed == true)
		wcscat(arguments, L"\"");
	
	wchar_t* gvimExe = _wcsdup(__wargv[0]);
	gvimExe[wcslen(gvimExe) - wcslen(L"GvimLauncher.exe")] = '\0';
	wcscat(gvimExe, L"gvim.exe");

	ShellExecute(NULL, NULL, gvimExe, arguments, NULL, 0);

	return (int) 0;
}


