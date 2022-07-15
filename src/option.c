// includes: project
//------------------------------------------------------------------------------
#include "option.h"

// function: option_create
//------------------------------------------------------------------------------
void_t option_create(option_t *option, option_id_t id, char_t *value)
{
        option->id = id;
        option->value = value;
}

// function: option_get_id
//------------------------------------------------------------------------------
option_id_t option_get_id(option_t *option)
{
        return option->id;
}

// function: option_get_value
//------------------------------------------------------------------------------
char_t *option_get_value(option_t *option)
{
        return option->value;
}
