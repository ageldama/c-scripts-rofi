#include "rofi.h"
#include "utarray.h"

void
rofi_show_error (const char *message)
{
  UT_array *cmdv = NULL;
  utarray_new (cmdv, &ut_str_icd);

  char *cmdv_[] = { "rofi", "-e", (char *)message };
  utarray_push_back (cmdv, &cmdv_[0]);
  utarray_push_back (cmdv, &cmdv_[1]);
  utarray_push_back (cmdv, &cmdv_[2]);

  rofi_result_t result;
  rofi_run (cmdv, rofi_write_nothing, &result);

  ROFI_FREE (result.stdout);
  utarray_free (cmdv);
}

void
rofi_write_nothing (const int fd)
{
  (void)fd;
}
