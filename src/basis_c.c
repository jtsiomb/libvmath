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

#include "basis.h"
#include "matrix.h"

void basis_matrix(mat4_t res, vec3_t i, vec3_t j, vec3_t k)
{
	m4_identity(res);
	m4_set_column(res, v4_cons(i.x, i.y, i.z, 1.0), 0);
	m4_set_column(res, v4_cons(j.x, j.y, j.z, 1.0), 1);
	m4_set_column(res, v4_cons(k.x, k.y, k.z, 1.0), 2);
}

void basis_matrix_dir(mat4_t res, vec3_t dir)
{
	vec3_t k = v3_normalize(dir);
	vec3_t j = {0, 1, 0};
	vec3_t i = v3_cross(j, k);
	j = v3_cross(k, i);
	basis_matrix(res, i, j, k);
}
