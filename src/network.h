#ifndef NETWORK_H
#define NETWORK_H

// includes: project
//------------------------------------------------------------------------------
#include "type.h"

// type: network_t
//------------------------------------------------------------------------------
typedef struct {
        // member: masquerade
        char_t *masquerade;

} network_t;

// function: network_create
//------------------------------------------------------------------------------
void_t network_create(network_t *network);

// function: network_configure
//------------------------------------------------------------------------------
void_t network_configure(network_t *network, i32_t pid);

// function: network_deconfigure
//------------------------------------------------------------------------------
void_t network_deconfigure(network_t *network, i32_t pid);

// function: network_set_masquerade
//------------------------------------------------------------------------------
void_t network_set_masquerade(network_t *network, char_t *masquerade);

// function: network_get_masquerade
//------------------------------------------------------------------------------
char_t *network_get_masquerade(network_t *network);

#endif
