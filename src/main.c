// includes: project
//------------------------------------------------------------------------------
#include "log.h"
#include "option.h"
#include "handler.h"
#include "console.h"
#include "container.h"

// includes: c
//------------------------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

// variable: container
//------------------------------------------------------------------------------
static container_t container;

// variable: console
//------------------------------------------------------------------------------
static console_t console;

// variable: handler
//------------------------------------------------------------------------------
static handler_t handler;

// variable: option
//------------------------------------------------------------------------------
static option_t option;

// function: signal_handler
//------------------------------------------------------------------------------
static void signal_handler(int signal)
{
        LOG_INFO("Captured signal: %d. Shutting down container.", signal);
}

// function: main
//------------------------------------------------------------------------------
int main(i32_t argc, char_t *argv[])
{
        // procedure: handle signal
        //----------------------------------------------------------------------
        signal(SIGINT, signal_handler);

        // procedure: create container
        //----------------------------------------------------------------------
        container_create(&container);

        // procedure: create console
        //----------------------------------------------------------------------
        console_create(&console, argc, argv);

        // procedure: create handler
        //----------------------------------------------------------------------
        handler_create(&handler, &container);

        // procedure: execute options
        //----------------------------------------------------------------------
        while (console_get_option(&console, &option))
        {
                handler_execute(&handler, &option);
        }

        // procedure: execute container
        //----------------------------------------------------------------------
        container_execute(&container);

        // procedure: shutdown container
        //----------------------------------------------------------------------
        container_destroy(&container);
}
