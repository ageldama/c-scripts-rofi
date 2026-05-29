#include "errmsg.h"
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

char *errmsg_fmt_alloc(const char* fmt, ...) {
    char* errmsg = NULL;
    va_list ap;

    va_start(ap, fmt);
    int errmsg_len = vasprintf(&errmsg, fmt, ap);
    va_end(ap);

    if (errmsg_len < 0) {
      errmsg = strdup("[ERROR] INTERNAL ERROR");
    }

    char* errmsg_copy = ERRMSG_MALLOC(strlen(errmsg));
    strcpy(errmsg_copy, errmsg);
    free(errmsg);

    return errmsg_copy;
}
