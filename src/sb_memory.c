// includes: project
//------------------------------------------------------------------------------
#include "sb_memory.h"

// includes: c
//------------------------------------------------------------------------------
#include <stdlib.h>

// defines:
//------------------------------------------------------------------------------
#define DEFAULT_MEMORY_SIZE (1024 * 1024)

// function: sb_memory_tcreate
//------------------------------------------------------------------------------
sb_void_t sb_memory_tcreate(sb_memory_tt *memory)
{
        memory->size            = DEFAULT_MEMORY_SIZE;
        memory->allocation      = malloc(memory->size);
}

// function: sb_memory_tdestroy
//------------------------------------------------------------------------------
sb_void_t sb_memory_tdestroy(sb_memory_tt *memory)
{
        free(memory->allocation);
}

// function: sb_memory_thead
//------------------------------------------------------------------------------
sb_void_t *sb_memory_thead(sb_memory_tt *memory)
{
        return memory->allocation + memory->size;
}
