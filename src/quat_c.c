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


#include <stdio.h>
#include <math.h>
#include "quat.h"

void quat_print(FILE *fp, quat_t q)
{
	fprintf(fp, "([ %.4f %.4f %.4f ] %.4f)", q.x, q.y, q.z, q.w);
}

quat_t quat_rotate(quat_t q, scalar_t angle, scalar_t x, scalar_t y, scalar_t z)
{
	quat_t rq;
	scalar_t half_angle = angle * 0.5;
	scalar_t sin_half = sin(half_angle);

	rq.w = cos(half_angle);
	rq.x = x * sin_half;
	rq.y = y * sin_half;
	rq.z = z * sin_half;

	return quat_mul(q, rq);
}

quat_t quat_rotate_quat(quat_t q, quat_t rotq)
{
	return quat_mul(quat_mul(rotq, q), quat_conjugate(rotq));
}

quat_t quat_slerp(quat_t q1, quat_t q2, scalar_t t)
{
	quat_t res;
	scalar_t a, b, angle, sin_angle, dot;

	dot = q1.w * q2.w + q1.x * q2.x + q1.y * q2.y + q1.z * q2.z;
	if(dot < 0.0) {
		/* make sure we interpolate across the shortest arc */
		q1.x = -q1.x;
		q1.y = -q1.y;
		q1.z = -q1.z;
		q1.w = -q1.w;
		dot = -dot;
	}

	/* clamp dot to [-1, 1] in order to avoid domain errors in acos due to
	 * floating point imprecisions
	 */
	if(dot < -1.0) dot = -1.0;
	if(dot > 1.0) dot = 1.0;

	angle = acos(dot);
	sin_angle = sin(angle);

	if(fabs(sin_angle) < SMALL_NUMBER) {
		/* for very small angles or completely opposite orientations
		 * use linear interpolation to avoid div/zero (in the first case it makes sense,
		 * the second case is pretty much undefined anyway I guess ...
		 */
		a = 1.0f - t;
		b = t;
	} else {
		a = sin((1.0f - t) * angle) / sin_angle;
		b = sin(t * angle) / sin_angle;
	}

	res.x = q1.x * a + q2.x * b;
	res.y = q1.y * a + q2.y * b;
	res.z = q1.z * a + q2.z * b;
	res.w = q1.w * a + q2.w * b;
	return res;
}
