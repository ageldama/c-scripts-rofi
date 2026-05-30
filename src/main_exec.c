#include "errmsg.h"
#include "exec.h"
#include "macrofun.h"
#include "main.h"
#include "strs.h"
#include <string.h>

void
exec_or_not (void)
{
  if (!argp.execute)
    return;

  //
  UT_array *cmdv = NULL;
  UTARRAY_STR_NEW (cmdv);

  if (select_script_result.base.alt && NULL != argp.term_command)
    {
      str_split_into (argp.term_command, " ", cmdv);
    }

  if (NULL != argp.exec_wrapper)
    {
      str_split_into (argp.exec_wrapper, " ", cmdv);
    }

  //
  utarray_push_back (cmdv, &select_script_result.selected);

  char *exec_errmsg = exec_vp (cmdv);
  ERRMSG_FAIL_IF (stderr, exec_errmsg);

  //
  utarray_free (cmdv);
  cmdv = NULL;
}
