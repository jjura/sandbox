#ifndef FILESYSTEM_H
#define FILESYSTEM_H

// includes: project
//------------------------------------------------------------------------------
#include "type.h"

// type: filesystem_entry_t
//------------------------------------------------------------------------------
typedef struct {
        // member: target
        //----------------------------------------------------------------------
        path_t target;

        // member: type
        //----------------------------------------------------------------------
        char_t *type;

        // member: data
        //----------------------------------------------------------------------
        char_t *data;

} filesystem_entry_t;

typedef struct {
        // member: offset
        //----------------------------------------------------------------------
        i32_t offset;

        // member: offset_max
        //----------------------------------------------------------------------
        i32_t offset_max;

        // member: entry
        //----------------------------------------------------------------------
        filesystem_entry_t *entry;

} filesystem_t;

// function: filesystem_create
//------------------------------------------------------------------------------
void_t filesystem_create(filesystem_t *filesystem);

// function: filesystem_destroy
//------------------------------------------------------------------------------
void_t filesystem_destroy(filesystem_t *filesystem);

// function: filesystem_set
//------------------------------------------------------------------------------
void_t filesystem_set(filesystem_t *filesystem, path_t target,
                char_t *type,
                char_t *data);

// function: filesystem_mount
//------------------------------------------------------------------------------
void_t filesystem_mount(filesystem_t *filesystem, path_t directory);

// function: filesystem_unmount
//------------------------------------------------------------------------------
void_t filesystem_unmount(filesystem_t *filesystem, path_t directory);

#endif
