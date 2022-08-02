// includes: project
//------------------------------------------------------------------------------
#include "sb_handler.h"

// includes: c
//------------------------------------------------------------------------------
#include <stddef.h>

// defines:
//------------------------------------------------------------------------------
#define ARGUMENT_SEPARATOR ':'

// type: sb_handler_function_t
//------------------------------------------------------------------------------
typedef sb_void_t (*sb_handler_function_t)(
                sb_handler_t *handler,
                sb_option_t *option);

// function: handle_binding
//------------------------------------------------------------------------------
static sb_void_t handle_binding(sb_handler_t *handler, sb_option_t *option)
{
        sb_char_t *source = sb_option_get_value(option);
        sb_char_t *target = source;

        for (sb_char_t *separator = source; *separator; ++separator)
        {
                if (*separator == ARGUMENT_SEPARATOR)
                {
                        target = separator + 1;
                        *separator = 0;
                }
        }

        sb_container_set_binding(handler->container, source, target);
}

// function: handle_command
//------------------------------------------------------------------------------
static sb_void_t handle_command(sb_handler_t *handler, sb_option_t *option)
{
        sb_char_t *value = sb_option_get_value(option);

        sb_container_set_command(handler->container, value);
}

// function: handle_directory
//------------------------------------------------------------------------------
static sb_void_t handle_directory(sb_handler_t *handler, sb_option_t *option)
{
        sb_char_t *value = sb_option_get_value(option);

        sb_container_set_directory(handler->container, value);
}

// function: handle_masquerade
//------------------------------------------------------------------------------
static sb_void_t handle_masquerade(sb_handler_t *handler, sb_option_t *option)
{
        sb_char_t *value = sb_option_get_value(option);

        sb_container_set_masquerade(handler->container, value);
}

// variable: handlers
//------------------------------------------------------------------------------
static sb_handler_function_t handlers[] =
{
        [ OPTION_ID_BINDING ]    = handle_binding,
        [ OPTION_ID_COMMAND ]    = handle_command,
        [ OPTION_ID_DIRECTORY ]  = handle_directory,
        [ OPTION_ID_MASQUERADE ] = handle_masquerade,
};

// function: sb_handler_create
//------------------------------------------------------------------------------
sb_void_t sb_handler_create(sb_handler_t *handler, sb_container_t *container)
{
        handler->container = container;
}

// function: sb_handler_execute
//------------------------------------------------------------------------------
sb_void_t sb_handler_execute(sb_handler_t *handler, sb_option_t *option)
{
        sb_option_id_t id = sb_option_get_id(option);

        handlers[id](handler, option);
}
