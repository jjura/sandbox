#ifndef SB_STACK_H
#define SB_STACK_H

#include "sb_type.h"

typedef struct {
    sb_char_t *address;
    sb_size_t size;
} sb_stack_t;

sb_void_t sb_stack_create(sb_stack_t *stack, sb_size_t size);

sb_void_t sb_stack_destroy(sb_stack_t *stack);

sb_char_t *sb_stack_head(sb_stack_t *stack);

#endif
