#ifndef DIRECTORY_H
#define DIRECTORY_H

// includes: project
//------------------------------------------------------------------------------
#include "type.h"

// function: directory_exists
//------------------------------------------------------------------------------
bool_t directory_exists(path_t directory);

// function: directory_create
//------------------------------------------------------------------------------
void_t directory_create(path_t directory);

#endif
