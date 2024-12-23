// Debugging.cpp : Defines the entry point for the application.
//

#include "stdafx.h"

#include <windows.h>
#include <shlwapi.h>

#pragma comment(lib, "shlwapi.lib")

int _tmain(int argc, _TCHAR* argv[])
{
// Can't step into this function. You get a "not indexed" error.
//char buf[256]={'\0'};
//::PathRemoveExtensionA(buf);

// Set a breakpoint on this function, then try to Step Into it.
GetConsoleMode(0,0);

// Stepping into this function should work too, but not on XP.
//UnregisterApplicationRestart();

return 0;
} 