#pragma once
#define PI ( 3.1415927f )

struct vec
{
	float x, y, z;

	vec() { x = y = z = 0; }
	vec(float a, float b, float c) : x(a), y(b), z(c) {}
	vec(float *v) : x(v[0]), y(v[1]), z(v[2]) {}

	bool iszero() const { return x == 0 && y == 0 && z == 0; }

	bool operator==(const vec &o) const { return x == o.x && y == o.y && z == o.z; }
	bool operator!=(const vec &o) const { return x != o.x || y != o.y || z != o.z; }
	vec operator-() const { return vec(-x, -y, -z); }

	vec &mul(float f) { x *= f; y *= f; z *= f; return *this; }
	vec &div(float f) { x /= f; y /= f; z /= f; return *this; }
	vec &add(float f) { x += f; y += f; z += f; return *this; }
	vec &sub(float f) { x -= f; y -= f; z -= f; return *this; }

	vec &add(const vec &o) { x += o.x; y += o.y; z += o.z; return *this; }
	vec &sub(const vec &o) { x -= o.x; y -= o.y; z -= o.z; return *this; }

	float squaredlen() const { return x*x + y*y + z*z; }
	float sqrxy() const { return x*x + y*y; }

	float dot(const vec &o) const { return x*o.x + y*o.y + z*o.z; }
	float dotxy(const vec &o) const { return x*o.x + y*o.y; }

	float magnitude() const { return sqrtf(squaredlen()); }
	vec &normalize() { div(magnitude()); return *this; }

	float dist(const vec &e) const { vec t; return dist(e, t); }
	float dist(const vec &e, vec &t) const { t = *this; t.sub(e); return t.magnitude(); }

	float distxy(const vec &e) const { float dx = e.x - x, dy = e.y - y; return sqrtf(dx*dx + dy*dy); }
	float magnitudexy() const { return sqrtf(x*x + y*y); }

	vec &cross(const vec &a, const vec &b) { x = a.y*b.z - a.z*b.y; y = a.z*b.x - a.x*b.z; z = a.x*b.y - a.y*b.x; return *this; }
	float cxy(const vec &a) { return x*a.y - y*a.x; }

	void rotate_around_z(float angle) { *this = vec(cosf(angle)*x - sinf(angle)*y, cosf(angle)*y + sinf(angle)*x, z); }
	void rotate_around_x(float angle) { *this = vec(x, cosf(angle)*y - sinf(angle)*z, cosf(angle)*z + sinf(angle)*y); }
	void rotate_around_y(float angle) { *this = vec(cosf(angle)*x - sinf(angle)*z, y, cosf(angle)*z + sinf(angle)*x); }

	vec &rotate(float angle, const vec &d)
	{
		float c = cosf(angle), s = sinf(angle);
		return rotate(c, s, d);
	}

	vec &rotate(float c, float s, const vec &d)
	{
		*this = vec(x*(d.x*d.x*(1 - c) + c) + y*(d.x*d.y*(1 - c) - d.z*s) + z*(d.x*d.z*(1 - c) + d.y*s),
			x*(d.y*d.x*(1 - c) + d.z*s) + y*(d.y*d.y*(1 - c) + c) + z*(d.y*d.z*(1 - c) - d.x*s),
			x*(d.x*d.z*(1 - c) - d.y*s) + y*(d.y*d.z*(1 - c) + d.x*s) + z*(d.z*d.z*(1 - c) + c));
		return *this;
	}

	//scale vec at a fixed point with equal dimension for screen drawing
	vec scaleFixedPoint(float scale, vec fixedPoint)
	{
		vec newVec;

		newVec.x = x * scale + fixedPoint.x*(1 - scale);
		newVec.y = y * scale + fixedPoint.y*(1 - scale);
		return newVec;
	}

	//scale vec at a fixed point, for screen drawing, variable
	vec scaleFixedPoint(float scalex, float scaley, vec fixedPoint)
	{
		vec newVec;

		newVec.x = x * scalex + fixedPoint.x*(1 - scalex);
		newVec.y = y * scaley + fixedPoint.y*(1 - scaley);
		return newVec;
	}
};

struct vec2
{
	float x, y;
	//scale vec at a fixed point with equal dimension for screen drawing
	void scaleFixedPoint(float scale, vec2 fixedPoint)
	{
		//scale = scale * fWindowScale;
		x = x * scale + fixedPoint.x*(1 - scale);
		y = y * scale + fixedPoint.y*(1 - scale);
	}
};

