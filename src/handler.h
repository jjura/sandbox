#ifndef HANDLER_H
#define HANDLER_H

// includes: project
//------------------------------------------------------------------------------
#include "option.h"
#include "container.h"

// type: handler_t
//------------------------------------------------------------------------------
typedef struct {
        // member: container
        //----------------------------------------------------------------------
        container_t *container;

} handler_t;

// function: handler_create
//------------------------------------------------------------------------------
void_t handler_create(handler_t *handler, container_t *container);

// function: handler_execute
//------------------------------------------------------------------------------
void_t handler_execute(handler_t *handler, option_t *option);

#endif
