#ifndef SCRIPTS_ROFI_MAIN_H
#define SCRIPTS_ROFI_MAIN_H

#include "externc.h"

#include "argp.h"
#include "db.h"

extern argp_t argp;
extern db_t *p_db;

EXTERN void cleanup (void);

#endif /* SCRIPTS_ROFI_MAIN_H */
