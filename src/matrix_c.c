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
#include "matrix.h"
#include "vector.h"
#include "quat.h"

void m3_to_m4(mat4_t dest, mat3_t src)
{
	int i, j;

	memset(dest, 0, sizeof(mat4_t));
	for(i=0; i<3; i++) {
		for(j=0; j<3; j++) {
			dest[i][j] = src[i][j];
		}
	}
	dest[3][3] = 1.0;
}

void m3_print(FILE *fp, mat3_t m)
{
	int i;
	for(i=0; i<3; i++) {
		fprintf(fp, "[ %12.5f %12.5f %12.5f ]\n", (float)m[i][0], (float)m[i][1], (float)m[i][2]);
	}
}

/* C matrix 4x4 functions */
void m4_to_m3(mat3_t dest, mat4_t src)
{
	int i, j;
	for(i=0; i<3; i++) {
		for(j=0; j<3; j++) {
			dest[i][j] = src[i][j];
		}
	}
}

void m4_set_translation(mat4_t m, scalar_t x, scalar_t y, scalar_t z)
{
	m4_identity(m);
	m[0][3] = x;
	m[1][3] = y;
	m[2][3] = z;
}

void m4_translate(mat4_t m, scalar_t x, scalar_t y, scalar_t z)
{
	mat4_t tm;
	m4_set_translation(tm, x, y, z);
	m4_mult(m, m, tm);
}

void m4_rotate(mat4_t m, scalar_t x, scalar_t y, scalar_t z)
{
	m4_rotate_x(m, x);
	m4_rotate_y(m, y);
	m4_rotate_z(m, z);
}

void m4_set_rotation_x(mat4_t m, scalar_t angle)
{
	m4_identity(m);
	m[1][1] = cos(angle); m[1][2] = -sin(angle);
	m[2][1] = sin(angle); m[2][2] = cos(angle);
}

void m4_rotate_x(mat4_t m, scalar_t angle)
{
	mat4_t rm;
	m4_set_rotation_x(m, angle);
	m4_mult(m, m, rm);
}

void m4_set_rotation_y(mat4_t m, scalar_t angle)
{
	m4_identity(m);
	m[0][0] = cos(angle); m[0][2] = sin(angle);
	m[2][0] = -sin(angle); m[2][2] = cos(angle);
}

void m4_rotate_y(mat4_t m, scalar_t angle)
{
	mat4_t rm;
	m4_set_rotation_y(rm, angle);
	m4_mult(m, m, rm);
}

void m4_set_rotation_z(mat4_t m, scalar_t angle)
{
	m4_identity(m);
	m[0][0] = cos(angle); m[0][1] = -sin(angle);
	m[1][0] = sin(angle); m[1][1] = cos(angle);
}

void m4_rotate_z(mat4_t m, scalar_t angle)
{
	mat4_t rm;
	m4_set_rotation_z(rm, angle);
	m4_mult(m, m, rm);
}

void m4_set_rotation_axis(mat4_t m, scalar_t angle, scalar_t x, scalar_t y, scalar_t z)
{
	scalar_t sina = sin(angle);
	scalar_t cosa = cos(angle);
	scalar_t one_minus_cosa = 1.0 - cosa;
	scalar_t nxsq = x * x;
	scalar_t nysq = y * y;
	scalar_t nzsq = z * z;

	m[0][0] = nxsq + (1.0 - nxsq) * cosa;
	m[0][1] = x * y * one_minus_cosa - z * sina;
	m[0][2] = x * z * one_minus_cosa + y * sina;
	m[1][0] = x * y * one_minus_cosa + z * sina;
	m[1][1] = nysq + (1.0 - nysq) * cosa;
	m[1][2] = y * z * one_minus_cosa - x * sina;
	m[2][0] = x * z * one_minus_cosa - y * sina;
	m[2][1] = y * z * one_minus_cosa + x * sina;
	m[2][2] = nzsq + (1.0 - nzsq) * cosa;

	/* the rest are identity */
	m[3][0] = m[3][1] = m[3][2] = m[0][3] = m[1][3] = m[2][3] = 0.0;
	m[3][3] = 1.0;
}

void m4_rotate_axis(mat4_t m, scalar_t angle, scalar_t x, scalar_t y, scalar_t z)
{
	mat4_t xform;
	m4_set_rotation_axis(xform, angle, x, y, z);
	m4_mult(m, m, xform);
}

