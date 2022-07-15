#ifndef CONSOLE_H
#define CONSOLE_H

// includes: project
//------------------------------------------------------------------------------
#include "type.h"
#include "option.h"

// type: console_t
//------------------------------------------------------------------------------
typedef struct {
        // member: offset
        //----------------------------------------------------------------------
        i32_t offset;

        // member: offset_max
        //----------------------------------------------------------------------
        i32_t offset_max;

        // member: argument
        //----------------------------------------------------------------------
        char_t **argument;

} console_t;

// function: console_create
//------------------------------------------------------------------------------
void_t console_create(console_t *console, i32_t argc, char_t **argv);

// function: console_get_option
//------------------------------------------------------------------------------
bool_t console_get_option(console_t *console, option_t *option);

#endif
