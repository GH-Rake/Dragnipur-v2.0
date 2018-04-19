#include <Windows.h>
#include <thread>
#pragma comment(lib, "lib\\detours.lib")
#include "include\detours.h"
#include "aimbot.h"
#include "openGLHacks.h"

//drawHUD function to hook:
typedef void(__cdecl *gl_drawHUD) (int w, int h, int curfps, int nquads, int curvert, bool underwater);
gl_drawHUD drawTheHUD;

//my drawHUD hooked function
void hackMain(int w, int h, int curfps, int nquads, int curvert, bool underwater)
{
	aBot.readPlayerData();
	ReadHotKeys(aBot);
	drawTheHUD(w, h, curfps, nquads, curvert, underwater);
}

//aiming
void shootThread()
{
	INPUT leftMouseShoot = { 0 };
	while (1)
	{
		if (bShooting)
		{
			//press
			leftMouseShoot.type = INPUT_MOUSE;
			leftMouseShoot.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
			SendInput(1, &leftMouseShoot, sizeof(INPUT));

			std::this_thread::sleep_for(std::chrono::milliseconds(5));

			// Release
			leftMouseShoot.mi.dwFlags = MOUSEEVENTF_LEFTUP;
			SendInput(1, &leftMouseShoot, sizeof(INPUT));
			bShooting = false;
		}

		std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}
}

DWORD WINAPI Dragnipur(LPVOID param)
{
	FreeConsole();
	HookSwapBuffers();

	//hookdrawHud function
	drawTheHUD = (gl_drawHUD)((DWORD)GetModuleHandleA("ac_client.exe") + 0xAAF0);
	DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());
	DetourAttach(&(PVOID&)drawTheHUD, hackMain);
	DetourTransactionCommit();

	std::thread shootThread(shootThread);
	shootThread.detach();

	//disable annoying ws:
	DWORD old_protect;
	VirtualProtect((void*)0x045F920, 6, PAGE_EXECUTE_READWRITE, &old_protect);
	memset((void*)(0x045F920), 0x90, 6);
	VirtualProtect((void*)0x045F920, 6, old_protect, &old_protect);

	return 0;
}

BOOL __stdcall DllMain(HINSTANCE hModule, DWORD dwReason, LPVOID lpReserved)
{
	switch (dwReason)
	{
	case DLL_PROCESS_ATTACH:
		CreateThread(nullptr, 0, Dragnipur, nullptr, 0, nullptr);
		DisableThreadLibraryCalls(hModule);
		break;

	case DLL_PROCESS_DETACH:

		DetourTransactionBegin();
		DetourUpdateThread(GetCurrentThread());
		DetourDetach(&(PVOID &)owglSwapBuffers, hwglSwapBuffers);
		DetourDetach(&(PVOID&)drawTheHUD, hackMain);
		DetourTransactionCommit();

		break;

	default:
		break;
	}
	return true;
}