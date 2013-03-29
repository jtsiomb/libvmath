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

#ifndef VMATH_RAY_H_
#define VMATH_RAY_H_

#include "matrix.h"
#include "vector.h"

typedef struct {
	vec3_t origin, dir;
} ray_t;

#ifdef __cplusplus
extern "C" {
#endif	/* __cplusplus */

static inline ray_t ray_cons(vec3_t origin, vec3_t dir);
ray_t ray_transform(ray_t r, mat4_t m);

#ifdef __cplusplus
}	/* __cplusplus */

#include <stack>

class Ray {
public:
	static scalar_t env_ior;

	Vector3 origin, dir;
	scalar_t energy;
	int iter;
	scalar_t ior;
	long time;

	Ray();
	Ray(const Vector3 &origin, const Vector3 &dir);

	void transform(const Matrix4x4 &xform);
	Ray transformed(const Matrix4x4 &xform) const;
};

inline Ray reflect_ray(const Ray &inray, const Vector3 &norm);
inline Ray refract_ray(const Ray &inray, const Vector3 &norm, scalar_t from_ior, scalar_t to_ior);
#endif	/* __cplusplus */

#include "ray.inl"

#endif	/* VMATH_RAY_H_ */
