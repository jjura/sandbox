#ifndef OPTION_H
#define OPTION_H

// includes: project
//------------------------------------------------------------------------------
#include "type.h"

// type: option_id_t
//------------------------------------------------------------------------------
typedef enum {
        OPTION_ID_BINDING,
        OPTION_ID_COMMAND,
        OPTION_ID_DIRECTORY,
        OPTION_ID_MASQUERADE,
} option_id_t;

// type: option_t
//------------------------------------------------------------------------------
typedef struct {
        // member: id
        //----------------------------------------------------------------------
        option_id_t id;

        // member: value
        //----------------------------------------------------------------------
        char_t *value;

} option_t;

// function: option_create
//------------------------------------------------------------------------------
void_t option_create(option_t *option, option_id_t id, char_t *value);

// function: option_get_id
//------------------------------------------------------------------------------
option_id_t option_get_id(option_t *option);

// function: option_get_value
//------------------------------------------------------------------------------
char_t *option_get_value(option_t *option);

#endif
