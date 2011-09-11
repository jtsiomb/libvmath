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

#include "ray.h"
#include "vector.h"

ray_t ray_transform(ray_t r, mat4_t xform)
{
	mat4_t upper;
	vec3_t dir;

	m4_copy(upper, xform);
	upper[0][3] = upper[1][3] = upper[2][3] = upper[3][0] = upper[3][1] = upper[3][2] = 0.0;
	upper[3][3] = 1.0;

	dir = v3_sub(r.dir, r.origin);
	dir = v3_transform(dir, upper);
	r.origin = v3_transform(r.origin, xform);
	r.dir = v3_add(dir, r.origin);
	return r;
}
