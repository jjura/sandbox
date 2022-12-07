#include "sb_vector.h"

#include <assert.h>
#include <stdlib.h>
#include <string.h>

sb_void_t sb_vector_create(
        sb_vector_t *vector,
        sb_size_t size_max,
        sb_size_t size_value)
{
    assert(vector);

    *vector = (sb_vector_t) {
        .size_max   = size_max,
        .size_value = size_value,
        .buffer     = malloc(size_value * size_max),
    };
}

sb_void_t sb_vector_destroy(sb_vector_t *vector)
{
    assert(vector);

    free(vector->buffer);
}

sb_void_t sb_vector_add(sb_vector_t *vector, sb_void_t *value)
{
    assert(vector);
    assert(value);

    if (vector->size == vector->size_max)
    {
        vector->size_max = vector->size_max * 2 + 1;
        vector->buffer = realloc(
                vector->buffer,
                vector->size_value * vector->size_max);
    }

    sb_char_t *destination =
        vector->buffer +
        vector->size * vector->size_value;

    memcpy(destination, value, vector->size_value);

    vector->size++;
}

sb_void_t *sb_vector_at(sb_vector_t *vector, sb_size_t index)
{
    assert(vector);

    return vector->buffer + vector->size_value * index;
}

sb_size_t sb_vector_size(sb_vector_t *vector)
{
    assert(vector);

    return vector->size;
}
