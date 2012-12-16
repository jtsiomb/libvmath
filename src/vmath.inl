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

#include <stdlib.h>

static inline scalar_t smoothstep(float a, float b, float x)
{
	if(x < a) return 0.0;
	if(x >= b) return 1.0;

	x = (x - a) / (b - a);
	return x * x * (3.0 - 2.0 * x);
}

/** Generates a random number in [0, range) */
static inline scalar_t frand(scalar_t range)
{
	return range * (scalar_t)rand() / (scalar_t)RAND_MAX;
}

/** Generates a random vector on the surface of a sphere */
static inline vec3_t sphrand(scalar_t rad)
{
	scalar_t u = (scalar_t)rand() / RAND_MAX;
	scalar_t v = (scalar_t)rand() / RAND_MAX;

	scalar_t theta = 2.0 * M_PI * u;
	scalar_t phi = acos(2.0 * v - 1.0);

	vec3_t res;
	res.x = rad * cos(theta) * sin(phi);
	res.y = rad * sin(theta) * sin(phi);
	res.z = rad * cos(phi);
	return res;
}

/** linear interpolation */
static inline scalar_t lerp(scalar_t a, scalar_t b, scalar_t t)
{
	return a + (b - a) * t;
}
