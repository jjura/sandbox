#include "sb_console.h"
#include "sb_logger.h"

#include <assert.h>
#include <stdlib.h>
#include <string.h>

typedef sb_bool_t (*sb_handler_t)(sb_container_t *, sb_char_t *);

typedef enum {
    SB_ARGUMENT_SET_BINDING,
    SB_ARGUMENT_SET_COMMAND,
    SB_ARGUMENT_SET_DIRECTORY,
    SB_ARGUMENT_SET_OVERLAY,
    SB_ARGUMENT_SET_USERNAME,
    SB_ARGUMENT_UNKNOWN,
} sb_argument_t;

static sb_char_t *handle_delimited_value(sb_char_t **value)
{
    assert(value);

    sb_char_t *copy = *value;
    sb_char_t *delimeter = strchr(*value, ':');

    if (delimeter)
    {
        *delimeter++ = 0;
        *value = delimeter;
    }

    return copy;
}

static sb_bool_t handle_set_binding(sb_container_t *container, sb_char_t *argument)
{
    assert(container);
    assert(argument);

    sb_char_t *source = handle_delimited_value(&argument);
    sb_char_t *destination = handle_delimited_value(&argument);

    return sb_container_set_binding(container, source, destination);
}

static sb_bool_t handle_set_command(sb_container_t *container, sb_char_t *argument)
{
    assert(container);
    assert(argument);

    return sb_container_set_command(container, argument);
}

static sb_bool_t handle_set_directory(sb_container_t *container, sb_char_t *argument)
{
    assert(container);
    assert(argument);

    return sb_container_set_directory(container, argument);
}

static sb_bool_t handle_set_overlay(sb_container_t *container, sb_char_t *argument)
{
    assert(container);
    assert(argument);

    sb_char_t *lower = handle_delimited_value(&argument);
    sb_char_t *upper = handle_delimited_value(&argument);
    sb_char_t *work = handle_delimited_value(&argument);

    return sb_container_set_overlay(container, lower, upper, work);
}

static sb_bool_t handle_set_username(sb_container_t *container, sb_char_t *argument)
{
    assert(container);
    assert(argument);

    return sb_container_set_username(container, argument);
}

static sb_bool_t handle_unknown(sb_container_t *container, sb_char_t *argument)
{
    assert(container);
    assert(argument);

    SB_LOGGER_ERROR("Unknown command: %s", argument);

    return false;
}

static sb_handler_t argument_to_handler[] = {
    [ SB_ARGUMENT_SET_BINDING   ] = handle_set_binding,
    [ SB_ARGUMENT_SET_COMMAND   ] = handle_set_command,
    [ SB_ARGUMENT_SET_DIRECTORY ] = handle_set_directory,
    [ SB_ARGUMENT_SET_OVERLAY   ] = handle_set_overlay,
    [ SB_ARGUMENT_SET_USERNAME  ] = handle_set_username,
    [ SB_ARGUMENT_UNKNOWN       ] = handle_unknown,
};

static sb_char_t *argument_to_input[] = {
    [ SB_ARGUMENT_SET_BINDING   ] = "--binding",
    [ SB_ARGUMENT_SET_COMMAND   ] = "--command",
    [ SB_ARGUMENT_SET_DIRECTORY ] = "--directory",
    [ SB_ARGUMENT_SET_OVERLAY   ] = "--overlay",
    [ SB_ARGUMENT_SET_USERNAME  ] = "--username",
};

sb_void_t sb_console_create(sb_console_t *console, sb_i32_t argc, sb_char_t **argv)
{
    assert(console);
    assert(argv);

    *console = (sb_console_t) {
        .arguments  = argv,
        .offset_max = argc,
        .offset     = 1,
    };
}

sb_bool_t sb_console_process(sb_console_t *console, sb_container_t *container)
{
    assert(console);
    assert(container);

    while (console->offset < console->offset_max)
    {
        sb_size_t size =
            sizeof(argument_to_input) / 
            sizeof(argument_to_input[0]);

        sb_char_t *input = console->arguments[console->offset];

        sb_argument_t argument = SB_ARGUMENT_UNKNOWN;

        for (sb_size_t i = 0; i < size; ++i)
        {
            if (!strcmp(argument_to_input[i], input))
            {
                argument = i;
                input = console->arguments[++console->offset];

                break;
            }
        }

        sb_handler_t handler = argument_to_handler[argument];

        if (!handler(container, input))
        {
            return false;
        }

        console->offset++;
    }

    return true;
}
