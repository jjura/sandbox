#ifndef SB_CONTAINER_H
#define SB_CONTAINER_H

// includes: project
//------------------------------------------------------------------------------
#include "sb_type.h"
#include "sb_memory.h"
#include "sb_network.h"
#include "sb_binding.h"
#include "sb_filesystem.h"

// type: sb_container_t
//------------------------------------------------------------------------------
typedef struct {
        // member: pid
        //----------------------------------------------------------------------
        sb_i32_t pid;

        // member: directory
        //----------------------------------------------------------------------
        sb_path_t directory;

        // member: command
        //----------------------------------------------------------------------
        sb_path_t command;

        // member: network
        //----------------------------------------------------------------------
        sb_network_t network;

        // member: binding
        //----------------------------------------------------------------------
        sb_binding_t binding;

        // member: filesystem
        //----------------------------------------------------------------------
        sb_filesystem_t filesystem;

        // member: memory
        //----------------------------------------------------------------------
        sb_memory_tt memory;

} sb_container_t;

// function: sb_container_create
//------------------------------------------------------------------------------
sb_void_t sb_container_create(sb_container_t *container);

// function: sb_container_destroy
//------------------------------------------------------------------------------
sb_void_t sb_container_destroy(sb_container_t *container);

// function: sb_container_set_directory
//------------------------------------------------------------------------------
sb_void_t sb_container_set_directory(
                sb_container_t *container,
                sb_path_t directory);

// function: sb_container_set_command
//------------------------------------------------------------------------------
sb_void_t sb_container_set_command(sb_container_t *container, sb_path_t command);

// function: sb_container_set_binding
//------------------------------------------------------------------------------
sb_void_t sb_container_set_binding(
                sb_container_t *container,
                sb_path_t source,
                sb_path_t target);

// function: sb_container_set_masquerade
//------------------------------------------------------------------------------
sb_void_t sb_container_set_masquerade(
                sb_container_t *container,
                sb_char_t *masquerade);

// function: sb_container_execute
//------------------------------------------------------------------------------
sb_void_t sb_container_execute(sb_container_t *container);

#endif
