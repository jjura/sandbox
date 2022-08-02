#define _GNU_SOURCE

// includes: project
//------------------------------------------------------------------------------
#include "sb_log.h"
#include "sb_network.h"

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
static inline sb_void_t execute(sb_char_t *format, ...)
{
        sb_char_t *command;

        va_list list;
        va_start(list, format);
        vasprintf(&command, format, list);
        va_end(list);

        system(command);
        free(command);
}

// function: sb_network_create
//------------------------------------------------------------------------------
sb_void_t sb_network_create(sb_network_t *network)
{
        network->masquerade = NULL;
}

// function: sb_network_configure
//------------------------------------------------------------------------------
sb_void_t sb_network_configure(sb_network_t *network, sb_i32_t pid)
{
        if (!network->masquerade)
        {
                return;
        }

        // procedure: chose subnet
        //----------------------------------------------------------------------
        // TODO: come up with way to generate unique subnet
        sb_i32_t subnet = pid % 256;

        // procedure: create host and container interface
        //----------------------------------------------------------------------
        execute("ip link add veth-%d type veth peer name veth0", pid);

        // procedure: set ip address of host interface
        //----------------------------------------------------------------------
        execute("ip addr add 10.0.%d.1/24 dev veth-%d", subnet, pid);

        // procedure: enable host interface
        //----------------------------------------------------------------------
        execute("ip link set veth-%d up", pid);

        // procedure: attach namespace to container process
        //----------------------------------------------------------------------
        execute("ip netns attach netns-%d %d", pid, pid);

        // procedure: attach container interface to container namespace
        //----------------------------------------------------------------------
        execute("ip link set veth0 netns netns-%d", pid);

        // procedure: set ip address of container interface
        //----------------------------------------------------------------------
        execute("ip netns exec netns-%d ip addr add 10.0.%d.2/24 dev veth0",
                        pid, subnet);

        // procedure: enable container interfaces
        //----------------------------------------------------------------------
        execute("ip netns exec netns-%d ip link set lo up", pid);
        execute("ip netns exec netns-%d ip link set veth0 up", pid);

        // procedure: add default route via the gateway
        //----------------------------------------------------------------------
        execute("ip netns exec netns-%d ip route add default via 10.0.%d.1",
                        pid, subnet);

        // procedure: configure nft
        //----------------------------------------------------------------------
        execute("echo 1 > /proc/sys/net/ipv4/ip_forward");

        execute("nft add table inet nat");
        execute("nft add chain inet nat postrouting"
                "'{ type nat hook postrouting priority 100 ; }'");
        execute("nft add rule inet nat postrouting oifname %s masquerade",
                        network->masquerade);
}

// function: sb_network_deconfigure
//------------------------------------------------------------------------------
sb_void_t sb_network_deconfigure(sb_network_t *network, sb_i32_t pid)
{
        if (!network->masquerade)
        {
                return;
        }

        // procedure: destroy host and container interface
        //----------------------------------------------------------------------
        execute("ip link delete veth-%d", pid);

        // procedure: destroy namespace
        //----------------------------------------------------------------------
        execute("ip netns delete netns-%d", pid);
}

// function: sb_network_set_masquerade
//------------------------------------------------------------------------------
sb_void_t sb_network_set_masquerade(sb_network_t *network, sb_char_t *masquerade)
{
        network->masquerade = masquerade;
}

// function: sb_network_get_masquerade
//------------------------------------------------------------------------------
sb_char_t *sb_network_get_masquerade(sb_network_t *network)
{
        return network->masquerade;
}
