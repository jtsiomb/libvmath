/*
libvmath - a vector math library
Copyright (C) 2004-2015 John Tsiombikas <nuclear@member.fsf.org>

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

#ifndef LIBVMATH_RAY_H_
#define LIBVMATH_RAY_H_

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

class Ray {
private:
	void (*data_destructor)(void*);

public:
	Vector3 origin, dir;
	void *data; // each ray may carry additional data

	Ray();
	Ray(const Vector3 &origin, const Vector3 &dir);

	void transform(const Matrix4x4 &xform);
	Ray transformed(const Matrix4x4 &xform) const;

	void set_data(void *data, void (*data_destr_func)(void*) = 0);
};

inline Ray reflect(const Ray &inray, const Vector3 &norm);
inline Ray refract(const Ray &inray, const Vector3 &norm, scalar_t ior, scalar_t ray_mag = -1.0);
#endif	/* __cplusplus */

#include "ray.inl"

#endif	/* LIBVMATH_RAY_H_ */
