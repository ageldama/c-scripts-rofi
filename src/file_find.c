#include "file_find.h"

#include <dirent.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

void
file_find_list (UT_array *dstarray, const char *dirname,
                file_find_args_t *p_args)
{
  const size_t path_len = 8192;
  char *path;
  struct dirent *dp;
  struct stat statbuf;
  DIR *dir = opendir (dirname);

  if (!dir)
    {
      return;
    }

  path = malloc (path_len);

  while ((dp = readdir (dir)) != NULL)
    {
      if (strcmp (dp->d_name, ".") == 0 || strcmp (dp->d_name, "..") == 0)
        {
          continue;
        }

      snprintf (path, path_len, "%s/%s", dirname, dp->d_name);

      if (stat (path, &statbuf) == 0)
        {
          if (S_ISDIR (statbuf.st_mode) && p_args->recurse)
            {
              file_find_list (dstarray, path, p_args);

              if (p_args->dir_matcher
                  && p_args->dir_matcher (path, dirname, dp->d_name, &statbuf,
                                          p_args->dir_matcher_closure))
                {
                  utarray_push_back (dstarray, &path);
                }
            }
          else if (S_ISREG (statbuf.st_mode))
            {
              if (p_args->file_matcher
                  && p_args->file_matcher (path, dirname, dp->d_name, &statbuf,
                                           p_args->file_matcher_closure))
                {
                  utarray_push_back (dstarray, &path);
                }
            }
        }
    }

  closedir (dir);
  free (path);
}

void
file_find_list_multiple (UT_array *dstarray, const UT_array *dirnames,
                         file_find_args_t *p_args)
{
  char **pp_dirname = NULL;
  while ((pp_dirname = (char **)utarray_next (dirnames, pp_dirname)))
    {
      file_find_list (dstarray, *pp_dirname, p_args);
    }
}

bool
only_file_matcher (const char *abs_path, const char *dirname, const char *name,
                   const struct stat *p_stat, void *closure)
{
  (void)abs_path;
  (void)dirname;
  (void)name;
  (void)closure;
  return S_ISREG (p_stat->st_mode);
}
