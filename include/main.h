#ifndef SCRIPTS_ROFI_MAIN_H
#define SCRIPTS_ROFI_MAIN_H

#include "externc.h"

#include "argp.h"
#include "db.h"

#include <stdio.h>

extern argp_t argp;
extern db_t *p_db;

EXTERN void cleanup (void);
EXTERN void dump_all (FILE *fp);

#endif /* SCRIPTS_ROFI_MAIN_H */
