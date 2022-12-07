#ifndef SB_FILE_H
#define SB_FILE_H

#include "sb_type.h"

sb_void_t sb_file_create(sb_char_t *file, sb_i32_t mode);

sb_bool_t sb_file_exists(sb_char_t *file);

sb_size_t sb_file_size(sb_char_t *file);

sb_void_t sb_file_read(sb_char_t *file, sb_char_t *buffer, sb_size_t size);

sb_char_t *sb_file_find(sb_char_t *file, sb_char_t *value, sb_char_t delimeter);

#endif
