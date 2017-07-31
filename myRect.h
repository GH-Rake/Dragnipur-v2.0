#pragma once
extern inline void initGLDraw();

class MyRect
{
public:
	vec2 tl, tr, br, bl, center; //top left, top right, bottom right, bottom left etc...

	//equal dimension scaling
	void scale(float scale)
	{
		tl.scaleFixedPoint(scale, center);
		tr.scaleFixedPoint(scale, center);
		br.scaleFixedPoint(scale, center);
		bl.scaleFixedPoint(scale, center);
	}

	/*
	//variable dimension scaling
	void scale(float scalex, float scaley)
	{
	tl = tl.scaleFixedPoint(scalex, scaley, center);
	tr = tr.scaleFixedPoint(scalex, scaley, center);
	br = br.scaleFixedPoint(scalex, scaley, center);
	bl = bl.scaleFixedPoint(scalex, scaley, center);
	}
	*/
};