#ifndef SCRIPTS_ROFI_MAIN_H
#define SCRIPTS_ROFI_MAIN_H

#include "externc.h"

#include "argp.h"
#include "db.h"

#include "utarray.h"

#include <regex.h>
#include <stdio.h>

extern argp_t argp;
extern db_t *p_db;
extern regex_t *p_regex;
extern UT_array *script_files;

EXTERN void cleanup (void);
EXTERN void load_or_not (void);
EXTERN void save_or_not (void);
EXTERN void dump_all_or_not (FILE *fp);
EXTERN void compile_file_regex_or_not (void);
EXTERN void list_script_files (void);

#endif /* SCRIPTS_ROFI_MAIN_H */
