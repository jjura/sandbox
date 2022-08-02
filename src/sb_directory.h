#ifndef SB_DIRECTORY_H
#define SB_DIRECTORY_H

// includes: project
//------------------------------------------------------------------------------
#include "sb_type.h"

// function: sb_directory_exists
//------------------------------------------------------------------------------
sb_bool_t sb_directory_exists(sb_path_t directory);

// function: sb_directory_create
//------------------------------------------------------------------------------
sb_void_t sb_directory_create(sb_path_t directory);

#endif
