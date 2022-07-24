#define _GNU_SOURCE

// includes: project
//------------------------------------------------------------------------------
#include "log.h"
#include "file.h"
#include "directory.h"
#include "container.h"

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

// function: container_process_execute
//------------------------------------------------------------------------------
static void_t container_process_execute(container_t *container)
{
        if (execl(DEFAULT_SHELL, DEFAULT_SHELL, "-c", container->command, NULL))
        {
                LOG_ERROR("Failed exec: %s.", strerror(errno));
        }
}

// function: container_process_set_hostname
//------------------------------------------------------------------------------
static void_t container_process_set_hostname(path_t file)
{
        if (file_exists(file))
        {
                i32_t size = file_size(file);
                char_t hostname[size];

                file_read(file, hostname, size);
                sethostname(hostname, size);
        }
}

// function: container_process_set_root
//------------------------------------------------------------------------------
static void_t container_process_set_root(container_t *container)
{
        if (chroot(container->directory))
        {
                LOG_ERROR("Failed chroot: %s.", strerror(errno));
        }
}

// function: container_process_set_directory
//------------------------------------------------------------------------------
static void_t container_process_set_directory(container_t *container)
{
        if (chdir(container->directory))
        {
                LOG_ERROR("Failed chdir: %s.", strerror(errno));
        }
}

// function: container_process
//------------------------------------------------------------------------------
static i32_t container_process(void_t *container)
{
        // procedure: change directory
        //----------------------------------------------------------------------
        container_process_set_directory(container);

        // procedure: change root
        //----------------------------------------------------------------------
        container_process_set_root(container);

        // procedure: change hostname
        //----------------------------------------------------------------------
        container_process_set_hostname(DEFAULT_HOSTNAME_FILE);

        // procedure: execute command
        //----------------------------------------------------------------------
        container_process_execute(container);

        return 0;
}

// function: container_create
//------------------------------------------------------------------------------
void_t container_create(container_t *container)
{
        // procedure: initialize container
        //----------------------------------------------------------------------
        container->pid          = 0;
        container->directory    = DEFAULT_DIRECTORY;
        container->command      = DEFAULT_COMMAND;

        // procedure: create memory
        //----------------------------------------------------------------------
        memory_create(&container->memory);

        // procedure: create filesystem
        //----------------------------------------------------------------------
        filesystem_create(&container->filesystem);

        // procedure: create binding
        //----------------------------------------------------------------------
        binding_create(&container->binding);

        // procedure: create network
        //----------------------------------------------------------------------
        network_create(&container->network);

        // procedure: configure filesystem
        //----------------------------------------------------------------------
        filesystem_set(&container->filesystem, "/dev/pts", "devpts",   NULL);
        filesystem_set(&container->filesystem, "/proc",    "proc",     NULL);
        filesystem_set(&container->filesystem, "/sys",     "sysfs",    NULL);

        // procedure: configure binding
        //----------------------------------------------------------------------
        binding_set(&container->binding, ttyname(STDOUT_FILENO), "/dev/console");
}

// function: container_destroy
//------------------------------------------------------------------------------
void_t container_destroy(container_t *container)
{
        // procedure: destroy binding
        //----------------------------------------------------------------------
        binding_destroy(&container->binding);

        // procedure: destroy filesystem
        //----------------------------------------------------------------------
        filesystem_destroy(&container->filesystem);

        // procedure: destroy memory
        //----------------------------------------------------------------------
        memory_destroy(&container->memory);
}

// function: container_set_directory
//------------------------------------------------------------------------------
void_t container_set_directory(container_t *container, path_t directory)
{
        container->directory = directory;
}

// function: container_set_command
//------------------------------------------------------------------------------
void_t container_set_command(container_t *container, path_t command)
{
        container->command = command;
}

// function: container_set_binding
//------------------------------------------------------------------------------
void_t container_set_binding(container_t *container,
                path_t source,
                path_t target)
{
        binding_set(&container->binding, source, target);
}

// function: container_set_masquerade
//------------------------------------------------------------------------------
void_t container_set_masquerade(container_t *container, char_t *masquerade)
{
        network_set_masquerade(&container->network, masquerade);
}

// function: container_execute
//------------------------------------------------------------------------------
void_t container_execute(container_t *container)
{
        // procedure: create container process
        //----------------------------------------------------------------------
        container->pid = clone(
                        container_process,
                        memory_head(&container->memory),
                        CLONE_NEWNS     |
                        CLONE_NEWNET    |
                        CLONE_NEWPID    |
                        CLONE_NEWUTS    |
                        CLONE_NEWCGROUP |
                        SIGCHLD,
                        container);

        if (container->pid == -1)
        {
                LOG_ERROR("Failed clone: %s", strerror(errno));
        }

        // procedure: mount filesystem
        //----------------------------------------------------------------------
        filesystem_mount(&container->filesystem, container->directory);

        // procedure: mount binding
        //----------------------------------------------------------------------
        binding_mount(&container->binding, container->directory);

        // procedure: configure network
        //----------------------------------------------------------------------
        network_configure(&container->network, container->pid);

        // procedure: wait for container
        //----------------------------------------------------------------------
        waitpid(container->pid, NULL, 0);

        // procedure: deconfigure network
        //----------------------------------------------------------------------
        network_deconfigure(&container->network, container->pid);

        // procedure: unmount binding
        //----------------------------------------------------------------------
        binding_unmount(&container->binding, container->directory);

        // procedure: unmount filesystem
        //----------------------------------------------------------------------
        filesystem_unmount(&container->filesystem, container->directory);
}
