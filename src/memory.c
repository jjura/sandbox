// includes: project
//------------------------------------------------------------------------------
#include "memory.h"

// includes: c
//------------------------------------------------------------------------------
#include <stdlib.h>

// defines:
//------------------------------------------------------------------------------
#define DEFAULT_MEMORY_SIZE (1024 * 1024)

// function: memory_create
//------------------------------------------------------------------------------
void_t memory_create(memory_t *memory)
{
        memory->size            = DEFAULT_MEMORY_SIZE;
        memory->allocation      = malloc(memory->size);
}

// function: memory_destroy
//------------------------------------------------------------------------------
void_t memory_destroy(memory_t *memory)
{
        free(memory->allocation);
}

// function: memory_head
//------------------------------------------------------------------------------
void_t *memory_head(memory_t *memory)
{
        return memory->allocation + memory->size;
}
