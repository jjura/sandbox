#ifndef SB_CONSOLE_H
#define SB_CONSOLE_H

// includes: project
//------------------------------------------------------------------------------
#include "sb_type.h"
#include "sb_option.h"

// type: sb_console_t
//------------------------------------------------------------------------------
typedef struct {
        // member: offset
        //----------------------------------------------------------------------
        sb_i32_t offset;

        // member: offset_max
        //----------------------------------------------------------------------
        sb_i32_t offset_max;

        // member: argument
        //----------------------------------------------------------------------
        sb_char_t **argument;

} sb_console_t;

// function: sb_console_create
//------------------------------------------------------------------------------
sb_void_t sb_console_create(
                sb_console_t *console,
                sb_i32_t argc,
                sb_char_t **argv);

// function: sb_console_get_option
//------------------------------------------------------------------------------
sb_bool_t sb_console_get_option(sb_console_t *console, sb_option_t *option);

#endif
