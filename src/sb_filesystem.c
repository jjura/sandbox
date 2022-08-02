// includes: project
//------------------------------------------------------------------------------
#include "sb_log.h"
#include "sb_directory.h"
#include "sb_filesystem.h"

// includes: c
//------------------------------------------------------------------------------
#include <errno.h>
#include <string.h>

// includes: linux
//------------------------------------------------------------------------------
#include <sys/mount.h>
#include <linux/limits.h>

// function: sb_filesystem_create
//------------------------------------------------------------------------------
sb_void_t sb_filesystem_create(sb_filesystem_t *filesystem)
{
        filesystem->offset      = 0;
        filesystem->offset_max  = 0;
        filesystem->entry       = NULL;
}

// function: sb_filesystem_destroy
//------------------------------------------------------------------------------
sb_void_t sb_filesystem_destroy(sb_filesystem_t *filesystem)
{
        free(filesystem->entry);
}

// function: sb_filesystem_set
//------------------------------------------------------------------------------
sb_void_t sb_filesystem_set(sb_filesystem_t *filesystem, sb_path_t target,
                sb_char_t *type,
                sb_char_t *data)
{
        if (filesystem->offset == filesystem->offset_max)
        {
                filesystem->offset_max = filesystem->offset_max * 2 + 1;
                filesystem->entry = realloc(
                                filesystem->entry,
                                filesystem->offset_max *
                                sizeof(sb_filesystem_entry_t));
        }

        filesystem->entry[filesystem->offset].target = target;
        filesystem->entry[filesystem->offset].type = type;
        filesystem->entry[filesystem->offset].data = data;
        filesystem->offset++;
}

// function: sb_filesystem_mount
//------------------------------------------------------------------------------
sb_void_t sb_filesystem_mount(sb_filesystem_t *filesystem, sb_path_t directory)
{
        sb_char_t path[PATH_MAX];

        for (sb_i32_t i = 0; i < filesystem->offset; ++i)
        {
                sb_filesystem_entry_t *entry = filesystem->entry + i;

                sprintf(path, "%s/%s", directory, entry->target);

                if (!sb_directory_exists(path))
                {
                        sb_directory_create(path);
                }

                if (mount(entry->type, path, entry->type, 0, entry->data))
                {
                        SB_LOG_ERROR("Failed filesystem mount: %s",
                                        strerror(errno));
                }
        }
}

// function: sb_filesystem_unmount
//------------------------------------------------------------------------------
sb_void_t sb_filesystem_unmount(sb_filesystem_t *filesystem, sb_path_t directory)
{
        sb_char_t path[PATH_MAX];

        for (sb_i32_t i = filesystem->offset - 1; i >= 0; --i)
        {
                sprintf(path, "%s/%s", directory, filesystem->entry[i].target);

                if (umount(path))
                {
                        SB_LOG_ERROR("Failed filesystem unmount: %s",
                                        strerror(errno));
                }
        }
}
