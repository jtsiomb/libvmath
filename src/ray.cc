#include "ray.h"
#include "vector.h"

scalar_t Ray::env_ior = 1.0;

Ray::Ray()
{
	ior = env_ior;
	energy = 1.0;
	time = 0;
	iter = 0;
}

Ray::Ray(const Vector3 &origin, const Vector3 &dir)
{
	this->origin = origin;
	this->dir = dir;
	ior = env_ior;
	energy = 1.0;
	time = 0;
	iter = 0;
}

void Ray::transform(const Matrix4x4 &xform)
{
	Matrix4x4 upper = xform;
	upper[0][3] = upper[1][3] = upper[2][3] = upper[3][0] = upper[3][1] = upper[3][2] = 0.0;
	upper[3][3] = 1.0;

	dir.transform(upper);
	origin.transform(xform);
}

Ray Ray::transformed(const Matrix4x4 &xform) const
{
	Ray foo = *this;
	foo.transform(xform);
	return foo;
}
