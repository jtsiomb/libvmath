#include <math.h>
#include "geom.h"
#include "vector.h"

plane_t plane_cons(scalar_t nx, scalar_t ny, scalar_t nz, scalar_t d)
{
	plane_t p;
	p.norm.x = nx;
	p.norm.y = ny;
	p.norm.z = nz;
	p.d = d;
	return p;
}

plane_t plane_poly(vec3_t v0, vec3_t v1, vec3_t v2)
{
	vec3_t a, b, norm;

	a = v3_sub(v1, v0);
	b = v3_sub(v2, v0);
	norm = v3_cross(a, b);
	norm = v3_normalize(norm);

	return plane_ptnorm(v0, norm);
}

plane_t plane_ptnorm(vec3_t pt, vec3_t normal)
{
	plane_t plane;

	plane.norm = normal;
	plane.d = v3_dot(pt, normal);

	return plane;
}

plane_t plane_invert(plane_t p)
{
	p.norm = v3_neg(p.norm);
	p.d = -p.d;
	return p;
}

scalar_t plane_signed_dist(plane_t plane, vec3_t pt)
{
	vec3_t pp = plane_point(plane);
	vec3_t pptopt = v3_sub(pt, pp);
	return v3_dot(pptopt, plane.norm);
}

scalar_t plane_dist(plane_t plane, vec3_t pt)
{
	return fabs(plane_signed_dist(plane, pt));
}

vec3_t plane_point(plane_t plane)
{
	return v3_scale(plane.norm, plane.d);
}
