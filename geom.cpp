#include "geom.h"

vec& vec::sub(const vec& o)
{
	x -= o.x; y -= o.y; z -= o.z; return *this;
}

const float vec::squaredlen()
{
	return x * x + y * y + z * z;
}
const float vec::magnitude()
{
	return sqrtf(squaredlen());
}

const float vec::dist(const vec& e, vec& t)
{
	t = *this; t.sub(e); return t.magnitude();
}

//scale vec at a fixed point with equal dimension for screen drawing
vec vec::scaleFixedPoint(float scale, vec fixedPoint)
{
	vec newVec;
	newVec.x = x * scale + fixedPoint.x * (1 - scale);
	newVec.y = y * scale + fixedPoint.y * (1 - scale);
	return newVec;
}

//scale vec at a fixed point, for screen drawing, variable
vec vec::scaleFixedPoint(float scalex, float scaley, vec fixedPoint)
{
	vec newVec;
	newVec.x = x * scalex + fixedPoint.x * (1 - scalex);
	newVec.y = y * scaley + fixedPoint.y * (1 - scaley);
	return newVec;
}

void vec2::scaleFixedPoint(float scale, vec2 fixedPoint)
{
	//scale = scale * fWindowScale;
	x = x * scale + fixedPoint.x * (1 - scale);
	y = y * scale + fixedPoint.y * (1 - scale);
}

const float glmatrixf::transformw(const vec& p)
{
	return p.x * v[3] + p.y * v[7] + p.z * v[11] + v[15];
}

float Get3dDistance(vec to, vec from)
{
	return
		(sqrtf(
		((to.x - from.x) * (to.x - from.x)) +
			((to.y - from.y) * (to.y - from.y)) +
			((to.z - from.z) * (to.z - from.z))
		));
}

vec CalcAngle(vec src, vec dst)
{
	vec angle;
	angle.x = -atan2f(dst.x - src.x, dst.y - src.y) / PI * 180.0f + 180.0f;
	angle.y = asinf((dst.z - src.z) / Get3dDistance(src, dst)) * (180.0f / PI);
	angle.z = 0.0f;

	return angle;
}