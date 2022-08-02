// includes: project
//------------------------------------------------------------------------------
#include "sb_option.h"

// function: sb_option_create
//------------------------------------------------------------------------------
sb_void_t sb_option_create(
                sb_option_t *option,
                sb_option_id_t id,
                sb_char_t *value)
{
        option->id = id;
        option->value = value;
}

// function: sb_option_get_id
//------------------------------------------------------------------------------
sb_option_id_t sb_option_get_id(sb_option_t *option)
{
        return option->id;
}

// function: sb_option_get_value
//------------------------------------------------------------------------------
sb_char_t *sb_option_get_value(sb_option_t *option)
{
        return option->value;
}
