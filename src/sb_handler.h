#ifndef SB_HANDLER_H
#define SB_HANDLER_H

// includes: project
//------------------------------------------------------------------------------
#include "sb_option.h"
#include "sb_container.h"

// type: sb_handler_t
//------------------------------------------------------------------------------
typedef struct {
        // member: container
        //----------------------------------------------------------------------
        sb_container_t *container;

} sb_handler_t;

// function: sb_handler_create
//------------------------------------------------------------------------------
sb_void_t sb_handler_create(sb_handler_t *handler, sb_container_t *container);

// function: sb_handler_execute
//------------------------------------------------------------------------------
sb_void_t sb_handler_execute(sb_handler_t *handler, sb_option_t *option);

#endif
