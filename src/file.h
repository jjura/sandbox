#ifndef FILE_H
#define FILE_H

// includes: project
//------------------------------------------------------------------------------
#include "type.h"

// function: file_exists
//------------------------------------------------------------------------------
bool_t file_exists(path_t path);

// function: file_size
//------------------------------------------------------------------------------
i32_t file_size(path_t path);

// function: file_create
//------------------------------------------------------------------------------
void_t file_create(path_t path);

// function: file_read
//------------------------------------------------------------------------------
void_t file_read(path_t path, char_t *buffer, i32_t size);

#endif
