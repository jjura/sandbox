// includes: project
//------------------------------------------------------------------------------
#include "handler.h"

// includes: c
//------------------------------------------------------------------------------
#include <stddef.h>

// defines:
//------------------------------------------------------------------------------
#define ARGUMENT_SEPARATOR ':'

// type: handler_function_t
//------------------------------------------------------------------------------
typedef void_t (*handler_function_t)(handler_t *handler, option_t *option);

// function: handle_binding
//------------------------------------------------------------------------------
static void_t handle_binding(handler_t *handler, option_t *option)
{
        char_t *source = option_get_value(option);
        char_t *target = source;

        for (char_t *separator = source; *separator; ++separator)
        {
                if (*separator == ARGUMENT_SEPARATOR)
                {
                        target = separator + 1;
                        *separator = 0;
                }
        }

        container_set_binding(handler->container, source, target);
}

// function: handle_command
//------------------------------------------------------------------------------
static void_t handle_command(handler_t *handler, option_t *option)
{
        container_set_command(handler->container, option_get_value(option));
}

// function: handle_directory
//------------------------------------------------------------------------------
static void_t handle_directory(handler_t *handler, option_t *option)
{
        container_set_directory(handler->container, option_get_value(option));
}

// function: handle_masquerade
//------------------------------------------------------------------------------
static void_t handle_masquerade(handler_t *handler, option_t *option)
{
        container_set_masquerade(handler->container, option_get_value(option));
}

// variable: handlers
//------------------------------------------------------------------------------
static handler_function_t handlers[] =
{
        [ OPTION_ID_BINDING ]    = handle_binding,
        [ OPTION_ID_COMMAND ]    = handle_command,
        [ OPTION_ID_DIRECTORY ]  = handle_directory,
        [ OPTION_ID_MASQUERADE ] = handle_masquerade,
};

// function: handler_create
//------------------------------------------------------------------------------
void_t handler_create(handler_t *handler, container_t *container)
{
        handler->container = container;
}

// function: handler_execute
//------------------------------------------------------------------------------
void_t handler_execute(handler_t *handler, option_t *option)
{
        option_id_t id = option_get_id(option);

        handlers[id](handler, option);
}
