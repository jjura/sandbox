#ifndef SB_VECTOR_H
#define SB_VECTOR_H

#include "sb_type.h"

typedef struct {
    sb_char_t *buffer;
    sb_size_t size;
    sb_size_t size_max;
    sb_size_t size_value;
} sb_vector_t;

sb_void_t sb_vector_create(
        sb_vector_t *vector,
        sb_size_t size_max,
        sb_size_t size_value);

sb_void_t sb_vector_destroy(sb_vector_t *vector);

sb_void_t sb_vector_add(sb_vector_t *vector, sb_void_t *value);

sb_void_t *sb_vector_at(sb_vector_t *vector, sb_size_t index);

sb_size_t sb_vector_size(sb_vector_t *vector);

#endif
