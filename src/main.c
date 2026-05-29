#include <stdio.h>
#include <stdlib.h>

#include "main.h"

#include "argp.h"
#include "db.h"
#include "errmsg.h"
#include "exec.h"
#include "file_find.h"
#include "rofi.h"
#include "strs.h"

int
main (int argc, char **argv)
{
  atexit (cleanup);

  p_db = db_init ();

  argp_init (&argp);
  argp_parse (argc, argv, &argp);

  /* load? */
  if (argp_load_db_allowed (&argp))
    {
      char *load_errmsg = db_load_from_filename (p_db, argp.db_file);
      if (NULL != load_errmsg)
        {
          fputs (load_errmsg, stderr);
          fputs ("\n", stderr);
          ERRMSG_FREE (load_errmsg);
        }
    }

  /* dump & exit? */
  if (argp.dump_and_exit)
    {
      dump_all (stdout);
      exit (EXIT_SUCCESS);
    }

  /* list script files */

  /* select in list */

  /* save? */

  /* exec? */

  /* print? */

  exit (EXIT_SUCCESS);
}

#if 0
  rofi_ask_yn_opts_t yn_opts = {
    .common = {
      .prompt = "Y/n?",
      .ignorecase = true,
      .addopts = NULL,
    },
    .label_y = "YYYYYEEEEESSS????",
    .label_n = "NO????",
  };

  rofi_ask_yn_result_t ask_yn_result;

  char *rofi_ask_yn_errmsg = rofi_ask_yn (&yn_opts, &ask_yn_result);
  if (NULL != rofi_ask_yn_errmsg)
    {
      fputs (rofi_ask_yn_errmsg, stderr);
      ROFI_FREE (rofi_ask_yn_errmsg);
      exit (EXIT_FAILURE);
    }

  printf ("yes/no: %d // canceled: %d\n", ask_yn_result.answer_yes,
          ask_yn_result.canceled);
  rofi_free_result (&(ask_yn_result.base));
#endif

#if 0
  rofi_show_error ("foobar 한글 여기도");
#endif

#if 0
  UT_array *cmdv = NULL;
  utarray_new (cmdv, &ut_str_icd);

  char *cmdv_[] = { "ls", "-lh", "/etc" };
  utarray_push_back (cmdv, &cmdv_[0]);
  utarray_push_back (cmdv, &cmdv_[1]);
  utarray_push_back (cmdv, &cmdv_[2]);
  exec_vp (cmdv);
  utarray_free (cmdv);
#endif

#if 0
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

  db_sort_by_last_epoch_desc (p_db, files);

  char **pp_file = NULL;
  while ((pp_file = (char **)utarray_next (files, pp_file)))
    {
      printf ("[%s]\n", *pp_file);
    }

  utarray_free (files);
  file_find_regex_free (&file_regex);
#endif

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
