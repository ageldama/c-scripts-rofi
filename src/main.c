#include <stdio.h>
#include <stdlib.h>

#include "argp.h"
#include "db.h"
#include "strs.h"

argp_t argp;
db_t *p_db = NULL;

void cleanup ();

int
main (int argc, char **argv)
{
  atexit (cleanup);

  p_db = db_init ();

  argp_init (&argp);
  argp_parse (argc, argv, &argp);

#if 0
  UT_array* script_dirs = str_split(
                                    "~/local/scripts:~/local/bin:~/.screenlayout:~/P/v3/bin", ":");

  if(script_dirs != NULL) {
    char **pp = NULL;

    while ((pp = (char **)utarray_next(script_dirs, pp))) {
      char *before = *pp;
      char *expanded = str_expand_tilde_alloc(before);
      printf("[%s]\n", expanded);
      STRS_FREE(expanded);
    }

    utarray_free(script_dirs);
  }
#endif

#if 0
  db_add_args_copying (&p_db, "foo", 1, false);
  db_add_args_copying (&p_db, "bar", 2, true);

  db_t *curr;
  db_t *tmp;

  HASH_ITER (hh, p_db, curr, tmp)
  {
    printf ("%s / %ld / %d\n", curr->cmd, curr->last_epoch, curr->run_alt);
  }
#endif

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

  argp_free_internal (&argp);
}
