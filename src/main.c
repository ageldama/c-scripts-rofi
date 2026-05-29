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
  load_or_not ();

  /* dump & exit? */
  dump_all_or_not (stdout);

  /* list script files */
  compile_file_regex_or_not ();
  list_script_files ();

  /* select in list */

  /* save? */
  save_or_not ();

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
