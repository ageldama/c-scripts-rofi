#include "errmsg.h"
#include "exec.h"
#include "main.h"
#include <string.h>

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

void
upd_last_epoch_of_selected (void)
{
  db_upd_last_epoch (p_db, select_script_result.selected);
}

void
print_or_not (void)
{
  if (!argp.print)
    return;
  fputs (select_script_result.selected, stdout);
  fputs ("\n", stdout);
}

void
exec_or_not (void)
{
  if (!argp.execute)
    return;

  // TODO argp.term_command
  // TODO argp.exec_wrapper
  // TODO strtok: select_script_result.selected
  // TODO char *exec_vp (UT_array *cmdv);
}
