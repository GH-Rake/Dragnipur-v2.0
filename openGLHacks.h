#pragma once
#pragma comment(lib, "lib\\OpenGL32.Lib")
#include "mem.h"
#include "geom.h"
#include "menu.h"

extern glmatrixf* glmvpmatrix;
extern void drawCrosshair();

typedef BOOL(__stdcall* twglSwapBuffers) (HDC hDc);

extern twglSwapBuffers owglSwapBuffers;

BOOL __stdcall hkwglSwapBuffers(HDC hDc);

//Detours the OpenGL SwapBuffers function
void HookSwapBuffers();

inline void initGLDraw();

vec2 W2S(glmatrixf* mvpmatrix, vec vPlayerLoc);