struct vec4
{
	union
	{
		struct { float x, y, z, w; };
		float v[4];
	};

	vec4() {}
	explicit vec4(const vec &p, float w = 0) : x(p.x), y(p.y), z(p.z), w(w) {}
	vec4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}

	float &operator[](int i) { return v[i]; }
	float  operator[](int i) const { return v[i]; }
};

struct glmatrixf
{
	float v[16];

	float operator[](int i) const { return v[i]; }
	float &operator[](int i) { return v[i]; }

#define ROTVEC(A, B) \
		    { \
        float a = A, b = B; \
        A = a*c + b*s; \
        B = b*c - a*s; \
		    }

	void rotate_around_x(float angle)
	{
		float c = cosf(angle), s = sinf(angle);
		ROTVEC(v[4], v[8]);
		ROTVEC(v[5], v[9]);
		ROTVEC(v[6], v[10]);
	}

	void rotate_around_y(float angle)
	{
		float c = cosf(angle), s = sinf(angle);
		ROTVEC(v[8], v[0]);
		ROTVEC(v[9], v[1]);
		ROTVEC(v[10], v[2]);
	}

	void rotate_around_z(float angle)
	{
		float c = cosf(angle), s = sinf(angle);
		ROTVEC(v[0], v[4]);
		ROTVEC(v[1], v[5]);
		ROTVEC(v[2], v[6]);
	}

#undef ROTVEC

#define MULMAT(row, col) v[col + row] = x[row]*y[col] + x[row + 4]*y[col + 1] + x[row + 8]*y[col + 2] + x[row + 12]*y[col + 3];

	template<class XT, class YT>
	void mul(const XT x[16], const YT y[16])
	{
		MULMAT(0, 0); MULMAT(1, 0); MULMAT(2, 0); MULMAT(3, 0);
		MULMAT(0, 4); MULMAT(1, 4); MULMAT(2, 4); MULMAT(3, 4);
		MULMAT(0, 8); MULMAT(1, 8); MULMAT(2, 8); MULMAT(3, 8);
		MULMAT(0, 12); MULMAT(1, 12); MULMAT(2, 12); MULMAT(3, 12);
	}

#undef MULMAT

	void mul(const glmatrixf &x, const glmatrixf &y)
	{
		mul(x.v, y.v);
	}

	void identity()
	{
		static const float m[16] =
		{
			1, 0, 0, 0,
			0, 1, 0, 0,
			0, 0, 1, 0,
			0, 0, 0, 1
		};
		memcpy(v, m, sizeof(v));
	}

	void translate(float x, float y, float z)
	{
		v[12] += x;
		v[13] += y;
		v[14] += z;
	}

	void translate(const vec &o)
	{
		translate(o.x, o.y, o.z);
	}

	void scale(float x, float y, float z)
	{
		v[0] *= x; v[1] *= x; v[2] *= x; v[3] *= x;
		v[4] *= y; v[5] *= y; v[6] *= y; v[7] *= y;
		v[8] *= z; v[9] *= z; v[10] *= z; v[11] *= z;
	}

	void invertnormal(vec &dir) const
	{
		vec n(dir);
		dir.x = n.x*v[0] + n.y*v[1] + n.z*v[2];
		dir.y = n.x*v[4] + n.y*v[5] + n.z*v[6];
		dir.z = n.x*v[8] + n.y*v[9] + n.z*v[10];
	}

	void invertvertex(vec &pos) const
	{
		vec p(pos);
		p.x -= v[12];
		p.y -= v[13];
		p.z -= v[14];
		pos.x = p.x*v[0] + p.y*v[1] + p.z*v[2];
		pos.y = p.x*v[4] + p.y*v[5] + p.z*v[6];
		pos.z = p.x*v[8] + p.y*v[9] + p.z*v[10];
	}

	void transform(const vec &in, vec4 &out) const
	{
		out.x = transformx(in);
		out.y = transformy(in);
		out.z = transformz(in);
		out.w = transformw(in);
	}

	float transformx(const vec &p) const
	{
		return p.x*v[0] + p.y*v[4] + p.z*v[8] + v[12];
	}

	float transformy(const vec &p) const
	{
		return p.x*v[1] + p.y*v[5] + p.z*v[9] + v[13];
	}

	float transformz(const vec &p) const
	{
		return p.x*v[2] + p.y*v[6] + p.z*v[10] + v[14];
	}

	float transformw(const vec &p) const
	{
		return p.x*v[3] + p.y*v[7] + p.z*v[11] + v[15];
	}

