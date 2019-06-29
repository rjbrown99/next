# GCC 2.95.3

Original source: https://www.savarese.org/patches/gcc.html

Compiling:

patch -p1 < ../gcc-2.95.3.next.patch


After installation:


cd /myinstallpath/lib/gcc-lib/m68k-next-nextstep3/2.95.3

patch -p0 < /pathtopatch/gcc.2.95.3.m68k.specs.patch

