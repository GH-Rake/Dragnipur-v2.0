#pragma once
#include "geom.h"
//#include "openGLHacks.h"

extern inline void initGLDraw();

class MyRect
{
public:
	vec2 tl, tr, br, bl, center; //top left, top right, bottom right, bottom left

	//equal dimension scaling
	void scale(float scale);
};