void m4_rotate_quat(mat4_t m, quat_t q)
{
	mat4_t rm;
	quat_to_mat4(rm, q);
	m4_mult(m, m, rm);
}

void m4_scale(mat4_t m, scalar_t x, scalar_t y, scalar_t z)
{
	mat4_t sm;
	m4_identity(sm);
	sm[0][0] = x;
	sm[1][1] = y;
	sm[2][2] = z;
	m4_mult(m, m, sm);
}

void m4_transpose(mat4_t res, mat4_t m)
{
	int i, j;
	mat4_t tmp;
	m4_copy(tmp, m);

	for(i=0; i<4; i++) {
		for(j=0; j<4; j++) {
			res[i][j] = tmp[j][i];
		}
	}
}

scalar_t m4_determinant(mat4_t m)
{
	scalar_t det11 =	(m[1][1] * (m[2][2] * m[3][3] - m[3][2] * m[2][3])) -
						(m[1][2] * (m[2][1] * m[3][3] - m[3][1] * m[2][3])) +
						(m[1][3] * (m[2][1] * m[3][2] - m[3][1] * m[2][2]));

	scalar_t det12 =	(m[1][0] * (m[2][2] * m[3][3] - m[3][2] * m[2][3])) -
						(m[1][2] * (m[2][0] * m[3][3] - m[3][0] * m[2][3])) +
						(m[1][3] * (m[2][0] * m[3][2] - m[3][0] * m[2][2]));

	scalar_t det13 =	(m[1][0] * (m[2][1] * m[3][3] - m[3][1] * m[2][3])) -
						(m[1][1] * (m[2][0] * m[3][3] - m[3][0] * m[2][3])) +
						(m[1][3] * (m[2][0] * m[3][1] - m[3][0] * m[2][1]));

	scalar_t det14 =	(m[1][0] * (m[2][1] * m[3][2] - m[3][1] * m[2][2])) -
						(m[1][1] * (m[2][0] * m[3][2] - m[3][0] * m[2][2])) +
						(m[1][2] * (m[2][0] * m[3][1] - m[3][0] * m[2][1]));

	return m[0][0] * det11 - m[0][1] * det12 + m[0][2] * det13 - m[0][3] * det14;
}

