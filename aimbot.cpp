#include "aimbot.h"

Menu menu;

bool bFullbright = false;
PlayerClass target;
std::vector <PlayerClass> targets;

void Aimbot::sortAimShoot()
{
	targets.clear();
	for each (PlayerClass p in playerVector)
	{
		if (p.ent == nullptr || p.ent->state != 0 || m_teammode && p.ent->team == localPlayer->team)
		{
			continue;
		}

		if (!p.IsVisible())
		{
			continue;
		}
		targets.push_back(p);
	}

	//sort targets Vector
	for (PlayerClass& p : targets)
	{
		p.vAimbotAngles = CalcAngle(localPlayer->vHead, p.ent->vHead);
		p.fAngleFromCross = Get3dDistance(p.vAimbotAngles, localPlayer->vViewAngle);
	}

	sort(targets.begin(), targets.end(), playerSorter);

	if (!targets.empty())
	{
		target = targets[0];
		localPlayer->vViewAngle = target.vAimbotAngles;
	}
}

void Aimbot::readPlayerData()
{
	playerVector.clear();
	int numOfOtherPlayers = *numOfPlayers - 1;
	intptr_t* playerArrayAddress = (intptr_t*)0x50F4F8;

	for (int x = 0; x <= numOfOtherPlayers; x++)
	{
		intptr_t* tempPlayerAddress = (intptr_t*)(*playerArrayAddress + x * 0x4);
		if (*tempPlayerAddress != 0)
		{
			if (*(intptr_t*)*tempPlayerAddress == 0x4E4A98 || *(intptr_t*)*tempPlayerAddress == 0x4E4AC0)
			{
				playerVector.push_back(PlayerClass(tempPlayerAddress));
			}
		}
	}
}

bool playerSorter(PlayerClass& lhs, PlayerClass& rhs)
{
	return lhs.fAngleFromCross < rhs.fAngleFromCross;
}

