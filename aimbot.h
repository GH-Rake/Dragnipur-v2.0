#pragma once
bool playerSorter(PlayerClass &lhs, PlayerClass &rhs);
std::vector <PlayerClass> targets;
PlayerClass target;
bool bShooting = false;
bool bFullbright = false;

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

	void sortAimShoot()
	{
		targets.clear();
		for each(PlayerClass p in playerVector)
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
		for (PlayerClass &p : targets)
		{
			p.vAimbotAngles = CalcAngle(localPlayer->vHead, p.ent->vHead);
			p.fAngleFromCross = DifferenceOfAngles(p.vAimbotAngles, localPlayer->vViewAngle);
		}

		sort(targets.begin(), targets.end(), playerSorter);

		if (!targets.empty())
		{
			target = targets[0];
			localPlayer->vViewAngle = target.vAimbotAngles;

			/* buggy auto shoot
			if (*localPlayer->weapon->gunWait == 0 && localPlayer->weapon->breload == false)
			{
				bShooting = TRUE;
			}
			*/
		}
	}

	void ReadHotKeys()
	{
		HWND focusWindow = GetFocus();
		if (GetFocus() == FindWindowA(0, "AssaultCube"))
		{
			if (GetAsyncKeyState(VK_RBUTTON) && aBot.bAimbotStatus && localPlayer->state == 0)
			{
				readPlayerData();
				sortAimShoot();
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
					//recoil
					VirtualProtect((void*)0x463786, 10, PAGE_EXECUTE_READWRITE, &old_protect);
					memcpy((void*)0x463786, (PBYTE)("\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90"), 10);
					VirtualProtect((void*)0x463786, 10, old_protect, &old_protect);
					menu.sNoRecoil = "ON";
				}

				else
				{
					//restore recoil
					VirtualProtect((void*)0x463786, 10, PAGE_EXECUTE_READWRITE, &old_protect);
					memcpy((void*)0x463786, (PBYTE)("\x50\x8D\x4C\x24\x1C\x51\x8B\xCE\xFF\xD2"), 10);
					VirtualProtect((void*)0x463786, 10, old_protect, &old_protect);
					menu.sNoRecoil = "OFF";
				}
			}

			if (GetAsyncKeyState(VK_F4) & 1)
			{
				aBot.bMapHack = !aBot.bMapHack;
				DWORD old_protect;
				if (aBot.bMapHack)
				{
					//bypass gameMode checking
					VirtualProtect((void*)0x0040968F, 6, PAGE_EXECUTE_READWRITE, &old_protect);
					memcpy((void*)0x0040968F, (PBYTE)("\x90\x90\x90\x90\x90\x90"), 6);
					VirtualProtect((void*)0x0040968F, 6, old_protect, &old_protect);

					//map show ALL
					VirtualProtect((void*)0x04096A1, 6, PAGE_EXECUTE_READWRITE, &old_protect);
					memcpy((void*)0x04096A1, (PBYTE)("\x90\x90\x90\x90\x90\x90"), 6);
					VirtualProtect((void*)0x04096A1, 6, old_protect, &old_protect);

					//bypass gameMode checking on radar
					VirtualProtect((void*)0x00409FA1, 6, PAGE_EXECUTE_READWRITE, &old_protect);
					memcpy((void*)0x00409FA1, (PBYTE)("\x90\x90\x90\x90\x90\x90"), 6);
					VirtualProtect((void*)0x00409FA1, 6, old_protect, &old_protect);

					//radar show ALL
					VirtualProtect((void*)0x0409FB3, 6, PAGE_EXECUTE_READWRITE, &old_protect);
					memcpy((void*)0x0409FB3, (PBYTE)("\x90\x90\x90\x90\x90\x90"), 6);
					VirtualProtect((void*)0x0409FB3, 6, old_protect, &old_protect);

					menu.sMapHack = "ON";
				}

				else
				{
					//bypass gameMode checking
					VirtualProtect((void*)0x0040968F, 6, PAGE_EXECUTE_READWRITE, &old_protect);
					memcpy((void*)0x0040968F, (PBYTE)("\x0F\x85\x65\x01\x00\x00"), 6);
					VirtualProtect((void*)0x0040968F, 6, old_protect, &old_protect);

					//map restore
					VirtualProtect((void*)0x04096A1, 6, PAGE_EXECUTE_READWRITE, &old_protect);
					memcpy((void*)0x04096A1, (PBYTE)("\x0f\x85\x53\x01\x00\x00"), 6);
					VirtualProtect((void*)0x04096A1, 6, old_protect, &old_protect);

					//radar restore gamemodeChecking?
					VirtualProtect((void*)0x00409FA1, 6, PAGE_EXECUTE_READWRITE, &old_protect);
					memcpy((void*)0x00409FA1, (PBYTE)("\x0F\x85\x5C\x01\x00\x00"), 6);
					VirtualProtect((void*)0x00409FA1, 6, old_protect, &old_protect);

					//radar restore
					VirtualProtect((void*)0x0409FB3, 6, PAGE_EXECUTE_READWRITE, &old_protect);
					memcpy((void*)0x0409FB3, (PBYTE)("\x0F\x85\x4a\x01\x00\x00"), 6);
					VirtualProtect((void*)0x0409FB3, 6, old_protect, &old_protect);

					menu.sMapHack = "OFF";
				}
			}

			if (GetAsyncKeyState(VK_F5) & 1)
			{
				DWORD old_protect;
				menu.sScopeHack = "ON";
				aBot.bScopeHack = !aBot.bScopeHack;
				if (aBot.bScopeHack)
				{
					VirtualProtect((void*)0x463CEB, 5, PAGE_EXECUTE_READWRITE, &old_protect);
					memcpy((void*)0x463CEB, (PBYTE)("\x90\x90\x90\x90\x90"), 5);
					VirtualProtect((void*)0x463CEB, 5, old_protect, &old_protect);
				}

				else //restore
				{
					menu.sScopeHack = "OFF";
					VirtualProtect((void*)0x463CEB, 5, PAGE_EXECUTE_READWRITE, &old_protect);
					memcpy((void*)0x463CEB, (PBYTE)("\xE8\x90\x43\xFA\xFF"), 5);
					VirtualProtect((void*)0x463CEB, 5, old_protect, &old_protect);
				}
			}

			//fullbright
			if (GetAsyncKeyState(VK_F6) & 1)
			{
				bFullbright = !bFullbright;
				//int * brightness = (int*)0x5100f0;

				if (bFullbright)
				{
					menu.sFullbright = "ON";

					DWORD fullbright = 0x00454EF0;
					__asm
					{
						call fullbright;
					}
				}
				else
				{
					menu.sFullbright = "OFF";

					DWORD calclight = 0x0044F040;
					__asm
					{
						call calclight;
					}
				}
			}

			//flyhack
			if (GetAsyncKeyState(VK_F7) & 1)
			{
				DWORD old_protect;
				aBot.bFlyHackStatus = !aBot.bFlyHackStatus;
				if (aBot.bFlyHackStatus)
				{
					VirtualProtect((void*)0x45ADD8, 1, PAGE_EXECUTE_READWRITE, &old_protect);
					*(BYTE *)0x45ADD8 = 1;
					VirtualProtect((void*)0x45ADD8, 1, old_protect, &old_protect);
					menu.sFlyHackStatus = "ON";
				}

				else
				{
					//restore
					VirtualProtect((void*)0x45ADD8, 1, PAGE_EXECUTE_READWRITE, &old_protect);
					*(BYTE *)0x45ADD8 = 0;
					VirtualProtect((void*)0x45ADD8, 1, old_protect, &old_protect);
					menu.sFlyHackStatus = "OFF";
				}
			}

			if (GetAsyncKeyState(VK_F8) & 1)
			{
				teleport = localPlayer->vLocation;
			}

			if (GetAsyncKeyState(VK_F9) & 1)
			{
				localPlayer->vLocation = teleport;
			}

			//TeleKill = BUGGED = removed
			/*
			if (GetAsyncKeyState(VK_F10))
			{
				targets.clear();
				for each(PlayerClass p in playerVector)
				{
					if (p.ent == nullptr || p.ent->state != 0 || m_teammode && p.ent->team == localPlayer->team)
					{
						continue;
					}
					targets.push_back(p);
				}

				for each (PlayerClass p in targets)
				{
					localPlayer->vLocation = p.ent->vLocation;
					bShooting = true;
				}
			}
			*/

			//Flag teleporter
			if (GetAsyncKeyState(VK_F11) & 1 && m_flags)
			{
				enum flagStatus { INBASE = 0, STOLEN = 1, DROPPED = 2, IDLE = 3 };

				flagEnt * flags[2] = { (flagEnt*)0x50F4A8, (flagEnt*)0x50F4CC };
				flagEnt * myFlag = 0;
				flagEnt * enemyFlag = 0;

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
					//how to find flag?  is
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

	void readPlayerData()
	{
		playerVector.clear();
		int numOfOtherPlayers = *numOfPlayers - 1;
		DWORD * playerArrayAddress = (DWORD*)0x50F4F8;

		for (int x = 0; x <= numOfOtherPlayers; x++)
		{
			DWORD * tempPlayerAddress = (DWORD*)(*playerArrayAddress + x * 0x4);
			if (*tempPlayerAddress != 0)
			{
				if (*(DWORD*)*tempPlayerAddress == 0x4E4A98 || *(DWORD*)*tempPlayerAddress == 0x4E4AC0)
				{
					playerVector.push_back(PlayerClass(tempPlayerAddress));
				}
			}
		}
	}
}aBot;

bool playerSorter(PlayerClass &lhs, PlayerClass &rhs)
{
	return lhs.fAngleFromCross < rhs.fAngleFromCross;
}