// includes: project
//------------------------------------------------------------------------------
#include "sb_log.h"
#include "sb_console.h"

// includes: c
//------------------------------------------------------------------------------
#include <string.h>

// defines:
//------------------------------------------------------------------------------
#define OFFSET_INCREMENT_WITH_VALUE     2
#define OFFSET_INCREMENT_WITHOUT_VALUE  1

// type: configuration_t
//------------------------------------------------------------------------------
typedef struct {
        // member: id
        //----------------------------------------------------------------------
        sb_option_id_t id;

        // member: argument
        //----------------------------------------------------------------------
        sb_char_t *argument;

        // member: value
        //----------------------------------------------------------------------
        sb_bool_t value;

} configuration_t;

// variable: sb_option_configs
//------------------------------------------------------------------------------
static configuration_t configuration[] =
{
        { OPTION_ID_BINDING,    "--binding",    true },
        { OPTION_ID_COMMAND,    "--command",    true },
        { OPTION_ID_DIRECTORY,  "--directory",  true },
        { OPTION_ID_MASQUERADE, "--masquerade", true },
};

// function: find_configuration
//------------------------------------------------------------------------------
static configuration_t *find_configuration(sb_char_t *argument)
{
        sb_i32_t size = sizeof(configuration) / sizeof(configuration[0]);

        for (sb_i32_t i = 0; i < size; ++i)
        {
                if (!strcmp(configuration[i].argument, argument))
                {
                        return configuration + i;
                }
        }

        return NULL;
}

// function: sb_console_create
//------------------------------------------------------------------------------
sb_void_t sb_console_create(
                sb_console_t *console,
                sb_i32_t argc,
                sb_char_t **argv)
{
        console->offset         = 1;
        console->offset_max     = argc;
        console->argument       = argv;
}

// function: sb_console_get_option
//------------------------------------------------------------------------------
sb_bool_t sb_console_get_option(sb_console_t *console, sb_option_t *option)
{
        if (console->offset == console->offset_max)
        {
                return false;
        }

        sb_char_t **argument = console->argument + console->offset;

        configuration_t *config = find_configuration(argument[0]);

        if (!config)
        {
                SB_LOG_ERROR("Unknown option: %s", argument[0]);
        }

        sb_option_create(option, config->id, config->value ? argument[1] : NULL);

        console->offset += config->value ?
                OFFSET_INCREMENT_WITH_VALUE :
                OFFSET_INCREMENT_WITHOUT_VALUE;

        return true;
}
