#include "db.h"
#include <string.h>
#include <stdio.h>
#include <errno.h>

db_t *
db_init ()
{
  return NULL;
}

void
db_free (db_t *p_db)
{
  db_t *curr;
  db_t *tmp;

  HASH_ITER (hh, p_db, curr, tmp)
  {
    HASH_DEL (p_db, curr);
    DB_FREE (curr->cmd);
    DB_FREE (curr);
  }
}

void
db_add (db_t **pp_db, db_t *p_entry)
{
  db_t *p_db = *pp_db;
  db_t *p_found = NULL;

  HASH_FIND_STR (p_db, p_entry->cmd, p_found);
  if (p_found == NULL)
    {
      HASH_ADD_STR (p_db, cmd, p_entry);
      *pp_db = p_db;
    }
  else
    {
      p_found->run_alt = p_entry->run_alt;
      p_found->last_epoch = p_entry->last_epoch;
    }
}

void
db_add_args_copying (db_t **pp_db, const char *cmd, time_t last_epoch,
                     bool run_alt)
{
  db_t *p_entry = DB_MALLOC (sizeof (db_t));
  memset (p_entry, 0, sizeof (db_t));
  //
  size_t cmd_len = strnlen (cmd, DB_CMD_MAX);
  char *cmd2 = DB_MALLOC (cmd_len + 1);
  memset (cmd2, 0, cmd_len + 1);
  strncpy (cmd2, cmd, cmd_len);
  //
  p_entry->cmd = cmd2;
  p_entry->run_alt = run_alt;
  p_entry->last_epoch = last_epoch;
  //
  db_add (pp_db, p_entry);
}

char* db_save_to_filename (db_t *p_db, const char *filename)
{
  FILE *fp = NULL;
  fp = fopen(filename, "wb");
  if(NULL == fp) {
    char* errmsg = NULL;
    asprintf(&errmsg, "[ERROR] %s %s %s", __func__,
             strerror(errno), filename);
    char* errmsg2 = DB_MALLOC(strlen(errmsg));
    strcpy(errmsg2, errmsg);
    free(errmsg);
    return errmsg2;
  }

  // TODO
}


