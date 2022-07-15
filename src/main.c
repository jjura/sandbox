// includes: project
//------------------------------------------------------------------------------
#include "option.h"
#include "handler.h"
#include "console.h"
#include "container.h"

int main(i32_t argc, char_t *argv[])
{
        // member: container
        //----------------------------------------------------------------------
        container_t container;
        container_create(&container);

        // member: console
        //----------------------------------------------------------------------
        console_t console;
        console_create(&console, argc, argv);

        // member: handler
        //----------------------------------------------------------------------
        handler_t handler;
        handler_create(&handler, &container);

        // procedure: execution
        //----------------------------------------------------------------------
        option_t option;

        while (console_get_option(&console, &option))
        {
                handler_execute(&handler, &option);
        }

        container_execute(&container);

        // procedure: shutdown
        //----------------------------------------------------------------------
        container_destroy(&container);
}
