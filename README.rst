libvmath
========

A mature C and C++ math library for 3D graphics.

Author: John Tsiombikas <nuclear@member.fsf.org>

License: GNU LGPL version 3 or later (see COPYING_ and COPYING.LESSER_ for details)

Download
--------
Latest release (vmath 3.2): http://nuclear.mutantstargoat.com/sw/libvmath/files/libvmath-3.2.tar.gz

web site: http://nuclear.mutantstargoat.com/sw/libvmath

code repository: https://github.com/jtsiomb/libvmath

Usage
-----
The vmath library has a double C and C++ interface. So for example a C program
could do the following:

.. code:: c

 #include <stdio.h>
 #include "vmath.h"
 
 int main(void)
 {
     vec3_t a, b, x;
 
     a = v3_cons(1, 0, 0);
     b = v3_cons(0, 1, 0);
     x = v3_cross(a, b);
 
     v3_print(stdout, x);
     putchar('\n');
 
     return 0;
 }

While a C++ program could do the following:

.. code:: c++

 #include <iostream>
 #include "vmath.h"
 
 int main(void)
 {
     Vector3 a(1, 0, 0);
     Vector3 b(0, 1, 0);
     Vector3 x = cross_product(a, b);
 
     std::cout << x << std::endl;
 }

.. _COPYING: http://www.gnu.org/licenses/gpl
.. _COPYING.LESSER: http://www.gnu.org/licenses/lgpl
