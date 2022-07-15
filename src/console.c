// includes: project
//------------------------------------------------------------------------------
#include "log.h"
#include "console.h"

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
        option_id_t id;

        // member: argument
        //----------------------------------------------------------------------
        char_t *argument;

        // member: value
        //----------------------------------------------------------------------
        bool_t value;

} configuration_t;

// variable: option_configs
//------------------------------------------------------------------------------
static configuration_t configuration[] =
{
        { OPTION_ID_BINDING,    "--binding",    true },
        { OPTION_ID_COMMAND,    "--command",    true },
        { OPTION_ID_NETWORK,    "--network",    true },
        { OPTION_ID_DIRECTORY,  "--directory",  true },
};

// function: find_configuration
//------------------------------------------------------------------------------
static configuration_t *find_configuration(char_t *argument)
{
        i32_t size = sizeof(configuration) / sizeof(configuration[0]);

        for (i32_t i = 0; i < size; ++i)
        {
                if (!strcmp(configuration[i].argument, argument))
                {
                        return configuration + i;
                }
        }

        return NULL;
}

// function: console_create
//------------------------------------------------------------------------------
void_t console_create(console_t *console, i32_t argc, char_t **argv)
{
        console->offset         = 1;
        console->offset_max     = argc;
        console->argument       = argv;
}

// function: console_get_option
//------------------------------------------------------------------------------
bool_t console_get_option(console_t *console, option_t *option)
{
        if (console->offset == console->offset_max)
        {
                return false;
        }

        char_t **argument = console->argument + console->offset;
        configuration_t *config = find_configuration(argument[0]);

        if (!config)
        {
                LOG_ERROR("Unknown option: %s", argument[0]);
        }

        option_create(option, config->id, config->value ? argument[1] : NULL);

        console->offset += config->value ?
                OFFSET_INCREMENT_WITH_VALUE :
                OFFSET_INCREMENT_WITHOUT_VALUE;

        return true;
}
