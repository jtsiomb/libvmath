/*
libvmath - a vector math library
Copyright (C) 2004-2011 John Tsiombikas <nuclear@member.fsf.org>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published
by the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/


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

int plane_ray_intersect(ray_t ray, plane_t plane, scalar_t *pos)
{
	vec3_t pt, orig_to_pt;
	scalar_t ndotdir;

	pt = plane_point(plane);
	ndotdir = v3_dot(plane.norm, ray.dir);

	if(fabs(ndotdir) < 1e-7) {
		return 0;
	}

	if(pos) {
		orig_to_pt = v3_sub(pt, ray.origin);
		*pos = v3_dot(plane.norm, orig_to_pt) / ndotdir;
	}
	return 1;
}

sphere_t sphere_cons(scalar_t x, scalar_t y, scalar_t z, scalar_t rad)
{
	sphere_t sph;
	sph.pos.x = x;
	sph.pos.y = y;
	sph.pos.z = z;
	sph.rad = rad;
	return sph;
}

int sphere_ray_intersect(ray_t ray, sphere_t sph, scalar_t *pos)
{
	scalar_t a, b, c, d, sqrt_d, t1, t2, t;

	a = v3_dot(ray.dir, ray.dir);
	b = 2.0 * ray.dir.x * (ray.origin.x - sph.pos.x) +
		2.0 * ray.dir.y * (ray.origin.y - sph.pos.y) +
		2.0 * ray.dir.z * (ray.origin.z - sph.pos.z);
	c = v3_dot(sph.pos, sph.pos) + v3_dot(ray.origin, ray.origin) +
		2.0 * v3_dot(v3_neg(sph.pos), ray.origin) - sph.rad * sph.rad;

	d = b * b - 4.0 * a * c;
	if(d < 0.0) {
		return 0;
	}

	sqrt_d = sqrt(d);
	t1 = (-b + sqrt_d) / (2.0 * a);
	t2 = (-b - sqrt_d) / (2.0 * a);

	if(t1 < 1e-7 || t1 > 1.0) {
		t1 = t2;
	}
	if(t2 < 1e-7 || t2 > 1.0) {
		t2 = t1;
	}
	t = t1 < t2 ? t1 : t2;

	if(t < 1e-7 || t > 1.0) {
		return 0;
	}

	if(pos) {
		*pos = t;
	}
	return 1;
}

int sphere_sphere_intersect(sphere_t sph1, sphere_t sph2, scalar_t *pos, scalar_t *rad)
{
	return -1;
}
