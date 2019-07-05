/* Copyright (C) 1991, 1992, 1993 Free Software Foundation, Inc.
This file is part of the GNU C Library.

The GNU C Library is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License as
published by the Free Software Foundation; either version 2 of the
License, or (at your option) any later version.

The GNU C Library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
General Public License for more details.

You should have received a copy of the GNU General Public
License along with the GNU C Library; see the file COPYING.  If
not, write to the Free Software Foundation, Inc., 59 Temple Place - Suite 330,
Boston, MA  02111-1307, USA.  */

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#ifndef HAVE_TEMPNAM

#include <errno.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifndef _POSIX_SOURCE
 #include "ntypes.h"
#else
 #include <sys/types.h>
#endif

#include <fcntl.h>
#include <sys/stat.h>
#ifndef FILENAME_MAX
#ifdef MAXPATHLEN
#define FILENAME_MAX MAXPATHLEN
#else
#define FILENAME_MAX 1024
#endif
#endif

#ifndef P_tmpdir
#define P_tmpdir "/tmp/"
#endif

/* Return nonzero if DIR is an existent directory.  */
static int
diraccess (const char *dir)
{
  struct stat buf;
  return stat (dir, &buf) == 0 && S_ISDIR (buf.st_mode);
}

/* Return nonzero if FILE exists.  */
static int
exists (const char *file)
{
  /* We can stat the file even if we can't read its data.  */
  struct stat st;
  int save = errno;
  if (stat (file, &st) == 0)
    return 1;
  else
    {
      /* We report that the file exists if stat failed for a reason other
	 than nonexistence.  In this case, it may or may not exist, and we
	 don't know; but reporting that it does exist will never cause any
	 trouble, while reporting that it doesn't exist when it does would
	 violate the interface of __stdio_gen_tempname.  */
      int exists = errno != ENOENT;
      errno = save;
      return exists;
    }
}


/* These are the characters used in temporary filenames.  */
static const char letters[] =
  "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";

/* Generate a temporary filename and return it (in a static buffer).  If
   STREAMPTR is not NULL, open a stream "w+b" on the file and set
   *STREAMPTR to it.  If DIR_SEARCH is nonzero, DIR and PFX are used as
   described for tempnam.  If not, a temporary filename in P_tmpdir with no
   special prefix is generated.  If LENPTR is not NULL, *LENPTR is set the
   to length (including the terminating '\0') of the resultant filename,
   which is returned.  This goes through a cyclic pattern of all possible
   filenames consisting of five decimal digits of the current pid and three
   of the characters in `letters'.  Data for tempnam and tmpnam is kept
   separate, but when tempnam is using P_tmpdir and no prefix (i.e, it is
   identical to tmpnam), the same data is used.  Each potential filename is
   tested for an already-existing file of the same name, and no name of an
   existing file will be returned.  When the cycle reaches its end
   (12345ZZZ), NULL is returned.  */
char *
__stdio_gen_tempname (const char *dir, const char *pfx,
		      int dir_search, size_t *lenptr,
		      FILE **streamptr)
{
  int saverrno = errno;
  static const char tmpdir[] = P_tmpdir;
  static size_t indices[2];
  size_t *idx;
  static char buf[FILENAME_MAX];
  static pid_t oldpid = (pid_t) 0;
  pid_t pid = getpid();
  register size_t len, plen, dlen;

  if (dir_search)
    {
      register const char *d = getenv("TMPDIR");
      if (d != NULL && !diraccess(d))
	d = NULL;
      if (d == NULL && dir != NULL && diraccess(dir))
	d = dir;
      if (d == NULL && diraccess(tmpdir))
	d = tmpdir;
      if (d == NULL && diraccess("/tmp"))
	d = "/tmp";
      if (d == NULL)
	{
	  errno = ENOENT;
	  return NULL;
	}
      dir = d;
    }
  else
    dir = tmpdir;

  dlen = strlen (dir);

  /* Remove trailing slashes from the directory name.  */
  while (dlen > 1 && dir[dlen - 1] == '/')
    --dlen;

  if (pfx != NULL && *pfx != '\0')
    {
      plen = strlen(pfx);
      if (plen > 5)
	plen = 5;
    }
  else
    plen = 0;

  if (dir != tmpdir && !strcmp(dir, tmpdir))
    dir = tmpdir;
  idx = &indices[(plen == 0 && dir == tmpdir) ? 1 : 0];

  if (pid != oldpid)
    {
      oldpid = pid;
      indices[0] = indices[1] = 0;
    }

  len = dlen + 1 + plen + 5 + 3;
  for (; *idx < ((sizeof (letters) - 1) * (sizeof (letters) - 1) *
		 (sizeof (letters) - 1));
       ++*idx)
    {
      /* Construct a file name and see if it already exists.

	 We use a single counter in *IDX to cycle each of three
	 character positions through each of 62 possible letters.  */

      if (sizeof (buf) < len)
	return NULL;

      sprintf (buf, "%.*s/%.*s%.5d%c%c%c",
	       (int) dlen, dir, (int) plen,
	       pfx, pid % 100000,
	       letters[*idx
		       % (sizeof (letters) - 1)],
	       letters[(*idx / (sizeof (letters) - 1))
		       % (sizeof (letters) - 1)],
	       letters[(*idx / ((sizeof (letters) - 1) *
				(sizeof (letters) - 1)))
		       % (sizeof (letters) - 1)]
	       );

      if (! buf || strlen (buf) != (int) len)
	return NULL;
  
      if (streamptr != NULL)
	abort ();
      else if (exists (buf))
	continue;

      /* If the file already existed we have continued the loop above,
	 so we only get here when we have a winning name to return.  */

      errno = saverrno;

      if (lenptr != NULL)
	*lenptr = len + 1;
      return buf;
    }

  /* We got out of the loop because we ran out of combinations to try.  */
  errno = EEXIST;		/* ? */
  return NULL;
}

#endif
