#pragma once
#include <vector>
#include "menu.h"
#include "reversals.h"

enum espMode { OFF = 0, PLAYERSONLY, ALL };

extern int iESP;

void espEnt(PlayerClass p);

void espMapEnt(mapEnt* e, std::string text);

//flags
void espFlags(vec e);

void espPlayers(std::vector<PlayerClass> playerVector);

void espMapEnts();

void espFlags();