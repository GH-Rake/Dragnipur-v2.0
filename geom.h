#pragma once
#define PI 3.14159265358979323846
#include <cmath>

struct vec
{
	float x, y, z;

	vec() { x = y = z = 0; }
	vec(float a, float b, float c) : x(a), y(b), z(c) {}

	vec& sub(const vec& o);
	const float squaredlen();
	const float magnitude();
	const float dist(const vec& e, vec& t);

	//scale vec at a fixed point with equal dimension for screen drawing
	vec scaleFixedPoint(float scale, vec fixedPoint);

	//scale vec at a fixed point, for screen drawing, variable width & height
	vec scaleFixedPoint(float scalex, float scaley, vec fixedPoint);
};

struct vec2
{
	float x{ 0 };
	float y{ 0 };
	//scale vec at a fixed point with equal dimension for screen drawing
	void scaleFixedPoint(float scale, vec2 fixedPoint);
};

struct vec4
{
	float x, y, z, w;
};

struct glmatrixf
{
	float v[16];
	const float transformw(const vec& p);
};

float Get3dDistance(vec to, vec from);

vec CalcAngle(vec src, vec dst);

vec2 W2S(glmatrixf* mvpmatrix, vec vPlayerLoc);