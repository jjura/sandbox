#ifndef SB_FILESYSTEM_H
#define SB_FILESYSTEM_H

// includes: project
//------------------------------------------------------------------------------
#include "sb_type.h"

// type: sb_filesystem_entry_t
//------------------------------------------------------------------------------
typedef struct {
        // member: target
        //----------------------------------------------------------------------
        sb_path_t target;

        // member: type
        //----------------------------------------------------------------------
        sb_char_t *type;

        // member: data
        //----------------------------------------------------------------------
        sb_char_t *data;

} sb_filesystem_entry_t;

// type: sb_filesystem_t
//------------------------------------------------------------------------------
typedef struct {
        // member: offset
        //----------------------------------------------------------------------
        sb_i32_t offset;

        // member: offset_max
        //----------------------------------------------------------------------
        sb_i32_t offset_max;

        // member: entry
        //----------------------------------------------------------------------
        sb_filesystem_entry_t *entry;

} sb_filesystem_t;

// function: sb_filesystem_create
//------------------------------------------------------------------------------
sb_void_t sb_filesystem_create(sb_filesystem_t *filesystem);

// function: sb_filesystem_destroy
//------------------------------------------------------------------------------
sb_void_t sb_filesystem_destroy(sb_filesystem_t *filesystem);

// function: sb_filesystem_set
//------------------------------------------------------------------------------
sb_void_t sb_filesystem_set(sb_filesystem_t *filesystem, sb_path_t target,
                sb_char_t *type,
                sb_char_t *data);

// function: sb_filesystem_mount
//------------------------------------------------------------------------------
sb_void_t sb_filesystem_mount(sb_filesystem_t *filesystem, sb_path_t directory);

// function: sb_filesystem_unmount
//------------------------------------------------------------------------------
sb_void_t sb_filesystem_unmount(
                sb_filesystem_t *filesystem,
                sb_path_t directory);

#endif
