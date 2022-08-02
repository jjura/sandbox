#ifndef SB_BINDING_H
#define SB_BINDING_H

// includes: project
//------------------------------------------------------------------------------
#include "sb_type.h"

// type: sb_binding_entry_t
//------------------------------------------------------------------------------
typedef struct {
        // member: source
        //----------------------------------------------------------------------
        sb_path_t source;

        // member: target
        //----------------------------------------------------------------------
        sb_path_t target;

} sb_binding_entry_t;

// type: binding
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
        sb_binding_entry_t *entry;

} sb_binding_t;

// function: sb_binding_create
//------------------------------------------------------------------------------
sb_void_t sb_binding_create(sb_binding_t *binding);

// function: sb_binding_destroy
//------------------------------------------------------------------------------
sb_void_t sb_binding_destroy(sb_binding_t *binding);

// function: sb_binding_set
//------------------------------------------------------------------------------
sb_void_t sb_binding_set(
                sb_binding_t *binding,
                sb_path_t source,
                sb_path_t target);

// function: sb_binding_mount
//------------------------------------------------------------------------------
sb_void_t sb_binding_mount(sb_binding_t *binding, sb_path_t directory);

// function: sb_binding_unmount
//------------------------------------------------------------------------------
sb_void_t sb_binding_unmount(sb_binding_t *binding, sb_path_t directory);

#endif
