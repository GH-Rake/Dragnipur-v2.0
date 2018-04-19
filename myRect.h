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

void MyRect::scale(float scale)
{
	tl.scaleFixedPoint(scale, center);
	tr.scaleFixedPoint(scale, center);
	br.scaleFixedPoint(scale, center);
	bl.scaleFixedPoint(scale, center);
}