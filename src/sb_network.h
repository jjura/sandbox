#ifndef SB_NETWORK_H
#define SB_NETWORK_H

// includes: project
//------------------------------------------------------------------------------
#include "sb_type.h"

// type: sb_network_t
//------------------------------------------------------------------------------
typedef struct {
        // member: masquerade
        sb_char_t *masquerade;

} sb_network_t;

// function: sb_network_create
//------------------------------------------------------------------------------
sb_void_t sb_network_create(sb_network_t *network);

// function: sb_network_configure
//------------------------------------------------------------------------------
sb_void_t sb_network_configure(sb_network_t *network, sb_i32_t pid);

// function: sb_network_deconfigure
//------------------------------------------------------------------------------
sb_void_t sb_network_deconfigure(sb_network_t *network, sb_i32_t pid);

// function: sb_network_set_masquerade
//------------------------------------------------------------------------------
sb_void_t sb_network_set_masquerade(
                sb_network_t *network,
                sb_char_t *masquerade);

// function: sb_network_get_masquerade
//------------------------------------------------------------------------------
sb_char_t *sb_network_get_masquerade(sb_network_t *network);

#endif
