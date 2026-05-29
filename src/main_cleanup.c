#include "main.h"

void
cleanup (void)
{
  if (p_db != NULL)
    {
      db_free (p_db);
      p_db = NULL;
    }

  argp_free_internal (&argp);
}
