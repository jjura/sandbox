#ifndef SB_OPTION_H
#define SB_OPTION_H

// includes: project
//------------------------------------------------------------------------------
#include "sb_type.h"

// type: sb_option_id_t
//------------------------------------------------------------------------------
typedef enum {
        OPTION_ID_BINDING,
        OPTION_ID_COMMAND,
        OPTION_ID_DIRECTORY,
        OPTION_ID_MASQUERADE,
} sb_option_id_t;

// type: sb_option_t
//------------------------------------------------------------------------------
typedef struct {
        // member: id
        //----------------------------------------------------------------------
        sb_option_id_t id;

        // member: value
        //----------------------------------------------------------------------
        sb_char_t *value;

} sb_option_t;

// function: sb_option_create
//------------------------------------------------------------------------------
sb_void_t sb_option_create(
                sb_option_t *option,
                sb_option_id_t id,
                sb_char_t *value);

// function: sb_option_get_id
//------------------------------------------------------------------------------
sb_option_id_t sb_option_get_id(sb_option_t *option);

// function: sb_option_get_value
//------------------------------------------------------------------------------
sb_char_t *sb_option_get_value(sb_option_t *option);

#endif
