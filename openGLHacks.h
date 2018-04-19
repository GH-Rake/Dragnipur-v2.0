#pragma comment(lib, "lib\\OpenGL32.Lib")

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

	HDC currentHDC = wglGetCurrentDC();
	if (!font.bBuilt || currentHDC != font.hdc)
	{
		font.Build(15);
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

vec2 W2S(glmatrixf *mvpmatrix, vec vPlayerLoc)
{
	//Matrix-Vector Product, multiplying world(eye) coordinates by projection matrix = clipCoords
	vec4 clipCoords;
	clipCoords.x = vPlayerLoc.x*mvpmatrix->v[0] + vPlayerLoc.y*mvpmatrix->v[4] + (vPlayerLoc.z)*mvpmatrix->v[8] + mvpmatrix->v[12];
	clipCoords.y = vPlayerLoc.x*mvpmatrix->v[1] + vPlayerLoc.y*mvpmatrix->v[5] + (vPlayerLoc.z)*mvpmatrix->v[9] + mvpmatrix->v[13];
	clipCoords.z = vPlayerLoc.x*mvpmatrix->v[2] + vPlayerLoc.y*mvpmatrix->v[6] + (vPlayerLoc.z)*mvpmatrix->v[10] + mvpmatrix->v[14];
	clipCoords.w = vPlayerLoc.x*mvpmatrix->v[3] + vPlayerLoc.y*mvpmatrix->v[7] + (vPlayerLoc.z)*mvpmatrix->v[11] + mvpmatrix->v[15];

	//perspective division, dividing by clip.W = NDC = Normalized Device Coordinates
	vec ndc;
	ndc.x = clipCoords.x / clipCoords.w;
	ndc.y = clipCoords.y / clipCoords.w;
	ndc.z = clipCoords.z / clipCoords.w;

	//viewport tranform to screenCooords
	GLfloat viewport[4] = { 0 };
	GLfloat depthrange[2] = { 0 };
	glGetFloatv(GL_VIEWPORT, viewport); // viewport = (0, 0, width, height)
	glGetFloatv(GL_DEPTH_RANGE, depthrange); //depthrange = (0,1)

	vec2 playerScreenCoords;
	playerScreenCoords.x = (viewport[2] / 2 * ndc.x) + (ndc.x + viewport[2] / 2);
	playerScreenCoords.y = -(viewport[3] / 2 * ndc.y) + (ndc.y + viewport[3] / 2);
	return playerScreenCoords;
}