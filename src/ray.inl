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
	ray.iter--;
	ray.dir = ray.dir.reflection(norm);
	return ray;
}

inline Ray refract_ray(const Ray &inray, const Vector3 &norm, scalar_t mat_ior, bool entering, scalar_t ray_mag)
{
	Ray ray = inray;
	ray.iter--;

	scalar_t ior = ray.calc_ior(entering, mat_ior);

	if(entering) {
		ray.enter(mat_ior);
	} else {
		ray.leave();
	}

	if(ray_mag < 0.0) {
		ray_mag = ray.dir.length();
	}
	ray.dir = (ray.dir / ray_mag).refraction(norm, ior) * ray_mag;

	/* check TIR */
	if(dot_product(ray.dir, norm) > 0.0) {
		if(entering) {
			ray.leave();
		} else {
			ray.enter(mat_ior);
		}
	}
	return ray;
}
#endif	/* __cplusplus */
