#include <sys/types.h>
size_t strxfrm (char *dest, char *src, size_t n)
{
  if (*src == '\0')
  {
    if (n != 0)
      *dest = '\0';

    return (1);
  }

  if (n != 0)
    strncpy (dest, src, n);

  return (strlen (src));
}

