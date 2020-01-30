#include "openGLHacks.h"
#include "menu.h"
#include "aimbot.h"

extern Menu menu;
twglSwapBuffers owglSwapBuffers;

BOOL __stdcall hkwglSwapBuffers(HDC hDc)
{
	GLfloat tmp_viewport[4];
	glGetFloatv(GL_VIEWPORT, tmp_viewport);
	fWindowScale = (tmp_viewport[2] / 800.0f);

	aBot.readPlayerData();
	ReadHotKeys(aBot);

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

	//TODO: Fix
	if (aBot.bScopeHack && localPlayer->weapon->ID == 5)
	{
		drawCrosshair();
	}

	return owglSwapBuffers(hDc);
}

//Detours the OpenGL SwapBuffers function
void HookSwapBuffers()
{
	owglSwapBuffers = (twglSwapBuffers)GetProcAddress(GetModuleHandle("opengl32.dll"), "wglSwapBuffers");
	owglSwapBuffers = (twglSwapBuffers)mem::TrampHook32((BYTE*)owglSwapBuffers, (BYTE*)hkwglSwapBuffers, 5);
}

inline void initGLDraw()
{
	glPushMatrix();
	GLfloat tmp_viewport[4];
	glGetFloatv(GL_VIEWPORT, tmp_viewport);

	glViewport(0, 0, tmp_viewport[2], tmp_viewport[3]);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, tmp_viewport[2], tmp_viewport[3], 0, -1, 1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

vec2 W2S(glmatrixf* mvpmatrix, vec vPlayerLoc)
{
	//Matrix-Vector Product, multiplying world(eye) coordinates by projection matrix = clipCoords
	vec4 clipCoords;
	clipCoords.x = vPlayerLoc.x * mvpmatrix->v[0] + vPlayerLoc.y * mvpmatrix->v[4] + (vPlayerLoc.z) * mvpmatrix->v[8] + mvpmatrix->v[12];
	clipCoords.y = vPlayerLoc.x * mvpmatrix->v[1] + vPlayerLoc.y * mvpmatrix->v[5] + (vPlayerLoc.z) * mvpmatrix->v[9] + mvpmatrix->v[13];
	clipCoords.z = vPlayerLoc.x * mvpmatrix->v[2] + vPlayerLoc.y * mvpmatrix->v[6] + (vPlayerLoc.z) * mvpmatrix->v[10] + mvpmatrix->v[14];
	clipCoords.w = vPlayerLoc.x * mvpmatrix->v[3] + vPlayerLoc.y * mvpmatrix->v[7] + (vPlayerLoc.z) * mvpmatrix->v[11] + mvpmatrix->v[15];

	//perspective division, dividing by clip.W = NDC = Normalized Device Coordinates
	vec ndc;
	ndc.x = clipCoords.x / clipCoords.w;
	ndc.y = clipCoords.y / clipCoords.w;
	ndc.z = clipCoords.z / clipCoords.w;

	//viewport tranform to screenCooords
	GLfloat tmpViewPort[4] = { 0 };
	glGetFloatv(GL_VIEWPORT, tmpViewPort); // viewport = (0, 0, width, height)

	vec2 playerScreenCoords;
	playerScreenCoords.x = (tmpViewPort[2] / 2 * ndc.x) + (ndc.x + tmpViewPort[2] / 2);
	playerScreenCoords.y = -(tmpViewPort[3] / 2 * ndc.y) + (ndc.y + tmpViewPort[3] / 2);
	return playerScreenCoords;
}