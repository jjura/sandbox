#include "sb_container.h"
#include "sb_directory.h"
#include "sb_file.h"
#include "sb_logger.h"
#include "sb_mountpoint.h"
#include "sb_process.h"

#include <assert.h>
#include <signal.h>
#include <string.h>

sb_void_t sb_container_create(sb_container_t *container)
{
    assert(container);

    *container = (sb_container_t) {
        .hostname   = "/etc/hostname",
        .command    = "/bin/sh",
        .shell      = "/bin/sh",
        .username   = "root",
    };

    sb_stack_create(&container->stack, 1024 * 1024);
    sb_vector_create(&container->mountpoints, 0, sizeof(sb_mountpoint_t));
}

sb_void_t sb_container_destroy(sb_container_t *container)
{
    assert(container);

    sb_stack_destroy(&container->stack);
    sb_vector_destroy(&container->mountpoints);
}

sb_void_t sb_container_execute(sb_container_t *container)
{
    assert(container);
    assert(container->directory);

    sb_process_create(&container->process, container);

    signal(SIGINT, SIG_IGN);
    signal(SIGQUIT, SIG_IGN);

    sb_process_wait(&container->process);
}

sb_bool_t sb_container_set_command(
        sb_container_t *container,
        sb_char_t *command)
{
    assert(container);
    assert(command);

    container->command = command;

    return true;
}

sb_bool_t sb_container_set_username(
        sb_container_t *container,
        sb_char_t *username)
{
    assert(container);
    assert(username);

    container->username = username;

    return true;
}

sb_bool_t sb_container_set_directory(
        sb_container_t *container,
        sb_char_t *directory)
{
    assert(container);
    assert(directory);

    if (!sb_directory_exists(directory))
    {
        SB_LOGGER_ERROR("Failed setting non-existing directory: %s", directory);

        return false;
    }

    sb_char_t *processes = "/proc";

    if (sb_directory_for_each(processes, directory, sb_directory_used))
    {
        SB_LOGGER_ERROR("Failed settings already used directory: %s", directory);

        return false;
    }

    container->directory = directory;

    return true;
}

sb_bool_t sb_container_set_binding(
        sb_container_t *container,
        sb_char_t *source,
        sb_char_t *destination)
{
    assert(container);
    assert(source);
    assert(destination);

    if (!sb_directory_exists(source) && !sb_file_exists(source))
    {
        SB_LOGGER_ERROR("Failed setting non-existing binding: %s", source);

        return false;
    }

    sb_vector_t *mountpoints = &container->mountpoints;

    for (sb_size_t i = 0; i < sb_vector_size(mountpoints); ++i)
    {
        sb_mountpoint_t *entry = sb_vector_at(mountpoints, i);

        if (!strcmp(destination, entry->destination))
        {
            SB_LOGGER_ERROR("Failed setting duplicated binding: %s", destination);

            return false;
        }
    }

    sb_mountpoint_t mountpoint = {
        .type        = SB_MOUNTPOINT_TYPE_BINDING,
        .source      = source,
        .destination = destination,
    };

    sb_vector_add(mountpoints, &mountpoint);

    return true;
}

sb_bool_t sb_container_set_filesystem(
        sb_container_t *container,
        sb_char_t *source,
        sb_char_t *destination,
        sb_char_t *options)
{
    assert(container);
    assert(source);
    assert(destination);

    sb_vector_t *mountpoints = &container->mountpoints;

    for (sb_size_t i = 0; i < sb_vector_size(mountpoints); ++i)
    {
        sb_mountpoint_t *entry = sb_vector_at(mountpoints, i);

        if (!strcmp(destination, entry->destination))
        {
            SB_LOGGER_ERROR("Failed setting duplicated filesystem: %s", destination);

            return false;
        }
    }

    sb_mountpoint_t mountpoint = {
        .type        = SB_MOUNTPOINT_TYPE_FILESYSTEM,
        .source      = source,
        .destination = destination,
        .options     = options,
    };

    sb_vector_add(mountpoints, &mountpoint);

    return true;
}

sb_bool_t sb_container_set_overlay(
        sb_container_t *container,
        sb_char_t *lower,
        sb_char_t *upper,
        sb_char_t *work)
{
    assert(container);
    assert(lower);
    assert(upper);
    assert(work);

    if (!sb_directory_exists(lower))
    {
        SB_LOGGER_ERROR("Failed setting non-existing lower overlay: %s", lower);

        return false;
    }

    if (!sb_directory_exists(upper))
    {
        SB_LOGGER_ERROR("Failed setting non-existing upper overlay: %s", upper);

        return false;
    }

    if (!sb_directory_exists(work))
    {
        SB_LOGGER_ERROR("Failed setting non-existing work overlay: %s", work);

        return false;
    }

    container->overlay = (sb_overlay_t) {
        .lower = lower,
        .upper = upper,
        .work  = work,
    };

    return true;
}
