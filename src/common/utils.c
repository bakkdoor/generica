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


void debug(char *fmt, ...)
{
  #if PRINT_DEBUG
  va_list ap;
  va_start(ap, fmt);
  vdebug(fmt, ap);
  va_end(ap);
  #endif
}

void vdebug(char *fmt, va_list ap)
{
  #if PRINT_DEBUG
  if (fmt != NULL) {
    vfprintf(stdout, fmt, ap);
  }
  fputc('\n', stdout);
  #endif
}

