#ifndef GEOM_H_
#define GEOM_H_

#include "vector.h"
#include "ray.h"

typedef struct {
	vec3_t norm;
	scalar_t d;
} plane_t;

#ifdef __cplusplus
extern "C" {
#endif

plane_t plane_cons(scalar_t nx, scalar_t ny, scalar_t nz, scalar_t d);
plane_t plane_poly(vec3_t v0, vec3_t v1, vec3_t v2);
plane_t plane_ptnorm(vec3_t pt, vec3_t normal);

plane_t plane_invert(plane_t p);

scalar_t plane_signed_dist(plane_t plane, vec3_t pt);
scalar_t plane_dist(plane_t plane, vec3_t pt);
vec3_t plane_point(plane_t plane);

scalar_t plane_ray_intersect(ray_t ray, plane_t plane);

#ifdef __cplusplus
}

class Plane : public plane_t {
public:
	/* TODO */
};

#endif

#endif	/* GEOM_H_ */
