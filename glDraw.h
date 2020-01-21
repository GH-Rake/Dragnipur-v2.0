#pragma once
#include "gltext.h"
#include <string>
#include "myRect.h"

namespace rgb
{
	const GLubyte red[3] = { 255, 0, 0 };
	const GLubyte green[3] = { 0, 255, 0 };
	const GLubyte gray[3] = { 55, 55, 55 };
	const GLubyte lightgray[3] = { 192, 192, 192 };
	const GLubyte black[3] = { 0, 0, 0 };
}

//draw rectangle outline
void drawRectangle(MyRect r, float lineWidth);

void drawFilledRect(MyRect r);

//NEW:
void renderText(std::string textString, float xpos, float ypos);

void drawOutline(MyRect box);

void drawCrosshair();