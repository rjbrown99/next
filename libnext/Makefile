## ====================================================================



TOP         = .

DESTDIR     =
prefix      = /storage2/opt
exec_prefix = ${prefix}
datarootdir = ${prefix}/share
bindir      = ${exec_prefix}/bin
libdir      = ${exec_prefix}/lib
includedir  = ${prefix}/include
mandir      = ${datarootdir}/man

SHELL       = /bin/sh
CC          = cc
AR	    = ar
ARFLAGS     = cru 
CFLAGS      = -D_NEXT_SOURCE  
LDFLAGS     = 
RM          = rm -f
LIBTOOL     = ./libtool
SHTOOL      = /bin/sh
LIBS        = libnext-sparc.a libnext-i386.a libnext-m68k.a libnext-hppa.a
INCLUDES    = fnmatch.h glob.h
FATLIB		= libnext.a
OBJS_SPARC	= tempnam.os tempname.os strchrnul.os fnmatch.os sigsuspend.os strptime.os snprintf.os termios.os glob.os next.os putenv.os setenv.os posix-compat.os strdup.os simple_lock_try.os  
OBJS_M68K	= tempnam.om tempname.om strchrnul.om fnmatch.om sigsuspend.om strptime.om snprintf.om termios.om glob.om next.om putenv.om setenv.om posix-compat.om strdup.om simple_lock_try.om
OBJS_I386	= tempnam.oi tempname.oi strchrnul.oi fnmatch.oi sigsuspend.oi strptime.oi snprintf.oi termios.oi glob.oi next.oi putenv.oi setenv.oi posix-compat.oi strdup.oi 
OBJS_HPPA       = tempnam.oh tempname.oh strchrnul.oh fnmatch.oh sigsuspend.oh strptime.oh snprintf.oh termios.oh glob.oh next.oh putenv.oh setenv.oh posix-compat.oh strdup.oh
OBJS_FAT       = tempnam.o tempname.o strchrnul.o fnmatch.o sigsuspend.o strptime.o snprintf.o termios.o glob.o next.o putenv.o  setenv.o posix-compat.o strdup.o


.SUFFIXES: .os .oi .om .oh .o

.c.os:
	$(CC) -arch sparc -c $(CFLAGS) $< -o $@ 
.c.oi:
	$(CC) -arch i386 -c $(CFLAGS) $< -o $@
.c.om:
	$(CC) -arch m68k -c $(CFLAGS) $< -o $@
.c.oh:
	$(CC) -arch hppa -c $(CFLAGS) $< -o $@
.c.o:
	$(CC) -arch hppa -arch m68k -arch i386 -arch sparc -c $(CFLAGS) $< -o $@

all: $(LIBS) $(FATLIB) 

libnext-sparc.a: $(OBJS_SPARC) 
	$(AR) $(ARFLAGS) $@ $(OBJS_SPARC) 
	    
libnext-i386.a: $(OBJS_I386)
	$(AR) $(ARFLAGS) $@ $(OBJS_I386)

libnext-m68k.a: $(OBJS_M68K)
	$(AR) $(ARFLAGS) $@ $(OBJS_M68K)

libnext-hppa.a: $(OBJS_HPPA)
	$(AR) $(ARFLAGS) $@ $(OBJS_HPPA)
libnext-test.a:  $(OBJS_FAT)
	$(AR) $(ARFLAGS) $@ $(OBJS_FAT)

libnext.a: $(OBJS_M68K)  $(OBJS_I386) $(OBJS_SPARC) $(OBJS_HPPA)
	lipo -create $(LIBS) -output $@


install: all
	#$(SHTOOL) /bin/mkdir -f -p -m 755 $(DESTDIR)$(bindir)
	#$(SHTOOL) /bin/mkdir -f -p -m 755 $(DESTDIR)$(includedir)
	#$(SHTOOL) /bin/mkdir -f -p -m 755 $(DESTDIR)$(libdir)
	install -c -m 644 $(INCLUDES) $(DESTDIR)$(includedir)	
	install -c -m 644 libnext.a $(DESTDIR)$(libdir)/libnext.a
	ranlib  $(DESTDIR)$(libdir)/libnext.a

clean:
	-$(RM) $(OBJS_SPARC)
	-$(RM) $(OBJS_M68K)
	-$(RM) $(OBJS_I386)
	-$(RM) $(OBJS_HPPA)
	-$(RM) $(OBJS_FAT)
	-$(RM) $(LIBS)
	-$(RM) $(FATLIB)
	-$(RM) core *.core *.bak *~
	-$(RM) -r .libs >/dev/null 2>&1 || true
	-$(RM) *.o *.lo

