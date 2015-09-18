/*
libvmath - a vector math library
Copyright (C) 2004-2015 John Tsiombikas <nuclear@member.fsf.org>

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

Ray::Ray()
{
	data = 0;
	data_destructor = 0;
}

Ray::Ray(const Vector3 &origin_arg, const Vector3 &dir_arg)
	: origin(origin_arg), dir(dir_arg)
{
	data = 0;
	data_destructor = 0;
}

void Ray::transform(const Matrix4x4 &xform)
{
	Matrix4x4 upper = xform;
	upper[0][3] = upper[1][3] = upper[2][3] = upper[3][0] = upper[3][1] = upper[3][2] = 0.0;
	upper[3][3] = 1.0;

	dir.transform(upper);
	origin.transform(xform);
}

Ray Ray::transformed(const Matrix4x4 &xform) const
{
	Ray foo = *this;
	foo.transform(xform);
	return foo;
}

void Ray::set_data(void *data, void (*data_destr_func)(void*))
{
	this->data = data;
	data_destructor = data_destr_func;
}
