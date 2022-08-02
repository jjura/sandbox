// includes: project
//------------------------------------------------------------------------------
#include "sb_log.h"
#include "sb_option.h"
#include "sb_handler.h"
#include "sb_console.h"
#include "sb_container.h"

// includes: c
//------------------------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

// variable: container
//------------------------------------------------------------------------------
static sb_container_t container;

// variable: console
//------------------------------------------------------------------------------
static sb_console_t console;

// variable: handler
//------------------------------------------------------------------------------
static sb_handler_t handler;

// variable: option
//------------------------------------------------------------------------------
static sb_option_t option;

// function: signal_handler
//------------------------------------------------------------------------------
static void signal_handler(int signal)
{
        SB_LOG_INFO("Captured signal: %d. Shutting down container.", signal);
}

// function: main
//------------------------------------------------------------------------------
int main(sb_i32_t argc, sb_char_t *argv[])
{
        // procedure: handle signal
        //----------------------------------------------------------------------
        signal(SIGINT, signal_handler);

        // procedure: create container
        //----------------------------------------------------------------------
        sb_container_create(&container);

        // procedure: create console
        //----------------------------------------------------------------------
        sb_console_create(&console, argc, argv);

        // procedure: create handler
        //----------------------------------------------------------------------
        sb_handler_create(&handler, &container);

        // procedure: execute options
        //----------------------------------------------------------------------
        while (sb_console_get_option(&console, &option))
        {
                sb_handler_execute(&handler, &option);
        }

        // procedure: execute container
        //----------------------------------------------------------------------
        sb_container_execute(&container);

        // procedure: shutdown container
        //----------------------------------------------------------------------
        sb_container_destroy(&container);
}
