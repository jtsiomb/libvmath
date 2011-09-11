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

#ifndef VMATH_TYPES_H_
#define VMATH_TYPES_H_

#include "vmath_config.h"

#define SMALL_NUMBER	1.e-4
#define XSMALL_NUMBER	1.e-8
#define ERROR_MARGIN	1.e-6


#ifdef SINGLE_PRECISION_MATH
typedef float scalar_t;
#else
typedef double scalar_t;
#endif	/* floating point precision */

/* vectors */
typedef struct { scalar_t x, y; } vec2_t;
typedef struct { scalar_t x, y, z; } vec3_t;
typedef struct { scalar_t x, y, z, w; } vec4_t;

/* quaternions */
typedef vec4_t quat_t;

/* matrices */
typedef scalar_t mat3_t[3][3];
typedef scalar_t mat4_t[4][4];


#ifdef __cplusplus
class Vector2;
class Vector3;
class Vector4;
class Quaternion;
class Matrix3x3;
class Matrix4x4;
class SphVector;
#endif	/* __cplusplus */

#endif	/* VMATH_TYPES_H_ */
