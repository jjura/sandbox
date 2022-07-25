// includes: project
//------------------------------------------------------------------------------
#include "log.h"
#include "directory.h"
#include "filesystem.h"

// includes: c
//------------------------------------------------------------------------------
#include <errno.h>
#include <string.h>

// includes: linux
//------------------------------------------------------------------------------
#include <sys/mount.h>
#include <linux/limits.h>

// function: filesystem_create
//------------------------------------------------------------------------------
void_t filesystem_create(filesystem_t *filesystem)
{
        filesystem->offset      = 0;
        filesystem->offset_max  = 0;
        filesystem->entry       = NULL;
}

// function: filesystem_destroy
//------------------------------------------------------------------------------
void_t filesystem_destroy(filesystem_t *filesystem)
{
        free(filesystem->entry);
}

// function: filesystem_set
//------------------------------------------------------------------------------
void_t filesystem_set(filesystem_t *filesystem, path_t target,
                char_t *type,
                char_t *data)
{
        if (filesystem->offset == filesystem->offset_max)
        {
                filesystem->offset_max = filesystem->offset_max * 2 + 1;
                filesystem->entry = realloc(
                                filesystem->entry,
                                filesystem->offset_max *
                                sizeof(filesystem_entry_t));
        }

        filesystem->entry[filesystem->offset].target = target;
        filesystem->entry[filesystem->offset].type = type;
        filesystem->entry[filesystem->offset].data = data;
        filesystem->offset++;
}

// function: filesystem_mount
//------------------------------------------------------------------------------
void_t filesystem_mount(filesystem_t *filesystem, path_t directory)
{
        char_t path[PATH_MAX];

        for (i32_t i = 0; i < filesystem->offset; ++i)
        {
                filesystem_entry_t *entry = filesystem->entry + i;

                sprintf(path, "%s/%s", directory, entry->target);

                if (!directory_exists(path))
                {
                        directory_create(path);
                }

                if (mount(entry->type, path, entry->type, 0, entry->data))
                {
                        LOG_ERROR("Failed filesystem mount: %s",
                                        strerror(errno));
                }
        }
}

// function: filesystem_unmount
//------------------------------------------------------------------------------
void_t filesystem_unmount(filesystem_t *filesystem, path_t directory)
{
        char_t path[PATH_MAX];

        for (i32_t i = filesystem->offset - 1; i >= 0; --i)
        {
                sprintf(path, "%s/%s", directory, filesystem->entry[i].target);

                if (umount(path))
                {
                        LOG_ERROR("Failed filesystem unmount: %s",
                                        strerror(errno));
                }
        }
}
