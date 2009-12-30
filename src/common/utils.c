#include "includes.h"

void warn(char *fmt, ...)
{
  va_list ap;
  va_start(ap, fmt);
  vwarn(fmt, ap);
  va_end(ap);
}

void vwarn(char *fmt, va_list ap)
{
  if (fmt != NULL) {
    vfprintf(stderr, fmt, ap);
  }
  fputc('\n', stderr);
}

