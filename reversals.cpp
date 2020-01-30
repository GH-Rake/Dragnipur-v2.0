#include "reversals.h"

int* gameMode = (int*)(0x50F49C);
int* numOfPlayers = (int*)(0x50f500);
glmatrixf* glmvpmatrix = (glmatrixf*)(0x501AE8);
sqr* world = (sqr*)0x50A1F8;
int* sfactor = (int*)0x505BB4;
int* lastmillis = (int*)0x509EAC;
playerent* localPlayer = *(playerent**)0x50F4F4;

PlayerClass::PlayerClass() {}

//playerVector constructor
PlayerClass::PlayerClass(intptr_t* player)
{
	ent = (playerent*)*(intptr_t*)player;
	dist = 0;
	fAngleFromCross = 0;
	vAimbotAngles = {};
}

bool PlayerClass::IsVisible()
{
	intptr_t traceLine = 0x048a310;
	traceresult_s traceresult;
	traceresult.collided = false;
	vec from = localPlayer->vHead;
	vec to = ent->vHead;

	__asm
	{
		push 0; bSkipTags
		push 0; bCheckPlayers
		push localPlayer
		push to.z
		push to.y
		push to.x
		push from.z
		push from.y
		push from.x
		lea eax, [traceresult]
		call traceLine;
		add esp, 36
	}
	return !traceresult.collided;
}