void ReadHotKeys(Aimbot& aBot)
{
	HWND focusWindow = GetFocus();

	if (GetFocus() == FindWindowA(0, "AssaultCube"))
	{
		if (GetAsyncKeyState(VK_RBUTTON) && aBot.bAimbotStatus && localPlayer->state == 0)
		{
			aBot.sortAimShoot();
		}

		if (GetAsyncKeyState(VK_F1) & 1)
		{
			aBot.bAimbotStatus = !aBot.bAimbotStatus;
			if (aBot.bAimbotStatus)
			{
				menu.sAimbotStatus = "ON";
			}
			else
			{
				menu.sAimbotStatus = "OFF";
			}
		}

		if (GetAsyncKeyState(VK_F2) & 1)
		{
			switch (iESP)
			{
			case OFF: iESP = PLAYERSONLY;  menu.sESP = "ON"; break;
			case PLAYERSONLY: iESP = ALL; break;
			case ALL: iESP = OFF; menu.sESP = "OFF"; break;
			}
		}

		if (GetAsyncKeyState(VK_F3) & 1)
		{
			DWORD old_protect;
			aBot.bNoRecoilStatus = !aBot.bNoRecoilStatus;
			if (aBot.bNoRecoilStatus)
			{
				mem::Nop((BYTE*)0x463786, 10);
				menu.sNoRecoil = "ON";
			}

			else
			{
				//restore recoil
				mem::Patch((BYTE*)0x463786, (BYTE*)"\x50\x8D\x4C\x24\x1C\x51\x8B\xCE\xFF\xD2", 10);
				menu.sNoRecoil = "OFF";
			}
		}

		if (GetAsyncKeyState(VK_F4) & 1)
		{
			aBot.bMapHack = !aBot.bMapHack;
			if (aBot.bMapHack)
			{
				//bypass gameMode checking
				mem::Nop((BYTE*)0x0040968F, 6);

				//map show ALL
				mem::Nop((BYTE*)0x04096A1, 6);

				//bypass gameMode checking on radar
				mem::Nop((BYTE*)0x00409FA1, 6);

				//radar show ALL
				mem::Nop((BYTE*)0x0409FB3, 6);

				menu.sMapHack = "ON";
			}

			else
			{
				//bypass gameMode checking
				mem::Patch((BYTE*)0x0040968F, (BYTE*)"\x0F\x85\x65\x01\x00\x00", 6);

				//map restore
				mem::Patch((BYTE*)0x04096A1, (BYTE*)"\x0f\x85\x53\x01\x00\x00", 6);

				//radar restore gamemodeChecking?
				mem::Patch((BYTE*)0x00409FA1, (BYTE*)"\x0F\x85\x5C\x01\x00\x00", 6);

				//radar restore
				mem::Patch((BYTE*)0x0409FB3, (BYTE*)"\x0F\x85\x4a\x01\x00\x00", 6);

				menu.sMapHack = "OFF";
			}
		}

		if (GetAsyncKeyState(VK_F5) & 1)
		{
			menu.sScopeHack = "ON";
			aBot.bScopeHack = !aBot.bScopeHack;
			if (aBot.bScopeHack)
			{
				mem::Nop((BYTE*)0x463CEB, 5);
			}

			else
			{
				menu.sScopeHack = "OFF";
				mem::Patch((BYTE*)0x463CEB, (BYTE*)"\xE8\x90\x43\xFA\xFF", 5);
			}
		}

		//fullbright
		if (GetAsyncKeyState(VK_F6) & 1)
		{
			bFullbright = !bFullbright;

			if (bFullbright)
			{
				menu.sFullbright = "ON";

				intptr_t fullbright = 0x00454EF0;
				__asm
				{
					call fullbright;
				}
			}
			else
			{
				menu.sFullbright = "OFF";

				intptr_t calclight = 0x0044F040;
				__asm
				{
					call calclight;
				}
			}
		}

		//flyhack
		if (GetAsyncKeyState(VK_F7) & 1)
		{
			aBot.bFlyHackStatus = !aBot.bFlyHackStatus;
			if (aBot.bFlyHackStatus)
			{
				mem::Patch((BYTE*)0x45ADD8, (BYTE*)"\x01", 1);
				menu.sFlyHackStatus = "ON";
			}

			else
			{
				//restore
				mem::Patch((BYTE*)0x45ADD8, (BYTE*)"\x00", 1);
				menu.sFlyHackStatus = "OFF";
			}
		}

		if (GetAsyncKeyState(VK_F8) & 1)
		{
			aBot.teleport = localPlayer->vLocation;
		}

		if (GetAsyncKeyState(VK_F9) & 1)
		{
			localPlayer->vLocation = aBot.teleport;
		}

		//Flag teleporter
		if (GetAsyncKeyState(VK_F11) & 1 && m_flags)
		{
			enum flagStatus { INBASE = 0, STOLEN = 1, DROPPED = 2, IDLE = 3 };

			flagEnt* flags[2] = { (flagEnt*)0x50F4A8, (flagEnt*)0x50F4CC };
			flagEnt* myFlag = 0;
			flagEnt* enemyFlag = 0;

			if (flags[0]->team == localPlayer->team)
			{
				myFlag = flags[0];
				enemyFlag = flags[1];
			}
			else
			{
				myFlag = flags[1];
				enemyFlag = flags[0];
			}

			//if holding flag, teleport to own flag
			if (enemyFlag->player == localPlayer)
			{
				localPlayer->vLocation = { (float)myFlag->mapent->x, (float)myFlag->mapent->y, (float)myFlag->mapent->z - 4 };
			}

			switch (myFlag->state)
			{
			case INBASE:
				if (enemyFlag->state == INBASE)
				{
					localPlayer->vLocation = { (float)enemyFlag->mapent->x, (float)enemyFlag->mapent->y, (float)enemyFlag->mapent->z - 4 };
				}
				break;
				//if my flag is stolen, teleport and kill
			case STOLEN:
				localPlayer->vLocation = myFlag->player->vLocation;
				//target = myFlag->player;
				break;

			case DROPPED:
				localPlayer->vLocation = myFlag->pos;
				//how to find flag?
				break;
			}
		}

		if (GetAsyncKeyState(VK_INSERT) & 1)
		{
			menu.bStatus = !menu.bStatus;
		}
		if (GetAsyncKeyState(VK_HOME) & 1)
		{
			if (menu.bStatus == true)
			{
				if (menu.iTab == 1)
				{
					menu.iTab = 2;
				}
				else menu.iTab = 1;
			}
		}
	}
}