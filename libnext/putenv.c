/* Copyright (C) 1991, 94, 95, 96, 97, 98 Free Software Foundation, Inc.
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
//#define __STRICT_BSD__
#if defined _AIX && !defined __GNUC__
 #pragma alloca
#endif

#if HAVE_CONFIG_H
# include <config.h>
#endif

#include <stdlib.h>
#include <sys/types.h>
#include <string.h>

#if !__GNU_LIBRARY__ && !HAVE_STRCHR
# define strchr index
#endif

#ifndef _LIBC
# ifdef HAVE_ALLOCA_H
#  include <alloca.h>
# else
#  ifdef __GNUC__
//#   define alloca __builtin_alloca
#  else
//extern char *alloca ();
#  endif /* __GNUC__ */
# endif /* HAVE_ALLOCA_H */
#endif /* _LIBC */


/* Put STRING, which is of the form "NAME=VALUE", in the environment.  */
int
putenv (string)
     const char *string;
{
  const char *const name_end = strchr (string, '=');

  if (name_end != NULL)
    {
#ifdef _LIBC
      char *name = strndupa (string, name_end - string);
#else
      char *name = alloca (name_end - string + 1);
      memcpy (name, string, name_end - string);
      name[name_end - string] = '\0';
#endif
      return setenv (name, name_end + 1, 1);
    }

  unsetenv (string);
  return 0;
}
