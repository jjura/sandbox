#define _GNU_SOURCE

// includes: project
//------------------------------------------------------------------------------
#include "log.h"
#include "network.h"

// includes: c
//------------------------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

// defines:
//------------------------------------------------------------------------------
#define DEFAULT_INTERFACE_HOST      "veth0"
#define DEFAULT_INTERFACE_CONTAINER "veth1"

// function: execute
//------------------------------------------------------------------------------
static inline void_t execute(char_t *format, ...)
{
        char_t *command;

        va_list list;
        va_start(list, format);
        vasprintf(&command, format, list);
        va_end(list);

        system(command);
        free(command);
}

// function: network_create
//------------------------------------------------------------------------------
void_t network_create(network_t *network)
{
        network->address                = NULL;
        network->gateway                = NULL;
        network->interface_host         = DEFAULT_INTERFACE_HOST;
        network->interface_container    = DEFAULT_INTERFACE_CONTAINER;
}

// function: network_destroy
//------------------------------------------------------------------------------
void_t network_destroy(network_t *network)
{
        if (!network->address || !network->gateway)
        {
                return;
        }

        // procedure: destroy host and container interface
        //----------------------------------------------------------------------
        execute("ip link delete %s", network->interface_host);

        // procedure: destroy namespace
        //----------------------------------------------------------------------
        execute("ip netns delete netns0");
}

// function: network_set_address
//------------------------------------------------------------------------------
void_t network_set_address(network_t *network, char_t *address, char_t *gateway)
{
        network->address = address;
        network->gateway = gateway;
}

// function: network_configure
//------------------------------------------------------------------------------
void_t network_configure(network_t *network, i32_t pid)
{
        if (!network->address || !network->gateway)
        {
                return;
        }

        // procedure: create host and container interface
        //----------------------------------------------------------------------
        execute("ip link add %s type veth peer name %s",
                        network->interface_host,
                        network->interface_container);

        // procedure: enable host interface
        //----------------------------------------------------------------------
        execute("ip link set %s up", network->interface_host);

        // procedure: attach host interface to bridge
        //----------------------------------------------------------------------
        execute("ip link set %s master br0", network->interface_host);

        // procedure: attach namespace to container process
        //----------------------------------------------------------------------
        execute("ip netns attach netns0 %d", pid);

        // procedure: attach container interface to container namespace
        //----------------------------------------------------------------------
        execute("ip link set %s netns netns0", network->interface_container);

        // procedure: set ip address of container interface
        //----------------------------------------------------------------------
        execute("ip netns exec netns0 ip addr add %s/24 dev %s",
                        network->address,
                        network->interface_container);

        // procedure: enable container interfaces
        //----------------------------------------------------------------------
        execute("ip netns exec netns0 ip link set lo up");
        execute("ip netns exec netns0 ip link set %s up",
                        network->interface_container);

        // procedure: add default route via the gateway
        //----------------------------------------------------------------------
        execute("ip netns exec netns0 ip route add default via %s",
                        network->gateway);
}
