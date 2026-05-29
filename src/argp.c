#include "argp.h"

void
argp_free_internal (argp_t *p_argp)
{
  if (NULL == p_argp)
    return;

  if (NULL != p_argp->__script_dirs_cache)
    {
      utarray_free (p_argp->__script_dirs_cache);
      p_argp->__script_dirs_cache = NULL;
    }

#define ARGP_FREE_AND_NULLFIFY(place)                                         \
  do                                                                          \
    {                                                                         \
      ARGP_FREE (place);                                                      \
      place = NULL;                                                           \
    }                                                                         \
  while (0)

#define ARGP_FREE_AND_NULLIFY_UNLESS_NULL(place)                              \
  if (NULL != place)                                                          \
  ARGP_FREE_AND_NULLFIFY (place)

  ARGP_FREE_AND_NULLIFY_UNLESS_NULL (p_argp->script_dirs);
  ARGP_FREE_AND_NULLIFY_UNLESS_NULL (p_argp->db_file);
  ARGP_FREE_AND_NULLIFY_UNLESS_NULL (p_argp->term_command);
  ARGP_FREE_AND_NULLIFY_UNLESS_NULL (p_argp->exec_wrapper);
  ARGP_FREE_AND_NULLIFY_UNLESS_NULL (p_argp->file_regexes);
  ARGP_FREE_AND_NULLIFY_UNLESS_NULL (p_argp->no_db_flag_file);
  ARGP_FREE_AND_NULLIFY_UNLESS_NULL (p_argp->run_alt_tag);
}

void
argp_init (argp_t *p_argp)
{
  memset (p_argp, 0, sizeof (argp_t));

  p_argp->print = false;
  p_argp->save = false;
  p_argp->execute = false;

  p_argp->script_dirs = ARGP_STRDUP (SCRIPT_ROFI_SCRIPT_DIRS);
  p_argp->__script_dirs_cache = NULL;

  p_argp->db_file = ARGP_STRDUP (SCRIPT_ROFI_DB_FILE);
  p_argp->term_command = ARGP_STRDUP (SCRIPT_ROFI_XTERM_COMMAND);

  p_argp->dump_and_exit = false;

  p_argp->execute = NULL;
  p_argp->file_regexes = NULL;

  p_argp->ignorecase = true;

  p_argp->no_db_flag_file = ARGP_STRDUP (SCRIPT_ROFI_NO_DB_FILE);
  p_argp->run_alt_tag = ARGP_STRDUP (SCRIPT_ROFI_RUN_ALT_TAG);

  p_argp->use_markup = true;
}
