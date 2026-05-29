#include <stdio.h>
#include <stdlib.h>

#include "main.h"

#include "argp.h"
#include "db.h"

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
  select_script ();

  /* save? */
  save_or_not ();

  /* exec? */
  exec_or_not ();

  /* print? */
  print_or_not ();

  // BYE:
  exit (EXIT_SUCCESS);
}