	//assault cube super optimized code, I may use this in the future.
	//same output as vec normalizedDeviceCoordinates = math2.transform(glmvpmatrix, player.ent->vCenterOfPlayer);
	//multiply by model view projection matrix = clip coordinates then divide by w to get NormalizedDeviceCoordinates
	vec transform(glmatrixf *matrix, vec &totransform)
	{
		return vec(matrix->transformx(totransform),
			matrix->transformy(totransform),
			matrix->transformz(totransform)).div(matrix->transformw(totransform));
	}

	////vPlayerLoc should be the exact center of the enemy model for scaling to work properly
	////multiply by model view projection matrix = clip coordinates then divide by w to get NormalizedDeviceCoordinates

	vec2 W2S(glmatrixf *mvpmatrix, vec vPlayerLoc)
	{
		//Matrix-Vector Product, multiplying world(eye) coordinates by projection matrix = clipCoords
		vec4 clipCoords;
		clipCoords.x = vPlayerLoc.x*mvpmatrix->v[0] + vPlayerLoc.y*mvpmatrix->v[4] + (vPlayerLoc.z)*mvpmatrix->v[8] + mvpmatrix->v[12];
		clipCoords.y = vPlayerLoc.x*mvpmatrix->v[1] + vPlayerLoc.y*mvpmatrix->v[5] + (vPlayerLoc.z)*mvpmatrix->v[9] + mvpmatrix->v[13];
		clipCoords.z = vPlayerLoc.x*mvpmatrix->v[2] + vPlayerLoc.y*mvpmatrix->v[6] + (vPlayerLoc.z)*mvpmatrix->v[10] + mvpmatrix->v[14];
		clipCoords.w = vPlayerLoc.x*mvpmatrix->v[3] + vPlayerLoc.y*mvpmatrix->v[7] + (vPlayerLoc.z)*mvpmatrix->v[11] + mvpmatrix->v[15];

		//perspective division, dividing by clip.W = NDC
		vec normalizedDeviceCoordinates;
		normalizedDeviceCoordinates.x = clipCoords.x / clipCoords.w;
		normalizedDeviceCoordinates.y = clipCoords.y / clipCoords.w;
		normalizedDeviceCoordinates.z = clipCoords.z / clipCoords.w;

		//viewport tranform to screenCooords
		GLfloat viewport[4] = { 0 };
		GLfloat depthrange[2] = { 0 };
		glGetFloatv(GL_VIEWPORT, viewport); // viewport = (0, 0, width, height)
		glGetFloatv(GL_DEPTH_RANGE, depthrange); //depthrange = (0,1)

		vec2 playerScreenCoords;
		playerScreenCoords.x = (viewport[2] / 2 * normalizedDeviceCoordinates.x) + (normalizedDeviceCoordinates.x + viewport[2] / 2);
		playerScreenCoords.y = -(viewport[3] / 2 * normalizedDeviceCoordinates.y) + (normalizedDeviceCoordinates.y + viewport[3] / 2);

		return playerScreenCoords;
	}

	vec gettranslation() const
	{
		return vec(v[12], v[13], v[14]);
	}
}math2;

//MFD
float distxy(vec src, vec dst)
{
	float dx = dst.x - src.x;
	float dy = dst.y - src.y;
	return sqrtf(dx*dx + dy*dy);
}

float Get3dDistance(vec to, vec from)
{
	return (float)
		(sqrt(
		((to.x - from.x) * (to.x - from.x)) +
			((to.y - from.y) * (to.y - from.y)) +
			((to.z - from.z) * (to.z - from.z))
		));
}

vec CalcAngle(vec src, vec dst)
{
	vec angles;

	angles.x = (-(float)atan2(dst.x - src.x, dst.y - src.y)) / PI * 180.0f + 180.0f;
	angles.y = (atan2(dst.z - src.z, Get3dDistance(src, dst))) * 180.0f / PI;//
	angles.z = 0.0f;

	return angles;
}

float DifferenceOfAngles(vec to, vec from)
{
	vec vdifference;

	vdifference.y = from.y - to.y;
	vdifference.x = from.x - to.x;

	//normalize by making them positive values if they are negative
	if (vdifference.y < 0)
	{
		vdifference.y *= -1;
	}
	if (vdifference.x < 0)
	{
		vdifference.x *= -1;
	}

	//add them together and divide by 2, gives an average of the 2 angles
	float fDifference = (vdifference.y + vdifference.x) / 2;
	return fDifference;
}