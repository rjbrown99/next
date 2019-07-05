/* Copyright (C) 1991, 1996, 1997, 1998 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Library General Public License as
   published by the Free Software Foundation; either version 2 of the
   License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Library General Public License for more details.

   You should have received a copy of the GNU Library General Public
   License along with the GNU C Library; see the file COPYING.LIB.  If not,
   write to the Free Software Foundation, Inc., 59 Temple Place - Suite 330,
   Boston, MA 02111-1307, USA.  */
#include <errno.h>
#ifndef _POSIX_SOURCE 
 #include "ntypes.h" 
 #include "nsignal.h"
#else
 #include <signal.h>
#endif

#include <stddef.h>
#include <unistd.h>

#define __set_errno(val) errno = (val)
/* Change the set of blocked signals to SET,
   wait until a signal arrives, and restore the set of blocked signals.  */
int
sigsuspend (set)
     const sigset_t *set;
{
  sigset_t oset;
  int save;

  if (set == NULL)
    {
      __set_errno (EINVAL);
      return -1;
    }

  if (sigprocmask (SIG_SETMASK, set, &oset) < 0)
    return -1;

  (void) pause();
  save = errno;

  if (sigprocmask (SIG_SETMASK, &oset, (sigset_t *) NULL) < 0)
    return -1;

  __set_errno (save);
  return -1;
}
