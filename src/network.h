#ifndef NETWORK_H
#define NETWORK_H

// includes: project
//------------------------------------------------------------------------------
#include "type.h"

// type: network_t
//------------------------------------------------------------------------------
typedef struct {
        // member: address
        //----------------------------------------------------------------------
        char_t *address;

        // member: gateway
        //----------------------------------------------------------------------
        char_t *gateway;

        // member: interface_host
        //----------------------------------------------------------------------
        char_t *interface_host;

        // member: interface_container
        //----------------------------------------------------------------------
        char_t *interface_container;

} network_t;

// function: network_create
//------------------------------------------------------------------------------
void_t network_create(network_t *network);

// function: network_destroy
//------------------------------------------------------------------------------
void_t network_destroy(network_t *network);

// function: network_set_address
//------------------------------------------------------------------------------
void_t network_set_address(network_t *network,
                char_t *address,
                char_t *gateway);

// function: network_configure
//------------------------------------------------------------------------------
void_t network_configure(network_t *network, i32_t pid);

#endif
