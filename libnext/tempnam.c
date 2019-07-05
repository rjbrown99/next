/* Copyright (C) 1991, 1993 Free Software Foundation, Inc.
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
License along with the GNU C Library; see the file COPYING.LIB.  If
not, write to the Free Software Foundation, Inc., 59 Temple Place - Suite 330,
Boston, MA  02111-1307, USA.  */

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#ifndef HAVE_TEMPNAM

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern char *__stdio_gen_tempname (const char *dir, const char *pfx,
				   int dir_search, size_t *lenptr,
				   FILE **streamptr);

/* Generate a unique temporary filename using up to five characters of PFX
   if it is not NULL.  The directory to put this file in is searched for
   as follows: First the environment variable "TMPDIR" is checked.
   If it contains the name of a writable directory, that directory is used.
   If not and if DIR is not NULL, that value is checked.  If that fails,
   P_tmpdir is tried and finally "/tmp".  The storage for the filename
   is allocated by `malloc'.  */
char *
tempnam (const char *dir, const char *pfx)
{
  size_t len;
  register char *s;
  register char *t = __stdio_gen_tempname(dir, pfx, 1, &len, (FILE **) NULL);

  if (t == NULL)
    return NULL;

  s = (char *) malloc(len);
  if (s == NULL)
    return NULL;

  (void) memcpy(s, t, len);
  return s;
}

#endif
