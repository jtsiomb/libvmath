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


Build
-----
To build and install ``libvmath`` on UNIX, run the usual::

 ./configure
 make
 make install

See ``./configure --help`` for build-time options. 

To build on windows, you may use the included visual studio project, or use
mingw, in which case just follow the UNIX instructions above.

To cross-compile for windows with mingw-w64, try the following incantation::

 ./configure --prefix=/usr/i686-w64-mingw32
 make CC=i686-w64-mingw32-gcc AR=i686-w64-mingw32-ar sys=mingw
 make install sys=mingw

.. _COPYING: http://www.gnu.org/licenses/gpl
.. _COPYING.LESSER: http://www.gnu.org/licenses/lgpl
