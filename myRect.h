#pragma once
#include "geom.h"
extern inline void initGLDraw();

class MyRect
{
public:
	vec2 tl, tr, br, bl, center; //top left, top right, bottom right, bottom left etc...

	//equal dimension scaling
	void scale(float scale);
};

