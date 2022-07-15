#ifndef MEMORY_H
#define MEMORY_H

// includes: project
//------------------------------------------------------------------------------
#include "type.h"

// type: memory_t
//------------------------------------------------------------------------------
typedef struct {
        // member: size_t
        //----------------------------------------------------------------------
        i32_t size;

        // member: allocation
        //----------------------------------------------------------------------
        char_t *allocation;

} memory_t;

// function: memory_create
//------------------------------------------------------------------------------
void_t memory_create(memory_t *memory);

// function: memory_destroy
//------------------------------------------------------------------------------
void_t memory_destroy(memory_t *memory);

// function: memory_head
//------------------------------------------------------------------------------
void_t *memory_head(memory_t *memory);

#endif
