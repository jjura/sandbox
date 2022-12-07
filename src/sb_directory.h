#ifndef SB_DIRECTORY_H
#define SB_DIRECTORY_H

#include "sb_type.h"

typedef sb_bool_t (*sb_directory_iterator_t)(
        sb_char_t *path,
        sb_char_t *argument);

sb_void_t sb_directory_create(sb_char_t *directory, sb_i32_t mode);

sb_bool_t sb_directory_exists(sb_char_t *directory);

sb_bool_t sb_directory_used(sb_char_t *directory, sb_char_t *argument);

sb_bool_t sb_directory_for_each(
        sb_char_t *directory,
        sb_char_t *argument,
        sb_directory_iterator_t iterator);

#endif
