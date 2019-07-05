#ifdef _POSIX_SOURCE
#undef _POSIX_SOURCE
#endif
#include <libc.h>
#include <stdio.h>
#include <sys/types.h>

boolean_t simple_lock_try(){
	return TRUE;
}
