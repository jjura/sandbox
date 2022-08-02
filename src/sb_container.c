#define _GNU_SOURCE

// includes: project
//------------------------------------------------------------------------------
#include "sb_log.h"
#include "sb_file.h"
#include "sb_directory.h"
#include "sb_container.h"

// includes: c
//------------------------------------------------------------------------------
#include <errno.h>
#include <string.h>

// includes: linux
//------------------------------------------------------------------------------
#include <sched.h>
#include <unistd.h>
#include <sys/wait.h>

// defines:
//------------------------------------------------------------------------------
#define DEFAULT_HOSTNAME_FILE   "/etc/hostname"
#define DEFAULT_DIRECTORY       "/"
#define DEFAULT_SHELL           "/bin/sh"
#define DEFAULT_COMMAND         DEFAULT_SHELL

// function: sb_container_process_execute
//------------------------------------------------------------------------------
static sb_void_t sb_container_process_execute(sb_container_t *container)
{
        if (execl(DEFAULT_SHELL, DEFAULT_SHELL, "-c", container->command, NULL))
        {
                SB_LOG_ERROR("Failed exec: %s.", strerror(errno));
        }
}

// function: sb_container_process_set_hostname
//------------------------------------------------------------------------------
static sb_void_t sb_container_process_set_hostname(sb_path_t file)
{
        if (!sb_file_exists(file))
        {
                return;
        }

        sb_i32_t size = sb_file_size(file);
        sb_char_t hostname[size];

        sb_file_read(file, hostname, size);
        sethostname(hostname, size);
}

// function: sb_container_process_set_root
//------------------------------------------------------------------------------
static sb_void_t sb_container_process_set_root(sb_container_t *container)
{
        if (chroot(container->directory))
        {
                SB_LOG_ERROR("Failed chroot: %s.", strerror(errno));
        }
}

// function: sb_container_process_set_directory
//------------------------------------------------------------------------------
static sb_void_t sb_container_process_set_directory(sb_container_t *container)
{
        if (chdir(container->directory))
        {
                SB_LOG_ERROR("Failed chdir: %s.", strerror(errno));
        }
}

// function: sb_container_process
//------------------------------------------------------------------------------
static sb_i32_t sb_container_process(sb_void_t *container)
{
        // procedure: change directory
        //----------------------------------------------------------------------
        sb_container_process_set_directory(container);

        // procedure: change root
        //----------------------------------------------------------------------
        sb_container_process_set_root(container);

        // procedure: change hostname
        //----------------------------------------------------------------------
        sb_container_process_set_hostname(DEFAULT_HOSTNAME_FILE);

        // procedure: execute command
        //----------------------------------------------------------------------
        sb_container_process_execute(container);

        return 0;
}

// function: sb_container_create
//------------------------------------------------------------------------------
sb_void_t sb_container_create(sb_container_t *container)
{
        // procedure: initialize container
        //----------------------------------------------------------------------
        container->pid          = 0;
        container->directory    = DEFAULT_DIRECTORY;
        container->command      = DEFAULT_COMMAND;

        // procedure: create memory
        //----------------------------------------------------------------------
        sb_memory_tcreate(&container->memory);

        // procedure: create filesystem
        //----------------------------------------------------------------------
        sb_filesystem_create(&container->filesystem);

        // procedure: create binding
        //----------------------------------------------------------------------
        sb_binding_create(&container->binding);

        // procedure: create network
        //----------------------------------------------------------------------
        sb_network_create(&container->network);

        // procedure: configure filesystem
        //----------------------------------------------------------------------
        sb_filesystem_set(&container->filesystem, "/dev/pts", "devpts",   NULL);
        sb_filesystem_set(&container->filesystem, "/proc",    "proc",     NULL);
        sb_filesystem_set(&container->filesystem, "/sys",     "sysfs",    NULL);

        // procedure: configure binding
        //----------------------------------------------------------------------
        sb_binding_set(&container->binding, ttyname(STDOUT_FILENO), "/dev/console");
}

// function: sb_container_destroy
//------------------------------------------------------------------------------
sb_void_t sb_container_destroy(sb_container_t *container)
{
        // procedure: destroy binding
        //----------------------------------------------------------------------
        sb_binding_destroy(&container->binding);

        // procedure: destroy filesystem
        //----------------------------------------------------------------------
        sb_filesystem_destroy(&container->filesystem);

        // procedure: destroy memory
        //----------------------------------------------------------------------
        sb_memory_tdestroy(&container->memory);
}

// function: sb_container_set_directory
//------------------------------------------------------------------------------
sb_void_t sb_container_set_directory(
                sb_container_t *container,
                sb_path_t directory)
{
        container->directory = directory;
}

// function: sb_container_set_command
//------------------------------------------------------------------------------
sb_void_t sb_container_set_command(sb_container_t *container, sb_path_t command)
{
        container->command = command;
}

// function: sb_container_set_binding
//------------------------------------------------------------------------------
sb_void_t sb_container_set_binding(sb_container_t *container,
                sb_path_t source,
                sb_path_t target)
{
        sb_binding_set(&container->binding, source, target);
}

// function: sb_container_set_masquerade
//------------------------------------------------------------------------------
sb_void_t sb_container_set_masquerade(
                sb_container_t *container,
                sb_char_t *masquerade)
{
        sb_network_set_masquerade(&container->network, masquerade);
}

// function: sb_container_execute
//------------------------------------------------------------------------------
sb_void_t sb_container_execute(sb_container_t *container)
{
        // procedure: prepare list of namespaces
        //----------------------------------------------------------------------
        sb_i32_t sb_container_namespaces =
                CLONE_NEWNS     |
                CLONE_NEWPID    |
                CLONE_NEWUTS    |
                CLONE_NEWCGROUP |
                SIGCHLD;

        if (sb_network_get_masquerade(&container->network) != NULL)
        {
                sb_container_namespaces |= CLONE_NEWNET;
        }

        // procedure: create container process
        //----------------------------------------------------------------------
        container->pid = clone(
                        sb_container_process,
                        sb_memory_thead(&container->memory),
                        sb_container_namespaces,
                        container);

        if (container->pid == -1)
        {
                SB_LOG_ERROR("Failed clone: %s", strerror(errno));
        }

        // procedure: mount filesystem
        //----------------------------------------------------------------------
        sb_filesystem_mount(&container->filesystem, container->directory);

        // procedure: mount binding
        //----------------------------------------------------------------------
        sb_binding_mount(&container->binding, container->directory);

        // procedure: configure network
        //----------------------------------------------------------------------
        sb_network_configure(&container->network, container->pid);

        // procedure: wait for container
        //----------------------------------------------------------------------
        waitpid(container->pid, NULL, 0);

        // procedure: deconfigure network
        //----------------------------------------------------------------------
        sb_network_deconfigure(&container->network, container->pid);

        // procedure: unmount binding
        //----------------------------------------------------------------------
        sb_binding_unmount(&container->binding, container->directory);

        // procedure: unmount filesystem
        //----------------------------------------------------------------------
        sb_filesystem_unmount(&container->filesystem, container->directory);
}
