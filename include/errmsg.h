#ifndef ERRMSG_H
#define ERRMSG_H

#include "externc.h"

#define ERRMSG_MALLOC malloc
#define ERRMSG_FREE free

EXTERN char *errmsg_fmt_alloc (const char *fmt, ...);

#endif /* ERRMSG_H */
