#ifndef SB_FILE_H
#define SB_FILE_H

// includes: project
//------------------------------------------------------------------------------
#include "sb_type.h"

// function: sb_file_create
//------------------------------------------------------------------------------
sb_void_t sb_file_create(sb_path_t path);

// function: sb_file_read
//------------------------------------------------------------------------------
sb_void_t sb_file_read(sb_path_t path, sb_char_t *buffer, sb_i32_t size);

// function: sb_file_exists
//------------------------------------------------------------------------------
sb_bool_t sb_file_exists(sb_path_t path);

// function: sb_file_size
//------------------------------------------------------------------------------
sb_i32_t sb_file_size(sb_path_t path);

#endif
