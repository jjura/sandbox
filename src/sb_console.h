#ifndef SB_CONSOLE_H
#define SB_CONSOLE_H

#include "sb_container.h"
#include "sb_type.h"

typedef struct {
    sb_char_t **arguments;
    sb_size_t offset;
    sb_size_t offset_max;
} sb_console_t;

sb_void_t sb_console_create(sb_console_t *console, sb_i32_t argc, sb_char_t **argv);

sb_bool_t sb_console_process(sb_console_t *console, sb_container_t *container);

#endif
