#include "sb_stack.h"

#include <assert.h>
#include <stdlib.h>

sb_void_t sb_stack_create(sb_stack_t *stack, sb_size_t size)
{
    assert(stack);

    stack->size = size;
    stack->address = malloc(size);
}

sb_void_t sb_stack_destroy(sb_stack_t *stack)
{
    assert(stack);

    free(stack->address);
}

sb_char_t *sb_stack_head(sb_stack_t *stack)
{
    assert(stack);

    return stack->address + stack->size;
}
