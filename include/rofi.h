#ifndef ROFI_H
#define ROFI_H

#include "externc.h"
#include "utarray.h"
#include <stdbool.h>

#define ROFI_MALLOC malloc
#define ROFI_FREE free

typedef void (*rofi_write_fn) (const int fd);

EXTERN ssize_t fd_write (int fd, const char *s);
EXTERN ssize_t fd_write_sep (int fd, const char *s, char sep);

EXTERN char *fd_slurp (int fd);

typedef struct
{
  int exitcode;
  bool alt;
  char *stdout;
} rofi_result_t;

EXTERN void rofi_free_result (rofi_result_t *p_result);

EXTERN char *rofi_run (UT_array *cmdv, const rofi_write_fn *write_fn,
                       rofi_result_t *p_result);

/*

struct rofi_common_opts {
    std::string prompt;
    bool ignorecase;
    std::string addopts;
};

auto ask_yn(const rofi_common_opts& common_opts,
    const std::string& label_y, const std::string& label_n)
    -> std::optional<rofi_result>;

void show_error(const std::string& message);

struct rofi_select_list_opts {
    rofi_common_opts common_opts;
    bool use_markup;
    std::string run_alt_tag;
};

class run_alt_callbacks {
public:
    virtual auto is_run_alt(const std::string& cmd) -> bool = 0;
    virtual auto toggle_run_alt(const std::string& cmd) -> bool = 0;
    virtual ~run_alt_callbacks() = default;
};

auto select_list(const rofi_select_list_opts& common_opts,
    run_alt_callbacks& callbacks, const SR::string_vector& sel_list)
    -> std::optional<rofi_result>;

}

struct rofi_common_opts {
    std::string prompt;
    bool ignorecase;
    std::string addopts;
};

auto ask_yn(const rofi_common_opts& common_opts,
    const std::string& label_y, const std::string& label_n)
    -> std::optional<rofi_result>;

void show_error(const std::string& message);

struct rofi_select_list_opts {
    rofi_common_opts common_opts;
    bool use_markup;
    std::string run_alt_tag;
};

class run_alt_callbacks {
public:
    virtual auto is_run_alt(const std::string& cmd) -> bool = 0;
    virtual auto toggle_run_alt(const std::string& cmd) -> bool = 0;
    virtual ~run_alt_callbacks() = default;
};

auto select_list(const rofi_select_list_opts& common_opts,
    run_alt_callbacks& callbacks, const SR::string_vector& sel_list)
    -> std::optional<rofi_result>;

}
*/

#endif /* ROFI_H */
