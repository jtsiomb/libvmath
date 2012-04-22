/*
libvmath - a vector math library
Copyright (C) 2004-2012 John Tsiombikas <nuclear@member.fsf.org>

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
#ifndef LIBVMATH_GEOM_H_
#define LIBVMATH_GEOM_H_

#include "vector.h"
#include "ray.h"

typedef struct {
	vec3_t norm;
	scalar_t d;
} plane_t;

typedef struct {
	vec3_t pos;
	scalar_t rad;
} sphere_t;

typedef struct {
	vec3_t min, max;
} aabox_t;

#ifdef __cplusplus
extern "C" {
#endif

/* planes are good... you need planes, yes you do */
plane_t plane_cons(scalar_t nx, scalar_t ny, scalar_t nz, scalar_t d);
plane_t plane_poly(vec3_t v0, vec3_t v1, vec3_t v2);
plane_t plane_ptnorm(vec3_t pt, vec3_t normal);

plane_t plane_invert(plane_t p);

scalar_t plane_signed_dist(plane_t plane, vec3_t pt);
scalar_t plane_dist(plane_t plane, vec3_t pt);
vec3_t plane_point(plane_t plane);

int plane_ray_intersect(ray_t ray, plane_t plane, scalar_t *pos);

/* spheres always come in handy */
sphere_t sphere_cons(scalar_t x, scalar_t y, scalar_t z, scalar_t rad);

int sphere_ray_intersect(ray_t ray, sphere_t sph, scalar_t *pos);
int sphere_sphere_intersect(sphere_t sph1, sphere_t sph2, scalar_t *pos, scalar_t *rad);

#ifdef __cplusplus
}

/* TODO
class Plane : public plane_t {
public:
};
*/

#endif

#endif	/* LIBVMATH_GEOM_H_ */
