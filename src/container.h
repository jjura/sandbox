#ifndef CONTAINER_H
#define CONTAINER_H

// includes: project
//------------------------------------------------------------------------------
#include "type.h"
#include "memory.h"
#include "network.h"
#include "binding.h"
#include "filesystem.h"

// type: container_t
//------------------------------------------------------------------------------
typedef struct {
        // member: pid
        //----------------------------------------------------------------------
        i32_t pid;

        // member: directory
        //----------------------------------------------------------------------
        path_t directory;

        // member: command
        //----------------------------------------------------------------------
        path_t command;

        // member: network
        //----------------------------------------------------------------------
        network_t network;

        // member: binding
        //----------------------------------------------------------------------
        binding_t binding;

        // member: filesystem
        //----------------------------------------------------------------------
        filesystem_t filesystem;

        // member: memory
        //----------------------------------------------------------------------
        memory_t memory;

} container_t;

// function: container_create
//------------------------------------------------------------------------------
void_t container_create(container_t *container);

// function: container_destroy
//------------------------------------------------------------------------------
void_t container_destroy(container_t *container);

// function: container_set_directory
//------------------------------------------------------------------------------
void_t container_set_directory(container_t *container, path_t directory);

// function: container_set_command
//------------------------------------------------------------------------------
void_t container_set_command(container_t *container, path_t command);

// function: container_set_binding
//------------------------------------------------------------------------------
void_t container_set_binding(container_t *container,
                path_t source,
                path_t target);

// function: container_set_masquerade
//------------------------------------------------------------------------------
void_t container_set_masquerade(container_t *container, char_t *masquerade);

// function: container_execute
//------------------------------------------------------------------------------
void_t container_execute(container_t *container);

#endif
