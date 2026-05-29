#ifndef STRS_H
#define STRS_H

#include "utarray.h"
#include "externc.h"

#define STRS_MALLOC malloc
#define STRS_FREE   free

EXTERN char* str_trim_both_alloc(const char* str);
EXTERN UT_array* str_split(const char* str, const char* delim);

#endif /* STRS_H */
