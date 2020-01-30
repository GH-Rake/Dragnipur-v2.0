#pragma once
#include <algorithm>
#include "mem.h"
#include "reversals.h"
#include "esp.h"
#include "geom.h"

class Aimbot
{
public:
	bool bAimbotStatus = false;
	bool bNoRecoilStatus = false;
	bool bHeadshots = false;
	bool bFlyHackStatus = false;
	bool bScopeHack = false;
	bool bMapHack = false;
	vec teleport;

	void sortAimShoot();

	void readPlayerData();
};

extern Aimbot aBot;

bool playerSorter(PlayerClass& lhs, PlayerClass& rhs);

void ReadHotKeys(Aimbot& aBot);