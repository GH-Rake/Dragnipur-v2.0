#include "reversals.h"

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