void m4_adjoint(mat4_t res, mat4_t m)
{
	int i, j;
	mat4_t coef;

	coef[0][0] =	(m[1][1] * (m[2][2] * m[3][3] - m[3][2] * m[2][3])) -
					(m[1][2] * (m[2][1] * m[3][3] - m[3][1] * m[2][3])) +
					(m[1][3] * (m[2][1] * m[3][2] - m[3][1] * m[2][2]));
	coef[0][1] =	(m[1][0] * (m[2][2] * m[3][3] - m[3][2] * m[2][3])) -
					(m[1][2] * (m[2][0] * m[3][3] - m[3][0] * m[2][3])) +
					(m[1][3] * (m[2][0] * m[3][2] - m[3][0] * m[2][2]));
	coef[0][2] =	(m[1][0] * (m[2][1] * m[3][3] - m[3][1] * m[2][3])) -
					(m[1][1] * (m[2][0] * m[3][3] - m[3][0] * m[2][3])) +
					(m[1][3] * (m[2][0] * m[3][1] - m[3][0] * m[2][1]));
	coef[0][3] =	(m[1][0] * (m[2][1] * m[3][2] - m[3][1] * m[2][2])) -
					(m[1][1] * (m[2][0] * m[3][2] - m[3][0] * m[2][2])) +
					(m[1][2] * (m[2][0] * m[3][1] - m[3][0] * m[2][1]));

	coef[1][0] =	(m[0][1] * (m[2][2] * m[3][3] - m[3][2] * m[2][3])) -
					(m[0][2] * (m[2][1] * m[3][3] - m[3][1] * m[2][3])) +
					(m[0][3] * (m[2][1] * m[3][2] - m[3][1] * m[2][2]));
	coef[1][1] =	(m[0][0] * (m[2][2] * m[3][3] - m[3][2] * m[2][3])) -
					(m[0][2] * (m[2][0] * m[3][3] - m[3][0] * m[2][3])) +
					(m[0][3] * (m[2][0] * m[3][2] - m[3][0] * m[2][2]));
	coef[1][2] =	(m[0][0] * (m[2][1] * m[3][3] - m[3][1] * m[2][3])) -
					(m[0][1] * (m[2][0] * m[3][3] - m[3][0] * m[2][3])) +
					(m[0][3] * (m[2][0] * m[3][1] - m[3][0] * m[2][1]));
	coef[1][3] =	(m[0][0] * (m[2][1] * m[3][2] - m[3][1] * m[2][2])) -
					(m[0][1] * (m[2][0] * m[3][2] - m[3][0] * m[2][2])) +
					(m[0][2] * (m[2][0] * m[3][1] - m[3][0] * m[2][1]));

	coef[2][0] =	(m[0][1] * (m[1][2] * m[3][3] - m[3][2] * m[1][3])) -
					(m[0][2] * (m[1][1] * m[3][3] - m[3][1] * m[1][3])) +
					(m[0][3] * (m[1][1] * m[3][2] - m[3][1] * m[1][2]));
	coef[2][1] =	(m[0][0] * (m[1][2] * m[3][3] - m[3][2] * m[1][3])) -
					(m[0][2] * (m[1][0] * m[3][3] - m[3][0] * m[1][3])) +
					(m[0][3] * (m[1][0] * m[3][2] - m[3][0] * m[1][2]));
	coef[2][2] =	(m[0][0] * (m[1][1] * m[3][3] - m[3][1] * m[1][3])) -
					(m[0][1] * (m[1][0] * m[3][3] - m[3][0] * m[1][3])) +
					(m[0][3] * (m[1][0] * m[3][1] - m[3][0] * m[1][1]));
	coef[2][3] =	(m[0][0] * (m[1][1] * m[3][2] - m[3][1] * m[1][2])) -
					(m[0][1] * (m[1][0] * m[3][2] - m[3][0] * m[1][2])) +
					(m[0][2] * (m[1][0] * m[3][1] - m[3][0] * m[1][1]));

	coef[3][0] =	(m[0][1] * (m[1][2] * m[2][3] - m[2][2] * m[1][3])) -
					(m[0][2] * (m[1][1] * m[2][3] - m[2][1] * m[1][3])) +
					(m[0][3] * (m[1][1] * m[2][2] - m[2][1] * m[1][2]));
	coef[3][1] =	(m[0][0] * (m[1][2] * m[2][3] - m[2][2] * m[1][3])) -
					(m[0][2] * (m[1][0] * m[2][3] - m[2][0] * m[1][3])) +
					(m[0][3] * (m[1][0] * m[2][2] - m[2][0] * m[1][2]));
	coef[3][2] =	(m[0][0] * (m[1][1] * m[2][3] - m[2][1] * m[1][3])) -
					(m[0][1] * (m[1][0] * m[2][3] - m[2][0] * m[1][3])) +
					(m[0][3] * (m[1][0] * m[2][1] - m[2][0] * m[1][1]));
	coef[3][3] =	(m[0][0] * (m[1][1] * m[2][2] - m[2][1] * m[1][2])) -
					(m[0][1] * (m[1][0] * m[2][2] - m[2][0] * m[1][2])) +
					(m[0][2] * (m[1][0] * m[2][1] - m[2][0] * m[1][1]));

	m4_transpose(res, coef);

	for(i=0; i<4; i++) {
		for(j=0; j<4; j++) {
			res[i][j] = j % 2 ? -res[i][j] : res[i][j];
			if(i % 2) res[i][j] = -res[i][j];
		}
	}
}

void m4_inverse(mat4_t res, mat4_t m)
{
	int i, j;
	mat4_t adj;
	scalar_t det;

	m4_adjoint(adj, m);
	det = m4_determinant(m);
	
	for(i=0; i<4; i++) {
		for(j=0; j<4; j++) {
			res[i][j] = adj[i][j] / det;
		}
	}
}

void m4_print(FILE *fp, mat4_t m)
{
	int i;
	for(i=0; i<4; i++) {
		fprintf(fp, "[ %12.5f %12.5f %12.5f %12.5f ]\n", (float)m[i][0], (float)m[i][1], (float)m[i][2], (float)m[i][3]);
	}
}
