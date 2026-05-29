#include <string.h>
#include <ctype.h>
#include "strs.h"

char* str_trim_both_alloc(const char* str)
{
  if (str == NULL) { return NULL; }

  char *lstr = (char *) str;
  while (isspace((unsigned char)*lstr)) {
    lstr++;
  }

  char *rstr = ((char *)str) + strlen(str) - 1;
  while (rstr > str && isspace((unsigned char)*rstr)) {
    rstr--;
  }

  size_t trimmed_len = rstr - lstr;
  if (trimmed_len < 1) return NULL;

  char *result = STRS_MALLOC(trimmed_len+1);
  memset(result, 0, trimmed_len+1);
  strncpy(result, lstr, trimmed_len);

  return result;
}

UT_array* str_split(const char* str, const char* delim)
{
  UT_array* results = NULL;
  utarray_new(results, &ut_str_icd);

  if (str == NULL) { return results; }
 
  char *saveptr;
  char *str_copy = strdup(str);

  char *token = strtok_r((char*)str_copy, delim, &saveptr);
  while (token != NULL) {
       if (strlen(token) > 0) {
            utarray_push_back(results, &token);
        }
    token = strtok_r(NULL, delim, &saveptr);
  }

  free(str_copy);

  return results;
}
