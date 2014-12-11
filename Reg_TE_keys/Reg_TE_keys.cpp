// Reg_TE_keys.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

TCHAR msg[MAX_PATH];
typedef int (*PFN_DllRegisterServer)(void);

void RegisterCOMDll(TCHAR* file)
{
	HINSTANCE hLib = LoadLibrary(file);
	if (hLib == NULL)
	{
		wsprintf(msg, L"Unable to load 'DllRegisterServer' from '%s' error is %i\n", file, GetLastError());
		goto exit;
	}

	PFN_DllRegisterServer DllRegisterServer = NULL;
	DllRegisterServer = (PFN_DllRegisterServer) GetProcAddress(hLib, _T("DllRegisterServer"));

	if (DllRegisterServer == NULL){
		wsprintf(msg, L"Unable to load 'DllRegisterServer' from '%s' error is %i\n", file, GetLastError());
		goto exit;
	}

	int iRes = DllRegisterServer();

	if (iRes != 0)
	{
		wsprintf(msg, L"Error %i (0x%08x)returned from DllRegisterServer in '%s'\n", iRes, iRes, file); //0x80070716
		goto exit;
	}
	else
		wsprintf(msg, L"DllRegister did success for '%s'\n", file);
exit:
	DEBUGMSG(1, (msg));
	FreeLibrary(hLib);
}




int _tmain(int argc, _TCHAR* argv[])
{
	RegisterCOMDll(L"\\windows\\TE_Keys.dll");
	return 0;
}

