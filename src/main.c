#include <stdio.h>
#include <stdlib.h>

#include "db.h"

db_t *p_db = NULL;

void cleanup ();

int
main (int argc, char **argv)
{
  (void)argc;
  (void)argv;

  atexit (cleanup);

  p_db = db_init ();

  db_add_args_copying (&p_db, "foo", 1, false);
  db_add_args_copying (&p_db, "bar", 2, true);

  db_t *curr;
  db_t *tmp;

  HASH_ITER (hh, p_db, curr, tmp)
  {
    printf ("%s / %ld / %d\n", curr->cmd, curr->last_epoch, curr->run_alt);
  }

  exit (EXIT_SUCCESS);
}

void
cleanup ()
{
  if (p_db != NULL)
    {
      db_free (p_db);
      p_db = NULL;
    }
}
