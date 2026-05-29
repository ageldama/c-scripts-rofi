#include <stdio.h>
#include <stdlib.h>

#include "argp.h"
#include "db.h"
#include "errmsg.h"
#include "file_find.h"
#include "strs.h"

argp_t argp;
db_t *p_db = NULL;

void cleanup (void);

int
main (int argc, char **argv)
{
  atexit (cleanup);

  p_db = db_init ();

  argp_init (&argp);
  argp_parse (argc, argv, &argp);

  regex_t file_regex;

  char *file_find_regex_errmsg
      = file_find_regex_compile (&file_regex, "\\.tcl$");
  if (NULL != file_find_regex_errmsg)
    {
      fputs (file_find_regex_errmsg, stderr);
      ERRMSG_FREE (file_find_regex_errmsg);
      exit (EXIT_FAILURE);
    }

  UT_array *files = NULL;
  utarray_new (files, &ut_str_icd);

  file_find_args_t file_find_args = {
    .dir_matcher = NULL,
    .dir_matcher_closure = NULL,
    .file_matcher = file_find_file_with_regex,
    .file_matcher_closure = &file_regex,
    .recurse = true,
  };

  file_find_list_multiple (files, argp_get_script_dirs_owned (&argp),
                           &file_find_args);

  char **pp_file = NULL;
  while ((pp_file = (char **)utarray_next (files, pp_file)))
    {
      printf ("[%s]\n", *pp_file);
    }

  utarray_free (files);
  file_find_regex_free (&file_regex);

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
cleanup (void)
{
  if (p_db != NULL)
    {
      db_free (p_db);
      p_db = NULL;
    }

  argp_free_internal (&argp);
}
