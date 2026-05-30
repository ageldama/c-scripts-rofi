#include "errmsg.h"
#include "exec.h"
#include "macrofun.h"
#include "main.h"
#include <string.h>

void
exec_or_not (void)
{
  if (!argp.execute)
    return;

  //
  UT_array *cmdv = NULL;
  UTARRAY_STR_NEW (cmdv);

  // TODO argp.term_command
  // TODO argp.exec_wrapper

  //
  utarray_push_back (cmdv, &select_script_result.selected);

  char *exec_errmsg = exec_vp (cmdv);
  ERRMSG_FAIL_IF (stderr, exec_errmsg);

  //
  utarray_free (cmdv);
  cmdv = NULL;
}
