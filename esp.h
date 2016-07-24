#pragma once
//bool bESP = false;
int iESP = 0;
bool bMapEntESP = false;
enum espMode { OFF = 0, PLAYERSONLY, ALL };

void esp(PlayerClass p)
{
	vec vCenter = { p.ent->vHead.x, p.ent->vHead.y, p.ent->vHead.z - 4.50f + (float)(PLAYER_HEIGHT / 2) }; //4.5 = eyeheight

	vec2 screenCoords = math2.W2S(glmvpmatrix, vCenter);
	p.dist = Get3dDistance(localPlayer->vLocation, p.ent->vLocation);

	//Creates an ESP box from the center the of the player scaled to the model
	MyRect box;
	box.tl = { screenCoords.x - HALF_PLAYER_WIDTH, screenCoords.y - float(PLAYER_HEIGHT / 2) };
	box.tr = { screenCoords.x + HALF_PLAYER_WIDTH, float(screenCoords.y - (PLAYER_HEIGHT / 2)) };
	box.br = { screenCoords.x + HALF_PLAYER_WIDTH, float(screenCoords.y + (PLAYER_HEIGHT / 2)) };
	box.bl = { screenCoords.x - HALF_PLAYER_WIDTH, float(screenCoords.y + (PLAYER_HEIGHT / 2)) };
	box.center = screenCoords;

	if (m_teammode && localPlayer->team == p.ent->team)
	{
		glColor3ub(0, 255, 0);//green
	}

	else
	{
		glColor3ub(255, 0, 0);//red
	}


	MyRect healthBarRed;

	//put center vertex to the right
	healthBarRed.center.x = float(screenCoords.x + HALF_PLAYER_WIDTH * 1.3 * 400 / p.dist * fWindowScale);
	healthBarRed.center.y = screenCoords.y;
	//healthBarRed.center.z = 0;

	//create a hbar out of the vector
	//X part changes width of healthbar, Y stays same as ESP box
	healthBarRed.tl = { healthBarRed.center.x - 0.15f, healthBarRed.center.y - float(PLAYER_HEIGHT / 2) };
	healthBarRed.tr = { healthBarRed.center.x + 0.15f, healthBarRed.center.y - float(PLAYER_HEIGHT / 2) };
	healthBarRed.br = { healthBarRed.center.x + 0.15f, healthBarRed.center.y + float(PLAYER_HEIGHT / 2) };
	healthBarRed.bl = { healthBarRed.center.x - 0.15f, healthBarRed.center.y + float(PLAYER_HEIGHT / 2) };

	MyRect healthBarGreen;

	//green same as above with health multiplier
	//put center vertex to the right
	healthBarGreen.center.x = float(screenCoords.x + HALF_PLAYER_WIDTH * 1.3 * 400 / p.dist * fWindowScale);
	healthBarGreen.center.y = screenCoords.y;
	//healthBarGreen.center.z = 0;

	//create a hbar out of the vector
	healthBarGreen.tl = { healthBarGreen.center.x - 0.15f, healthBarGreen.center.y - float(PLAYER_HEIGHT / 2) * p.ent->health / 100 };
	healthBarGreen.tr = { healthBarGreen.center.x + 0.15f, healthBarGreen.center.y - float(PLAYER_HEIGHT / 2) * p.ent->health / 100 };
	healthBarGreen.br = { healthBarGreen.center.x + 0.15f, healthBarGreen.center.y + float(PLAYER_HEIGHT / 2) };
	healthBarGreen.bl = { healthBarGreen.center.x - 0.15f, healthBarGreen.center.y + float(PLAYER_HEIGHT / 2) };

	//scale all boxes
	float scale = (400 / p.dist) * fWindowScale;//WTF
	box.scale(scale);
	healthBarRed.scale(scale);
	healthBarGreen.scale(scale);

	drawRectangle(box, 2);

	//text render:
	float boxWidth = box.tr.x - box.tl.x;
	std::string playerName = p.ent->name;//annoying but need to do this?
	float textWidth = playerName.length() * 8;//8 font width

	float textX = 0;
	float textY = 0;

	if (textWidth < boxWidth)
	{
		float difference = boxWidth - textWidth;
		textX = box.tl.x + (difference / 2);

	}

	if (textWidth >= boxWidth)
	{
		float difference = textWidth - boxWidth;
		textX = box.tl.x - (difference / 2);
	}

	textY = box.tl.y -4;

	renderText(p.ent->name, GLUT_BITMAP_8_BY_13, textX, textY);

	//Draw Health Bars
	glColor3ub(0, 255, 0);//green
	drawFilledRect(healthBarGreen);
	glColor3ub(255, 0, 0);//red
	drawFilledRect(healthBarRed);
}

