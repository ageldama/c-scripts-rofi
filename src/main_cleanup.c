#include "main.h"

void
cleanup (void)
{
  if (p_regex != NULL)
    {
      free (p_regex);
      p_regex = NULL;
    }

  if (script_files != NULL)
    {
      utarray_free (script_files);
      script_files = NULL;
    }

  if (p_db != NULL)
    {
      db_free (p_db);
      p_db = NULL;
    }

  argp_free_internal (&argp);
}
