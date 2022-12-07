#include "sb_directory.h"
#include "sb_file.h"
#include "sb_mountpoint.h"

#include <assert.h>
#include <stdio.h>
#include <string.h>

#include <sys/mount.h>

sb_bool_t sb_mountpoint_mount(sb_mountpoint_t *mountpoint, sb_char_t *directory)
{
    assert(mountpoint);
    assert(directory);

    sb_size_t size =
        strlen(directory) +
        strlen(mountpoint->destination) + 2;

    sb_char_t destination[size];

    sprintf(destination, "%s/%s", directory, mountpoint->destination);

    if (sb_directory_exists(mountpoint->source))
    {
        sb_directory_create(destination, 0755);
    }

    if (sb_file_exists(mountpoint->source))
    {
        sb_file_create(destination, 0644);
    }

    sb_u64_t flags = 0;

    if (mountpoint->type == SB_MOUNTPOINT_TYPE_BINDING)
    {
        flags |= MS_BIND;
    }

    return !(mount(
        mountpoint->source, destination,
        mountpoint->source, flags,
        mountpoint->options));
}

sb_bool_t sb_mountpoint_mount_all(sb_vector_t *mountpoints, sb_char_t *directory)
{
    assert(mountpoints);
    assert(directory);

    for (sb_size_t i = 0; i < sb_vector_size(mountpoints); ++i)
    {
        sb_mountpoint_t *mountpoint = sb_vector_at(mountpoints, i);

        if (!sb_mountpoint_mount(mountpoint, directory))
        {
            return false;
        }
    }

    return true;
}

sb_bool_t sb_mountpoint_umount(sb_mountpoint_t *mountpoint, sb_char_t *directory)
{
    assert(mountpoint);
    assert(directory);

    sb_size_t size =
        strlen(directory) +
        strlen(mountpoint->destination) + 2;

    sb_char_t destination[size];

    sprintf(destination, "%s/%s", directory, mountpoint->destination);

    return !(umount(destination));
}

sb_bool_t sb_mountpoint_umount_all(sb_vector_t *mountpoints, sb_char_t *directory)
{
    assert(mountpoints);
    assert(directory);

    for (sb_size_t i = sb_vector_size(mountpoints) - 1; i >= 0; --i)
    {
        sb_mountpoint_t *mountpoint = sb_vector_at(mountpoints, i);

        if (!sb_mountpoint_umount(mountpoint, directory))
        {
            return false;
        }
    }

    return true;
}
