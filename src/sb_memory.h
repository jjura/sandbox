#ifndef SB_MEMORY_H
#define SB_MEMORY_H

// includes: project
//------------------------------------------------------------------------------
#include "sb_type.h"

// type: sb_memory_tt
//------------------------------------------------------------------------------
typedef struct {
        // member: size_t
        //----------------------------------------------------------------------
        sb_i32_t size;

        // member: allocation
        //----------------------------------------------------------------------
        sb_char_t *allocation;

} sb_memory_tt;

// function: sb_memory_tcreate
//------------------------------------------------------------------------------
sb_void_t sb_memory_tcreate(sb_memory_tt *memory);

// function: sb_memory_tdestroy
//------------------------------------------------------------------------------
sb_void_t sb_memory_tdestroy(sb_memory_tt *memory);

// function: sb_memory_thead
//------------------------------------------------------------------------------
sb_void_t *sb_memory_thead(sb_memory_tt *memory);

#endif
