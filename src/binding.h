#ifndef BINDING_H
#define BINDING_H

// includes: project
//------------------------------------------------------------------------------
#include "type.h"

// type: binding_entry_t
//------------------------------------------------------------------------------
typedef struct {
        // member: source
        //----------------------------------------------------------------------
        path_t source;

        // member: target
        //----------------------------------------------------------------------
        path_t target;

} binding_entry_t;

// type: binding
//------------------------------------------------------------------------------
typedef struct {
        // member: offset
        //----------------------------------------------------------------------
        i32_t offset;

        // member: offset_max
        //----------------------------------------------------------------------
        i32_t offset_max;

        // member: entry
        //----------------------------------------------------------------------
        binding_entry_t *entry;

} binding_t;

// function: binding_create
//------------------------------------------------------------------------------
void_t binding_create(binding_t *binding);

// function: binding_destroy
//------------------------------------------------------------------------------
void_t binding_destroy(binding_t *binding);

// function: binding_set
//------------------------------------------------------------------------------
void_t binding_set(binding_t *binding, path_t source, path_t target);

// function: binding_mount
//------------------------------------------------------------------------------
void_t binding_mount(binding_t *binding, path_t directory);

// function: binding_unmount
//------------------------------------------------------------------------------
void_t binding_unmount(binding_t *binding, path_t directory);

#endif
