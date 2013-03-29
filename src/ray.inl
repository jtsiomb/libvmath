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

#ifdef __cplusplus
extern "C" {
#endif	/* __cplusplus */

static inline ray_t ray_cons(vec3_t origin, vec3_t dir)
{
	ray_t r;
	r.origin = origin;
	r.dir = dir;
	return r;
}

#ifdef __cplusplus
}

inline Ray reflect_ray(const Ray &inray, const Vector3 &norm)
{
	Ray ray = inray;
	ray.dir = ray.dir.reflection(norm);
	return ray;
}

inline Ray refract_ray(const Ray &inray, const Vector3 &norm, scalar_t from_ior, scalar_t to_ior)
{
	Ray ray = inray;
	ray.dir = ray.dir.refraction(norm, from_ior, to_ior);

	/* check TIR */
	if(dot_product(ray.dir, norm) > 0.0) {
		return reflect_ray(inray, norm);
	}
	return ray;
}
#endif	/* __cplusplus */