void esp(mapEnt * e, std::string text)
{
	float newz = (float)(1 + sinf(*lastmillis / 100.0f + e->x + e->y) / 20);
	newz = newz + e->attr1;
	int bullshit = (e->x + (e->y << *sfactor)) << 4;
	DWORD cubeAddress = bullshit + *(DWORD*)world;
	sqr * currCube = (sqr*)cubeAddress;
	newz = newz + currCube->floor + 0.5;

	float dist = Get3dDistance(localPlayer->vLocation, vec(e->x, e->y, newz));
	vec2 screenCoords = math2.W2S(glmvpmatrix, vec(e->x, e->y, newz));

	//Creates an ESP box from the center the of the object scaled in modelspace
	MyRect box;
	box.tl = { screenCoords.x - 1, screenCoords.y - 1 };
	box.tr = { screenCoords.x + 1, screenCoords.y - 1 };
	box.br = { screenCoords.x + 1, screenCoords.y + 1 };
	box.bl = { screenCoords.x - 1, screenCoords.y + 1 };
	box.center = screenCoords;

	//scale all boxes
	float scale = (400 / dist) * fWindowScale;
	box.scale(scale);

	drawRectangle(box,2);

	//text render:
	float boxWidth = box.tr.x - box.tl.x;
	float textWidth = text.length() * 8;//8 font width
	float textX;
	float textY;
	if (textWidth < boxWidth)
	{
		float difference = boxWidth - textWidth;
		textX = box.tl.x + (difference / 2);
	}
	if (textWidth >= boxWidth)
	{
		float difference = textWidth - boxWidth;
		textX = box.tl.x - (difference / 2);
	}
	textY = box.tl.y -4;
	renderText(text, GLUT_BITMAP_8_BY_13, textX, textY);
}

//flags
void esp(vec e)
{
	std::string text = "FLAG";
	float dist = Get3dDistance(localPlayer->vLocation, e);

	vec2 screenCoords = math2.W2S(glmvpmatrix, e);

	//Creates an ESP box from the center the of the object scaled in modelspace
	MyRect box;
	box.tl = { screenCoords.x - 1, screenCoords.y - 2 };
	box.tr = { screenCoords.x + 1, screenCoords.y - 2 };
	box.br = { screenCoords.x + 1, screenCoords.y + 2 };
	box.bl = { screenCoords.x - 1, screenCoords.y + 2 };
	box.center = screenCoords;

	//scale all boxes
	float scale = (400 / dist) * fWindowScale;
	box.scale(scale);

	drawRectangle(box, 2);

	//text render:
	float boxWidth = box.tr.x - box.tl.x;
	float textWidth = text.length() * 8;//8 font width
	float textX = 0;
	float textY = 0;
	if (textWidth < boxWidth)
	{
		float difference = boxWidth - textWidth;
		textX = box.tl.x + (difference / 2);
	}
	if (textWidth >= boxWidth)
	{
		float difference = textWidth - boxWidth;
		textX = box.tl.x - (difference / 2);
	}
	textY = float(box.tl.y) -4;
	renderText(text, GLUT_BITMAP_8_BY_13, textX, textY);
}


void espPlayers(std::vector<PlayerClass> playerVector)
{
	for (auto player : playerVector)
	{
		if (player.ent->state != 0 || glmvpmatrix->transformw(player.ent->vHead) < 0.1f)
			continue;
		else
		{
			esp(player);
		}
	}
}


void espMapEnts()
{
	int numOfEnts = *(int*)0x510120;
	for (int i = 0; i < numOfEnts; i++)
	{
		DWORD temp = *(DWORD*)(0x510118);
		mapEnt * e = (mapEnt*)(temp + i * 0x14);

		if (e->bSpawned == 1)
		{
			if (glmvpmatrix->transformw(vec(e->x, e->y, e->z)) < 0.1f)	{ continue; }

			switch (e->type)
			{
			case I_AMMO:
				glColor3ub(255, 255, 0);
				esp(e, "Ammo");
				break;

			case I_HEALTH:
				glColor3ub(255, 128, 0);
				esp(e, "Health");
				break;

			case I_HELMET:
				glColor3ub(255, 0, 255);
				esp(e, "Armor");
				break;

			case I_ARMOUR:
				glColor3ub(255, 0, 255);
				esp(e, "Armor");
				break;

			case I_GRENADE:
				glColor3ub(0, 255, 255);
				esp(e, "Grenade");
				break;
			}
		}
	}
}

void espFlags()
{
	enum { INBASE = 0, STOLEN = 1, DROPPED = 2, IDLE = 3 };
	flagEnt * flags[2] = { (flagEnt*)0x50F4A8, (flagEnt*)0x50F4CC };

	for each (flagEnt* flag in flags)
	{
		if (flag->team == localPlayer->team)
		{
			glColor3ub(0, 255, 0);//green
		}
		else
		{
			glColor3ub(255, 0, 0);//red
		}

		if (flag->state == STOLEN)
		{
			if (glmvpmatrix->transformw(flag->player->vLocation) < 0.1f)	{ continue; }

			esp(flag->player->vLocation);
		}

		else if (flag->state == INBASE || DROPPED)
		{
			if (glmvpmatrix->transformw(flag->pos) < 0.1f)	{ continue; }

			esp(flag->pos);
		}
	}
}