CC          = cc
RM          = rm -f
DESTDIR     =
prefix      =
exec_prefix = ${prefix}
bindir      = ${exec_prefix}/bin

all: uname

uname:
	$(CC) -o $@ uname.c

install: all
	install -c -m 755 uname $(DESTDIR)$(bindir)

clean:
	-$(RM) uname
	-$(RM) core *.core *.bak *~
