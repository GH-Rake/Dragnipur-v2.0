#include <Windows.h>
#include "aimbot.h"
#include "openGLHacks.h"

DWORD WINAPI Dragnipur(LPVOID param)
{
	HookSwapBuffers();

	//disable annoying ws:
	mem::Nop((BYTE*)0x045F920, 6);

	return 0;
}

BOOL __stdcall DllMain(HINSTANCE hModule, DWORD dwReason, LPVOID lpReserved)
{
	switch (dwReason)
	{
	case DLL_PROCESS_ATTACH:
		CreateThread(nullptr, 0, Dragnipur, nullptr, 0, nullptr);
		break;

	case DLL_PROCESS_DETACH:
		break;

	default:
		break;
	}
	return true;
}