#include "errmsg.h"
#include "file_find.h"
#include "main.h"
#include <string.h>

void
compile_file_regex_or_not (void)
{
  if (NULL == argp.file_regex)
    return;

  p_regex = malloc (sizeof (regex_t));

  char *errmsg = file_find_regex_compile (p_regex, argp.file_regex);

  if (NULL != errmsg)
    {
      fputs (errmsg, stderr);
      fputs ("\n", stderr);
      ERRMSG_FREE (errmsg);
      exit (EXIT_FAILURE);
    }
}

void
list_script_files (void)
{
  utarray_new (script_files, &ut_str_icd);

  file_find_args_t file_find_args = {
    .dir_matcher = NULL,
    .dir_matcher_closure = NULL,
    .file_matcher
    = p_regex == NULL ? file_find_only_file : file_find_file_with_regex,
    .file_matcher_closure = p_regex == NULL ? NULL : p_regex,
    .recurse = true,
  };

  file_find_list_multiple (script_files, argp_get_script_dirs_owned (&argp),
                           &file_find_args);

  db_sort_by_last_epoch_desc (p_db, script_files);
}

void
load_or_not (void)
{
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
}

void
save_or_not (void)
{
  if (argp_save_db_allowed (&argp))
    {
      char *save_errmsg = db_save_to_filename (p_db, argp.db_file);
      if (NULL != save_errmsg)
        {
          fputs (save_errmsg, stderr);
          fputs ("\n", stderr);
          ERRMSG_FREE (save_errmsg);
        }
    }
}
