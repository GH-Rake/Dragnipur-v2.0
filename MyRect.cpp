#include "myRect.h"

void MyRect::scale(float scale)
{
	tl.scaleFixedPoint(scale, center);
	tr.scaleFixedPoint(scale, center);
	br.scaleFixedPoint(scale, center);
	bl.scaleFixedPoint(scale, center);
}