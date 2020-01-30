#pragma once
#include "glDraw.h"
#include <vector>

extern float fWindowScale;

float centerTextX(MyRect box, std::string text);

vec2 centerTextXY(MyRect box, std::string text);

extern GL::Font font;

class Menu
{
public:
	bool bStatus = true;
	int iTab = 1;

	std::string menuText[10];
	std::string sAimbotStatus = "OFF";
	std::string sHeadshots = "OFF";
	std::string sNoRecoil = "OFF";
	std::string sESP = "OFF";
	std::string sMapHack = "OFF";
	std::string sFlyHackStatus = "OFF";
	std::string sFullbright = "OFF";
	std::string sScopeHack = "OFF";

	float textHeight = 15;
	float buff = 2;
	float menuWidth = 0;
	float header = buff + textHeight + buff;
	float textWidth = 9;
	float buffW = textWidth * 2;
	float tabHeight = buff + textHeight + buff;
	float numFunctions = 8;
	float body = buff + numFunctions * (textHeight + buff) + buff;
	float footer = header;
	float outlineWidth = 2;

	//new
	void renderLine(std::string textString, float& xpos, float& ypos);

	void DrawMenu();
};
