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
