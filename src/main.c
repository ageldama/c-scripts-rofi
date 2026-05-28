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

  db_add_args_copying (p_db, "foo", 0, false);

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
