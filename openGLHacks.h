extern glmatrixf * glmvpmatrix;
extern void drawCrosshair();
#pragma once

typedef BOOL(WINAPI * _wglSwapBuffers) (_In_ HDC hDc);
_wglSwapBuffers owglSwapBuffers;

//wglSwapBuffers Hook
BOOL WINAPI hwglSwapBuffers(_In_ HDC hDc)
{
	fWindowScale = (WINDOWWIDTH / 800.0f);

	if (m_botmode)
	{
		localPlayer->health = 999;
		*localPlayer->weapon->ammo = 999;
	}

	if (menu.bStatus)
	{
		menu.DrawMenu();
	}

	if (iESP != OFF)
	{
		espPlayers(playerVector);

		if (iESP == ALL)
		{
			espMapEnts();
		}


		if (m_flags)
		{
			espFlags();
		}
	}

	if (aBot.bScopeHack && localPlayer->weapon->ID == 5)
	{
		drawCrosshair();
	}
	return owglSwapBuffers(hDc);
}

//Detours the OpenGL SwapBuffers function
void HookSwapBuffers()
{
	HMODULE hMod = GetModuleHandle("opengl32.dll");

	if (hMod)
	{
		owglSwapBuffers = (_wglSwapBuffers)(DWORD)GetProcAddress(hMod, "wglSwapBuffers");
		DetourTransactionBegin();
		DetourUpdateThread(GetCurrentThread());
		DetourAttach(&(PVOID &)owglSwapBuffers, hwglSwapBuffers);
		DetourTransactionCommit();
	}
}

inline void initGLDraw()
{
	glPushMatrix();
	glGetFloatv(GL_VIEWPORT, viewport); // viewport = (0, 0, width, height)
	glGetFloatv(GL_DEPTH_RANGE, depthrange); //depthrange = (0,1)

	glViewport(0, 0, WINDOWWIDTH, WINDOWHEIGHT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, WINDOWWIDTH, WINDOWHEIGHT, 0, -1, 1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}