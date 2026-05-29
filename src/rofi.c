#include "rofi.h"
#include "utstring.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

ssize_t
fd_write (int fd, const char *s)
{
  return write (fd, s, strlen (s));
}

ssize_t
fd_write_sep (int fd, const char *s, char sep)
{
  ssize_t written = fd_write (fd, s);
  char buf[1];
  buf[0] = sep;
  written += write (fd, buf, 1);
  return written;
}

#define fd_slurp_buflen 4096

char *
fd_slurp_alloc (int fd)
{
  UT_string *sbuf;
  utstring_new (sbuf);

  char *buf = malloc (fd_slurp_buflen);
  ssize_t nread;

  while ((nread = read (fd, buf, fd_slurp_buflen)) > 0)
    {
      utstring_bincpy (sbuf, buf, nread);
    }

  //
  size_t result_len = utstring_len (sbuf);
  char *result = ROFI_MALLOC (result_len + 1);
  result[result_len] = '\0';

  strncpy (result, utstring_body (sbuf), result_len);

  free (buf);
  utstring_free (sbuf);

  return result;
}

void
rofi_free_result (rofi_result_t *p_result)
{
  if (NULL == p_result || NULL == p_result->stdout)
    return;

  ROFI_FREE (p_result->stdout);
  p_result->stdout = NULL;
}
