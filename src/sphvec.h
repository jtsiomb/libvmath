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

#ifndef VMATH_SPHVEC_H_
#define VMATH_SPHVEC_H_

#include "vmath_types.h"

#ifdef __cplusplus
/* Vector in spherical coordinates */
class SphVector {
public:
	scalar_t theta, phi, r;

	SphVector(scalar_t theta = 0.0, scalar_t phi = 0.0, scalar_t r = 1.0);
	SphVector(const Vector3 &cvec);
	SphVector &operator =(const Vector3 &cvec);
};
#endif	/* __cplusplus */

#endif	/* VMATH_SPHVEC_H_ */
